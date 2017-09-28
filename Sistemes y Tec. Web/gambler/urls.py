from django.views.generic import TemplateView
from django.conf.urls import patterns, url, include
from rest_framework import routers

from gambler.views import *
from gambler.views import APIPartidoDetail, APIResultadoDetail
from gambler.forms import *


# RESTful API
router = routers.DefaultRouter()
router.register(r'partidos', PartidoList2)
router.register(r'equipos', EquipoList2)
router.register(r'apuestas', ApuestaList2)
router.register(r'resultados', ResultadoList2)

urlpatterns = patterns('gambler.views',

                       url(r'^api/', include(router.urls)),
                       url(r'^api/partidos/(?P<pk>\d+)/$',
                           APIPartidoDetail.as_view(),
                           name='partido-detail'),

                       url(r'^api/resultados/(?P<pk>\d+)/$',
                           APIResultadoDetail.as_view(),
                           name='resultado-detail'),

                       # Non RESTful API

                       # Home Page /gambler/
                       url(r'^$',
                           TemplateView.as_view(template_name='base.html'),
                           name='base'),

                       # List latest 5 apuestas: /gambler/apuestas
                       url(r'^apuestas$',
                           ApuestaList.as_view(),
                           name='apuestas_list'),

                       # List latest 5 partidos: /gambler/partidos
                       url(r'^partidos$',
                           PartidoList.as_view(),
                           name='partidos_list'),

                       # List latest 5 equipos: /gambler/equipos
                       url(r'^equipos$',
                           EquipoList.as_view(),
                           name='equipos_list'),

                       # List latest 5 resultados: /gambler/equipos
                       url(r'^resultados$',
                           ResultadoList.as_view(),
                           name='resultados_list'),

    # List partidos: /gambler/partidos.json
        url(r'^partidos\.(?P<extension>(json| xml))$',
        PartidoList.as_view(),
        name='partido_list_conneg'),

    # List equipos: /gambler/equipos.json
    url(r'^equipos\.(?P<extension>(json|xml))$',
        EquipoList.as_view(),
        name='equipo_list_conneg'),

    # List apuestas: /gambler/apuestas.json
    url(r'^apuestas\.(?P<extension>(json|xml))$',
        ApuestaList.as_view(),
        name='apuesta_list_conneg'),

    # List resultados: /gambler/resultados.json
    url(r'^resultados\.(?P<extension>(json|xml))$',
        ResultadoList.as_view(),
        name='resultado_list_conneg'),

    # Partido details, ex.: /gambler/partido/1/
    url(r'^partido/(?P<pk>\d+)/$',
        PartidoDetail.as_view(),
        name='partido_detail'),

    # Partido details, ex.: /gambler/partido/1.json
    url(r'^partido/(?P<pk>\d+)\.(?P<extension>(json|xml))$',
        PartidoDetail.as_view(),
        name='partido_detail_conneg'),

    # Apuesta details, ex.: /gambler/partido/1/
    url(r'^apuesta/(?P<pk>\d+)/$',
        ApuestaDetail.as_view(),
        name='apuesta_detail'),

    # Apuesta details, ex.: /gambler/apuesta/1.json
    url(r'^apuesta/(?P<pk>\d+)\.(?P<extension>(json|xml))$',
        ApuestaDetail.as_view(),
        name='apuesta_detail_conneg'),

    # Create a apuesta, ex: /gambler/partido/1/apuesta/create/
    url(r'^partido/(?P<pk>\d+)/apuesta/create/$',
        ApuestaCreate.as_view(),
        name='apuesta_create'),

    # Create a resultado, ex: /gambler/resultado/create/
    url(r'^resultado/create/$',
        ResultadoCreate.as_view(),
        name='resultado_create'),

    # Resultado details, ex.: /gambler/resultado/1/
    url(r'^resultado/(?P<pk>\d+)/$',
        ResultadoDetail.as_view(),
        name='resultado_detail'),


       url(r'^equipos_estatico$',
           EquipoBusqueda.as_view(),
           name='equipos_estatico'),

        url(r'^equipos_dinamico$',
           EquipoBusqueda.as_view(),
           name='equipos_dinamico'),
)
