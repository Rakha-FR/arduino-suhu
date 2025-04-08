#!/bin/bash

composer update

chown -R www-data:www-data /var/www/storage
chown -R www-data:www-data /var/www/bootstrap/cache
chmod -R 775 /var/www/storage
chmod -R 775 /var/www/bootstrap/cache

if grep -q "^APP_KEY=$" /var/www/.env; then
  echo "APP_KEY kosong, menjalankan php artisan key:generate..."
  php artisan key:generate
else
  echo "APP_KEY sudah terisi, skip php artisan key:generate"
fi

php artisan migrate

php-fpm
