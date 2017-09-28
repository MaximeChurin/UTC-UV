#! /usr/bin/python3

from cassandra.cluster import Cluster
import csv
import arrow
import json
import math
import random
import folium

SIGNIFICANT_FIGURES = math.pow(10,3)
CENTROIDS = list()
COLOR = ["orange", "blue", "red", "green", "black", "pink"]
FOLIUM_ZOOM = (41.151264, -8.612841)

def connection():
	cluster = Cluster(control_connection_timeout=9990.0)
	session = cluster.connect()
	session.default_timeout = 9999.0
	session.set_keyspace("e03")
	return session

def cast_geom(position, is_zone=False):
	longitude, latitude = position
	if(is_zone):
		longitude = math.floor(longitude*SIGNIFICANT_FIGURES)/SIGNIFICANT_FIGURES
		latitude = math.floor(latitude*SIGNIFICANT_FIGURES)/SIGNIFICANT_FIGURES

	res = dict()
	res['longitude'] = longitude
	res['latitude'] = latitude
	return res

def create_table(table_name, attributes, primary_keys):
	query = "CREATE TABLE IF NOT EXISTS " + table_name + " (";
	for attribute_name, attribute_type in attributes.items():
		query += attribute_name + " " + attribute_type + ", "
	query += " PRIMARY KEY ("
	for primary_key in primary_keys:
		query += primary_key + ', '
	query = query[:-2]
	query += "));"

	return query

def insert_table(table_name, my_dict):
	query = "INSERT INTO " + table_name + " (";
	for attribute in my_dict.keys():
		query += attribute + ", "
	query = query[:-2]
	query += ") VALUES ("
	for value in my_dict.values():
		value = str(value)
		if(value.startswith('{')):
			value = value.replace("'", "")
		query += value + ', '
	query = query[:-2]
	query += ");"

	return query

def read_file_and_insert_in_table(path_to_file, session, tables_name):
	with open (path_to_file) as train:
		reader = csv.reader(train)
		#skip the headers
		next(reader, None)
		for row in reader:
			polyline = json.loads(row[8])
			if(row[7]!="True" and len(polyline)>=1):
				my_dict = dict()
				my_dict['trip_id'] = "\'"+row[0]+"\'"
				my_dict['taxi_id'] = row[4]
				my_dict['day_type']= "\'"+row[6]+"\'"

				if(len(polyline)==1):
					my_dict['start_pos'] = my_dict['end_pos'] = cast_geom(polyline[0])
					my_dict['start_zone'] = my_dict['end_zone'] = cast_geom(polyline[0], True)
				else:
					my_dict['start_pos'] = cast_geom(polyline[0])
					my_dict['start_zone'] = cast_geom(polyline[0], True)
					polyline.reverse()
					my_dict['end_pos'] = cast_geom(polyline[0])
					my_dict['end_zone'] = cast_geom(polyline[0], True)

				timestamp = arrow.Arrow.utcfromtimestamp(row[5]);
				my_dict['year'] = timestamp.year
				my_dict['month'] = timestamp.month
				my_dict['day'] = timestamp.day
				my_dict['hour'] = timestamp.hour
				my_dict['minute'] = timestamp.minute
				my_dict['second'] = timestamp.second

				for table_name in tables_name:
					session.execute(insert_table(table_name, my_dict))

	print('Fin des insertions')

def tables_creation(session):
	session.execute(create_table("Facts_by_time", 
		{'trip_id': 'varchar', 'taxi_id': 'int', 'day_type': 'varchar',
		'year': 'int', 'month': 'int', 'day': 'int', 'hour': 'int', 'minute': 'int', 'second': 'int',
		'start_pos': 'frozen <geom>', 'end_pos': 'frozen <geom>', 
		'start_zone': 'frozen <geom>', 'end_zone': 'frozen <geom>'}, 
		['(year, month, day)', 'hour', 'minute', 'second', 'trip_id']))

	session.execute(create_table("Facts_by_start_zone", 
		{'trip_id': 'varchar', 'taxi_id': 'int', 'day_type': 'varchar',
		'year': 'int', 'month': 'int', 'day': 'int', 'hour': 'int', 'minute': 'int', 'second': 'int',
		'start_pos': 'frozen <geom>', 'end_pos': 'frozen <geom>', 
		'start_zone': 'frozen <geom>', 'end_zone': 'frozen <geom>'}, 
		['(start_zone, year)', 'month', 'day', 'hour', 'minute', 'second', 'trip_id']))

	session.execute(create_table("Facts_by_end_zone", 
		{'trip_id': 'varchar', 'taxi_id': 'int', 'day_type': 'varchar',
		'year': 'int', 'month': 'int', 'day': 'int', 'hour': 'int', 'minute': 'int', 'second': 'int',
		'start_pos': 'frozen <geom>', 'end_pos': 'frozen <geom>', 
		'start_zone': 'frozen <geom>', 'end_zone': 'frozen <geom>'}, 
		['(end_zone, year)', 'month', 'day', 'hour', 'minute', 'second', 'trip_id']))

	session.execute(create_table("Facts_by_zone", 
		{'trip_id': 'varchar', 'taxi_id': 'int', 'day_type': 'varchar',
		'year': 'int', 'month': 'int', 'day': 'int', 'hour': 'int', 'minute': 'int', 'second': 'int',
		'start_pos': 'frozen <geom>', 'end_pos': 'frozen <geom>', 
		'start_zone': 'frozen <geom>', 'end_zone': 'frozen <geom>'}, 
		['(start_zone, end_zone, year)', 'month', 'day', 'hour', 'minute', 'second', 'trip_id']))

	print('Création des tables Okay !')

def manage_selected_variables(selected_variables):
	variables = ""
	if (selected_variables != '*'):
		for selected_variable in selected_variables:
			variables += selected_variable + ', '
		selected_variables = variables[:-2]
	return selected_variables

def manage_xtra_arguments(xtra_arguments):
	query = ""
	for argument_name, argument_value in xtra_arguments.items():
		query += " AND " + argument_name
		if(type(argument_value) == str):
			argument_value = '\"' + argument_value + '\"'
		query += "=" + str(argument_value)
	return query

def request_time_table(year, month, day, selected_variables='*', xtra_arguments={}):
	selected_variables = manage_selected_variables(selected_variables)
	query = "SELECT " + selected_variables + " FROM facts_by_time WHERE year=" + str(year) + " AND month=" + str(month) + " AND day=" + str(day)
	query += manage_xtra_arguments(xtra_arguments) + ";"

	return query

def request_single_zone_table(table_name, longitude, latitude, year, selected_variables='*', xtra_arguments={}):
	selected_variables = manage_selected_variables(selected_variables)
	query = "SELECT " + selected_variables + " FROM " + table_name + " WHERE start_zone={latitude:" + str(latitude) + ", longitude:" + str(longitude) + "} AND year=" + str(year)
	query += manage_xtra_arguments(xtra_arguments) + ";"

	return query

def request_zone_table(start_longitude, start_latitude, end_longitude, end_latitude, year, selected_variables='*', xtra_arguments={}):
	selected_variables = manage_selected_variables(selected_variables)
	query = "SELECT " + selected_variables + " FROM facts_by_zone WHERE start_zone={latitude:" + str(start_latitude) + ", longitude:" + str(start_longitude) + "} AND end_zone={latitude:" + str(end_latitude) + ", longitude:" + str(end_longitude) + "} AND year=" + str(year)
	query += manage_xtra_arguments(xtra_arguments) + ";"
	
	return query

class Centroid:
	def __init__(self, k, start_pos, end_pos):
		self.k = k
		self.start_pos = {'longitude': start_pos.longitude, 'latitude': start_pos.latitude}
		self.end_pos = {'longitude': end_pos.longitude, 'latitude': end_pos.latitude}
		self.points = list()

	def show(self):	
		print("Centroid %d :" % self.k)
		print("\tStart position (latitude, longitude): %f %f" % (self.start_pos['latitude'], self.start_pos['longitude']))
		print("\tEnd position (latitude, longitude): %f %f" % (self.end_pos['latitude'], self.end_pos['longitude']))
		print("\tNumber of points %d\n" % len(self.points))

	def distance_to(self, row):
		return math.sqrt(math.pow(self.start_pos['latitude']-row.start_pos.latitude,2) +
					math.pow(self.start_pos['longitude']-row.start_pos.longitude,2) +
					math.pow(self.end_pos['latitude']-row.end_pos.latitude,2) +
					math.pow(self.end_pos['longitude']-row.end_pos.longitude,2))

	def resize(self):
		start_pos_lat = start_pos_long = end_pos_lat = end_pos_long = 0

		n = len(self.points)

		for point in self.points:
			start_pos_lat += point.start_pos.latitude
			start_pos_long += point.start_pos.longitude
			end_pos_lat += point.end_pos.latitude
			end_pos_long += point.end_pos.longitude

		if(self.start_pos['latitude'] == (start_pos_lat / n) and
			self.start_pos['longitude'] == (start_pos_long / n) and
			self.end_pos['latitude'] == (end_pos_lat / n) and
			self.end_pos['longitude'] == (end_pos_long /n)):

			return True
		else:
			self.start_pos['latitude'] = start_pos_lat / n 
			self.start_pos['longitude'] = start_pos_long / n
			self.end_pos['latitude'] = end_pos_lat / n
			self.end_pos['longitude'] = end_pos_long /n

			return False

	def reset_points(self):
		self.points= list()
		
def centroids_initialization(session, table_name, rows, k):
	n = session.execute("SELECT COUNT(*) FROM %s;" % (table_name))
	random_list =  random.sample(range(n[0].count), k)
	for i in random_list:
		row = rows[i]
		CENTROIDS.append(Centroid(i, row.start_pos, row.end_pos))

def find_closest_centroid(row):
	distance = -1
	for centroid in CENTROIDS:
		new_distance = centroid.distance_to(row)

		if(distance == -1):
			distance = new_distance
			k = centroid

		if(new_distance < distance):
			distance = new_distance
			k = centroid
	return k

def k_means(rows):
	print('Début analyse de la table')
	for row in rows:
		k = find_closest_centroid(row)
		k.points.append(row)
	for centroid in CENTROIDS:
		convergence = centroid.resize()
		centroid.show()
		centroid.reset_points()
	print('Fin itération sur la table avec convergence = %s' % convergence)
	return convergence

def construct_maps():	
	my_map = folium.Map(location=FOLIUM_ZOOM)
	i = 0
	for centroid in CENTROIDS:
		folium.PolyLine([(centroid.start_pos['latitude'], centroid.start_pos['longitude']), (centroid.end_pos['latitude'], centroid.end_pos['longitude'])], color=COLOR[i]).add_to(my_map)
		folium.Marker([centroid.start_pos['latitude'], centroid.start_pos['longitude']], icon = folium.Icon(color =COLOR[i])).add_to(my_map)
		folium.Marker([centroid.end_pos['latitude'], centroid.end_pos['longitude']], icon = folium.Icon(color =COLOR[i])).add_to(my_map)
		i += 1
	my_map.save('trajets.html')

def do_kmeans(session, table_name, K):
	rows = session.execute("SELECT start_pos, end_pos FROM %s;" % (table_name))
	print('Récuperation des rows terminée')
	centroids_initialization(session, table_name, rows, K)
	print('Initialisation des means terminée')
	convergence = False
	i = 0
	while(convergence == False):
		i += 1
		print('Itération %d' % i)
		convergence = k_means(rows)
