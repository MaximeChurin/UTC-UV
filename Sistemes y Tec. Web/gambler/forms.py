from django.forms import ModelForm
from gambler.models import Apuesta, Equipo, Resultado

class ApuestaForm(ModelForm):
    class Meta:
        model = Apuesta
        exclude = ('partido', 'user', 'date',)

class EquipoForm(ModelForm):
    class Meta:
        model = Equipo
        exclude = ('nombreEquipo',)

class ResultadoForm(ModelForm):
    class Meta:
        model = Resultado
        exclude = ('',)