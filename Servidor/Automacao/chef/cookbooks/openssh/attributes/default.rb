case platform
when "redhat","centos"
  set[:openssh][:os]                = "redhat"
  set[:openssh][:pkgs_install]      = [ "openssh-clients", "openssh" ]
  set[:openssh][:srv_pkgs_install]  = [ "openssh-server" ]
  set[:openssh][:ssh_confdir]       = "/etc/ssh"
  set[:openssh][:ssh_config]        = "/etc/ssh/ssh_config"
  set[:openssh][:sshd_config]       = "/etc/ssh/sshd_config"
  set[:openssh][:sshd_libexecpath]  = "/usr/libexec/openssh"
  set[:openssh][:sshd_service]      = "sshd"
  set[:openssh][:lpk]               = "yes"
  set[:openssh][:lpk_ldapconf]      = "/etc/ldap.conf"
  set[:openssh][:motd]		    = "yes"
when "debian","ubuntu"
  set[:openssh][:os]                = "ubuntu"
  set[:openssh][:pkgs_install]      = [ "openssh-client", "openssh-server" ]
  #set[:openssh][:srv_pkgs_install]  = [ "openssh-server" ]
  set[:openssh][:ssh_confdir]       = "/etc/ssh"
  set[:openssh][:ssh_config]        = "/etc/ssh/ssh_config"
  set[:openssh][:sshd_config]       = "/etc/ssh/sshd_config"
  set[:openssh][:sshd_libexecpath]  = "/usr/lib/openssh"
  set[:openssh][:sshd_service]      = "ssh"
  set[:openssh][:motd]		    = "no"
  case chef_environment
  when "devel","homol"
    set[:openssh][:lpk]               = "yes"
    set[:openssh][:lpk_ldapconf]      = "/etc/ldap.conf"
  when "prod"
    set[:openssh][:lpk]               = "no"
    set[:openssh][:lpk_ldapconf]      = "/etc/ldap.conf"
  end
end

set[:openssh][:srv_port]            = "22"
set[:openssh][:x11forwarding]       = "yes"
set[:openssh][:allow_users]         = []
set[:openssh][:allow_groups]        = []
set[:openssh][:deny_users]          = []
set[:openssh][:deny_groups]         = []
