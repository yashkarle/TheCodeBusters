sudo ip tuntap add mode tun dev tun30
sudo ip addr add 10.30.0.1/24 dev tun30
sudo ip link set dev tun30 up
wget 35.154.77.64:8000/static/ClientPackage.tar.gz
tar -xvf ClientPackage.tar.gz
rm ClientPackage.tar.gz
echo CloudSwitch Username:
read username
echo CloudSwitch Password:
read password
echo Device Registration Name:
read devname
cd ClientPackage
./client $username $devname
