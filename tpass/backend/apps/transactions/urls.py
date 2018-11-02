from django.urls import include

from rest_framework.routers import SimpleRouter

from . import views

router = SimpleRouter()
router.register('', views.TransactionsViewSet, base_name='transaction')


urlpatterns = router.urls
