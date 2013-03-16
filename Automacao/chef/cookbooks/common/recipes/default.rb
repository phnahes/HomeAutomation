#
# Cookbook Name:: common
# Recipe:: default
#
#
# All rights reserved - Do Not Redistribute
#
#log "Atributos Common: ip=" + node[:common][:ipaddress] + " ambiente=" + node[:common][:ambiente] + " datacenter=" + node[:common][:datacenter] + " pool=" + node[:common][:pool] + " servico=" + node[:common][:servico]

log "Recipe: common"

include_recipe "common::staticfiles"
#include_recipe "common::resolv"
include_recipe "common::config"
#include_recipe "common::packages"
