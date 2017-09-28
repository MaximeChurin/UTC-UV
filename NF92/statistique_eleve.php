<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Statistique élève
</title>

</head>

<body>

<?php
$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$result = mysqli_query($connect,"SELECT * FROM Inscription where Nbre_erreurs!='?'");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (!isset($_POST['envoyer']) )
	{
		if (!empty($row) )
		{
		echo "<h1><center> Statistique de l'élève </center> </h1> <br> <br>";
		$result = mysqli_query($connect,"SELECT * FROM eleves");

		echo "<FORM METHOD='POST' ACTION='statistique_eleve.php'>";
		
		echo"<center><table>";

			echo"<tr>";
				echo"<th> Elève : </th>";
				echo"<td> <select name='id_eleves' size='1'>";
				echo "<option value=''>";
				echo "</option>";

					while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
					{
					echo "<option value='$row[0]'>";
					echo " $row[1] $row[2]";
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
			<?php 
	
			echo"<tr>";
				echo"<th> Affichage par : </th>";
				echo"<td> <select name='affichage' size='1'>";
				echo "<option value='1'>Séance</option>";
				echo "<option value='2'>Thème</option>";
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
				<INPUT VALUE="Afficher" name='envoyer' TYPE="SUBMIT" class="bouton">
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
		echo "<center> Il n'y a aucune séance validée </center>";
		}
	}

	if (isset($_POST['envoyer']) )
	{
	echo "<h1><center> Résultat </center> </h1> <br><br>";

		if(!empty($_POST['id_eleves']) && !empty($_POST['affichage']) )
		{
		$id_eleve=$_POST['id_eleves'];
		$affich=$_POST['affichage'];
		
		$result = mysqli_query($connect,"SELECT * FROM Inscription where id_eleve='$id_eleve' and Nbre_erreurs!='?'");
		$row = mysqli_fetch_array($result, MYSQL_NUM);

			if (!empty($row) )
			{
			$result = mysqli_query($connect,"SELECT * FROM eleves where id_eleve='$id_eleve'");
			$row = mysqli_fetch_array($result, MYSQL_NUM);

			echo"<center> Statistique de $row[1] $row[2] : </center><br>";
				if ($affich==1)
				{
				$nbre_seance=0;
				$reussite1=0;

				echo "<br><center><table class='tableau'>";
				echo "<tr>";
				echo "<th>Séance(s)";
				echo "</th>";
				echo "<th> % de Réussite";
				echo "</th>";
				echo "</tr>";

				$result = mysqli_query($connect,"SELECT * FROM Inscription where id_eleve='$id_eleve' and Nbre_erreurs!='?'");

					while ($row = mysqli_fetch_array($result, MYSQL_NUM))
					{
					$result1 = mysqli_query($connect,"SELECT * FROM Seances where id_seance='$row[0]'");
					$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

					$result2 = mysqli_query($connect,"SELECT * FROM themes where id_theme='$row1[3]'");
					$row2 = mysqli_fetch_array($result2, MYSQL_NUM);

					echo "<tr>";
					echo "<td> ";
					echo "Le $row1[1] à $row1[2] h sur le thème $row2[1]</td> ";
					echo "<td>";

						if($row[2]<='5')
						{
						echo "100%";
						$reussite=1;
						}
						else
						{
						echo "0%";
						$reussite=0;
						}

					echo "</td> ";
					echo "</tr>";

					$nbre_seance=$nbre_seance+1;
					$reussite1=$reussite1+$reussite;
					}

				echo "<tr>";
				echo "<th> Moyenne";
				echo "</th>";

				$reussite_global=$reussite1*100/$nbre_seance;

				$reussite_global=number_format($reussite_global, 0);

				echo "<td> $reussite_global %  ";
				echo "</td> ";
				echo "</tr>";

				echo "</table></center>";
				}

				if ($affich==2)
				{
				echo "<br><center><table class='tableau'>";
				echo "<tr>";
				echo "<th> Thème(s)";
				echo "</th>";
				echo "<th> % de Réussite";
				echo "</th>";
				echo "</tr>";

				$result1 = mysqli_query($connect,"SELECT * FROM themes ");
				$nbre_theme=0;
				$reussite1=0;

					while($row1 = mysqli_fetch_array($result1, MYSQL_NUM))
					{
					$increment=0;
					$reussite=0;

					$result = mysqli_query($connect,"SELECT themes.id_theme, Seances.id_seance, Nbre_erreurs FROM Seances, themes, Inscription where Seances.id_theme=themes.id_theme and Seances.id_seance=Inscription.id_seance and Inscription.id_eleve='$id_eleve' and Nbre_erreurs!='?'");

						while($row = mysqli_fetch_array($result, MYSQL_NUM))
						{
							if($row1[0]==$row[0])
							{
								if($row[2]<='5')
								{
								$test=1;
								}
								else
								{
								$test=0;
								}

							$reussite=$reussite+$test;
							$increment=$increment+1;
							}

						}

						if ($increment!=0)
						{
						echo "<tr>";
						echo "<td> ";
						echo "$row1[1] </td> ";
						echo "<td> ";

						$reussite_theme=$reussite/$increment * 100;

						$reussite_theme=number_format($reussite_theme, 0);

						echo "$reussite_theme % sur $increment séance(s)</td> ";
						echo "</tr>";
						$nbre_theme=$nbre_theme+1;
						$reussite1=$reussite1+$reussite_theme;
						}

					}

				echo "<tr>";
				echo "<th>Moyenne";
				echo "</th>";

				$reussite_global=$reussite1/$nbre_theme;

				$reussite_global=number_format($reussite_global, 0);

				echo "<td> $reussite_global %  ";
				echo "</td> ";
				echo "</tr>";

				echo "</table></center>";
				}
			}

			else
			{
			echo "<center> Cet élève n'a validé aucune séance </center>";
			}
		}

		else
		{
		echo "<center>  L'élève n'a pas été saisi <br><br>";
		echo "<form method = 'post' action='statistique_eleve.php'>";	
		echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
		echo "</form></center> ";
		}

	}

mysqli_close($connect);

?>

</body>

</html>
