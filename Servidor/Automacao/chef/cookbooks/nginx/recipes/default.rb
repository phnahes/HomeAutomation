#
# Cookbook Name:: nginx
# Recipe:: default
#

case node["platform"]
  when "ubuntu", "debian"
    include_recipe "nginx::light"
    include_recipe "nginx::config"
  when "centos", "redhat"
    package "nginx"
    include_recipe "nginx::config"
end
