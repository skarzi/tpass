from django.urls import path

from . import consumers

websocket_urlpatterns = [
    path(
        'ws/transactions/<str:transaction_id>',
        consumers.TransactionsJSONConsumer,
    ),
]
