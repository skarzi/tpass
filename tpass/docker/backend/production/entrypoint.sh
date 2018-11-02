#!/usr/bin/env bash

set -o errexit
set -o pipefail
# set -o nounset


cmd="$*"


migrate() {
    python manage.py migrate --noinput
}


collectstatic() {
    python manage.py collectstatic --clear --no-input
}


case "$cmd" in
    migrate)
        migrate
    ;;
    collectstatic)
        collectstatic
    ;;
    *)
        $cmd  # usage start.sh or gunicorn.sh
    ;;
esac
