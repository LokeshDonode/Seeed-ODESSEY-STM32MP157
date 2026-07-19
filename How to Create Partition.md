# How to Create a Partition

> Warning: These steps modify disk partitions and can destroy data. Double-check the device name and back up any important data before proceeding.

## Prerequisites

- Root access (use `sudo -i` or `sudo su`).
- A spare disk or removable media (SD card, USB drive, eMMC) with free space.
- Know the correct device name (e.g. `/dev/sda`, `/dev/mmcblk0`, `/dev/nvme0n1`).

## Overview
This document explains how to create a new partition using `fdisk`, force the kernel to re-read the partition table, and optionally create a filesystem and mount the partition.

---

## Steps

### 1. List disks and existing partitions
Identify the correct disk before making changes:

```sh
# list block devices and partitions
lsblk
# or show detailed partition/size information
sudo fdisk -l
# inspect a specific device (example)
lsblk /dev/sda
# or for SD/eMMC devices
lsblk /dev/mmcblk0
```

Carefully confirm which device (for example `/dev/sda` or `/dev/mmcblk0`) you will modify.

### 2. Start fdisk on the target disk
Open an interactive `fdisk` session for the target disk (replace `/dev/sdX` with your device):

```sh
sudo fdisk /dev/sdX
```

### 3. Create a new partition
Inside the `fdisk` prompt:

- Type `n` and press Enter to create a new partition.
- Choose partition type:
  - `p` — primary
  - `e` — extended (usually not needed on modern systems)
- Choose a partition number (or press Enter to accept the default).
- For the first sector press Enter to accept the default (recommended).
- For the last sector you can press Enter to use the remaining space, or specify a size like `+1G`, `+500M`, etc.

Example interactive session:

```
Command (m for help): n
Select (default p): p
Partition number (1-4, default 1): [Enter]
First sector (2048-..., default 2048): [Enter]
Last sector, +sectors or +size{K,M,G,T,P} (2048-..., default ...): +2G
```

### 4. (Optional) Change partition type/code
The default type is Linux (code `83`). To change it:

- Type `t` and Enter.
- Enter the partition number if prompted.
- Enter the hex code for the type, or type `L` to list available codes and choose one.

Common type codes:
- `83` — Linux filesystem
- `82` — Linux swap
- `07` — NTFS/exFAT
- `ef` — EFI System (FAT)

### 5. Write the partition table and exit
When ready, save changes with:

```
Command (m for help): w
```

This writes the partition table to disk and exits `fdisk`. If you quit without `w` (for example with `q`), no changes will be saved.

### 6. Make the kernel re-read the partition table
Force the kernel to re-read the partition table so the new partition becomes visible:

```sh
sudo partprobe /dev/sdX
# or
sudo partx -a /dev/sdX
# verify
lsblk
sudo fdisk -l /dev/sdX
```

If the kernel cannot re-read the table, a reboot may be required.

### 7. (Optional) Create a filesystem and mount the partition
After creating a partition (for example `/dev/sdX1`) you can create a filesystem:

```sh
# create ext4 filesystem
sudo mkfs.ext4 /dev/sdX1
# or create FAT32 (useful for SD cards / cross-platform):
sudo mkfs.vfat -F 32 /dev/sdX1
```

Mount it:

```sh
sudo mkdir -p /mnt/my-partition
sudo mount /dev/sdX1 /mnt/my-partition
# check usage
df -h /mnt/my-partition
```

To auto-mount at boot, use the partition UUID in `/etc/fstab`:

```sh
sudo blkid /dev/sdX1
# example fstab entry (replace UUID and mount point):
# UUID=xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx  /mnt/my-partition  ext4  defaults  0  2
```

## Tips and precautions

- ALWAYS double-check the device name; writing to the wrong device will destroy data.
- On eMMC/SD devices, partitions are named like `/dev/mmcblk0p1` (note the `p` before the number).
- On NVMe devices, device names are like `/dev/nvme0n1` and partitions like `/dev/nvme0n1p1`.
- Use `lsblk` and `fdisk -l` to confirm sizes and partitions before and after changes.

## References
- fdisk manual: `man fdisk`
- lsblk manual: `man lsblk`

---

If you want I can rename this file to `How to Create Partition.md` and commit that change, or create a separate .md file instead. Tell me which you'd prefer and which branch to use.
