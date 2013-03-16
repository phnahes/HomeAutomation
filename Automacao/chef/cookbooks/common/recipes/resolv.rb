#
# Cookbook Name:: resolv
# Recipe:: install
#
# Copyright 2011, 
#
# All rights reserved - Do Not Redistribute
#

template "/etc/resolv.conf" do
    owner "root"
    group "root"
    mode "644"
    source "resolv.conf.erb"
end
