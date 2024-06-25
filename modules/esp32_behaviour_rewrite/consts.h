const char* TAG = "ESP-32 Module";
const char* SSID = "Domotica Lapenna";
const char* PASSWORD = "domotica";
const long OPEN_TAG = 0x3D8279;
const long CLOSE_TAG = 0x3D7235;

const char* STYLE = R"(:root {
    --foreground: #2C3E50;
    --primary: #E74C3C;
    --secondary: #3498DB;
    --background: #ECF0F1;

    --open: #22DD22;
    --closed: #DD2222;
}

* {
    font-family: sans-serif;
    color: var(--foreground);
}

body {
    margin: 0px;
    background-color: var(--background);
}

b {
    text-align: center;
}

.content {
    display: flex;
    justify-content: space-evenly;
}

.row {
    display: flex;
    align-items: center;
    justify-content: space-between;
}
.row>* {
    margin: 10px;
}
.centered.row {
    justify-content: center;
}

.open {
    color: var(--open);
}
.closed {
    color: var(--closed);
}
.open, .closed {
    background-color: var(--foreground);
    padding: 10px;
    border-radius: 10px;
}

#title {
    text-align: center;
}

#loading {
    opacity: 1;
}

#page {
    opacity: 0;
})";

const char* GRID = R"(#loading {
    --uib-size: 60px;
    --uib-color: #E74C3CAA;
    --uib-speed: 1.5s;
    --uib-dot-size: calc(var(--uib-size) * 1);
    position: absolute;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
    display: flex;
    align-items: center;
    justify-content: flex-start;
    height: calc(var(--uib-size) * 0.64 * 10);
    width: calc(var(--uib-size) * 0.64 * 10);
}

@keyframes jump {
    0%,
    100% {
      transform: translateY(120%);
    }

    50% {
      transform: translateY(-120%);
    }
}

.dot {
    --uib-d1: -0.48;
    --uib-d2: -0.4;
    --uib-d3: -0.32;
    --uib-d4: -0.24;
    --uib-d5: -0.16;
    --uib-d6: -0.08;
    --uib-d7: -0;
    position: absolute;
    bottom: calc(var(--uib-bottom) + var(--uib-dot-size) / 2);
    right: calc(var(--uib-right) + var(--uib-dot-size) / 2);
    display: flex;
    align-items: center;
    justify-content: flex-start;
    height: var(--uib-dot-size);
    width: var(--uib-dot-size);
    animation: jump var(--uib-speed) ease-in-out infinite;
    opacity: var(--uib-scale);
    will-change: transform;
    backface-visibility: hidden;
}

.dot::before {
    content: '';
    height: 100%;
    width: 100%;
    background-color: var(--uib-color);
    border-radius: 50%;
    transform: scale(var(--uib-scale));
    transition: background-color 0.3s ease;
}

.dot:nth-child(1) {
    --uib-bottom: 24%;
    --uib-right: -35%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d1));
}
.dot:nth-child(2) {
    --uib-bottom: 16%;
    --uib-right: -6%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d2));
}
.dot:nth-child(3) {
    --uib-bottom: 8%;
    --uib-right: 23%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d3));
}
.dot:nth-child(4) {
    --uib-bottom: -1%;
    --uib-right: 51%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d4));
}
.dot:nth-child(5) {
    --uib-bottom: 38%;
    --uib-right: -17.5%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d2));
}
.dot:nth-child(6) {
    --uib-bottom: 30%;
    --uib-right: 10%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d3));
}
.dot:nth-child(7) {
    --uib-bottom: 22%;
    --uib-right: 39%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d4));
}
.dot:nth-child(8) {
    --uib-bottom: 14%;
    --uib-right: 67%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d5));
}.dot:nth-child(9) {
    --uib-bottom: 53%;
    --uib-right: -0.8%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d3));
}
.dot:nth-child(10) {
    --uib-bottom: 44.5%;
    --uib-right: 27%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d4));
}
.dot:nth-child(11) {
    --uib-bottom: 36%;
    --uib-right: 55.7%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d5));
}
.dot:nth-child(12) {
    --uib-bottom: 28.7%;
    --uib-right: 84.3%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d6));
}
.dot:nth-child(13) {
    --uib-bottom: 66.8%;
    --uib-right: 15%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d4));
}
.dot:nth-child(14) {
    --uib-bottom: 58.8%;
    --uib-right: 43%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d5));
}
.dot:nth-child(15) {
    --uib-bottom: 50%;
    --uib-right: 72%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d6));
}
.dot:nth-child(16) {
    --uib-bottom: 42%;
    --uib-right: 100%;
    animation-delay: calc(var(--uib-speed) * var(--uib-d7));
}

.dot:nth-child(3) {
    --uib-scale: 0.98;
}
.dot:nth-child(2), .dot:nth-child(8) {
    --uib-scale: 0.96;
}
.dot:nth-child(1), .dot:nth-child(7) {
    --uib-scale: 0.94;
}
.dot:nth-child(6), .dot:nth-child(12) {
    --uib-scale: 0.92;
}
.dot:nth-child(5), .dot:nth-child(11) {
    --uib-scale: 0.9;
}
.dot:nth-child(10), .dot:nth-child(16) {
    --uib-scale: 0.88;
}
.dot:nth-child(9), .dot:nth-child(15) {
    --uib-scale: 0.86;
}
.dot:nth-child(14) {
    --uib-scale: 0.84;
}
.dot:nth-child(13) {
    --uib-scale: 0.82;
}
)";

const char* SWITCH = R"(:root {
    --color: #3498DB;
}

.switch {
    font-size: 17px;
    position: relative;
    display: inline-block;
    width: 3.5em;
    height: 2em;
}

.switch input {
    opacity: 0;
    width: 0;
    height: 0;
}

.slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: rgb(182, 182, 182);
    transition: .4s;
    border-radius: 10px;
}
  
.slider:before {
    position: absolute;
    content: "";
    height: 1.4em;
    width: 1.4em;
    border-radius: 8px;
    left: 0.3em;
    bottom: 0.3em;
    transform: rotate(270deg);
    background-color: rgb(255, 255, 255);
    transition: .4s;
}
  
.switch input:checked + .slider {
    background-color: var(--color);
}
  
.switch input:focus + .slider {
    box-shadow: 0 0 1px #2196F3;
}
  
.switch input:checked + .slider:before {
    transform: translateX(1.5em);
})";

const char* INDEX = R"(<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="./style.css">
        <link rel="stylesheet" href="./grid.css">
        <link rel="stylesheet" href="./switch.css">
        <title>Pannello di controllo</title>
    </head>
    <body>
        <div id="loading">
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
            <div class="dot"></div>
        </div>

        <div id="page">
            <h1 id="title">Pannello di controllo</h1>
            <div class="content">
                <div class="left">
                    <div id="lights">
                        <h3>💡 Luci 💡</h3>
                    </div>
                </div>
                
                <div class="right">
                    <div id="garage">
                        <h3>🚗 Garage 🚗</h3>
                        <div class="row">
                            <p>Serranda</p>
                            <label class="switch">
                                <input type="checkbox" name="garage" id="garage-input">
                                <span class="slider"></span>
                            </label>
                        </div>
                    </div>

                    <div id="fan">
                        <h3>🍃 Ventilatore 🍃</h3>
                        <div class="row">
                            <p>Ventilazione</p>
                            <label class="switch">
                                <input type="checkbox" name="fan" id="fan-input">
                                <span class="slider"></span>
                            </label>
                        </div>
                    </div>

                    <div id="pump">
                        <h3>⛲ Irrigazione ⛲</h3>
                        <div class="row">
                            <p>Pompa</p>
                            <label class="switch">
                                <input type="checkbox" name="pump" id="pump-input">
                                <span class="slider"></span>
                            </label>
                        </div>
                    </div>

                    <div id="door">
                        <h3>🔐 Lucchetto 🔐</h3>
                        <div class="centered row">
                            <b id="door-status" class="open">Aperto</b>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <script src="./index.js"></script>
    </body>
</html>)";

const char* SCRIPT = R"(const PAGE = document.getElementById("page");
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
}, 500);)";