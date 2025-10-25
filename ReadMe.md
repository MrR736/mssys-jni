# MsSys JNI

**MsSys JNI** is a Java Native Interface (JNI) library written in C that provides direct low-level disk and file system manipulation for various file systems, including FAT12, FAT16, FAT32, exFAT, and NTFS. It allows Java programs to interact with disks and partitions, perform boot record analysis, and modify file system structures safely.

---

## Table of Contents

* [Features](#features)
* [Supported File Systems](#supported-file-systems)
* [Installation](#installation)
* [Usage](#usage)
* [Usage Examples](#usage-examples)
* [Requirements](#requirements)
* [API](#api)
* [License](#license)

---

## Features

* Open and close files and devices through JNI.
* Read and write Master Boot Records (MBR) for multiple operating systems.
* Detect and modify OEM IDs on disk.
* Handle FAT12, FAT16, FAT32, exFAT, and NTFS file systems.
* Compute exFAT boot sector checksums.
* Low-level partition analysis and manipulation.
* Supports major, minor, and patch version queries for the JNI library.

---

## Usage

### Load the JNI library in Java
```java
package com.mssys;

public class MsSys {
    static {
        System.loadLibrary("mssys-jni");
    }
}
```

---

---

## Usage Examples

### 1. MsSys: File Operations and Version
```java
import com.mssys.MsSys;

public class MsSysExample {
    public static void main(String[] args) {
        MsSys ms = new MsSys();
        ms.fopen("/dev/sdX", "rb+");

        int major = ms.get_version_major();
        int minor = ms.get_version_minor();
        int patch = ms.get_version_patch();
        System.out.println("MsSys JNI Version: " + major + "." + minor + "." + patch);

        ms.fclose(ms);
    }
}
```

### 2. Br: Master Boot Record Handling
```java
import com.mssys.Br;

public class BrExample {
    public static void main(String[] args) {
        Br br = new Br();

        Br.fopen("/dev/sdX", "rb+");

        // Example: Set custom bytes per sector (optional)
        br.set_bytes_per_sector(512);

        // Read Windows Disk Signature from MBR
        int diskSignature = br.read_windows_disk_signature(br);
        System.out.println("Current Windows Disk Signature: " + diskSignature);

        // Check if MBR is DOS type
        boolean isDosMbr = br.is_dos_mbr(br) != 0;
        System.out.println("Is DOS MBR: " + isDosMbr);

        // Check for Grub4DOS MBR
        boolean isGrub4dosMbr = br.is_grub4dos_mbr(br) != 0;
        System.out.println("Is Grub4DOS MBR: " + isGrub4dosMbr);

        // Write a new DOS MBR (example)
        int writeResult = br.write_dos_mbr(br);
        System.out.println("Write DOS MBR Result: " + (writeResult != 0 ? "Success" : "Failure"));
    }
}
```

### 3. Identify: Disk and Partition Info
```java
import com.mssys.Identify;

public class IdentifyExample {
    public static void main(String[] args) {
        Identify disk = new Identify();

        String devicePath = "/dev/sdX";
        disk.fopen(devicePath "rb+");

        // Get start sector of the first partition
        long startSector = disk.partition_start_sector(disk);
        System.out.println("Partition Start Sector: " + startSector);

        // Get number of heads for the drive
        short heads = disk.partition_number_of_heads(disk);
        System.out.println("Number of Heads: " + heads);

        // Perform a sanity check for a specific boot record type (e.g., FAT32)
        int brType = Identify.FAT32_BR;
        int sanity = disk.sanity_check(disk, devicePath, brType, 1); // 1 = print messages
        System.out.println("Sanity Check Result: " + (sanity != 0));

        // Automatic smart selection of boot record type
        int selectedBr = disk.smart_select(disk);
        System.out.println("Smart Selected Boot Record Type: " + selectedBr);

        // Print diagnostic info for the device
        disk.diagnose(disk, devicePath);
    }
}
```

### 4. OemId: Read/Write OEM ID
```java
import com.mssys.OemId;

public class OemIdExample {
    public static void main(String[] args) {
        OemId oem = new OemId();

        oem.fopen("/dev/sdX", "rb+");

        // Read OEM ID from the file system
        String currentOemId = oem.read_oem_id(oem);
        System.out.println("Current OEM ID: " + currentOemId);

        // Check if it is safe to write a new OEM ID
        String newOemId = "MSDOS5.0";
        int okToWrite = oem.ok_to_write_oem_id(oem, newOemId, 1); // 1 = print messages
        if (okToWrite != 0) {
            // Write new OEM ID
            int result = oem.write_oem_id(oem, newOemId);
            System.out.println("OEM ID Write Result: " + (result != 0 ? "Success" : "Failure"));
        } else {
            System.out.println("Not safe to write OEM ID.");
        }
    }
}
```

### 5. PartitionInfo: Writing Partition Data
```java
import com.mssys.PartitionInfo;

public class PartitionExample {
    public static void main(String[] args) {
        PartitionInfo partition = new PartitionInfo();

        partition.fopen("/dev/sdX", "rb+");

        // Example: Write number of heads (use -1 to auto-detect)
        int successHeads = partition.write_partition_number_of_heads(partition, -1);
        System.out.println("Write Number of Heads Success: " + (successHeads != 0));

        // Example: Write start sector number (hidden sectors)
        int successStart = partition.write_partition_start_sector_number(partition);
        System.out.println("Write Start Sector Success: " + (successStart != 0));

        // Example: Set physical disk drive ID for FAT16, FAT32, and exFAT
        int fat16Drive = partition.write_partition_physical_disk_drive_id_fat16(partition);
        int fat32Drive = partition.write_partition_physical_disk_drive_id_fat32(partition);
        int exfatDrive = partition.write_partition_physical_disk_drive_id_exfat(partition);

        System.out.println("FAT16 Drive ID Success: " + (fat16Drive != 0));
        System.out.println("FAT32 Drive ID Success: " + (fat32Drive != 0));
        System.out.println("exFAT Drive ID Success: " + (exfatDrive != 0));
    }
}
```

### 6. FileData: Raw Read/Write
```java
import com.mssys.FileData;

public class FileDataExample {
    public static void main(String[] args) {
        FileData file = new FileData();

        file.fopen("/dev/sdX", "rb+");

        byte[] buffer = new byte[FileData.MAX_DATA_LEN];
        long position = 0;  // starting position
        int length = 512;   // number of bytes to read/write

        // Read data
        int bytesRead = file.read_data(file, position, buffer, length);
        System.out.println("Bytes Read: " + bytesRead);

        // Check if a data pattern exists
        byte[] pattern = {0x01, 0x02, 0x03, 0x04};
        int contains = file.contains_data(file, position, pattern, pattern.length);
        System.out.println("Pattern Found: " + (contains != 0));

        // Write data
        int bytesWritten = file.write_data(file, position, buffer, length);
        System.out.println("Bytes Written: " + bytesWritten);
    }
}
```

### 7. File System Boot Record Management
#### Fat12
```java
import com.mssys.Fat12;

public class Fat12Example {
    public static void main(String[] args) {
        Fat12 fat12 = new Fat12();

        fat12.fopen("/dev/sdX", "rb+");

        // Check if the file has a FAT12 file system
        boolean isFat12 = fat12.is_fat_12_fs(fat12) != 0;
        System.out.println("Is FAT12 FS: " + isFat12);

        // Check if the boot record matches the exact pattern we would write
        boolean matches = fat12.entire_fat_12_br_matches(fat12) != 0;
        System.out.println("Exact FAT12 BR match: " + matches);

        // Write a new FAT12 boot record (keep label = 1)
        boolean written = fat12.write_fat_12_br(fat12, 1) != 0;
        System.out.println("FAT12 BR write: " + (written ? "Success" : "Failure"));
    }
}
```

#### Fat16
```java
import com.mssys.Fat16;

public class Fat16Example {
    public static void main(String[] args) {
        Fat16 fat16 = new Fat16();

        fat16.fopen("/dev/sdX", "rb+");

        boolean isFat16 = fat16.is_fat_16_fs(fat16) != 0;
        System.out.println("Is FAT16 FS: " + isFat16);

        // Check for a normal FAT16 boot record
        boolean matches = fat16.entire_fat_16_br_matches(fat16) != 0;
        System.out.println("Exact FAT16 BR match: " + matches);

        // Write a FAT16 ReactOS boot record
        boolean written = fat16.write_fat_16_ros_br(fat16, 1) != 0;
        System.out.println("FAT16 ReactOS BR write: " + (written ? "Success" : "Failure"));
    }
}
```

#### Fat32
```java
import com.mssys.Fat32;

public class Fat32Example {
    public static void main(String[] args) {
        Fat32 fat32 = new Fat32();

        fat32.fopen("/dev/sdX", "rb+");

        boolean isFat32 = fat32.is_fat_32_fs(fat32) != 0;
        System.out.println("Is FAT32 FS: " + isFat32);

        // Check for FAT32 DOS boot record match
        boolean matches = fat32.entire_fat_32_br_matches(fat32) != 0;
        System.out.println("Exact FAT32 DOS BR match: " + matches);

        // Write a FAT32 NT6 boot record (keep label = 1)
        boolean written = fat32.write_fat_32_nt6_br(fat32, 1) != 0;
        System.out.println("FAT32 NT6 BR write: " + (written ? "Success" : "Failure"));
    }
}
```

#### Ntfs
```java
import com.mssys.Ntfs;

public class NtfsExample {
    public static void main(String[] args) {
        Ntfs ntfs = new Ntfs();

        // Check if the file has an NTFS file system
        boolean isNtfs = ntfs.is_ntfs_fs(ntfs) != 0;
        System.out.println("Is NTFS FS: " + isNtfs);

        // Check if the file has an NTFS boot record
        boolean hasBr = ntfs.is_ntfs_br(ntfs) != 0;
        System.out.println("Has NTFS Boot Record: " + hasBr);

        // Check if the boot record matches the exact pattern this program would write
        boolean matches = ntfs.entire_ntfs_br_matches(ntfs) != 0;
        System.out.println("Exact NTFS BR match: " + matches);

        // Write a new NTFS boot record (keep label = 1)
        boolean written = ntfs.write_ntfs_br(ntfs, 1) != 0;
        System.out.println("NTFS BR write: " + (written ? "Success" : "Failure"));
    }
}
```

---

## Supported File Systems

* **FAT12**
* **FAT16**
* **FAT32**
* **exFAT**
* **NTFS**

---

## Installation

### Prerequisites

* **Java Development Kit (JDK)**
* **C Compiler** (GCC, Clang, or compatible)
* **GNU Make** (optional, for build automation)
* **JNI headers** (usually included with JDK)

## Requirements

Before building, ensure you have the following dependencies installed:

```bash
sudo apt update
sudo apt install cmake make gcc g++ xz-utils
```

## Build

### Building from Source

```bash
git clone https://github.com/MrR736/MsSys.git
cd MsSys

cmake .
make
```
