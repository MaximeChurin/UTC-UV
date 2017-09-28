<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Ajouter une séance
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

$verif=0;

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$Date_seance =$_POST['annee_seance'].'-'.$_POST['mois_seance'].'-'.$_POST['jour_seance'];
date_default_timezone_set('Europe/Paris');
$datedujour = date("Ymd");
$testdate=$_POST['annee_seance'].''.$_POST['mois_seance'].''.$_POST['jour_seance'];
$heure_seance =$_POST['heure_seance'];

	if ($testdate>$datedujour && is_numeric($_POST['annee_seance']) && is_numeric($_POST['mois_seance']) && is_numeric($_POST['jour_seance']) && !empty($_POST["id_theme"]) && checkdate($_POST['mois_seance'],$_POST['jour_seance'],$_POST['annee_seance']) && !empty($heure_seance) )
	{
	$id_theme =$_POST["id_theme"];
	$result = mysqli_query($connect, "select * from Seances"); 

		while ($row=mysqli_fetch_array($result, MYSQL_NUM))
		{
			if ($row[1]==$Date_seance && $row[3]==$id_theme)
			{
			$verif=1;
			echo"<center> Thème de séance ayant déja lieu à cette date </center>";
			}

			if ($row[1]==$Date_seance && $row[2]==$heure_seance)
			{
			$verif=1;
			echo"<br><center> Il y a déjà une séance à cette date et cette heure </center>";
			}
		}

		if ($verif==0)
		{
		$query = "insert into Seances values (NULL, '$Date_seance', '$heure_seance', '$id_theme', 20)"; 
		$result1 = mysqli_query($connect,"SELECT * FROM themes where id_theme=$id_theme");
		$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

		echo"<center><table class='resultat'>";

				echo"<tr>";
					echo"<th> Nom du thème : </th>";
					echo"<td> $row1[1] </td>";
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
				<?php

				echo"<tr>";
					echo"<th> Date de la séance : </th>";
					echo"<td> $Date_seance </td>";
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
				<?php
		
				echo"<tr>";
					echo"<th> Heure : </th>";
					echo"<td> $heure_seance </td>";
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
				<?php

				echo"<tr>";
					echo"<th> Effectif : </th>";
					echo"<td> 20 personnes</td>";
				echo"</tr>";

		echo"</table></center>"; 

		$result = mysqli_query($connect, $query); 

			if (!$result) 
			{ 
			echo "<br>pas bon".mysqli_error($connect);
			}

		mysqli_close($connect);
		}

	}

	else
	{
	echo "<center> Formulaire mal saisi (la séance doit avoir une date future)<br><br>";
	echo "<form method = 'post' action='ajout_seance.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}
?>

</body>

</html>
