# pi-temp-c
## Temperature monitor for RaspBerry Pi.
Created for C and GitHub learning.

### Usage:<br>
`./[program name] [options]`<br>

### Options:<br>
`-c`       : use "vcgencmd measure_temp" command, this is defualt.<br>
`-f`       : read file /sys/class/thermal/thermal_zone0/temp. This mode is lower on RES and should work on most Debian/Ubuntu.<br>
`-d [NUM]` : delay in second between measures, this option should be used separetely, must be integer, default is 2.<br>
`-t`       : print timestamp before temperature.<br>
`-r`	      :	use monitor mode instead of history mode.<br>
`-h`, `--help`	: show this help.<br>
<br>
Examples:<br>
`pi-temp -f -t -l -d 3`<br>
 
### Instalation:
Option A:
1) Download source file pi-temp.c
2) Compile it: `gcc pi-temp.c -o pi-temp`
3) Run `./pi-temp -h`

Option B:
1) Just download executable/release
2) Run it: `./pi-temp -h`

<br>
<p>P.S.<br>
BTW, here are:<br>
good shell script by Shahriar Shovon to monitor temp:<br>
https://linuxhint.com/raspberry_pi_temperature_monitor/<br>
useful, python, shell, c, pascal examples:<br>
https://www.pragmaticlinux.com/2020/06/check-the-raspberry-pi-cpu-temperature/<br>
and good exapmles by Vivek Gite:<br>
https://www.cyberciti.biz/faq/linux-find-out-raspberry-pi-gpu-and-arm-cpu-temperature-command/<br></p>

<p>P.S.<br>
And, of course, a lot of thanks to all perosns, who created related programm/atricles/etc. And can't remember all places where I found help, inspiration and examples. So, thank you, community!<br></p>

