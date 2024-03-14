#include <linux/module.h>
#include <asm/mytee.h>

EXPORT_SYMBOL(mytee_up_priv);
EXPORT_SYMBOL(mytee_down_priv);
EXPORT_SYMBOL(mytee_shield_mmio);
EXPORT_SYMBOL(mytee_unshield_mmio);
EXPORT_SYMBOL(mytee_get_kernel_phys);
EXPORT_SYMBOL(mytee_unshield_mmio_4kb);
EXPORT_SYMBOL(mytee_shield_mmio_4kb);
