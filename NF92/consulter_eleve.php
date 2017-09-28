<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Consulter les informations d'un élève
</title>

</head>

<center>
<h1>
Résultat
</h1>
</center>
<br>

<body>

<?php

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$id_eleve=$_POST['id_eleves'];
date_default_timezone_set('Europe/Paris');
$datedujour = date("Ymd");

	if(!empty($id_eleve) )
	{
	$test=0;
	$result = mysqli_query($connect,"SELECT * FROM eleves WHERE id_eleve=$id_eleve");
	$row = mysqli_fetch_array($result, MYSQL_NUM);

	echo "<center><table class='resultat'>";
		echo "<tr>";
			echo "<th> Elève :";
			echo "</th>";
			echo "<td> $row[1] $row[2]";
			echo "</td>";
		echo "</tr>";

		?>	
			<tr>
				<td>
				&nbsp
				</td>

				<td>
				&nbsp
				</td>
			</tr>
		<?php

		echo "<tr>";
			echo "<th> Date de Naissance : ";
			echo "</th>";
			echo "<td> $row[3]";
			echo "</td>";
		echo "</tr>";

		?>	
			<tr>
				<td>
				&nbsp
				</td>

				<td>
				&nbsp
				</td>
			</tr>
		<?php

		echo "<tr>";
			echo "<th> Date Inscription : ";
			echo "</th>";
			echo "<td> $row[4]";
			echo "</td>";
		echo "</tr>";

		?>	
			<tr>
				<td>
				&nbsp
				</td>

				<td>
				&nbsp
				</td>
			</tr>
		<?php

		echo "<tr>";
			echo "<th>Séance(s) effectuée(s) : ";
			echo "</th>";

			$result1 = mysqli_query($connect,"SELECT * FROM Inscription WHERE id_eleve=$id_eleve ");

			while ($row1 = mysqli_fetch_array($result1, MYSQL_NUM))
			{
			$result2 = mysqli_query($connect,"SELECT * FROM Seances WHERE id_seance=$row1[0] and date<$datedujour");
			$row2 = mysqli_fetch_array($result2, MYSQL_NUM);

				if(!empty($row2))
				{
				$test=1;
				$result3 = mysqli_query($connect,"SELECT * FROM themes WHERE id_theme=$row2[3]");
				$row3 = mysqli_fetch_array($result3, MYSQL_NUM);

				echo "<td> - le $row2[1] à $row2[2] h sur le thème $row3[1] | $row1[2] faute(s)</td></tr><tr><th></th>";
				}
			}

			if ($test==0)
			{
			echo "<td> Aucune séance effectuée</td>";
			}

		echo "</tr>";
	echo"</table></center>";
	}

	else
	{
	echo "<br> <center> L'élève n'a pas été saisi ";
	echo "<form method = 'post' action='consultation_eleve.php'>";	
	echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}

mysqli_close($connect);

?>

</body>

</html>
