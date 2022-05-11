# pi-temp-c
## Temperature monitor for RaspBerry Pi.

### Usage:<br>
`./pi-temp [options]`<br>

### Options:<br>
`-c` : use "vcgencmd measure_temp" command, this is defualt.<br>
`-f` : read file /sys/class/thermal/thermal_zone0/temp<br>
`-d [NUM]` : delay in second between measures, this option should be used separetely, must be integer, default is 3.<br>
`-t` : print timestamp before temperature.<br>
`-l` : write results in file, default file./pi-temp.log<br>
<br>
Examples:<br>
`pi-temp -f -t -l -d 3`<br>
 

<p>P.S.<br>
BTW, here are:<br>
good shell script by Shahriar Shovon to monitor temp:<br>
https://linuxhint.com/raspberry_pi_temperature_monitor/<br>
useful, python, shell, c, pascal examples:<br>
https://www.pragmaticlinux.com/2020/06/check-the-raspberry-pi-cpu-temperature/<br></p>
and good exapmles by Vivek Gite:<br>
https://www.cyberciti.biz/faq/linux-find-out-raspberry-pi-gpu-and-arm-cpu-temperature-command/<br>
