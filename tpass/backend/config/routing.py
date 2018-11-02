from apps.transactions import routing as transactions_routing
from channels.auth import AuthMiddlewareStack
from channels.routing import (
    ProtocolTypeRouter,
    URLRouter,
)

application = ProtocolTypeRouter({
    'websocket': AuthMiddlewareStack(
        URLRouter(
           transactions_routing.websocket_urlpatterns
        ),
    ),
})
