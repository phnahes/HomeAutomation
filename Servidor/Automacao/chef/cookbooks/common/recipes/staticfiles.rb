#
# Cookbook Name:: common
# Recipe:: staticfiles
#
#
# All rights reserved - Do Not Redistribute
#

directory "/data" do
    owner "root"
    group "root"
    mode "0755"
end

# Dir base de Logs
directory "/data/logs" do
    owner "root"
    group "root"
    mode "0755"
end

# Dir base de Scripts
directory "/data/scripts" do
    owner "root"
    group "root"
    mode "0755"
end

# Mensagem de entrada de servidores 
cookbook_file node[:common][:motd_file] do
    source "motd"
    owner "root"
    group "root"
    mode "0644"
end

# Preferencias gerais do bash (historico, prompt, etc)
template "/etc/profile.d/prefs.sh" do
    owner "root"
    group "root"
    mode "0644"
    source "prefs.sh.erb"
end

# Arquivo vazio de bash_history com permissoes 600 para novos homes
file "/etc/skel/.bash_history" do
    owner "root"
    group "root"
    mode "0600"
end

# Known hosts com todas as chaves das maquinas
#remote_file "/etc/ssh/ssh_known_hosts" do
#  owner "root"
#  group "root"
#  mode "0644"
#  action :create
#  backup false
#  source "http://chef.nahes.com.br/shared/ssh_known_hosts"
#end

# Especificos para cada distribuicao
case node[:platform]
    when "redhat", "centos"
        # Desabilitando o SELinux sempre
        template "/etc/selinux/config" do
            owner "root"
            group "root"
            mode "0644"
            source "selinux_config.erb"
        end
    when "debian", "ubuntu"
      # SH apontando pro bash
      link "/bin/sh" do
        to "/bin/bash"
        owner "root"
        group "root"
      end
      cookbook_file "/etc/apt/apt.conf.d/local" do
       source "local"
       owner "root"
       group "root"
       mode "0644"
     end
end

