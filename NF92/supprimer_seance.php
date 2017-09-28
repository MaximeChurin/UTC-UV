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

$dbhost = 'tuxa.sme.utc';
$dbuser = 'nf92a020'; 
$dbpass = 'DE9ZujcI'; 
$dbname = 'nf92a020'; 
$connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting
to mysql');

$id_seance=$_POST['id_seance'];

	if(!empty($id_seance) )
	{ 
	$result = mysqli_query($connect,"SELECT * FROM Seances where id_seance=$id_seance");
	$row = mysqli_fetch_array($result, MYSQL_NUM);
	$result1 = mysqli_query($connect,"SELECT * FROM themes where id_theme='$row[3]'");
	$row1 = mysqli_fetch_array($result1, MYSQL_NUM);

	echo "<br> <center> La séance du $row[1] à $row[2] sur le thème $row1[1] a bien été supprimée</center>";

	$query=mysqli_query($connect, "delete from Seances where id_seance=$id_seance");

	$result = mysqli_query($connect,"SELECT * FROM Inscription WHERE id_seance='$id_seance'");
	$row = mysqli_fetch_array($result, MYSQL_NUM);

		if(!empty($row))
		{
		$query1=mysqli_query($connect, "delete from Inscription where id_seance=$id_seance"); 
		echo "<br><br><center> Le(s) inscription(s) à cette séance ont été supprimés </center>";
		}
	}

	else
	{
	echo "<br> <center> La séance n'a pas été choisie <br><br>";
	echo "<form method = 'post' action='suppression_seance.php'>";	
	echo"<br><INPUT VALUE='Retour' TYPE='SUBMIT' class='bouton'>";
	echo "</form></center> ";
	}

mysqli_close($connect);
?>
</body>
</html>
