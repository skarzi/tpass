FROM python:3.7-slim

ENV PYTHONUNBUFFERED 1

RUN apt-get -qq update \
    && apt-get -qq -y install \
        bash \
        gcc \
        gettext \
        less \
        libcairo2 \
        libffi-dev \
        libfreetype6-dev \
        libjpeg-dev \
        libpango1.0-0 \
        libpng-dev \
        libpq-dev \
        vim \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get -qq -y clean

COPY ./docker/backend/production/entrypoint.sh /entrypoint.sh
RUN sed -i 's/\r//' /entrypoint.sh \
    && chmod +x /entrypoint.sh

COPY ./docker/backend/local/start.sh /start.sh
RUN sed -i 's/\r//' /start.sh \
    && chmod +x /start.sh

COPY ./backend/requirements /requirements/
RUN pip install --no-cache-dir -r /requirements/local.txt \
    && rm -rf /requirements

COPY ./shared/ /app/shared/
COPY ./backend /app

WORKDIR /app

ENTRYPOINT ["/entrypoint.sh"]
CMD ["/start.sh"]

