<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Annuler une séance pour un élève
</title>

</head>

<center>
<h1>
Annuler une séance pour un élève
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
$result = mysqli_query($connect,"SELECT * FROM Seances where date>=$datedujour");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (empty($row))
	{
	echo "<center> Il n'y a aucune séance de prévue </center>";
	}

	if (!empty($row) && !isset($_POST['enregistrer']))
	{
	echo "<FORM METHOD='POST' ACTION='annulation_seance.php'>";
	$result = mysqli_query($connect,"SELECT * FROM Seances where date>=$datedujour");

	echo"<center><table>";
		echo"<tr>";
			echo"<th> Séance : </th>";
			echo"<td> <select name='id_seances' size='1'>";
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
			<INPUT VALUE="Valider" name='enregistrer' TYPE="SUBMIT" class='bouton'>
			</center></td>

			<td><center>
			<INPUT VALUE="Annuler" TYPE="RESET" class='bouton'>
			</center></td>
		</tr>

	</table></center>
	</form>
	
	<?php		
	}

	if(isset($_POST['enregistrer']) && !empty($_POST['id_seances']) )
	{
	$id_seances=$_POST['id_seances'];
	$result = mysqli_query($connect,"SELECT * FROM Inscription Where id_seance='$id_seances'");
	$row = mysqli_fetch_array($result, MYSQL_NUM);

		if( !empty($row) )
		{
		$a=0;

		$result2= mysqli_query($connect,"SELECT * FROM Seances Where id_seance='$id_seances'");
		$row2 = mysqli_fetch_array($result2, MYSQL_NUM);

		$result3= mysqli_query($connect,"SELECT * FROM themes Where id_theme='$row2[3]'");
		$row3= mysqli_fetch_array($result3, MYSQL_NUM);

		echo "<center> Séance du $row2[1] à $row2[2] h sur le thème $row3[1]</center><br> <br>";

		echo "<FORM METHOD='POST' ACTION='annuler_seance.php'>";

		$result = mysqli_query($connect,"SELECT * FROM Inscription Where id_seance='$id_seances'");

		echo"<center><table>";
			echo"<tr>";
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

				echo"<th> Elève : </th>";
				echo"<td> <select name='id_eleves' size='1'>";
				echo "<option value=''>";
				echo "</option>";

					while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
					{

					$result1= mysqli_query($connect,"SELECT * FROM eleves Where id_eleve='$row[1]'");
					$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

					echo "<option value='$row1[0]'>";
					echo " $row1[1] $row1[2] ";
					echo "</option>";
					}

				echo "</select></td>";
			echo"</tr>";
			echo "<input type='hidden' name='id_seances' value='$_POST[id_seances]'> ";
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
				<INPUT VALUE="Valider" TYPE="SUBMIT" class='bouton'>
				</center></td>

				<td><center>
				<INPUT VALUE="Annuler" TYPE="RESET" class='bouton'>
				</center></td>
			</tr>

		</table></center>
		</form>
	
		<?php
		}

		else 
		{
		echo "<center> Il n'y a aucun élève inscrit à cette séance </center> ";
		}
	}

	if(isset($_POST['enregistrer']) && empty($_POST['id_seances']))
	{
	echo "<center> La séance n'a pas été choisie<br><br>";
	echo "<form method = 'post' action='annulation_seance.php'>";
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}

mysqli_close($connect);

?>

</body>

</html>
