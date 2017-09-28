<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Calendrier de l'élève
</title>

</head>

<center>
<h1>
Résultat
</h1>
</center>

<body>

<?php

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

	if (!empty($_POST['id_eleves']))
	{
	date_default_timezone_set('Europe/Paris');
	$datedujour = date("Ymd");
	$id_eleve=$_POST['id_eleves'];

	$result = mysqli_query($connect,"SELECT Seances.id_seance, Seances.date FROM Seances, Inscription where Seances.id_seance=Inscription.id_seance and Inscription.id_eleve='$id_eleve' and date>'$datedujour' ");
	$row = mysqli_fetch_array($result, MYSQL_NUM);

		if( !empty($row))
		{

		$result1 = mysqli_query($connect,"SELECT * FROM eleves where id_eleve='$id_eleve'");
		$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

		echo"<br><center> Calendrier de $row1[1] $row1[2] : </center>";

		$result = mysqli_query($connect,"SELECT * FROM Inscription where id_eleve=$id_eleve");

		echo "<br><br><center><table class='tableau'>";

			echo "<tr>";
				echo "<th> Date";
				echo "</th>";
				echo "<th> Heure";
				echo "</th>";
				echo "<th> Thème";
				echo "</th>";
			echo "</tr>";

			while ($row = mysqli_fetch_array($result, MYSQL_NUM))
			{
			$result1 = mysqli_query($connect,"SELECT * FROM Seances WHERE id_seance=$row[0] and date>$datedujour");
			$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

				if( !empty($row1))
				{
				$result2 = mysqli_query($connect,"SELECT * FROM themes WHERE id_theme=$row1[3]");
				$row2 = mysqli_fetch_array($result2, MYSQL_NUM);

				echo "<tr>";
					echo "<td> $row1[1]";
					echo "</td>";
					echo "<td> $row1[2]";
					echo "</td>";
					echo "<td>$row2[1]";
					echo "</td>";
				echo "</tr>";
				}

			}

		echo"</table></center>";
		}

		else
		{
		echo "<center><br>Aucune séance de prévue</center>";
		}
	}

	else
	{
	echo "<br><center> Vous n'avez pas choisi d'élève<br><br>";
	echo "<form method = 'post' action='visualisation_calendrier_eleve.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";	
	}


mysqli_close($connect);

?>

</body>

</html>
