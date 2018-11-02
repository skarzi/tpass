from django.apps import AppConfig


class TransactionsConfig(AppConfig):
    name = 'apps.transactions'
    verbose_name = "Transactions"

    def ready(self):
        """
        Override this to put in:
        - Transactions system checks
        - Transactions signal registration
        """
