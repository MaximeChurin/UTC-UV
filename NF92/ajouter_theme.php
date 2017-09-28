<html>
<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Ajouter un thème
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
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to
mysql');

$nom = $_POST["nom_theme"];
$supprime = 0;
$descriptif = $_POST["descriptif"];
$verif=0;

$test_bon_nom=$nom;
$accept = array("-", "à", "ç", "é", "ù"," ","è","â","ô","î","û","ö","ï","ü"); 
$test = str_replace($accept, "", $test_bon_nom);

	if (ctype_alpha($test) && !empty($nom) && !empty($descriptif))
	{ 
	$result = mysqli_query($connect, "select * from themes where supprime='0' and nom='$nom'");
	$row = mysqli_fetch_array($result, MYSQL_NUM);

		if (!empty($row))
		{
		$result = mysqli_query($connect, "select * from themes where supprime='0' and nom='$nom'");
			while ($row=mysqli_fetch_array($result, MYSQL_NUM))
			{
				if ($row[1]==$nom)
				{
				$verif=1;
				echo "<br> <center> Thème déja existant et actif </center> <br><br>";
				}

			}
		}

	$result = mysqli_query($connect, "select * from themes where supprime='1' and nom='$nom'"); 
	$row=mysqli_fetch_array($result, MYSQL_NUM);

		if (!empty($row))
		{
		$result = mysqli_query($connect, "select * from themes where supprime='1' and nom='$nom'"); 
			while ($row=mysqli_fetch_array($result, MYSQL_NUM))
			{
				if ($row[1]==$nom)
				{
				$verif=2;
				}

			}
		}

		if ($verif==0)
		{
		echo"<center><table class='resultat'>";
		
				echo"<tr>";
					echo"<th> Nom du thème : </th>";
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
					echo"<th> Descriptif : </th>";
					echo"<td> $descriptif </td>";
				echo"</tr>";

		echo"</table></center>"; 

		$descriptif= str_replace ( "'", "\'", $descriptif) ;
		$query = "insert into themes values (NULL, '$nom', '$supprime', '$descriptif')"; 

		$result = mysqli_query($connect, $query);
			if (!$result) 
			{
			echo "<br>pas bon".mysqli_error($connect);
			}

		}

		if ($verif==2)
		{ 
		echo"<center><table class='resultat'>";
		
				echo"<tr>";
					echo"<th> Nom du thème : </th>";
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
					echo"<th> Descriptif : </th>";
					echo"<td> $descriptif </td>";
				echo"</tr>";

		echo"</table></center>";

		$descriptif= str_replace ( "'", "\'", $descriptif) ;		
		$query=mysqli_query($connect, "UPDATE themes SET supprime='0', descriptif='$descriptif' WHERE nom='$nom'"); 
		}

	mysqli_close($connect);
	}



	else
	{
	echo "<br> <center>Formulaire mal rempli<br><br>";
	echo "<form method = 'post' action='ajout_theme.html'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}
 
?>

</body>

</html>

