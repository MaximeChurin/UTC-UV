<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Visualiser le calendrier  d'un élève
</title>

</head>

<center>
<h1>
Visualiser le calendrier d'un élève
</h1>
</center>
<br>
<br>

<body>

<?php

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$result = mysqli_query($connect,"SELECT * FROM eleves");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (!empty($row) )
	{
	$result = mysqli_query($connect,"SELECT * FROM eleves");

	echo "<FORM METHOD='POST' ACTION='visualiser_calendrier_eleve.php'>";

	echo"<center><table>";

		echo"<tr>";
			echo"<th>  Elève : </th>";
			echo"<td> <select name='id_eleves' size='1'>";
			echo "<option value=''>";
			echo "</option>";

				while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
				{
				echo "<option value='$row[0]'>";
				echo " $row[1] $row[2]";
				echo "</option>";
				}

			echo "</select>"; 
			echo"</td>";
		echo"</tr>";
		?>	

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>

		<tr>
			<td>
			&nbsp
			</td>

			<td>
			&nbsp
			</td>
		</tr>		
	
		<tr>
			<td><center>
			<INPUT VALUE="Visualiser" TYPE="SUBMIT" class="bouton">
			</center></td>

			<td><center>
			<INPUT VALUE="Annuler" TYPE="RESET" class="bouton">
			</center></td>
		</tr>

	</table></center>
	</FORM>

	<?php
	}

	else
	{
	echo "<center>La table élèves est vide </center>";
	}

mysqli_close($connect);

?>

</body>

</html>
