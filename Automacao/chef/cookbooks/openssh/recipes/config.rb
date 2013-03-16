#
# Cookbook Name:: openssh
# Recipe:: config
#

template node[:openssh][:ssh_config] do
  source "ssh_config.erb"
  mode "0644"
  owner "root"
  group "root"
end

template node[:openssh][:sshd_config] do
  source "sshd_config.erb"
  mode "0644"
  owner "root"
  group "root"
  variables(
    :allow_users => node[:openssh][:allow_users],
    :allow_groups => node[:openssh][:allow_groups],
    :deny_users => node[:openssh][:deny_users],
    :deny_groups => node[:openssh][:deny_groups]
  )
  notifies :restart, resources(:service => "sshd")
end

# hold no pacote com patch do openssh

case node.platform
  when "debian","ubuntu"
    template "/etc/apt/preferences.d/openssh-lpk" do
      owner "root"
      group "root"
      mode "0644"
      source "openssh-lpk.erb"
    end
end
