#!/bin/bash

arch=$(uname -a)
tcp_connections=$(ss -t state established | wc -l)
count=$(echo "$tcp_connections - 1" | bc)

pCPU=$(cat /proc/cpuinfo | grep 'processor' | wc -l)

vCPU=$(nproc)

mem_used=$(free -m | grep -i mem | awk -F' ' '{print $3}')
mem_total=$(free -m | grep -i mem | awk -F' ' '{print $2}')
mem_final=$(echo "scale=2; ($mem_used/$mem_total) * 100" | bc)

total_disk=$(df -h --block-size=G --total | tail -n 1 | awk -F' ' '{print $2}' | cut -d'G' -f1)
total_percent=$(df -h --block-size=G --total | tail -n 1 | awk -F' ' '{print $5}')
total_disk_used=$(df -h --block-size=G --total | tail -n 1 | awk -F' ' '{print $3}' | cut -d'G' -f1)

cpu_load=$(mpstat 1 1 | tail -n2 | head -n1 | awk '/all/ {printf "%.2f", 100 - $NF}')

last_boot=$(who -b | awk -F' ' '{print $3 " " $4}')

lvm_use=$(lsblk | grep ' lvm ')
y_or_n='no'
if [[ -n $lvm_use ]];then
	y_or_n='yes'
else
	y_or_n='no'
fi

log_count=$(echo "$(w | wc -l) - 2" | bc) 

ip=$(ip a | grep enp | grep inet | awk -F'/' '{print $1}' | awk -F' ' '{print $2}')
mac=$(ip a | grep ether | awk -F' ' '{print $2}')

cmd_count=$(echo "obase=10;ibase=36;$(cat /var/log/sudo/seq)" | bc)

wall "	#Architecture: $arch
	#CPU Physical : $pCPU
	#vCPU : $vCPU
	#Memory Usage: $mem_used/${mem_total}MB (${mem_final}%)
	#Disk Usage: ${total_disk_used}/${total_disk}Gb (${total_percent})
	#CPU Load: ${cpu_load}%
	#Last boot: ${last_boot}
	#LVM use: $y_or_n
	#Connections TCP : $count ESTABLISHED
	#User log: $log_count
	#Network: $ip (${mac})
	#Sudo : $cmd_count cmd"
