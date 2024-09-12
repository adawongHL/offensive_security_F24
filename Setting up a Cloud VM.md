The [[Setting Up An Emulated Environment|Docker solution for M1/2/3 series MacBooks]] works well for running x86_64 binaries and `pwntools` scripting. Unfortunately, GDB does not appear to be available for macOS[1] and proposed solutions like running in split terminals with GDB server[2] and command line flags with `SYS_PTRACE`[3] do not appear to work. The result of each case is output errors such as `Couldn't get registers: Input/output error`.

1. [GDB not out for Mac Silicon](https://stackoverflow.com/questions/77725087/how-to-run-gdb-on-an-m2-macbook-air)
2. [Running GDB in Docker on Mac Silicon with remote](https://github.com/docker/for-mac/issues/6921)
3. [`SYS_PTRACE` suggested fix](https://forums.docker.com/t/sys-ptrace-capability-for-linux-amd64/138482)

For those interested in experimenting with GDB that do not have access to a device with an Intel processor, some general outlines are included in [[0. Operating Systems Refresher & Pwntools#Cloud-based Approach|Cloud-based Approach]] from [[0. Operating Systems Refresher & Pwntools]]. This guide will outline a specific approach to spin up a free* AWS Ubuntu VM for experimentation with GDB.

*\*free for new users under the [Free Tier Account guidelines](https://aws.amazon.com/free/?gclid=EAIaIQobChMI-d-4wOq5iAMVmWlHAR0PxzsHEAAYASAAEgLSE_D_BwE&trk=78b916d7-7c94-4cab-98d9-0ce5e648dd5f&sc_channel=ps&ef_id=EAIaIQobChMI-d-4wOq5iAMVmWlHAR0PxzsHEAAYASAAEgLSE_D_BwE:G:s&s_kwcid=AL!4422!3!432339156165!e!!g!!free%20aws%20account!9572385111!102212379047&all-free-tier.sort-by=item.additionalFields.SortRank&all-free-tier.sort-order=asc&awsf.Free%20Tier%20Types=*all&awsf.Free%20Tier%20Categories=*all)*

*Note that all the alternatives presented here do require a credit card or bank information to charge if the VM exceeds certain threshold or has certain specs. If you do not have the ability to sign up for a free tier Amazon, please email the Professor.* 

## Alternatives

[Digital Ocean](https://www.digitalocean.com/) and [GCP](https://cloud.google.com/gcp?utm_source=google&utm_medium=cpc&utm_campaign=na-US-all-en-dr-bkws-all-all-trial-e-dr-1707554&utm_content=text-ad-none-any-DEV_c-CRE_665735450624-ADGP_Hybrid+%7C+BKWS+-+EXA+%7C+Txt-Core-GCP-KWID_43700077223807298-aud-2232802565252:kwd-87853815&utm_term=KW_gcp-ST_gcp&gad_source=1&gclid=EAIaIQobChMIxfy3puq5iAMVUGBHAR19QTLaEAAYASAAEgLVt_D_BwE&gclsrc=aw.ds&hl=en) are both viable alternatives, but as of Fall 2024 neither have free options even for new users. Both are useful, though, and Digital Ocean is a breeze setting up and spinning up new VMs.

## AWS

Sign up for a new [AWS](https://aws.amazon.com/?nc2=h_lg) account and add your mailing address and a credit card or bank account. *Should you stay under the Free Tier requirements, there should be no charge to this card*. Afterward, navigate to the AWS Console Home and search for the EC2 services. Click on the "Launch Instance" option.

![[ec2_create.png]]

Here, you may be directed to enable the EC2 API. Click "enable." This may take some time to enable—you can check the status using the notification bell in the top toolbar.

Again, try and launch an instance. If it takes you back to the API enabling option, log out and log back in. The button should now direct you to a configuration menu of VM options.

Choose the Ubuntu OS and x64 architecture along with a Free Tier eligible Ubuntu Server OS. Both 24.04 and 22.04 should work for this course.

![[ec2_os_and_arch_choice.png]]

Next, ensure the instance type has specifications that fall within the Free Tier. If you want to pay for more performance, you can select a more performant specification here.

![[ec2_instance_type.png]]

Create a new keypair and follow [Amazon's instructions](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html?icmpid=docs_ec2_console) to configure that keypair. Instructions for macOS are below. If you have trouble or a step-by-step for other OSs, please inform the Professor.

Finish the installation and wait for the VM to boot. You can use the AWS EC2 console to find the public IP address and SSH into `ubuntu@<IP of VM>`.

## Configuring the VM

Before doing anything else on your VM, run `sudo apt-get update && sudo apt-get upgrade`. This will take a minute to update, but it is essential before trying to install other programs from the package manager.

After it completes, you can install utilities like `sudo apt-get install -y python3-pip gdb`, and `pip3 install pwntools`. You can use `scp <file> ubuntu@<ip of vm>:~/`  to move files from your local computer to the `~/` directory of the VM (use the `-r` flag for directories of files).

#### Configuring the KeyPair on macOS

1. Move the downloaded .pem file to `~/.ssh`
2. Edit your SSH config at `/etc/ssh/ssh_config` (requires `root` privileges) to include the following code:

```config
Host <ip of VM>
    IdentityFile ~/.ssh/<keypair name>.pem
```

3. Change the permissions of the .pem file with `chmod 400 ~/.ssh/<keypair name>.pem`
4. Try `ssh ubuntu@<ip of VM>`. SSH should ask you to trust the keypair. Select `yes` and you should have a terminal on the VM. You can change to the root user with `sudo su`
