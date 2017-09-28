<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Faire une Inscription
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

$verif=0;
$a=0;
$id_seances =$_POST['id_seances'];
$id_eleves =$_POST['id_eleves'];

	if(!empty($id_seances) && !empty($id_eleves))
	{
	$result= mysqli_query($connect, "select * from Inscription where id_seance=$id_seances");
		while ($row=mysqli_fetch_array($result, MYSQL_NUM))
		{
		$a=$a+1;
		}

		if ($a<20)
		{
		$result = mysqli_query($connect, "select * from Inscription"); 

			while ($row=mysqli_fetch_array($result, MYSQL_NUM))
			{
				if ($row[0]==$id_seances && $row[1]==$id_eleves)
				{
				$verif=1;
				echo"<center>Elève déjà inscrit à cette séance</center>";
				}
			}

			if ($verif==0)
			{
			$query = "insert into Inscription values ('$id_seances', '$id_eleves', '?')"; 
			$result1 = mysqli_query($connect,"SELECT * FROM Seances where id_seance=$id_seances");
			$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

			$result2 = mysqli_query($connect,"SELECT * FROM themes where id_theme=$row1[3]");
			$row2 = mysqli_fetch_array($result2, MYSQL_NUM);

			$result3 = mysqli_query($connect,"SELECT * FROM eleves where id_eleve=$id_eleves");
			$row3 = mysqli_fetch_array($result3, MYSQL_NUM);

			echo"<center><table border='1' class='resultat'>";
			echo"<tr><th>Elève inscrit(e) :</th>";
			echo"<td> $row3[1] $row3[2] </td></tr>";

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

			echo"<tr><th>Séance : :</th>";
			echo"<td> Le $row1[1] à $row1[2] sur le thème $row2[1] </td></tr>";
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
		echo "<center>Impossible de s'inscrire car la séance est complète (ou élève déja inscrit)</center>";
		}
	}

	else
	{
	echo "<center>Vous n'avez pas saisi le formulaire correctement <br><br>";
	echo "<form method = 'post' action='inscription_eleve.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}

?>

</body>

</html>
