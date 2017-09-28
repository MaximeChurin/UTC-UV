# Create your views here.
from django.http import HttpResponse
from django.shortcuts import render
from django.views.generic import DetailView, ListView
from django.views.generic.base import TemplateResponseMixin
from django.views.generic.edit import CreateView
from rest_framework import generics, permissions
from rest_framework import viewsets

from gambler import serializers
from gambler.serializers import *
from gambler.models import Partido, Apuesta, Equipo, Resultado
from gambler.forms import *


class ConnegResponseMixin(TemplateResponseMixin):

    def render_json_object_response(self, objects, **kwargs):
        json_data = serializers.serialize(u"json", objects, **kwargs)
        return HttpResponse(json_data, content_type=u"application/json")

    def render_xml_object_response(self, objects, **kwargs):
        xml_data = serializers.serialize(u"xml", objects, **kwargs)
        return HttpResponse(xml_data, content_type=u"application/xml")

    def render_to_response(self, context, **kwargs):
        if 'extension' in self.kwargs:
            try:
                objects = [self.object]
            except AttributeError:
                objects = self.object_list
            if self.kwargs['extension'] == 'json':
                return self.render_json_object_response(objects=objects)
            elif self.kwargs['extension'] == 'xml':
                return self.render_xml_object_response(objects=objects)
        else:
            return super(ConnegResponseMixin, self).render_to_response(context)

def search(request):
    if 'pais' in request.GET and request.GET['pais']:
        pais = request.GET['pais']
        equipos = Equipo.objects.filter(pais__icontains=pais)
        return render(request, 'search_results.html',
            {'equipos': equipos, 'query': pais})
    else:
        return render(request, 'search_results.html', {'error': True})

class PartidoList(ListView, ConnegResponseMixin):
    model = Partido
    queryset = Partido.objects.all()
    context_object_name = 'latest_partido_list'
    template_name = 'gambler/partidos_list.html'

class EquipoList(ListView, ConnegResponseMixin):
    model = Equipo
    context_object_name = 'latest_equipo_list'
    template_name = 'gambler/equipos_list.html'

class ApuestaList(ListView, ConnegResponseMixin):
    model = Apuesta
    context_object_name = 'latest_apuesta_list'
    template_name = 'gambler/apuestas_list.html'

class ResultadoList(ListView, ConnegResponseMixin):
    model = Resultado
    context_object_name = 'latest_resultado_list'
    template_name = 'gambler/resultados_list.html'

class PartidoDetail(DetailView, ConnegResponseMixin):
    model = Partido
    template_name = 'gambler/partidos_detail.html'

    def get_context_data(self, **kwargs):
        context = super(PartidoDetail, self).get_context_data(**kwargs)
        return context

class ApuestaDetail(DetailView, ConnegResponseMixin):
    model = Apuesta
    template_name = 'gambler/apuestas_detail.html'

    def get_context_data(self, **kwargs):
        context = super(ApuestaDetail, self).get_context_data(**kwargs)
        return context

class ApuestaCreate(CreateView):
    model = Apuesta
    template_name = 'gambler/form.html'
    form_class = ApuestaForm

    def form_valid(self, form):
        form.instance.user = self.request.user
        form.instance.partido = Partido.objects.get(id=self.kwargs['pk'])
        return super(ApuestaCreate, self).form_valid(form)

class ResultadoCreate(CreateView):
    model = Resultado
    template_name = 'gambler/form.html'
    form_class = ResultadoForm

    def form_valid(self, form):
        return super(ResultadoCreate, self).form_valid(form)

class ResultadoDetail(DetailView, ConnegResponseMixin):
    model = Resultado
    template_name = 'gambler/resultado_detail.html'

    def get_context_data(self, **kwargs):
        context = super(ResultadoDetail, self).get_context_data(**kwargs)
        return context


class EquipoBusqueda(CreateView):
    model = Equipo
    template_name = 'gambler/form_search.html'
    form_class = EquipoForm

    def form_valid(self, form):
        return super(EquipoBusqueda, self).form_valid(form)

### RESTful API views ###

class IsOwnerOrReadOnly(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        # Read permissions are allowed to any request,
        # so we'll always allow GET, HEAD or OPTIONS requests.
        if request.method in permissions.SAFE_METHODS:
            return True

        # Instance must have an attribute named `owner`.
        return obj.user == request.user


class PartidoList2(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = Partido.objects.all()
    serializer_class = PartidoSerializer


class EquipoList2(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = Equipo.objects.all()
    serializer_class = EquipoSerializer


class ApuestaList2(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = Apuesta.objects.all()
    serializer_class = ApuestaSerializer


class ResultadoList2(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = Resultado.objects.all()
    serializer_class = ResultadoSerializer


class APIPartidoDetail(generics.RetrieveUpdateDestroyAPIView):
    permission_classes = (IsOwnerOrReadOnly,)
    model = Partido
    queryset = Partido.objects.all()
    serializer_class = PartidoSerializer


class APIResultadoDetail(generics.RetrieveUpdateDestroyAPIView):
    permission_classes = (IsOwnerOrReadOnly,)
    model = Resultado
    queryset = Resultado.objects.all()
    serializer_class = ResultadoSerializer

