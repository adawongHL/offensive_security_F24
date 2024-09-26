Transferring files between our host environment and research environment is an important and common process during vulnerability research. There are a couple common ways to accomplish this.

## SCP

The [Secure Copy Protocol](https://en.wikipedia.org/wiki/Secure_copy_protocol) (SCP) is a quick way to transfer a file or directory from a host to remote VM, or vice versa, leveraging SSH authentication:
* `scp username@<ip>:file/on/remote/device path/to/copy/to/on/host`
* `scp file/on/host username@<ip>:/path/to/copy/to/on/remote/device`

For example, transferring a file at `/home/ubuntu/Documents/myfile.txt` on the remote device at IP `1.1.1.1` to the current directory on a host machine would be:

```console
scp ubuntu@1.1.1.1:/home/ubuntu/Documents/myfile.txt .
```

We can also copy directories and all files inside, recursively, with `-r`:
* `scp -r username@<ip>:directory/on/remote/device path/to/copy/to/on/host`
* `scp -r directory/on/host username@<ip>:/path/to/copy/to/on/remote/device`

## SSH Key on Remote Machine

SCP is fine for infrequent copies, however consistently syncing new files, such as updates to our GitHub repo containing the Obsidian Notebook becomes arduous. The weekly and one-off updates would require figuring out all the files that are modified and then uploading them to the remote server. That is time consuming, and there are better options.

One quick solution that is a bit extraneous is adding a new SSH key to our remote server and registering that key to our GitHub account. That way, we can `git clone` and `git pull` the repo and its changes whenever they're made. This ensures the files on the remote server are always up to date.

## SSH Agent Forwarding

A sightly better solution is forwarding our SSH key from our host to our remote machine with SSH Agent. This is deemed "better" because it is one less key to worry about—we only use our host key and "authorize" the VM to use it by passing it through our SSH connection.

GitHub has a [good walkthrough](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/using-ssh-agent-forwarding) for generating a new key and adding that to the SSH config so it can pass through a connection when running `ssh username@ip`. 

Two important considerations are:
* [Your SSH key is added to the host machine](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/using-ssh-agent-forwarding#your-key-must-be-available-to-ssh-agent). We can do this with `ssh-add <path to key on host>`, such as `ssh-add ~/.ssh/id_rsa`
* [SSH agent is running on the remote server](https://kb.iu.edu/d/aeww). We can do this on the remote server with 

```sh
eval `ssh-agent`
```

Once these steps are in place, we can SSH into the server and run `ssh-add -L`, which should show that our host key is available. We can also check that GitHub authentication is successful with `ssh -T git@github.com`. We can now `git clone` and `git pull` the repo directly onto the remote machine!