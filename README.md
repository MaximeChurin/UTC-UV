# UTC-UV
Folder with differents student projects and exercices

## IA02
Implementation of the Khan board game in `prolog` (rules available [here](https://www.google.no/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwiCq8a-2crWAhUJLZoKHQ6UDrIQFggnMAA&url=https%3A%2F%2Fmoodle.utc.fr%2Fpluginfile.php%2F864%2Fmod_folder%2Fcontent%2F0%2FR%25C3%25A8gles%2520du%2520Jeu%2520KHAN.pdf%3Fforcedownload%3D1&usg=AFQjCNGR2UH4DSJU6ZA4kQdZjPRMmw1Cbg)). Possibility to play at two player or against an IA. The IA is made to rush as fast as possible your kalista to win. UI with the console.
Launching with GNU-Prolog:
```prolog
change_directory('your_directory').
consult('projet_IA02_Churin_Maxime_Bria_Robin.pl').
main.
```
[Khan Game](IA02/screenshot_khan.png)

## LO21
Implementation of a Reverse Polish notation calculator in `C++` with an UI made with `Qt`. The calculator handles operations between integers, reals, rationnals, expressions and complex numbers. It can storage variables and programs. Usage of multiples design patterns such as *singleton, template method, memento, strategy or iterator*.

[UTC_computer](LO21/UTC_computer.png)

## NF16
Differents TPs in `C` such as : 
- managing a library using linked lists with a borrowing system, research of books, adding books...
- coding how to handle binary tree and his nodes

## NF26
Data analisis of the taxis running in the city of Porto, in Portugal (link [here](https://archive.ics.uci.edu/ml/datasets/Taxi+Service+Trajectory+-+Prediction+Challenge,+ECML+PKDD+2015)). A set of real data from 2015 with more than 1 700 000 records described by 9 measurements. The purpose of this set of data and this analysis was to improve customer satisfaction regarding the waiting time and to be more competitive and profitable in the transport business. We clean, prepare and store the data in a cassandra database. Finally we did an offline k-means to retrieve the most important clusters of rides, plot them using a `python` lib called *Folium* and analyse them.

[Clusters de taxi](NF26/screenshot_taxis.png)

## NF92
Simple website using `PHP`, `HTML` and `CSS` to manage a driving school and his customers : possibility to plan sessions, register a user, have some statistics ... Launch using *website.html*.

[Driving school](NF92/screenshot_driving_school.png)

## ProgII
Differents `Java` projects such as : 
- implementation of infinite precision naturals using arrays of integers
- implementation of a graphical clock using *canvas* lib
- an application to store NFL players data as their running distance and display some statistics

## SR03
A project of a video game shop with an API server with authentification, request entities ..., a client website with login  for displaying the results and also an native android app with login and list-views.

## SY09
Data analisis and Data-Mining TPs in `R`. We use different algorithm such as principal component analysis, hierarchical clustering, kmeans, k-nearest neighbor, Bayes rules, discriminant analysis, Logistic regression...
