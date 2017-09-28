from django.conf.urls import patterns, include, url
from django.conf import settings

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
from gambler import views

admin.autodiscover()

urlpatterns = patterns('',
    url(r'^accounts/', include('registration.backends.simple.urls')),
    url(r'^gambler/', include('gambler.urls', namespace='gambler')),
    url(r'^accounts/login/$', 'django.contrib.auth.views.login'),
    url(r'^accounts/logout/$', 'django.contrib.auth.views.logout'),
    url(r'^admin/', include(admin.site.urls)),
    (r'^search/$', views.search),
)