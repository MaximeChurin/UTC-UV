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
        <h1>All games</h1>
        <div id="games-list" class="container"></div>
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
                    item.appendChild(document.createTextNode(jsonCustomer[element]  + '€'));
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

        function makeDivsFromJson(jsonCustomer) {
            var divGames = document.createElement('div');

            for(element in jsonCustomer) {
                var divGame = document.createElement('div');
                divGame.classList.add('col-sm-4');
                divGame.classList.add('div-game');
                divGame.classList.add('col-sm-offset-1');

                divGame.appendChild(makeGameDiv(jsonCustomer[element]));
                divGames.appendChild(divGame);

                var divOffset = document.createElement('div');
                divOffset.classList.add('col-sm-1');
                divOffset.classList.add('div-game-offset');
                divGames.appendChild(divOffset);
            }

            return divGames;
        }

        function showAllGames() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', 'http://127.0.0.1:8180/videoGameAPI/rest/jeux');

            xhr.addEventListener('readystatechange', function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    var response = JSON.parse(xhr.responseText);
                    if(200 == xhr.status) {
                        divGamesList = document.getElementById('games-list');

                        oldList =  document.getElementById('all-games-list');
                        if(oldList) {
                            divCustomer.removeChild(oldList);
                        }

                        var list = makeDivsFromJson(response);

                        list.setAttribute('id', 'all-games-list');
                        divGamesList.appendChild(list);
                    }
                }
            });

            xhr.send();
        }

        var callback = function(){
            // Handler when the DOM is fully loaded
            showAllGames();
        };

        if (
            document.readyState === "complete" ||
            (document.readyState !== "loading" && !document.documentElement.doScroll)
        ) {
          callback();
        } else {
          document.addEventListener("DOMContentLoaded", callback);
        }
        </script>
    </body>
</html>
