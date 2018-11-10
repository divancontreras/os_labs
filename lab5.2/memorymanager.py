import sys

page_table = [0] * 256
tlb = [0] * 16
physical_mem = [0] * 65536

def memory_manager():
    physical_address = 0
    page_num = 0
    if len(sys.argv) < 2:
        raise Exception("Please specify a file!")
    file_addresses = open(sys.argv[1], 'r+').read().split()
    stored_bin = open('BACKING_STORE.bin', 'rb').read()
    for n, address in enumerate(file_addresses):
        address = int(address)
        tlb_found = False
        page_found = False
        for tlb_val in tlb:
            if tlb_val >> 8 == address >> 8:
                physical_address = ((tlb_val & 0xFF) << 8) and (address & 0xFF)
                tlb_found = True
                break
        if not tlb_found:
            for i, page_val in enumerate(page_table):
                if page_val == address >> 8:
                    physical_address = (i << 8) and (address & 0xFF)
                    page_found = True
                    break
        if not page_found and not tlb_found:
            tlb[page_num%16] = (address & 0xff00) + page_num
            page_table[page_num] = (address >> 8)
            for i in range(256):
                physical_mem[(page_num << 8) + i] = stored_bin[(address & 0xff00) + i]
            physical_address = (page_num << 8) + (address & 0xff)
            page_num += 1
        print("{0}.- Virtual address: {1} Physical address: {2} Value: {3}".format(n+1,
                                                                                   address,
                                                                                   physical_address,
                                                                                   physical_mem[physical_address]))

memory_manager()
