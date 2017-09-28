# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
from django.conf import settings
import datetime


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Apuesta',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, primary_key=True, auto_created=True)),
                ('apuesta', models.DecimalField(max_digits=11, decimal_places=2)),
            ],
        ),
        migrations.CreateModel(
            name='Equipo',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, primary_key=True, auto_created=True)),
                ('nombreEquipo', models.TextField()),
                ('pais', models.TextField(blank=True, null=True)),
            ],
        ),
        migrations.CreateModel(
            name='Partido',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, primary_key=True, auto_created=True)),
                ('jornada', models.IntegerField()),
                ('cuota', models.DecimalField(max_digits=3, decimal_places=2, default=1)),
                ('fecha', models.DateField(default=datetime.date.today)),
                ('equipoLocal', models.ForeignKey(related_name='equipo_local', to='gambler.Equipo')),
                ('equipoVisitante', models.ForeignKey(related_name='equipo_visitante', to='gambler.Equipo')),
            ],
        ),
        migrations.CreateModel(
            name='Resultado',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, primary_key=True, auto_created=True)),
                ('golLocal', models.IntegerField(default=-1)),
                ('golVisitante', models.IntegerField(default=-1)),
            ],
        ),
        migrations.AddField(
            model_name='partido',
            name='resultado',
            field=models.ForeignKey(to='gambler.Resultado'),
        ),
        migrations.AddField(
            model_name='apuesta',
            name='partido',
            field=models.ForeignKey(related_name='apuestas', to='gambler.Partido'),
        ),
        migrations.AddField(
            model_name='apuesta',
            name='resultado',
            field=models.ForeignKey(to='gambler.Resultado'),
        ),
        migrations.AddField(
            model_name='apuesta',
            name='user',
            field=models.ForeignKey(to=settings.AUTH_USER_MODEL),
        ),
    ]
