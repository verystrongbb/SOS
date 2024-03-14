#pragma once

#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<stack>
#include<vector>
#include<iomanip>
#include<cstring>

using namespace std;
/*
			  Block Structure of the Filesystem:
 ------------------------------------------------------------
 |SuperBlock|INODE Bitmap|DBlock Bitmap| INODE | Data Block |
 |    1     |      1     |      16    |  16  |    ...     |
 ------------------------------------------------------------
 */
const string SYSTEM_FILE = "my_system.dat";
const int SYSTEM_SIZE = 16 * 1024 * 1024;                                       // 16MB total space
const int BLOCK_SIZE = 1 * 1024;                                               // 1KB block size
const int BLOCK_NUM = 16 * 1024;                                               // 16384 total blocks
const int INODE_NUM = 256;                                                       // 256 inodes
const int INODE_DIRECT_ADDR = 10;                                               // 10 direct block address
const int INODE_INDIRE_ADDR = 1;                                               // 1 indirect block address
const int ADDR_LENGTH = 3;                                                       // 24-bits address length
const int DEFAULT_MAGIC = 0x53;                                                // default magic num
const int NUM_BLOCK_SUPER_BLOCK = 1;                                           // 1 block for super block
const int NUM_BLOCK_INODE_BITMAP = 1;                                           // 1 block for inode bitmap
const int NUM_BLOCK_DATA_BITMAP = 16;                                           // 16 blocks for data bitmap
const int NUM_BLOCK_INODE = 16;                                                   // 16 blocks for inode

const int OFFSET_SUPER_BLOCK = 0;                                              // start of super block
const int OFFSET_INODE_BITMAP = OFFSET_SUPER_BLOCK + NUM_BLOCK_SUPER_BLOCK;       // start of inode bitmap
const int OFFSET_DBLOCK_BITMAP = OFFSET_INODE_BITMAP + NUM_BLOCK_INODE_BITMAP; // start of data block bitmap
const int OFFSET_INODE = OFFSET_DBLOCK_BITMAP + NUM_BLOCK_DATA_BITMAP;           // start of inodes
const int OFFSET_DBLOCK = OFFSET_INODE + NUM_BLOCK_INODE;                       // start of data block
const int DBLOCK_NUM = BLOCK_NUM - OFFSET_DBLOCK;                               // rest blocks for data blocks

const int DIR_ENTRY_LENGTH = 32;                                               // dir entry length
const int NAME_LENGTH = 29;                                                       // file/Dir name length
const int INODE_ID_LENGTH = DIR_ENTRY_LENGTH - NAME_LENGTH;                       // length of inode id
const int NUM_ENTRY_PER_BLOCK = BLOCK_SIZE / DIR_ENTRY_LENGTH;                   // num of directory entry
const int NUM_IND_TO_DIR = BLOCK_SIZE / INODE_ID_LENGTH;                       // num of indirect to direct (341)
const int INODE_MAX_NUM_BLOCKS = INODE_DIRECT_ADDR + INODE_INDIRE_ADDR * NUM_IND_TO_DIR + INODE_INDIRE_ADDR;
const int MAX_FILE_SIZE = INODE_MAX_NUM_BLOCKS - INODE_INDIRE_ADDR;            // max file size

//以下是一些数据结构
class address_24bit {
private:
    unsigned char addr[ADDR_LENGTH];  // 3 byte address

public:
    address_24bit() = default;

    address_24bit(int addr) {
        if (addr > 0xffffff || addr < 0) {
            cout << "Address out of range!" << endl;
            return;
        }
        this->addr[0] = (addr >> 16) & 0xff;
        this->addr[1] = (addr >> 8) & 0xff;
        this->addr[2] = addr & 0xff;
    }

    int toInt() {
        return (addr[0] << 16) + (addr[1] << 8) + addr[2];
    }

    // deprecated
    unsigned char *getAddr() {
        return addr;
    }

    address_24bit &operator=(int addr) {
        if (addr > 0xffffff || addr < 0) {
            cout << "Address out of range!" << endl;
            return *this;
        }
        this->addr[0] = (addr >> 16) & 0xff;
        this->addr[1] = (addr >> 8) & 0xff;
        this->addr[2] = addr & 0xff;
        return *this;
    }

    address_24bit &operator=(const address_24bit &addr) {
        this->addr[0] = addr.addr[0];
        this->addr[1] = addr.addr[1];
        this->addr[2] = addr.addr[2];
        return *this;
    }

    bool operator==(const address_24bit &addr) {
        return this->addr[0] == addr.addr[0] && this->addr[1] == addr.addr[1] && this->addr[2] == addr.addr[2];
    }

    bool operator==(int addr) {
        return this->toInt() == addr;
    }

    bool operator!=(const address_24bit &addr) {
        return this->addr[0] != addr.addr[0] || this->addr[1] != addr.addr[1] || this->addr[2] != addr.addr[2];
    }

    bool operator!=(int addr) {
        return this->toInt() != addr;
    }

    bool operator<(address_24bit addr) {
        return this->toInt() < addr.toInt();
    }

    bool operator<(int addr) {
        return this->toInt() < addr;
    }

    bool operator>(address_24bit addr) {
        return this->toInt() > addr.toInt();
    }

    bool operator>(int addr) {
        return this->toInt() > addr;
    }

    address_24bit &operator++() {
        int addr = this->toInt();
        addr++;
        *this = addr;
        return *this;
    }

    address_24bit &operator--() {
        int addr = this->toInt();
        addr--;
        *this = addr;
        return *this;
    }

    address_24bit &operator+(const int num) {
        int addr = this->toInt();
        addr += num;
        *this = addr;
        return *this;
    }

    address_24bit &operator+(address_24bit num) {
        int addr = this->toInt();
        addr += num.toInt();
        *this = addr;
        return *this;
    }

    address_24bit &operator-(const int num) {
        int addr = this->toInt();
        addr -= num;
        *this = addr;
        return *this;
    }

    address_24bit &operator-(address_24bit num) {
        int addr = this->toInt();
        addr -= num.toInt();
        *this = addr;
        return *this;
    }

    address_24bit operator*(const int num) {
        int addr = this->toInt();
        addr *= num;
        return {addr};
    }

    friend ostream &operator<<(ostream &os, address_24bit &addr) {
        os << addr.toInt();
        return os;
    }
};

class Inode {
private:
    short type; // 0 for file, 1 for directory
    int size; // file size
    string name; // file name
    address_24bit addr[INODE_DIRECT_ADDR]; // file address



public:
    Inode() {
        type = -1;
        size = -1;
        name = "";
    }


};

class SuperBlock {

};

//块号 大小3B(24bits) 应该可以不写？
class BlockID {

};



