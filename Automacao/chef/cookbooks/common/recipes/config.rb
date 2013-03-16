cookbook_file "/etc/profile" do
  source node[:common][:profile_file]
  mode "0644"
  owner "root"
  group "root"
end

template "/etc/profile.d/bash_color.sh" do
    source "bash_color.sh.erb"
    mode "0600"
    owner "root"
    group "root"
end

file "/root/.bashrc" do
  action :delete
end
