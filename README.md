# Seeed-ODESSEY-STM32MP157
Getting Started 
https://wiki.seeedstudio.com/ODYSSEY-STM32MP157C/
> firmware/build -- debian@npi -- stm32mp1-debian-buster-console-armhf-latest-2gb.img.xz 
    -- Wifi Fix
    > wget fw_bcm43438a1.bin https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/fw_bcm43438a1.bin
    > cp fw_bcm43438a1.bin /lib/firmware/brcm/fw_bcm43438a1.bin
    > cp /lib/firmware/brcm/nvram_ap6236.txt /lib/firmware/brcm/nvram.txt
    > reboot
    > use connmanctl for wifi connection

# Provided by Digikey needs u-boot configuration
https://forum.digikey.com/t/debian-getting-started-with-the-odyssey-stm32mp157c/12838
> firmware/build --- debian@arm 

# Provided by STM32 
> Installing repo and generating build
https://wiki.st.com/stm32mpu/wiki/STM32MPU_Distribution_Package
> firmware/build -- openstlinux -- 
