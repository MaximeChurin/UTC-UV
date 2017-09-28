<html>
<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Ajouter un élève
</title>

</head>

<center>
	<h1>
	Résultat
	</h1>
</center>
<br>

<body >

<?php 

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to
mysql');

	if(!isset($_POST['choix']))

	{
	$nom = $_POST['nom']; 
	$prenom = $_POST['prenom'];
	$dateNaiss = $_POST['annee_naiss'].'-'.$_POST['mois_naiss'].'-'.$_POST['jour_naiss'];
	$verif=0;

	$test_bon_nom=$nom.''.$prenom;
	$accept = array("'", "-", "à", "ç", "é", "ù"," ","è","â","ô","î","û","ö","ï","ü"); 
	$test = str_replace($accept, "", $test_bon_nom);

		if (ctype_alpha($test) && is_numeric($_POST['annee_naiss']) && is_numeric($_POST['mois_naiss']) && is_numeric($_POST['jour_naiss']) && !empty($nom) && !empty($prenom) && !empty($dateNaiss) && checkdate($_POST['mois_naiss'],$_POST['jour_naiss'],$_POST['annee_naiss']) )

		{
		date_default_timezone_set('Europe/Paris');
		$dateInscription = date("Y\-m\-d");

		$result = mysqli_query($connect,"select * from eleves"); 

			while ($row=mysqli_fetch_array($result, MYSQL_NUM))
			{
				if ($row[1]==$nom && $row[2]==$prenom)
				{
				$verif=1;
				echo"<center>L'élève $nom $prenom est déjà existant, sa date de naissance est $row[3] </center><br>";
				}
			}

			if ($verif==1)
			{
			echo"<br><center>";
			echo"Voulez vous quand même l'ajouter ?</center>";
			echo"<form method = 'post' action='ajouter_eleve.php'>";	
			echo"<input type='hidden' name='nom' value=$nom >";
			echo"<input type='hidden' name='prenom' value=$prenom >";
			echo"<input type='hidden' name='dateNaiss' value=$dateNaiss >";
			?><center><table>
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
				
			<?php

			echo"<tr><th><center><INPUT VALUE='Oui' name='choix' TYPE='SUBMIT' class='choix'></center></th>";
			echo"<th><center><INPUT VALUE='Non' name='choix' TYPE='SUBMIT' class='choix'></th></center></tr>";
			echo"</form>";
			echo"</table></center>";
			}

			if ($verif==0)
			{
			echo"<center><table class='resultat' border='1'>";
		
				echo"<tr>";
					echo"<th> Nom : </th>";
					echo"<td> $nom </td>";
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
					echo"<th> Prénom : </th>";
					echo"<td> $prenom </td>";
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
					echo"<th> Date de naissance : </th>";
					echo"<td> $dateNaiss </td>";
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
					echo"<th> Date d'inscription : </th>";
					echo"<td> $dateInscription </td>";
				echo"</tr>";

			echo"</table></center>";
			
			$nom= str_replace ( "'", "\'", $nom) ; 
			$prenom= str_replace ( "'", "\'", $prenom) ;

			$query = "insert into eleves values (NULL, '$nom', '$prenom', '$dateNaiss', '$dateInscription')"; 

			$result = mysqli_query($connect, $query);

			if (!$result) 
			{ 
			echo "<br>pas bon".mysqli_error($connect);
			}
			}

		mysqli_close($connect);
		}

		else
		{
		echo "<br> <center> Formulaire mal rempli <br><br>";
		echo "<form method = 'post' action='ajout_eleve.html'>";	
		echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
		echo "</form></center> ";
		}
	}

	if(isset($_POST['choix']))
	{
	$nom = $_POST['nom']; 
	$prenom = $_POST['prenom'];
	$dateNaiss = $_POST['dateNaiss'];
	date_default_timezone_set('Europe/Paris');
	$dateInscription = date("Y\-m\-d");

		if ($_POST["choix"]=='Oui')
		{
		echo"<center><table class='resultat' border='1'>";
		
				echo"<tr>";
					echo"<th> Nom : </th>";
					echo"<td> $nom </td>";
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
					echo"<th> Prénom : </th>";
					echo"<td> $prenom </td>";
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
					echo"<th> Date de naissance : </th>";
					echo"<td> $dateNaiss </td>";
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
					echo"<th> Date d'inscription : </th>";
					echo"<td> $dateInscription </td>";
				echo"</tr>";

		echo"</table></center>";
			
		$nom= str_replace ( "'", "\'", $nom) ; 
		$prenom= str_replace ( "'", "\'", $prenom) ;

		$query = "insert into eleves values (NULL, '$nom', '$prenom', '$dateNaiss', '$dateInscription')"; 

		$result = mysqli_query($connect, $query);

			if (!$result) 
			{ 
			echo "<br>pas bon".mysqli_error($connect);
			}

		mysqli_close($connect);
		}

		else 
		{
		echo"<br><center> Aucune modification effectuée </center>";
		}

	}


?>

</body>

</html>


