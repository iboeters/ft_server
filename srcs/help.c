/*
first
remove containers:
docker container rm [ID] -f
docker stop $(docker ps -a -q)
docker rm $(docker ps -a -q) -f

remove images:
docker rmi [ID] -f
docker rmi $(docker images -a -q) -f

docker stop $(docker ps -a -q)  && docker rm $(docker ps -a -q) -f && docker rmi $(docker images -a -q) -f

docker container runnen stappen:
1. create image
docker image build -t mynginx . -q
-q: Suppress the build output and print image ID on success
2. run container
docker container run -it -p 80:80 -p 443:443 mynginx
-d = detach / run on background
--> otherwise prompt wont return without killing the container
-p = specify port
--> port 80 on the container to port 80 on the host
afterwards: container ID is displayed

docker container ps
docker container ps -a
-a: the ones that are not active

port 334 nodig voor https om te werken; 80 voor http
debian OS heeft minste dingen, zoals vim en nano

basic html abbrevation: type ! + right mouseclick

with nginx, the web root is gonna be usr/share/nginx/html:
-> hierin zit de index.html file met welcome to nginx

verschil apt en apt-get: sommige systemen gaat apt mis
-y: betekend yes zeggen als ze erom vragen
@voor command makefile = output niet laten zien

ssl voor 443 alleen?
in /etc/nginx/nginx.conf: include /etc/nginx/sites-enabled/*;

when copying files: last backslash to copy more than one file: directory

copy all html files to webroot
COPY srcs/index.html /usr/share/nginx/html/
COPY srcs/*.html /usr/share/nginx/html/

tar:
-x: extract files from archive
-z: needed for files with the extension .tar.gz to read/write archives through gzip
-v: verbosely = uitgebreid: displays/gets more information
-C: change to directory before performing any operations

get self signed certificate : self-signed certificate generator
https://linux.die.net/man/1/mysql
https://github.com/Tishj/ft_server/blob/master/Dockerfile
https://www.phpmyadmin.net/downloads/
https://www.google.com/search?q=phpymadmin+deffault+config&oq=phpymadmin+deffault+config&aqs=chrome..69i57j0l7.4900j0j7&sourceid=chrome&ie=UTF-8
https://kifarunix.com/install-phpmyadmin-with-nginx-on-debian-10-buster/#:~:text=Navigate%20to%20your%20browser%20and,manage%20your%20MariaDB%2FMySQL%20databases.

all info for website is stored in a mysql database
wordpress uses php to store and retrieve info from that database
php code unable to connect with mysql database

# install wget (after install!)
# system: get new lists of packages from sources.list & upgrade installed packages to newer version
COPY srcs/info.php /var/www/html/
FLUSH PRIVILEGES = # reload privileges
sendmail: wordpress error: sh: 1: /usr/sbin/sendmail: not found
# see /etc/nginx/sites-available/default for default nginx configuration
# RUN rm /etc/nginx/sites-enabled/default
# RUN cp -r phpMyAdmin-4.9.4-english/* /var/www/html/phpmyadmin/
# RUN cp -r /var/www/localhost/phpmyadmin/phpMyAdmin-4.9.4-english/* /var/www/localhost/phpmyadmin
# wp cli to use wp as a command: wordpress command line interface
# WORKDIR /var/www/html/wordpress/
#RUN chmod +x var/www/html/wordpress/wp-cli.phar
#RUN mv var/www/html/wordpress/wp-cli.phar /usr/local/bin/wp
# RUN service mysql start && \
#  	wp core install --url=localhost --title="welcome" --admin_name=iboeterss --admin_password=irisannamariadb104 --admin_email=iboeters@student.codam.nl --allow-root
# start nginx service & set up interactive shell/bash into nginx container. CMD mag maar 1x! daarom start.sh
#WORKDIR /root/
	ssl_certificate /root/mkcert/localhost.pem;
	ssl_certificate_key /root/mkcert/localhost-key.pem;

# # Get SSL certifier
# RUN wget -O mkcert https://github.com/FiloSottile/mkcert/releases/download/v1.3.0/mkcert-v1.3.0-linux-amd64
# RUN chmod +x mkcert
# RUN mv mkcert /usr/local/bin/
# RUN mkcert -install
# # Make SSL certificate and key
# RUN mkcert localhost
# RUN mkdir /root/mkcert/
# RUN mv localhost.pem /root/mkcert/
# RUN mv localhost-key.pem /root/mkcert/

sed -i: edit files in place:
docker exec -it 32d901888b3b bash /switch_autoindex.sh 0

# voor evaluatie bash weghalen en -g "deamon off" in start.sh aangeven na nginx
service nginx -g "daemon off;"
docker exec -it 043a9572775f bash /switch_autoindex.sh 0
 */