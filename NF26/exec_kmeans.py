#! /usr/bin/python3

import functions as _f

K = 4

session = _f.connection()
_f.do_kmeans(session, 'facts_by_zone', K)
_f.construct_maps()