# shipcap - git but with scp

`shipcap` is a simple command-line tool that allows you to securely transfer files between your local machine and a remote server using the SCP (Secure Copy Protocol) over SSH. It is designed to make file transfers easy and secure.

## Features

- **Push Files**: Upload local files to a remote server.
- **Pull Files**: Download files from a remote server to your local machine.
- **Secure**: Utilizes SSH for secure file transfers.
- **Reads Credentials from ~/.shipcap**: Stores your SSH username, password, and the remote hostname in `~/.shipcap`.
- **Verbose Mode**: Optional `--verbose` flag for detailed output.

## Prerequisites

Before using `shipcap`, ensure you have the following prerequisites:

- **SSH**: You should have SSH installed and configured on your local machine and the remote server.

## Installation

To install `shipcap`:

1. Clone this repository or download the source code.

2. Run the installation script with superuser privileges to compile and install the binary:

   ```bash
   sudo ./install.sh
   ```

3. The `shipcap` binary will be installed in `/usr/local/bin`, making it accessible system-wide.

## Usage

`shipcap` supports the following commands:

- **Push**: Upload a local file to the remote server.

   ```bash
   shipcap push <local_file>
   ```

- **Pull**: Download files from the remote server to the local directory. This command creates the destination directory if it doesn't exist.

   ```bash
   shipcap pull <destination_dir>
   ```

### Verbose Mode

You can use the `--verbose` flag to enable verbose mode, which provides detailed output during file transfers:

```bash
shipcap --verbose push <local_file>
shipcap --verbose pull <destination_dir>
```

## Configuration

To configure `shipcap`, store your SSH username, password, and the remote hostname in the `~/.shipcap` file in the following format:

```
your_username
your_password
csa1.bu.edu
```

Ensure that the file permissions for `~/.shipcap` are set to be secure (`chmod 600 ~/.shipcap`) to protect your credentials.

## Uninstallation

To uninstall `shipcap`, you can use the provided Makefile:

```bash
sudo make uninstall
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
