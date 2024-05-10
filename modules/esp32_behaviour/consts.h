const char* TAG = "MainModule";
const char* SSID = "TP-LINK_F79280";
const char* PASSWORD = "06182533";

const char* ROOT_PAGE = R"(<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="./style.css">
        <title>Pannello di controllo</title>
    </head>
    <body>
        <a href="./">home</a>
        <h1 id="title">Pannello di controllo</h1>
        <a href="./lights">💡<b>Luci</b></a>
        <br>
        <a href="./garage">🚗<b>Garage</b></a>
        <br>
        <a href="./water">💧<b>Acqua</b></a>
    </body>
</html>)";

const char* LIGHTS_PAGE = R"(<!DOCTYPE html>
<html dir="ltr" lang="it">
    <head>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="./style.css">
        <title>Gestione luci</title>
    </head>
    <body>
        <a href="./">home</a>
        <h1 id="title">Gestione luci</h1>
        <form action="./lights" method="get">
            <button type="submit" name="target" value="1">Ingresso</button>
            <button type="submit" name="target" value="2">Salotto</button>
            <button type="submit" name="target" value="4">Cucina</button>
            <button type="submit" name="target" value="8">Corridoio</button>
            <button type="submit" name="target" value="16">Camera da letto</button>
            <button type="submit" name="target" value="32">Garage</button>
            <button type="submit" name="target" value="64">Bagno</button>
            <button type="submit" name="target" value="128">Cameretta</button>
        </form>
    </body>
</html>)";

const char* STYLE = R"(* {
    font-family: sans-serif;
}

h1#title {
    text-align: center;
})";