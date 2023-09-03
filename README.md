# KFS2-42

# Setup

## 1. KVM

[source website](https://ubuntu.com/blog/kvm-hyphervisor)

```bash
sudo apt -y install bridge-utils cpu-checker libvirt-clients libvirt-daemon qemu qemu-kvm xorriso mtools
sudo kvm-ok

# Should output
# INFO: /dev/kvm exists
# KVM acceleration can be used
```

You will have to enable virtualisation in your bios if `kvm-ok` says nope.

# KFS

[Source](https://wiki.osdev.org/Bare_Bones)

## 2. Making a cross compiler

[source website](https://wiki.osdev.org/GCC_Cross-Compiler)

#### Download & Extract GCC and binutils

Install homebrew for linux

Then  
```
brew install i686-elf-gcc i686-elf-binutils
```

And you're done :)

#### Test
```
❯ which i686-elf-gcc
/home/linuxbrew/.linuxbrew/bin/i686-elf-gcc
```

## 3. Launch the OS

```
make brun
```