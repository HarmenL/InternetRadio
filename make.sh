#!/bin/bash
echo "Uploading to the server.."
command="curl http://imegumii.space:12001/upradio.php -w '\n'  --progress-bar  ";
for i in *.c; do
   command="$command -F \"file[]=@$i\"";
done

output=$(eval $command);

echo "$output";

if [ "$output" = "success" ]; then
	rm ipac.hex -f
	echo "Downloading hex file.."
	wget http://imegumii.space:12001/source/ipac.hex -q --show-progress;
	echo "Starting flash..";
	mono internetradioflash.exe f=ipac.hex p="/dev/ttyUSB0"
else
	echo "Errors when making; Stopped";
fi




