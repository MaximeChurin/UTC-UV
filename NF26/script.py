#! /usr/bin/python3

import functions as _f

session = _f.connection()
_f.tables_creation(session)
_f.read_file_and_insert_in_table('../../../train.csv', session, ['facts_by_zone', 'facts_by_time', 'facts_by_start_zone', 'facts_by_end_zone'])

"""print(_f.request_time_table(2013, 11, 9))
print(_f.request_single_zone_table('Facts_by_start_zone', -8.601, 41.148, 2013, ['trip_id'], {'month':11}))
print(_f.request_zone_table(-8.601, 41.148, -8.601, 41.148,2013, ['trip_id'], {'month':11}))
"""