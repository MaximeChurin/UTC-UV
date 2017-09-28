<html>

<head>

<meta charset="UTF-8" />
<link type="text/css" rel="stylesheet" href="style.css"/>

<title>
Statistique globale
</title>

</head>

<center>
<h1>
Statistique globale
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

$result = mysqli_query($connect,"SELECT * FROM Inscription where Nbre_erreurs!='?'");
$row = mysqli_fetch_array($result, MYSQL_NUM);

	if (!empty($row) )
	{
	echo "<center><table class='tableau'>";
	echo "<tr>";
	echo "<th> Thème(s)";
	echo "</td>";
	echo "<th> Nombre d'élèves inscrits";
	echo "</th>";
	echo "<th> % de Réussite";
	echo "</th>";
	echo "<th> Moyenne de faute";
	echo "</th>";
	echo "</tr>";

	$result1 = mysqli_query($connect,"SELECT * FROM themes ");
	$nbre_theme=0;
	$reussite1=0;

		while($row1 = mysqli_fetch_array($result1, MYSQL_NUM))
		{
		$increment=0;
		$reussite=0;
		$faute=0;

		$result = mysqli_query($connect,"SELECT themes.id_theme, Seances.id_seance, Nbre_erreurs FROM Seances, themes, Inscription where Seances.id_theme=themes.id_theme and Seances.id_seance=Inscription.id_seance and Nbre_erreurs!='?'");

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
				$faute=$faute+$row[2];
				}
			}
			if ($increment!=0)
			{
			echo "<tr>";
				echo "<td> ";
				echo "$row1[1] </td> ";

				echo "<td> $increment ";
				echo " </td> ";

				echo "<td> ";

				$reussite_theme=$reussite/$increment * 100;
				$reussite_theme=number_format($reussite_theme, 0);

				echo "$reussite_theme % </td> ";
	
				$faute=$faute/$increment;
				$faute=number_format($faute, 0);
				echo "<td>  $faute ";
				echo " </td> ";

			echo "</tr>";
			}
		}
		echo "</table></center>";
	}

	else
	{
	echo "<center> Il n'y a aucune séance de validée </center>";
	}

mysqli_close($connect);

?>

</body>

</html>
