# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Dockerfile                                         :+:    :+:             #
#                                                      +:+                     #
#    By: iboeters <iboeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/24 14:14:21 by iboeters       #+#    #+#                 #
#    Updated: 2020/03/11 16:21:01 by iboeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Debian buster as container OS
FROM debian:buster

EXPOSE 80 443 110

# System update
RUN apt-get update -y
RUN apt-get upgrade -y

# Install tools
RUN apt-get install wget -y
RUN apt-get install sendmail -y

# Install Nginx
RUN apt-get install nginx -y
COPY srcs/nginx.conf /etc/nginx/sites-available/
RUN ln -s /etc/nginx/sites-available/nginx.conf /etc/nginx/sites-enabled/

# Copy sources
RUN mkdir /var/www/html/wordpress/
RUN mkdir /var/www/html/wordpress/phpmyadmin/
RUN mkdir /var/www/html/wordpress/menu/
COPY srcs/index.html /var/www/html/wordpress/menu/
RUN mkdir /root/mkcert/
COPY srcs/localhost.cert /root/mkcert/
COPY srcs/localhost.key /root/mkcert/
COPY srcs/switch_autoindex.sh .

# Change owner
RUN chown www-data:www-data /var/www/html/wordpress/ -R
RUN chown www-data:www-data /usr/share/nginx/html/ -R

# Install MariaDB server
RUN apt-get install mariadb-server -y
# Enable password based authentication
RUN service mysql start && \
	echo "CREATE DATABASE wordpress;" | mysql -u root && \
	echo "GRANT ALL PRIVILEGES ON *.* TO 'iboeters'@'localhost' IDENTIFIED BY 'irisannamariadb';" | mysql -u root && \
	echo "FLUSH PRIVILEGES" | mysql -u root

# Install phpMyAdmin + phpMyAdmin apache + MySQL extensions
RUN apt-get install php7.3 php7.3-fpm php7.3-mysql php-common php7.3-cli php7.3-common php7.3-json php7.3-opcache php7.3-readline php7.3-mbstring -y
RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.4/phpMyAdmin-4.9.4-english.tar.gz
RUN tar -xzf phpMyAdmin-4.9.4-english.tar.gz -C /var/www/html/wordpress/phpmyadmin/ --strip-components 1
COPY /srcs/config.inc.php /var/www/html/wordpress/phpmyadmin/

# Install WordPress
RUN wget https://wordpress.org/latest.tar.gz
RUN tar -xzf latest.tar.gz -C /var/www/html/wordpress/ --strip-components 1
RUN rm /var/www/html/wordpress/wp-config-sample.php
COPY /srcs/wp-config.php /var/www/html/wordpress/
RUN chmod 755 /var/www/html/wordpress/
# Get WordPress command line interface
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN wp core download --allow-root
WORKDIR	/var/www/html/wordpress/
RUN service mysql restart && \
	mysql < /var/www/html/wordpress/phpmyadmin/sql/create_tables.sql && \
	wp core install --url=localhost --title="Hello world!" --admin_name=iboeterss --admin_password=irisannamariadb104 --admin_email=iboeters@student.codam.nl --allow-root

# Change owner and rights
RUN chown -R www-data /var/www/html/wordpress/wp-content/ && \
	chmod 755 /var/www/html/wordpress/* -R

# Change upload size
RUN cd /etc/php/7.3/fpm && sed -i 's/upload_max_filesize = 2M/upload_max_filesize = 10M/g' php.ini && \
	sed -i 's/post_max_size = 8M/post_max_size = 20M/g' php.ini

# Start Nginx, MySQL and PHP MyAdmin
COPY srcs/start.sh /var/
RUN chmod 755 /var/start.sh
CMD /var/start.sh && bash
