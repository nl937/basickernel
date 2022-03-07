void ata_init();
void* ata_read_sectors(unsigned int lba, unsigned short sectors, unsigned int* target);
void ata_write_sectors(unsigned int lba, unsigned short secors, unsigned int* origin);