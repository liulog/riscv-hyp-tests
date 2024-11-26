#!/bin/bash

export PLAT=qemu
export MACHINE=virt

# make clean PLAT=${PLAT}
make PLAT=${PLAT}

cd /home/jingyu/hypervisor/xiangshan/opensbi-devel
# make distclean
# make -j8 ARCH=riscv PLATFORM=generic FW_PAYLOAD_PATH=/home/jingyu/hypervisor/riscv-hyp-tests/build/${PLAT}/rvh_test.bin \
#     FW_FDT_PATH=./kmh-v2-1core.dtb

# make -j8 ARCH=riscv PLATFORM=generic FW_PAYLOAD_PATH=/home/jingyu/linux-6.9/arch/riscv/boot/Image \
#     FW_FDT_PATH=./kmh-v2-1core.dtb

# ../qemu-devel/build/qemu-system-riscv64 -nographic \
    # -machine bosc-kmh -smp 1 -m 4G \
    # -kernel /home/jingyu/hypervisor/riscv-hyp-tests/build/qemu-kmh/rvh_test.bin


# ../qemu-devel/build/qemu-system-riscv64 -machine bosc-kmh -smp 1 -m 1G -bios ~/hypervisor/opensbi-1.5.1/build/platform/generic/firmware/fw_payload.bin  -nographic
../qemu-devel/build/qemu-system-riscv64 -machine ${MACHINE} -smp 1 -m 1G -bios /home/jingyu/hypervisor/riscv-hyp-tests/build/${PLAT}/rvh_test.bin -nographic -s -S