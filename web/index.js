const PAGE = document.getElementById("page");
const LOADING = document.getElementById("loading");

PAGE.style.opacity = 0;
LOADING.style.opacity = 1;

const NAMES = ["Ingresso", "Salotto", "Cucina", "Corridoio", "Camera da letto", "Garage", "Bagno", "Cameretta"];
const LIGHTS_DIV = document.getElementById("lights");
for (let i = 0; i < 8; i++) {
    let entry = `<div class="row">
        <p>${NAMES[i]}</p>
        <label class="switch">
            <input type="checkbox" name="${i}" id="lights-${i}-input">
            <span class="slider"></span>
        </label>
    </div>`;
    LIGHTS_DIV.innerHTML += entry;
}

function receiveStatus() {
    if (this.readyState == 4 && this.status == 200) {
        let obj = JSON.parse(this.responseText);
        console.log(obj);
        for (let i = 0; i < 8; i++) {
            if (obj.lights[i]) {
                document.getElementById(`lights-${i}-input`).setAttribute("checked", "true");
            }
        }
        if (obj.garage) {
            document.getElementById("garage-input").setAttribute("checked", "true");
        }
        if (obj.fan) {
            document.getElementById("fan-input").setAttribute("checked", "true");
        }
        if (obj.pump) {
            document.getElementById("pump-input").setAttribute("checked", "true");
        }
        let door = document.getElementById("door-status");
        door.className = obj.door ? "open" : "closed";
        door.innerText = obj.door ? "Aperto" : "Chiuso";
    }
}

let request = new XMLHttpRequest();
request.open("GET", "status.json", true);
request.onreadystatechange = receiveStatus;
request.send();

document.querySelectorAll(`input[type="checkbox"]`).forEach((element) => {
    element.addEventListener("change", (event) => {
        console.log(`status.json?${event.target.name}=${event.target.checked}`);

        let request = new XMLHttpRequest();
        request.open("GET", `status.json?${event.target.name}=${event.target.checked}`, true);
        request.onreadystatechange = receiveStatus;
        request.send();
    });
});

setInterval(() => {
    let request = new XMLHttpRequest();
    request.open("GET", "status.json", true);
    request.onreadystatechange = receiveStatus;
    request.send();
}, 2000);

setTimeout(() => {
    PAGE.style.opacity = 1;
    LOADING.style.opacity = 0;
}, 500);
