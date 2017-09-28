<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Valider une séance
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

$id_seances=$_POST['id_seances'];

	if(!isset($_POST['choix']) )
	{
	$nbre_erreurs=$_POST['note'];
	$id_eleves=$_POST['id_eleves'];
	$test=0;

		if (isset($nbre_erreurs))
		{
		    if (preg_match("#^([0-9]){1,2}$#", $nbre_erreurs))
		    {
			$test=1;
		    }
		}

// sinon faire un select avec les bons nombres

		if ($test==1 && is_numeric($nbre_erreurs) && !empty($id_eleves) && $nbre_erreurs>=0 && $nbre_erreurs<=40 )
		{
		$result= mysqli_query($connect,"SELECT * FROM Inscription Where id_eleve='$id_eleves' and id_seance='$id_seances'");
		$row = mysqli_fetch_array($result, MYSQL_NUM);

			if($row[2]=='?')
			{
			$query=mysqli_query($connect, "UPDATE Inscription SET Nbre_erreurs='$nbre_erreurs' WHERE id_eleve=$id_eleves and id_seance=$id_seances"); 
			echo "<center> L'élève a fait $nbre_erreurs faute(s)";
			echo "<form method = 'post' action='validation_seance.php'>";
			echo" <input type='hidden' name='id_seances' value=$id_seances >";
			echo" <input type='hidden' name='enregistrer' value=$id_seances >";
			echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
			echo "</form></center> ";

				if(empty($query))
				{
				echo "<br>pas bon".mysqli_error($connect);
				}
			}

			else
			{
			echo"<center> L'élève a déjà un résultat : $row[2] erreur(s) <br><br>";
			echo"<br>Voulez vous quand même le changer ?<br>";
			echo "<form method = 'post' action='valider_seance.php'>";	
			echo" <input type='hidden' name='id_eleves' value=$id_eleves >";
			echo" <input type='hidden' name='id_seances' value=$id_seances >";
			echo" <input type='hidden' name='nbre_erreurs' value=$nbre_erreurs >";
			echo"<br><br><table><tr><td><INPUT VALUE='Oui' name='choix' TYPE='SUBMIT' class='bouton'></td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td>&nbsp</td><td><INPUT VALUE='Non' name='choix' TYPE='SUBMIT' class='bouton'></td></tr></table>";
			echo "</form></center>";
			}

		}

		else
		{
		echo "<center><br>Formulaire mal saisi <br><br>";
		echo "<form method = 'post' action='validation_seance.php'>";
		echo" <input type='hidden' name='id_seances' value=$id_seances >";
		echo" <input type='hidden' name='enregistrer' value=$id_seances >";	
		echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
		echo "</form></center> ";
		}

	}

	if(isset($_POST['choix']) )
	{
	$nbre_erreurs=$_POST['nbre_erreurs'];
	$id_eleves=$_POST['id_eleves'];

		if ($_POST["choix"]=='Oui')
		{
		$query=mysqli_query($connect, "UPDATE Inscription SET Nbre_erreurs='$nbre_erreurs' WHERE id_eleve=$id_eleves and id_seance=$id_seances"); 
		echo "<center> L'élève a fait $nbre_erreurs faute(s)";
		echo "<form method = 'post' action='validation_seance.php'>";
		echo" <input type='hidden' name='id_seances' value=$id_seances >";
		echo" <input type='hidden' name='enregistrer' value=$id_seances >";	
		echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
		echo "</form></center> ";
		}

		else 
		{
		echo"<center>Aucune modification effectuée";
		echo "<form method = 'post' action='validation_seance.php'>";
		echo" <input type='hidden' name='id_seances' value=$id_seances >";
		echo" <input type='hidden' name='enregistrer' value=$id_seances >";	
		echo"<br><br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
		echo "</form></center> ";
		}
	}

mysqli_close($connect);

?>

</body>

</html>
