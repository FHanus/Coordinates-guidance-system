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
    height:45px; width:28%; margin-top:40px;">Start</button>

    <button type="button" onclick="sendData(1)" class="btn btn-primary"style="margin:2%;
    height:45px; width:28%; margin-top:40px;">Pause</button>

    <button type="button" onclick="sendData(2)" class="btn btn-danger"style="margin:2%;
    height:45px; width:28%; margin-top:40px;">Reset</button>
    
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

        <!-- ===== Zde je zatím jediný place holder pro hodnotu (Později doplním pro každou souřadnici) ===== -->

        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 1</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X1Value">0</span></td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y1">Y</span></td>
      </tr>
      
      <tr>
        <td style="height:40px; width:30%">Location 2</td>
        <td style="height:45px; width:25%">X</td>
        <td style="height:45px; width:25%">Y</td>
      </tr>
      
      <tr>
        <td bgcolor="#D3D3D3" style="height:45px; width:30%">Location 3</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%">X</td>
        <td bgcolor="#D3D3D3" style="height:45px; width:25%">Y</td>
      </tr>
      
    </table>
  </body>

 <!-- ======================== Část s kódem ======================== -->

<script>

  <!-- ===== Zde funkce tlačítek ===== -->

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
 
setInterval(function(){ getData();},2000); 

function getData() 

  <!-- ===== Zde funkce načítání hodnot do tabulky ===== -->

  {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
      if (this.readyState == 4 && this.status == 200) 
      {
        document.getElementById("X1Value").innerHTML =
        this.responseText;
      }
    };
    xhttp.open("GET", "readValues", true);
    xhttp.send();
  }
  
</script>
</body>
</html>
)=====";

