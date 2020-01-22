const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<head> 
<!-- ======================== Načtení vzhledu tlačítek z tutorial webu ======================== -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet"href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
<!-- ======================== Nastavení tabulky ======================== -->   
    <style>
      tab-table, th, td {border: 1px solid black; border-collapse:collapse; text-align: center;}
    </style>
    
  </head>

<!-- ======================== Tlačítka ======================== -->
  <div id="demo" align="center">
      <button type="button" onclick="sendData(0)" class="btn btn-success" style="margin:2%;
      height:45px; width:40%; margin-top:40px;">Start</button>
      <button type="button" onclick="sendData(1)" class="btn btn-primary"style="margin:2%;
      height:45px; width:40%; margin-top:40px;">Pause</button>
      <!-- <button type="button" onclick="sendData(2)" class="btn btn-danger"style="margin:2%;
      height:45px; width:28%; margin-top:40px;">Reset</button>-->
      
  </div>

<!-- ======================== Tabulka ======================== -->
  <body>
    <table style="margin-top:20px; width:92.8%; margin-left:3.6%; ">
    
      <tr>
        <th style="height:45px; width:30%">Name</th>
        <th style="height:45px; width:25%">X location</th>
        <th style="height:45px; width:25%">Y location</th>
      </tr>
      
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 1</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X0">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y0">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 2</td>
        <td style="height:45px; width:25%"><span id="X1">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y1">N/A</span></td>
      </tr>

      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 3</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X2">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y2">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 4</td>
        <td style="height:45px; width:25%"><span id="X3">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y3">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 5</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X4">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y4">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 6</td>
        <td style="height:45px; width:25%"><span id="X5">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y5">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 7</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X6">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y6">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 8</td>
        <td style="height:45px; width:25%"><span id="X7">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y7">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 9</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X8">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y8">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 10</td>
        <td style="height:45px; width:25%"><span id="X9">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y9">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 11</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X10">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y10">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 12</td>
        <td style="height:45px; width:25%"><span id="X11">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y11">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 13</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X12">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y12">N/A</span></td>
      </tr>
      
      <tr>
        <td style="height:45px; width:30%">Location 14</td>
        <td style="height:45px; width:25%"><span id="X13">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y13">N/A</span></td>
      </tr>
            
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 15</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X14">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y14">N/A</span></td>
      </tr>
            
      <tr>
        <td style="height:45px; width:30%">Location 16</td>
        <td style="height:45px; width:25%"><span id="X15">N/A</span></td>
        <td style="height:45px; width:25%"><span id="Y15">N/A</span></td>
      </tr>
      
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 17</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X16">N/A</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y16">N/A</span></td>
      </tr>

    </table>
  </body>
<!-- ======================== Část s kódem ======================== -->
  <script>
  <!-- ===== Funkce tlačítek ===== -->
    function sendData(led) 
    {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() 
      {
        if (this.readyState == 4 && this.status == 200) 
        {
          document.getElementById("LEDState").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "setLED?LEDstate="+led, true);
      xhttp.send();
    }  
    
  <!-- ===== Funkce načítání hodnot do tabulky ===== -->
    setInterval(function(){ getData();},2000); 
    function getData() {
      var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("X0").innerHTML = this.responseText.split(",")[0];
            document.getElementById("Y0").innerHTML = this.responseText.split(",")[1];
            document.getElementById("X1").innerHTML = this.responseText.split(",")[2];
            document.getElementById("Y1").innerHTML = this.responseText.split(",")[3];
            document.getElementById("X2").innerHTML = this.responseText.split(",")[4];
            document.getElementById("Y2").innerHTML = this.responseText.split(",")[5];
            document.getElementById("X3").innerHTML = this.responseText.split(",")[6];
            document.getElementById("Y3").innerHTML = this.responseText.split(",")[7];
            document.getElementById("X4").innerHTML = this.responseText.split(",")[8];
            document.getElementById("Y4").innerHTML = this.responseText.split(",")[9];
            document.getElementById("X5").innerHTML = this.responseText.split(",")[10];
            document.getElementById("Y5").innerHTML = this.responseText.split(",")[11];
            document.getElementById("X6").innerHTML = this.responseText.split(",")[12];
            document.getElementById("Y6").innerHTML = this.responseText.split(",")[13];
            document.getElementById("X7").innerHTML = this.responseText.split(",")[14];
            document.getElementById("Y7").innerHTML = this.responseText.split(",")[15];
            document.getElementById("X8").innerHTML = this.responseText.split(",")[16];
            document.getElementById("Y8").innerHTML = this.responseText.split(",")[17];
            document.getElementById("X9").innerHTML = this.responseText.split(",")[18];
            document.getElementById("Y9").innerHTML = this.responseText.split(",")[19];
            document.getElementById("X10").innerHTML = this.responseText.split(",")[20];
            document.getElementById("Y10").innerHTML = this.responseText.split(",")[21];
            document.getElementById("X11").innerHTML = this.responseText.split(",")[22];
            document.getElementById("Y11").innerHTML = this.responseText.split(",")[23];
            document.getElementById("X12").innerHTML = this.responseText.split(",")[24];
            document.getElementById("Y12").innerHTML = this.responseText.split(",")[25];
            document.getElementById("X13").innerHTML = this.responseText.split(",")[26];
            document.getElementById("Y13").innerHTML = this.responseText.split(",")[27];
            document.getElementById("X14").innerHTML = this.responseText.split(",")[28];
            document.getElementById("Y14").innerHTML = this.responseText.split(",")[29];
            document.getElementById("X15").innerHTML = this.responseText.split(",")[30];
            document.getElementById("Y15").innerHTML = this.responseText.split(",")[31];
            document.getElementById("X16").innerHTML = this.responseText.split(",")[32];
            document.getElementById("Y16").innerHTML = this.responseText.split(",")[33];
          }
        };
      xhttp.open("GET", "readValues", true);
      xhttp.send();
    }
  </script>
</body>
</html>
)=====";
