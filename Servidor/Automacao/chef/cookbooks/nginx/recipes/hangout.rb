include_recipe "nginx"

template "/etc/nginx/conf.d/hangout.conf" do
	source "hangout/hangout.conf.erb"
	owner "#{node[:nginx][:user]}"
	group "#{node[:nginx][:user]}"
	mode "0644"
#	notifies :reload, resources(:service => "nginx")
end


