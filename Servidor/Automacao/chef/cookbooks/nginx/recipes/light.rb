package "nginx-light" do
    options "--force-yes"
end

service "nginx" do
    action [:enable, :start]
end

include_recipe "nginx::config"
