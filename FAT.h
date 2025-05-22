#include "goonal.h"
#include "interrupt.h"
#include "GDT.h"
#include "serial.h"
#include <stdint>

// FAT_BootSector
struct __attribute__((packed)) fat_bpb {
    uint8_t jmp[3];
    uint8_t oem[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t num_fats;
    uint16_t root_entries;
    uint16_t total_sectors_16;
    uint8_t media_descriptor;
    uint16_t fat_size_sectors;
    // ... and more fields ...
};

