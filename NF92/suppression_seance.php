<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Supprimer une séance
</title>

</head>

<center>
<h1>
Supprimer une séance
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

date_default_timezone_set('Europe/Paris');
$datedujour = date("Ymd");
$result = mysqli_query($connect,"SELECT * FROM Seances where date>'$datedujour'");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (!empty($row) )
	{
	$result = mysqli_query($connect,"SELECT *FROM Seances where date>'$datedujour'");

	echo "<FORM METHOD='POST' ACTION='supprimer_seance.php'>";
	echo"<center><table>";

		echo"<tr>";
			echo"<th> Séance : </th>";
			echo"<td> <select name='id_seance' size='1'>";
			echo "<option value=''>";
			echo "</option>";

				while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
				{
				$test = mysqli_query ($connect,"SELECT * FROM themes WHERE id_theme = '$row[3]'");
				$row1 = mysqli_fetch_array($test, MYSQL_NUM);

				echo "<option value='$row[0]'>";
				echo "Thème : $row1[1] | Date : $row[1] à $row[2] h ";
				echo "</option>";
				}
			echo "</select></td>";
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
			<INPUT VALUE="Supprimer" TYPE="SUBMIT" class="bouton">
			</center></td>

			<td><center>
			<INPUT VALUE="Annuler" TYPE="RESET" class="bouton">
			</center></td>
		</tr>

	</table></center>
	</form>
	
	<?php		
	}

	else
	{
	echo "<center> Il n'y a aucune séance de prévue </center>";
	}

mysqli_close($connect);

?>

</body>

</html>
