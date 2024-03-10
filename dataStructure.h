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
const int SYSTEM_SIZE = 16 * 1024 * 1024;									   // 16MB total space
const int BLOCK_SIZE = 1 * 1024;											   // 1KB block size
const int BLOCK_NUM = 16 * 1024;											   // 16384 total blocks
const int INODE_NUM = 256;													   // 256 inodes
const int INODE_DIRECT_ADDR = 10;											   // 10 direct block address
const int INODE_INDIRE_ADDR = 1;									   		   // 1 idnirect block address 
const int ADDR_LENGTH = 3;													   // 24-bits address length
const int DEFAULT_MAGIC = 0x53;                                                // default magic num
const int NUM_BLOCK_SUPER_BLOCK = 1;                                           // 1 blcok for super block
const int NUM_BLOCK_INODE_BITMAP = 1;									       // 1 block for inode bitmap
const int NUM_BLOCK_DATA_BITMAP = 16;										   // 16 blocks for data bitmap
const int NUM_BLOCK_INODE = 16;												   // 16 blocks for inode

const int OFFSET_SUPER_BLOCK = 0;                                              // start of super block
const int OFFSET_INODE_BITMAP = OFFSET_SUPER_BLOCK + NUM_BLOCK_SUPER_BLOCK;	   // start of inode bitmap
const int OFFSET_DBLOCK_BITMAP = OFFSET_INODE_BITMAP + NUM_BLOCK_INODE_BITMAP; // start of data block bitmap
const int OFFSET_INODE = OFFSET_DBLOCK_BITMAP + NUM_BLOCK_DATA_BITMAP;	       // start of inodes
const int OFFSET_DBLOCK = OFFSET_INODE + NUM_BLOCK_INODE;				       // start of data block
const int DBLOCK_NUM = BLOCK_NUM - OFFSET_DBLOCK;						       // rest blocks for data blocks

const int DIR_ENTRY_LENGTH = 32;										       // dir entry length
const int NAME_LENGTH = 29;												       // file/Dir name length
const int INODE_ID_LENGTH = DIR_ENTRY_LENGTH - NAME_LENGTH;					   // length of inode id
const int NUM_ENTRY_PER_BLOCK = BLOCK_SIZE / DIR_ENTRY_LENGTH;				   // num of directory entry
const int NUM_IND_TO_DIR = BLOCK_SIZE / INODE_ID_LENGTH;					   // num of indirect to direct (341)
const int INODE_MAX_NUM_BLOCKS = INODE_DIRECT_ADDR + INODE_INDIRE_ADDR * NUM_IND_TO_DIR + INODE_INDIRE_ADDR;
const int MAX_FILE_SIZE = INODE_MAX_NUM_BLOCKS - INODE_INDIRE_ADDR;            // max file size

//以下是一些数据结构
class Inode
{

};
class SuperBlock
{

};

//块号 大小3B(24bits) 应该可以不写？
class BlockID
{

};



