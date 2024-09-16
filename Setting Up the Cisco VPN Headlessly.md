Accessing ports on the challenge server (excluding 443, the default SSL port, which is accessible to the broader internet) requires tunneling through the NYU VPN. NYU has instructions for [installing on Windows and Mac](https://www.nyu.edu/life/information-technology/infrastructure/network-services/vpn.html) and NYU Shanghai has a [link for Linux machines](https://shanghai.nyu.edu/it/vpn). But there is no guidance for running this on a headless system without a GUI, as the Duo MFA requires a UI to interact with the push approval.

That is, until now!

To install and run the NYU VPN on a Digital Ocean Droplet, AWS VM, GCP instance, or any other headless Linux server, follow these instructions:

> The Duo MFA push in headless mode defaults to your default device. For someone (like myself) that has changed devices since originally registering the Duo account, this may be a device that is no longer accessible. Follow [these instructions](https://nyu.service-now.com/sp?id=kb_article&sysparm_article=KB0018788&sys_kb_id=2cd8244b1bf82490a54ffdd51a4bcb2f&spa=1) to update and remove old devices so that the default option is a device you own and have access to. _If you do not do this, the login prompt will hang before eventually timing out_.

1. [Install openconnect](https://gist.github.com/marshki/834d8b6f19c69b189df1e6b5b2aba428). For Debian and Ubuntu hosts, the command is `sudo apt-get install openconnect network-manager-openconnect network-manager-openconnect-gnome`
2. Run `sudo openconnect --background --user <NetID> vpnsec.nyu.edu`  with your NetID
3. In the first `password` prompt, enter your NYU password
4. In the second `password` prompt, enter "push" to send a Duo Push
5. Approve the push on your device. _If this hangs and times out, see the note in the block quote above_
6. Try connecting to one of the challenge ports with `nc`

To stop tunneling through the VPN, kill the `openconnect` process. An example of this is shown below.

1. Find the process PID, e.g., `sudo ps -axjf | grep openconnect`. In the example below it is the second column in the second match: 31070
2. Kill the process with `sudo kill -9 <pid>`

```
ubuntu@ip-172-31-23-18:~$ sudo ps -axjf | grep openconnect
  27948   31184   31183   27948 pts/0      31183 S+    1000   0:00              \_ grep --color=auto openconnect
      1   31070   31069   31068 ?             -1 S        0   0:00 openconnect --background --user id774 vpnsec.nyu.edu
ubuntu@ip-172-31-23-18:~$ sudo kill -9 31070
```