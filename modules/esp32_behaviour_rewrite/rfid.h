/*
  1 byte header (value = 2)
  2 byte version
  8 byte tag data
  2 byte checksum
  1 byte tail (value = 3)
*/

#define RFID Serial2 // TX = GPIO17, RX = GPIO16

const int BUFFER_SIZE = 14; // 1 + 2 + 8 + 2 + 1
byte buffer[BUFFER_SIZE];
int buffer_idx = 0;

class Tag {
  private:
    byte header, tail;
    byte *data_ptr, *checksum_ptr;

    long hexstr_to_long(byte* ptr, unsigned int length) {
      byte* copy = (byte*)malloc((sizeof(byte) * length) + 1);
      memcpy(copy, ptr, sizeof(byte) * length);
      copy[length] = NULL;
      long value = strtol((char*)copy, NULL, 16);
      free(copy);
      return value;
    }
  public:
    Tag(byte* buf) {
      header = buf[0];
      data_ptr = buf + 1;
      checksum_ptr = data_ptr + 10;
      tail = buf[13];
    }
    Tag() {}
    bool verifyChecksum() {
      long x = 0;
      for (int i = 0; i < 10; i += 2) x ^= hexstr_to_long(data_ptr + i, 2);
      long y = hexstr_to_long(checksum_ptr, 2);
      return x == y;
    }
    void print() {
      ESP_LOGI(
        "RFID",
        "Header: 0x%X, Version: 0x%X, Data: 0x%X, Tail: 0x%X",
        header,
        version(),
        data(),
        tail
      );
    }
    long data() {
      return hexstr_to_long(data_ptr + 2, 8);
    }
    long version() {
      return hexstr_to_long(data_ptr, 2);
    }
} last_tag;

void RFIDInit() {
  RFID.begin(9600);
}

bool TryReceiveTag() {
  if (RFID.available() > 0) {
    byte b = RFID.read();
    bool extract_tag = false;
    switch (b) {
      // tag incoming (found header)
      case 2:
        buffer_idx = 0;
        break;
      // tag fully transmitted (found tail)
      case 3:
        extract_tag = true;
        break;
      default:
        if (b < '0' || (b > '9' && b < 'A') || b > 'F') {
          return false;
        }
        break;
    }
    if (buffer_idx >= BUFFER_SIZE) {
      ESP_LOGW("RFID", "Buffer overflow");
      return false;
    }
    buffer[buffer_idx++] = b;
    if (!extract_tag) {
      return false;
    }
    if (buffer_idx != BUFFER_SIZE) {
      buffer_idx = 0;
      return false;
    }
    Tag tmp = Tag(buffer);
    if (!tmp.verifyChecksum()) {
      ESP_LOGW("RFID", "Corrupted tag (checksum mismatch)");
      return false;
    }
    last_tag = tmp;
    return true;
  }
}

Tag LastTag() {
  return last_tag;
}