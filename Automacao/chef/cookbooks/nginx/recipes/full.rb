package "nginx-full" do
    options "--force-yes"
end
include_recipe "nginx::config"

