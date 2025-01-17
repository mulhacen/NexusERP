<ol>
<h1>NexusERP</h1>
Sencillo ERP sobre IoT utilizando placas Arduino mini y API en PHP

<h2><li>API</li></h2>
Para interaccionar con la api tenemos varias llamadas:

<code>http://DOMINIO-SERVIDOR/nexus-erp/api/device/add/
http://DOMINIO-SERVIDOR/nexus-erp/api/device/update/
http://DOMINIO-SERVIDOR/nexus-erp/api/device/delete/
http://DOMINIO-SERVIDOR/nexus-erp/api/device/show/
http://DOMINIO-SERVIDOR/nexus-erp/api/mesure/add/
</code>

<h3><li>Dispositivos</li></h3>
<ol>
<p>Los dispositivos son arduinos conectados diferentes sensores: </p>

<h3><li>Añadir un dispositivo</li></h3>
<p>Para poder dar de alta un dispositivos utilizaremos <code>http://DOMINIO-SERVIDOR/nexus-erp/api/device/add/</code>
 por <b>POST</b> deberemos de pasar los siguiente parametros que vemos en el ejemplo:</p>
<code>"mac" : "E02B98BAFF75"
  "latitude" : "36.83814"
  "longitude" : "-2.45974"
  "frequency" : "30"
</code>

<h3><li>Actualizar datos dispositivo</li></h3>
<p>Para poder modificar los datos de instalacion de un dispositivos utilizaremos <code>http://DOMINIO-SERVIDOR/nexus-erp/api/device/update/</code>
 por <b>POST</b> deberemos de pasar los siguiente parametros que vemos en el ejemplo:</p>

<code>"mac" : "E02B98BAFF75"
  "latitude" : "39.83814"
  "longitude" : "-3.45974"
  "frequency" : "120"</code>

<p><b>Solo se modificara latitude, longitude y frequency</b>. Mac se utilizara para autentificar el dispositivo sobre el que hacemos los cambios pero no se podra actualizar la mac.</p>

<h3><li>Borrar dispositivo</li></h3>
<p>Para poder borar un dispositivos utilizaremos <code>http://DOMINIO-SERVIDOR/nexus-erp/api/device/delete/</code>
 por <b>POST</b> deberemos de pasar los siguiente parametros que vemos en el ejemplo:</p>

por post deberemos de pasar los siguiente parametros que vemos en el ejemplo:
<code>
  "mac" : "E02B98BAFF75"</code>

  <h3><li>Mostrar datos Dispositivo</li></h3>
<p>Para poder leer los datos de instalacion de un dispositivo utilizaremos <code>http://DOMINIO-SERVIDOR/nexus-erp/api/device/show/</code>
 por <b>POST</b> deberemos de pasar los siguiente parametros que vemos en el ejemplo:</p>

por post deberemos de pasar los siguiente parametros que vemos en el ejemplo:
<code>
  "mac" : "E02B98BAFF75"</code>

</ol>

<h3><li>Sensores</li></h3>
<ol>
    <h3><li>Añadir lectura</li></h3>
    <p>Para poder añadir la lectura de sensores de un dispositivo utilizaremos la llamada <code>http://DOMINIO-SERVIDOR/nexus-erp/api/mesure/add/</code>
 por <b>POST</b> deberemos de pasar los siguiente parametros que vemos en el ejemplo:
    <code>
  "mac" : "E02B98BAFF75"
  "idSensor": 1
  "idSensorType": 1
  "value" : 24.5</code>
    </p>

    <h3><li>Borrar lectura</li></h3>
    <h3><li>Consultar lectura</li></h3>
</ol>

<h2><li>Recursos y bibliografia:</li></h2>
<ul>
<li>Informacion CURL: https://blog.marcnuri.com/curl-post-request-ejemplos</li>
<li>Tipos de peticiones http en API https://dev.to/qbentil/http-methods-get-post-put-patch-delete-1fhi</li>
<li>WeMos D1 R2 wifi configuration https://nerd-corner.com/wemos-d1-r2-setup-and-wifi-integration/</li>
<li>POST&Get http requests ESP8266 https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/</li>
<li>Self upgrade firmware from http server https://www.mischianti.org/2021/12/15/esp8266-self-ota-update-firmware-from-server-with-version-check-2/</li>
<li>Generate bin binary files Sketch https://randomnerdtutorials.com/bin-binary-files-sketch-arduino-ide/</li>
<li>Manage Energy Saving Wemos D1 ESP8266 https://www.mischianti.org/2019/11/21/wemos-d1-mini-esp8266-the-three-type-of-sleep-mode-to-manage-energy-savings-part-4/</li>
<li>DeepSleep bypass cable https://randomnerdtutorials.com/esp8266-deep-sleep-with-arduino-ide/</li>
<li>Tzapu - Wifi manager https://github.com/tzapu/WiFiManager</li>
</ul>

<h2><li>Diseño PCB:</li></h2>
<ul>
 <li>Diseño de circuitos https://fritzing.org/</li>
 <li>Produccion PCB https://www.elecrow.com/</li>
 </ul>
</ol>
