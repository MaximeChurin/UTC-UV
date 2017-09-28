<?php
    session_start();

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
        <h1>Search a game:</h1>
        <form class="search-form" onsubmit="return false">
            <p>Title : <input id="game-id" type="text" name="game-id" onkeydown="if(event.keyCode == 13) showGame()"/></p>
            <br>
            <input type="button" id="click-button" value="OK"/>
        </form>
        <div id="game"></div>
        <script>

        function makeLI(jsonCustomer) {
            var list = document.createElement('ul');

            for(element in jsonCustomer) {
                var node = element + ' = ' + jsonCustomer[element];
                var item = document.createElement('li');

                item.appendChild(document.createTextNode(node));

                list.appendChild(item);
            }

            return list;
        }

        function makeGameDiv(jsonCustomer) {
            var list = document.createElement('div');
            var row1 = document.createElement('div');
            row1.classList.add('row');

            var row2 = document.createElement('div');
            row2.classList.add('row');

            var ul1 = document.createElement('ul');
            ul1.classList.add('col-xs-6');
            ul1.classList.add('game-ul');
            row2.appendChild(ul1);

            var ul2 = document.createElement('ul');
            ul2.classList.add('col-xs-6');
            ul2.classList.add('game-ul');
            row2.appendChild(ul2);

            for(element in jsonCustomer) {
                if('id' === element) { continue; }

                if('title' === element) {
                    var item = document.createElement('p');
                    item.innerHTML = jsonCustomer[element]
                    item.classList.add('col-xs-12');
                    row1.appendChild(item);
                }

                if('price' === element) {
                    var item = document.createElement('li');
                    item.appendChild(document.createTextNode('Price'));
                    ul1.appendChild(item);

                    var item = document.createElement('li');
                    item.appendChild(document.createTextNode(jsonCustomer[element] + '$'));
                    ul1.appendChild(item);
                }

                if('isPlayedOns' === element) {
                    var item = document.createElement('li');
                    item.appendChild(document.createTextNode('Console'));
                    ul2.appendChild(item);

                    var item = document.createElement('li');
                    item.appendChild(document.createTextNode(jsonCustomer[element]));
                    ul2.appendChild(item);
                }
            }

            list.appendChild(row1);
            list.appendChild(row2);

            return list;
        }

        function testText(champAControler) {
            var formatTexte = /^[a-zàäâéèêëïîöôùüû\s]*$/i;

            return formatTexte.test(champAControler);
        }

        function showGame() {
            var gameTitle = document.getElementById('game-id').value;
            var gameTitleFound = ''

            if(!testText(gameTitle)) {
                return;
            }

            divGame = document.getElementById('game');

            oldList =  document.getElementById('my-game');
            if(oldList) {
                divGame.removeChild(oldList);
            }

            oldParagraph =  document.getElementById('error-paragraph');
            if(oldParagraph) {
                divGame.removeChild(oldParagraph);
            }

            for (index = 0; index < allGamesTitles.length; ++index) {
                currentGameTitle = allGamesTitles[index];
                if(currentGameTitle.toLowerCase().indexOf(gameTitle.toLowerCase()) !== -1) {
                    gameTitleFound = currentGameTitle;

                    break;
                }
            }

            if ('' === gameTitleFound) {
                var paragraph = document.createElement('p');
                paragraph.innerHTML = 'Jeu non trouvé';
                divGame.appendChild(paragraph);
                paragraph.setAttribute('id', 'error-paragraph');
            } else {
                for(element in allGames) {
                    currentGame = allGames[element];
                    if(currentGame['title'] === gameTitleFound) {
                        var gameFound = currentGame;
                        break;
                    }
                }

                var game = document.getElementById('game');
                var divGame = document.createElement('div');
                divGame.classList.add('col-sm-4');
                divGame.classList.add('div-game');
                divGame.classList.add('col-sm-offset-4');

                divGame.setAttribute('id', 'my-game');

                divGame.appendChild(makeGameDiv(gameFound));
                game.appendChild(divGame);
            }
        }

        function getAllGames() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', 'http://127.0.0.1:8180/videoGameAPI/rest/jeux');

            xhr.addEventListener('readystatechange', function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    var response = JSON.parse(xhr.responseText);
                    if(200 == xhr.status) {
                        allGames = response;

                        for(element in allGames) {
                            game = allGames[element];
                            allGamesTitles.push(game['title']);
                        }
                    }
                }
            });

            xhr.send();
        }

        var allGames;
        var allGamesTitles = [];

        var callback = function(){
            // Handler when the DOM is fully loaded
            getAllGames();
        };

        if (
            document.readyState === "complete" ||
            (document.readyState !== "loading" && !document.documentElement.doScroll)
        ) {
          callback();
        } else {
          document.addEventListener("DOMContentLoaded", callback);
        }

        document.getElementById("click-button").onclick = showGame;
        </script>
    </body>
</html>
