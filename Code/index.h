const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>

<html>
<head> 
<!-- ======================== Načtení vzhledu tlačítek z tutorial webu ======================== -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet"href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
<!-- ======================== Nastavení tabulky ======================== -->    
    <style>
      tab-table, th, td {border: 1px solid black; border-collapse:collapse; text-align: center;}
    </style>
    
  </head>
<!-- ======================== Tlačítka ======================== -->
  <div align="center">
  
	  <button type="button" onclick="return show('Page1','Page2');" style="margin:2%;
      height:45px; width:45%; margin-top:25px;">&laquo; Tabulka hodnot </button>
      
      <button type="button" onclick="return show('Page2','Page1');" style="margin:2%;
      height:45px; width:45%; margin-top:25px;"> Manuální ovládání&raquo;</button>
  </div>
  <div id="demo" align="center">
      <button type="button" onclick="sendData(0)"style="margin:1%;
      height:45px; width:45%; margin-top:20px;">Start</button>
      <button type="button" onclick="sendData(1)" style="margin:1%;
      height:45px; width:45%; margin-top:20px;">Zastavit</button>
  </div>
<!-- ======================== Rozdělení stran ======================== -->
  <script>
    function show(shown, hidden) {
      document.getElementById(shown).style.display='block';
      document.getElementById(hidden).style.display='none';
      return false;
    }
  </script>
  <body>
    <div id="Page1">
      <!-- ======================== Tabulka ======================== -->
        <table style="margin-top:20px; width:92.8%; margin-left:3.6%; ">
          <tr>
            <th style="height:45px; width:30%">Cislo stredu</th>
            <th style="height:45px; width:25%">X souradnice [mm]</th>
            <th style="height:45px; width:25%">Y souradnice [mm]</th>
          </tr>
          
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 0</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X0">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y0">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 1</td>
            <td style="height:45px; width:25%"><span id="X1">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y1">N/A</span></td>
          </tr>
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 2</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X2">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y2">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 3</td>
            <td style="height:45px; width:25%"><span id="X3">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y3">N/A</span></td>
          </tr>
                
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 4</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X4">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y4">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 5</td>
            <td style="height:45px; width:25%"><span id="X5">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y5">N/A</span></td>
          </tr>
                
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 6</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X6">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y6">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 7</td>
            <td style="height:45px; width:25%"><span id="X7">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y7">N/A</span></td>
          </tr>
                
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 8</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X8">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y8">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 9</td>
            <td style="height:45px; width:25%"><span id="X9">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y9">N/A</span></td>
          </tr>
                
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 10</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X10">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y10">N/A</span></td>
          </tr>
          
          <tr>
            <td style="height:45px; width:30%">Stred 11</td>
            <td style="height:45px; width:25%"><span id="X11">N/A</span></td>
            <td style="height:45px; width:25%"><span id="Y11">N/A</span></td>
          </tr>
                
          <tr>
            <td bgcolor="#D3D3D3" style="height:45px; width:30%">Stred 12</td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="X12">N/A</span></td>
            <td bgcolor="#D3D3D3" style="height:45px; width:25%"><span id="Y12">N/A</span></td>
          </tr>
          
        </table>
      <!-- ======================== Tlačítko download ======================== -->
        <div id="buttonD" align="center">
            <button style="margin:2%; height:35px; width:90%; margin-top:25px;" onclick="exportTableToCSV('data.csv')">Exportovat tabulku do CSV</button>
        </div>
        </body>
      
      <!-- ======================== Část s kódem ======================== -->
          <script>
          <!-- ===== Funkce Stahování tabulky ===== -->   
            function downloadCSV(csv, filename) {
              var csvFile;
              var downloadLink;
              // CSV file
              csvFile = new Blob([csv], {type: "text/csv"});
              // Download link
              downloadLink = document.createElement("a");
              // File name
              downloadLink.download = filename;
              // Create a link to the file
              downloadLink.href = window.URL.createObjectURL(csvFile);
              // Hide download link
              downloadLink.style.display = "none";
              // Add the link to DOM
              document.body.appendChild(downloadLink);
              // Click download link
              downloadLink.click();
            }
            function exportTableToCSV(filename) {
              var csv = [];
              var rows = document.querySelectorAll("table tr");
              for (var i = 0; i < rows.length; i++) {
                  var row = [], cols = rows[i].querySelectorAll("td, th");
                  for (var j = 0; j < cols.length; j++) 
                      row.push(cols[j].innerText);
                  csv.push(row.join(","));        
              }
              // Download CSV file
              downloadCSV(csv.join("\n"), filename);
            }
          <!-- ===== Funkce tlačítek ===== -->
            function sendData(led){
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
   
    </div>
    <div id="Page2" style="display:none">
      <style>
        div.a {
          text-align: center;
          style="margin:1%; 
          height:15px; 
          width:90%; 
          margin-top:30px;"
        }
        input[type=number], select {
          width: 25%;
          padding: 8px 20px;
          margin: 8px auto;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
        }
        input[type=submit] {
          width: 25%;
          color: black;
          padding: 8px 20px;
          margin: 8px auto;
          border: none;
          border-radius: 2px;
          cursor: pointer;
        }
      </style>
      <div style="margin-top:30px;" align="center">
        <label>  Zadejte číslo požadovaného středu</label>
      </div>
      <div align="center">
        <form method="post" action="/form">  
          <input type="number" name="position" min="0" max="17">
          <input type="submit" value="Submit">
        </form>
      </div>
      <div style="margin-top:30px;" align="center">
        <label >Manuální ovládání</label>
      </div>
      <div id="demo"  align="center">
        <button type="button" onclick="sendData(2)" style="margin:0.5%;height:75px; width:25%;" >Y+</button><br>
        <button type="button" onclick="sendData(3)" style="margin:0.5%;height:75px; width:25%;" >X-</button>
        <button type="button" onclick="sendData(4)" style="margin:0.5%;height:75px; width:25%;" >Stát</button>
        <button type="button" onclick="sendData(5)" style="margin:0.5%;height:75px; width:25%;" >X+</button><br>
        <button type="button" onclick="sendData(6)" style="margin:0.5%;height:75px; width:25%;" >Y-</button>
      </div>
      
    </div>
  </body>
</html>


)=====";
