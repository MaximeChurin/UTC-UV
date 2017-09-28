<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>
<title>
Supprimer un thème
</title>

</head>

<center>
<h1>
Supprimer un thème
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

$result = mysqli_query($connect,"SELECT * FROM themes where supprime=0");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if(!empty($row) )
	{
	$result = mysqli_query($connect,"SELECT * FROM themes where supprime=0");

	echo "<FORM METHOD='POST' ACTION='supprimer_theme.php'>";

	echo"<center><table>";

		echo"<tr>";
			echo"<th> Thème à supprimer : </th>";
			echo"<td> <select name='id_theme' size='1'>";
			echo "<option value=''>";
			echo "</option>";

				while ($row = mysqli_fetch_array($result, MYSQL_NUM)) 
				{
				echo "<option value='$row[0]'>";
				echo " $row[1] ";
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
	<form>
	
	<?php
	}

	else
	{
	echo "<center>La table des thèmes est vide </center>";
	}

mysqli_close($connect);

?>

</body>

</html>
