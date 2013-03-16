service "nginx" do
	supports :status => true, :restart => true, :start => true, :reload => true
	action :enable
end

template "/etc/nginx/nginx.conf" do
	source "nginx.conf.erb"
	owner "#{node[:nginx][:user]}"
	group "#{node[:nginx][:user]}"
	mode "0644"
	notifies :reload, resources(:service => "nginx")
end

directory "/data/nginx/cache/" do
	recursive true
	owner "www-data"
	group "www-data"
	mode "0775"
end

service "nginx" do
  action :start
end

# script personalite para ulimit no ubuntu
case node[:platform]
when "debian", "ubuntu"
  template "/etc/init.d/nginx" do
    source "init-nginx-ubuntu.erb"
    owner "root"
    group "root"
    mode "0755"
  end
end


# script para cache
cookbook_file "/usr/local/bin/nginx_cache" do
    source "nginx_cache"
    owner "root"
    group "root"
    mode "0755"
end

