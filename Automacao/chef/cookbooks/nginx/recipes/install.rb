#puts "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

case node[:platform]
when "debian", "ubuntu"
  package "nginx" do
      options "--force-yes"
  end
when "fedora", "centos", "redhat"
  package "nginx"
end

include_recipe "nginx::config"

