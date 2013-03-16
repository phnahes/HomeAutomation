case platform
when "redhat","centos","fedora"
  set[:nginx][:user] = "nginx"
when "debian","ubuntu"
  set[:nginx][:user] = "www-data"
end

# cache 200 por padrao, excessoes deverao ser declaradas
set[:nginx][:cache_200] = "yes"
# 05 minutos de cache 200 por padrao
default[:nginx][:cache_valid] = "5m"
default[:nginx][:keys_zone_size] = "10m"

default[:nginx][:keepalive_timeout] = "0"
default[:nginx][:tcp_nodelay] = "no"
default[:nginx][:worker_processes] = "2"
default[:nginx][:worker_connections] = "2048"


# ulimit nao por padrao
default[:nginx][:ulimit] = "no" 
default[:nginx][:hard_limit] = "16384"
default[:nginx][:soft_limit] = "16384"

