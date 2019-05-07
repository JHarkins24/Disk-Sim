
//Joe Harkins
//Project 2
//04/23/19

//remember to use
//ioctl()
//remember to use
#include "time.h"
#include "disk.h"
//#define_DEBUG
disk_t disk;
time_t timer;

int log2phys(int logaddr, physaddr_t *phaddr) {
    // TODO: AFRICA

    if (logaddr < 0 && logaddr > MAX_LOGICAL_SECTOR) {
        printf("Logical address error");
        return LOGICAL_ADDRESS_ERROR;
    } else
        phaddr->cyl = (logaddr / SECT_SIZE) + 1;

    if (phaddr->cyl > NUM_OF_CYLS)
    {
        printf("greater than NUM_OF_CYLS [phaddr->cyl]");
        return CYL_ERROR;
    }
    phaddr->head = ((logaddr % SECT_SIZE) / NUM_OF_SECTS) + 1;

    if (phaddr->head > NUM_OF_HEADS)
    {
        printf("greater then NUM_OF_HEADS [phaddr->head]");
        return HEAD_ERROR;
    }
    phaddr->sect = logaddr % (NUM_OF_SECTS) + 1;

    if (phaddr->sect > NUM_OF_SECTS)
    {
        printf("greater then MAX_LOGICAL_SECTOR [phaddr->sect]");
        return SECT_ERROR;
    }

    return 0;
}

int phys2log(physaddr_t *phaddr)
{
    // TODO: AFRICA
\
    return (phaddr->head * NUM_OF_SECTS) + phaddr->sect + (phaddr->cyl * SECT_SIZE);
}

void printTransl(int logaddr)
{
    physaddr_t phaddr;

    printf("Logical sector number: %d\n", logaddr);
    if (log2phys(logaddr, &phaddr) == 0)
    {
        printf("Physical address: (%d, %d, %d)\n", phaddr.cyl, phaddr.head, phaddr.sect);

        if (phys2log(&phaddr) != logaddr)
            printf("ERROR: no match!\n");
    } else
        printf("ERROR: invalid logical address!\n");
}


int readDisk(int logical_block_num, int numOfBlocks, void **buffer) 
{
    // TODO: AFRICA?
    // find number of blocks, create an array to hold that and then add to that array
    // numOfBlocks is the number of sectors we want to copy
    // logical_block_num is the starting address we wish to use
    // buffer is what we are using to store the information from the disk

    // create the array
    // as long as the starting address is within our bounds run through the disk and
    // copy the information at each sector into the buffer
    if (logical_block_num < 0)
        return -1;
    if (logical_block_num + numOfBlocks < MAX_LOGICAL_SECTOR)
        return 0;

    physaddr_t phyaddr;
    for (int i = 0; i < numOfBlocks; ++i)
    {
        log2phys(logical_block_num + i, &phyaddr);
      //  (*buffer)[i] = disk[phyaddr.cyl][phyaddr.head][phyaddr.sect];


    }
    return 0;
    
}

int writeDisk(int logicalBlockNum, int numOfSectors, void *buffer)
{
//     // TODO: AFRICA?

       if (logicalBlockNum < 0)
            return -1;
        if (logicalBlockNum + numOfSectors < MAX_LOGICAL_SECTOR)
            return 0;
    // create physical address object
    physaddr_t phyaddr;


    for(int i = 0; i < numOfSectors; ++i)
        {
            log2phys(logicalBlockNum, &phyaddr);

            // Array type 'sector_t(aka 'char[1280]' is not assignable
            // Subscript of a pointer to a void is a GNU exception

         //   disk[phyaddr.cyl][phyaddr.head][phyaddr.sect] = buffer[i];
        }

    return 0;

}

//int main(int argc, char *argv[])
//{
//    // TODO: extend to also test for reading and writing AFRICA
//
//    physaddr_t phaddr;
//
//    char buf[8 * SECT_SIZE];
//
//    int logaddr;
//
//    if (argc < 2)
//        while (1)
//        {
//            logaddr = rand() % MAX_LOGICAL_SECTOR;
//            printTransl(logaddr);
//            switch (rand() % 2)
//            {
//                case 0:
//                    readDisk(logaddr, rand() % 8, (void *) &buf);
//                    break;
//                case 1:
//                    writeDisk(logaddr, rand() % 8, buf);
//                    break;
//            }
//            usleep(10);
//        }
//
//    switch (argv[1][0]) // "l" for logical "p" for physical
//    {
//        case 'l': // logical
//            if (argv[2] == NULL)
//                break;
//            logaddr = strtol(argv[2], NULL, 10) % MAX_LOGICAL_SECTOR;
//            printTransl(logaddr);
//            break;
//
//        case 'p': // physical
//            if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
//                break;
//            phaddr.cyl = strtol(argv[2], NULL, 10);
//            phaddr.head = strtol(argv[3], NULL, 10);
//            phaddr.sect = strtol(argv[4], NULL, 10);
//            logaddr = phys2log(&phaddr);
//            printTransl(logaddr);
//            break;
//
//        case 'r': // read
//            if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
//                break;
//            // run the phys test as well for the sake of time and testing stuff
//            phaddr.cyl = strtol(argv[2], NULL, 10);
//            phaddr.head = strtol(argv[3], NULL, 10);
//            phaddr.sect = strtol(argv[4], NULL, 10);
//            logaddr = phys2log(&phaddr);
//            printTransl(logaddr);
//
//            // testing for success
//            readDisk(logaddr, rand() % 8, (void *) &buf);
//            // checking to see if the failure is working for an address below the bounds
//            readDisk(-1, rand() % 8, (void *) &buf);
//            // checking to see the bounds going over still triggers a failure
//            readDisk(MAX_LOGICAL_SECTOR, rand() % 8, (void *) &buf);
//            break;
//
//        case 'w': // write
//            if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
//                break;
//
//            // run the log test as well for the sake of time and testing stuff
//            logaddr = strtol(argv[2], NULL, 10) % MAX_LOGICAL_SECTOR;
//            printTransl(logaddr);
//
//            // testing for success
//            writeDisk(logaddr, rand() % 8, buf);
//            // checking to see if the failure is working for an address below th ebounds
//            writeDisk(-1, rand() % 8, buf);
//            // checking to see the bounds going over still triggers a failure
//            writeDisk(MAX_LOGICAL_SECTOR, rand() % 8, buf);
//            break;
//    }
//}
