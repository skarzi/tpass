import uuid

from asgiref.sync import async_to_sync
from channels.generic.websocket import JsonWebsocketConsumer

from . import (
    models,
    serializers,
)


class TransactionsJSONConsumer(JsonWebsocketConsumer):
    def connect(self):
        self.transaction_id = self.scope['url_route']['kwargs'][
            'transaction_id'
        ]
        self.transaction_id = uuid.UUID(self.transaction_id, version=4).hex
        print(f'Connecting to "{self.transaction_id}" group.')
        async_to_sync(self.channel_layer.group_add)(
            self.transaction_id,
            self.channel_name,
        )
        self.accept()

    def disconnect(self, close_code):
        print(
            f'Leaving "{self.transaction_id}" group with close code - '
            f'{close_code}.'
        )
        if self.transaction_id is not None:
            async_to_sync(self.channel_layer.group_discard)(
                self.transaction_id,
                self.channel_name,
            )

    def receive_json(self, content, **kwargs):
        type_ = f"transaction_{content.get('status', 'init')}"
        print(
            f'Receive data in group "{self.transaction_id}": {content}'
            f' with type "{type_}"'
        )
        async_to_sync(self.channel_layer.group_send)(
            self.transaction_id,
            {
                'type': type_,
                'data': content,
            },
        )

    def transaction_init(self, event):
        transaction, created = models.Transaction.objects.get_or_create(
            id=self.transaction_id,
            defaults={
                'url': event['data']['url'],
                'status': models.Transaction.INIT,
            },
        )
        print('created transaction: {transaction}')
        serializer = serializers.TransactionSerializer(transaction)
        self.send_json(content={'data': serializer.data})

    def transaction_approved(self, event):
        transaction = models.Transaction.objects.get(id=self.transaction_id)
        transaction.status = models.Transaction.APPROVED
        transaction.save()
        serializer = serializers.TransactionSerializer(transaction)
        self.send_json(content={'data': serializer.data})

    def transaction_rejected(self, event):
        transaction = models.Transaction.objects.get(id=self.transaction_id)
        transaction.status = models.Transaction.REJECTED
        transaction.save()
        serializer = serializers.TransactionSerializer(transaction)
        self.send_json(content={'data': serializer.data})
