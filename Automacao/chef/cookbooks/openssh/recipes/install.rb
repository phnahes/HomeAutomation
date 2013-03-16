#
# Cookbook Name:: openssh
# Recipe:: install
#

node[:openssh][:pkgs_install].each do |pkg|
  package pkg do
	case node.platform
	 when "redhat","centos"
    	   action :upgrade
	 when "debian","ubuntu"
#	   version "1:5.3p1-3ubuntu3lpk0"
	   options "--force-yes"
#	   node[:openssh][:lpk] = "yes"
#	   node[:openssh][:lpk_ldapconf] = "/etc/ldap.conf"
	end
  end
end

service "sshd" do
    service_name node[:openssh][:sshd_service]
    supports :status => true,
             :restart => true,
             :reload => true
    action [ :enable, :start ]
end
