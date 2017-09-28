from rest_framework.serializers import HyperlinkedModelSerializer
from rest_framework.relations import HyperlinkedRelatedField

from gambler.models import Equipo, Partido, Resultado, Apuesta


class EquipoSerializer(HyperlinkedModelSerializer):
    class Meta:
        model = Equipo
        fields = ('nombreEquipo', 'pais')


class ResultadoSerializer(HyperlinkedModelSerializer):
    class Meta:
        model = Resultado
        fields = ('golLocal', 'golVisitante',)


class PartidoSerializer(HyperlinkedModelSerializer):
    equipoVisitante = EquipoSerializer('nombreEquipo')
    equipoLocal = EquipoSerializer('nombreEquipo')

    class Meta:
        model = Partido
        fields = ('fecha', 'equipoLocal', 'equipoVisitante', 'cuota',)


class ApuestaSerializer(HyperlinkedModelSerializer):
    partido = HyperlinkedRelatedField(view_name='gambler:partido-detail', read_only=True)
    resultado = HyperlinkedRelatedField(view_name='gambler:resultado-detail', read_only=True)

    class Meta:
        model = Apuesta
        fields = ('partido', 'resultado', 'apuesta',)