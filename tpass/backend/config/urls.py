from itertools import chain

from django.conf import settings
from django.conf.urls.static import static
from django.urls import (
    include,
    path,
)
from django.views import defaults as default_views

urlpatterns = [
    path('healthz/', include('health_check.urls')),
]

# Custom urls includes go here
custom_urlpatterns = [
    path('transactions/', include('apps.transactions.urls')),
]

urlpatterns = list(chain(
    urlpatterns,
    custom_urlpatterns,
    static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT),
))


if settings.DEBUG:
    # This allows the error pages to be debugged during development, just visit
    # these url in browser to see how these error pages look like.
    urlpatterns += [
        path(
            '400/',
            default_views.bad_request,
            kwargs={'exception': Exception('Bad Request!')},
        ),
        path(
            '403/',
            default_views.permission_denied,
            kwargs={'exception': Exception('Permission Denied')},
        ),
        path(
            '404/',
            default_views.page_not_found,
            kwargs={'exception': Exception('Page not Found')},
        ),
        path('500/', default_views.server_error),
    ]
    if 'debug_toolbar' in settings.INSTALLED_APPS:
        import debug_toolbar
        urlpatterns = list(chain(
            [path('__debug__/', include(debug_toolbar.urls))],
            urlpatterns,
        ))
