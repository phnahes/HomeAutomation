case node["platform"]
when "redhat","centos"

#  # Usar prod quando com tag
#  if tagged?('reposerver-prod')
#    reposerver = "http://pkg.nahes.com.br"
#  else
#    reposerver = node[:common][:reposerver]
#  end
#
#  # Arquivo de configuracao principal do yum
#  cookbook_file "/etc/yum.conf" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum.conf"
#  end
#
#  # Prioridades do yum
#  cookbook_file "/etc/yum/pluginconf.d/priorities.conf" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum-priorities.conf"
#  end
#
#  directory "/etc/yum.repo.d" do
#    owner "root"
#    group "root"
#    mode "0755"
#  end
#
#  template "/etc/yum.repos.d/os.repo" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum/" + node[:platform] + "/os.repo.erb"
#    variables(
#      :reposerver => reposerver
#    )
#  end
#
#  template "/etc/yum.repos.d/epel.repo" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum/epel.repo.erb"
#    variables(
#      :reposerver => reposerver
#    )
#  end
#
#  template "/etc/yum.repos.d/nahes.repo" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum/nahes.repo.erb"
#    variables(
#      :reposerver => reposerver
#    )
#  end
#
#  template "/etc/yum.repos.d/3rd.repo" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum/3rd.repo.erb"
#    variables(
#      :reposerver => reposerver
#    )
#  end
#
#  template "/etc/yum.repos.d/ius.repo" do
#    owner "root"
#    group "root"
#    mode "0644"
#    source "yum/ius.repo.erb"
#    variables(
#      :reposerver => reposerver
#    )
#  end
#
#  [ "nahes-prod.repo", "nahes-dev.repo", "Citrix.repo", "CentOS-Base.repo", "CentOS-Debuginfo.repo", "CentOS-Media.repo", "CentOS-Vault.repo" ].each do |arquivo|
#    cookbook_file "/etc/yum.repos.d/" + arquivo do
#      action :delete
#    end
#  end

  node[:common][:default_pkgs].each do |pkg|
    package pkg
  end

  node[:common][:removed_pkgs].each do |pkg|
    package pkg do
      action :purge
    end
  end
when "debian", "ubuntu"


  %w[ nahes.list ].each do |cfg|
    template "/etc/apt/sources.list.d/#{cfg}" do
      source cfg
      mode "0644"
      owner "root"
      group "root"
    end
  end

  execute "apt-key" do
    command "/usr/bin/apt-get update 1> /tmp/chef-last-apt-key.log 2>&1"
  end

#  %w[ repo.list 3rd.list opscode.list partner.list ].each do |cfg|
#    template "/etc/apt/sources.list.d/#{cfg}" do
#      source cfg
#      mode "0644"
#      owner "root"
#      group "root"
#    end
#  end
#
#  execute "apt-key" do
#    command "/usr/bin/apt-get update"
#  end
#
#  template "/etc/apt/sources.list" do
#    source "sources.list"
#    mode "0644"
#    owner "root"
#    group "root"
#  end
#
#  cookbook_file "/etc/apt/listchanges.conf" do
#    source "listchanges.conf"
#    mode "0644"
#    owner "root"
#    group "root"
#  end

  node[:common][:default_pkgs].each do |pkg|
    package pkg do
      options "--force-yes"
    end
  end

  node[:common][:removed_pkgs].each do |pkg|
    package pkg do
      action :purge
      options "--force-yes"
    end
  end

#  template "/etc/apticron/apticron.conf" do
#    source "apticron.conf"
#    mode "0644"
#    owner "root"
#    group "root"
#  end
#
#  service "postfix" do
#    action [:enable, :start]
#    supports :status => true, :start => true, :restart => true
#  end  
#
#  if node[:fqdn] != "guri1.nahes.com.br" 
#   %w[canonical-table main.cf].each do |cfg|
#     template "/etc/postfix/#{cfg}" do
#       source cfg
#       mode "0644"
#       owner "root"
#       group "root"
#       notifies :restart, resources(:service => "postfix")
#     end
#   end
#  end
#
#  execute "canonical-table" do
#    command "/usr/sbin/postmap /etc/postfix/canonical-table"
#    creates "/etc/postfix/canonical-table.db"
#    action :run
#    notifies :restart, resources(:service => "postfix")
#  end
#
#  file "/etc/apt/apt.conf.d/20listchanges" do
#    action :delete
#  end
end
