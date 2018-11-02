import uuid

from django.db import models


class Transaction(models.Model):
    INIT = 1
    APPROVED = 2
    REJECTED = 3
    STATUS = (
        (INIT, 'Transaction initialized'),
        (APPROVED, 'Transaction approved'),
        (REJECTED, 'Transaction rejected'),
    )

    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    init_date = models.DateTimeField(auto_now_add=True)
    url = models.URLField()
    status = models.PositiveIntegerField(choices=STATUS, default=INIT)
