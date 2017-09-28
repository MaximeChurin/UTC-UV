<?php
    session_start();

    if(isset($_POST['session-id'])) {
        $_SESSION['session_id'] = $_POST['session-id'];
        $_SESSION['email'] = $_POST['email'];
        $_SESSION['password'] = $_POST['password'];
        $_SESSION['firstname'] = $_POST['firstname'];
    }

    if(!isset($_SESSION['session_id'])) {
        header('Location: connexion.php');
        exit();
    }
?>
<!DOCTYPE html>
<html>
    <head>
        <link href="bootstrap-3.3.6-dist/css/bootstrap.css" rel="stylesheet">
        <link href="global.css" rel="stylesheet">
    </head>
    <body>
        <nav class="navbar navbar-inverse sticky-navbar navbar-fixed-top" role="navigation">
            <div class="container-fluid">
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar_content">
                    </button>
                </div>
                <a class="navbar-brand" href="index.php">Home</a>
                <div class="collapse navbar-collapse" id="navbar_content">
                    <ul class="nav navbar-nav navbar-left">
                        <li class="pull-left"><p class="navbar-text">Hello  <?php echo json_encode($_SESSION['firstname'], JSON_HEX_TAG); ?></p></li>
                    </ul>
                    <ul class="nav navbar-nav navbar-right">
                        <li class="pull-right">
                            <a href="customer-informations.php"><span class="glyphicon glyphicon-user" aria-hidden="true"></span></a>
                        </li>
                        <li class="pull-right">
                            <a href="logout.php"><span class="glyphicon glyphicon-off" aria-hidden="true"></span></a>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>
        <h1>Welcome to the video game online store</h1>
        <div id="dom-target-session-id" style="display: none;">
            <?php
                $sessionId = $_SESSION['session_id'];
                echo htmlspecialchars($sessionId);
            ?>
        </div>
        <div class="list-links">
            <a class="index-link" href="all-games.php"><button type="button" class="btn btn-lg btn-primary margin-top">See all games</button></a>
            <br>
            <a class="index-link" href="search-game.php"><button type="button" class="btn btn-lg btn-primary">Search a game</button></a>
        </div>
    </body>
</html>
