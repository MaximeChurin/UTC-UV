# Create your models here.
from django.db import models
from django.contrib.auth.models import User
from django.core.urlresolvers import reverse
from datetime import date

class Equipo(models.Model):
    nombreEquipo = models.TextField()
    pais = models.TextField(blank=True, null=True)
    def __str__(self):
        return u"%s" % str(self.nombreEquipo)+'-'+str(self.pais)
    def get_absolute_url(self):
        return reverse('gambler:equipo_detail', kwargs={'pk': self.pk})

class Resultado(models.Model):
    golLocal = models.IntegerField(default=-1)
    golVisitante = models.IntegerField(default=-1)

    def __str__(self):
        return u"%s" % str(self.golLocal)+' - '+str(self.golVisitante)
    def get_absolute_url(self):
        return reverse('gambler:resultado_detail', kwargs={'pk': self.pk})

class Partido(models.Model):
    jornada = models.IntegerField()
    equipoLocal = models.ForeignKey(Equipo, related_name='equipo_local')
    equipoVisitante = models.ForeignKey(Equipo, related_name='equipo_visitante')
    cuota = models.DecimalField(max_digits=3, decimal_places=2, default=1)
    fecha = models.DateField(default=date.today)
    resultado = models.ForeignKey(Resultado)
    def __str__(self):
        return u"%s" % str(self.jornada)+' / '+str(self.equipoLocal)+' - '+str(self.equipoVisitante)
    def get_absolute_url(self):
        return reverse('gambler:partido_detail', kwargs={'pk': self.pk})

class Apuesta(models.Model):
    user = models.ForeignKey(User)
    partido = models.ForeignKey(Partido, related_name='apuestas')
    apuesta = models.DecimalField(max_digits=11, decimal_places=2)
    resultado = models.ForeignKey(Resultado)
    def __str__(self):
        return u"%s" % str(self.partido.equipoLocal)+'-'+str(self.partido.equipoVisitante)+'/'+str(self.resultado.golLocal)+' - '+str(self.resultado.golVisitante)+' / '+str(self.apuesta)+'$ - '
    def get_absolute_url(self):
        return reverse('gambler:apuesta_detail', kwargs={'pk': self.pk})