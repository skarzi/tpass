from rest_framework import viewsets

from . import (
    models,
    serializers,
)


class TransactionsViewSet(viewsets.ModelViewSet):
    serializer_class = serializers.TransactionSerializer

    def get_queryset(self):
        return models.Transaction.objects.filter(
            status__in=(
                models.Transaction.APPROVED,
                models.Transaction.REJECTED,
            )
        ).order_by('-init_date')
