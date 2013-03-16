hostname = node[:hostname]
ipaddress = node[:ipaddress]

datacenter = "default"

# DNS / Servidor de repositorios
dnsdomains = [ "nahes.com.br" ]
nameservers = [ "8.8.8.8", "8.8.4.4" ]
reposerver = "http://pkg.nahes.com.br"

set[:common][:dnsdomains] = dnsdomains
set[:common][:nameservers] = nameservers
set[:common][:reposerver] = reposerver

# Particularidades de cada distro
case platform
  when "centos", "redhat"
    set[:common][:default_pkgs] = ["yum", "yum-utils", "yum-priorities" ]
    set[:common][:removed_pkgs] = []
    set[:common][:profile_file] = "profile_centos"
    set[:common][:motd_file] = "/etc/motd"
  when "ubuntu","debian"
    set[:common][:default_pkgs] = ["vim", "debsums", "sysstat", "statgrab", "sysv-rc-conf", "screen", "ccze", "apticron", "grc", "htop", "dstat"]
    set[:common][:removed_pkgs] = [ "libaugeas-ruby1.8", "libaugeas0", "augeas-lenses", "facter", "puppet-common"]
    set[:common][:profile_file] = "profile_debian"
    set[:common][:motd_file] = "/etc/motd"
    #set[:common][:motd_file] = "/etc/motd.tail"
end

## Define a cor do bash
#if hostname == "i-d2032ecf"
#	set[:common][:prompt] = "33" # Vermelho para Servidor
#else 
#	set[:common][:prompt] = "34" # Verde para Pontos
#end
