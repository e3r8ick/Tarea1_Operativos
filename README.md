# Tarea Corta 1 Principios de SO

## Instalaciones Previas
```
sudo apt-get install libmicrohttpd-dev
```

## Intrucciones de uso
Para ver los puertos abiertos
```
nmap localhost
fuser -k puerto/tcp
```

## Configurar el demonio
Abra con su editor favorito el archivo ./daemon-scripts/ImageServer.service actualice los paths de las variables ExecStart y ExecStop a la dirección exacta en su computadora a los scripts ./daemon-scripts/start.sh respectivamente y ./daemon-scripts/start.sh

Copie el archivo ./daemon-scripts/ImageServer.service al directorio /etc/systemd/system/

## Administrar el demonio

```
systemctl start ImageServer
systemctl stop ImageServer
systemctl restart ImageServer
```
Para agregar ImageServer a los servicios que inician con el inicio del sistemas utilice el comando
``` 
systemctl enable ImageServer
```

Para revisar si está actualmente habilitado para el incio del sistema puede utlizar el siguiente comando
```
systemctl is-enabled ImageServer
```
