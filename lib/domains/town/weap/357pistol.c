#include <lib.h>
#include <vendor_types.h>
inherit "/lib/pistol";

void create(){
    pistol::create();
    SetKeyName("gun");
    SetId(({"gun","pistol","piece","revolver"}));
    SetAdjectives(({".357","357","magnum"}));
    SetShort("a .357 magnum revolver");
    SetLong("This is a thick, heavy chunk of weaponry that fires some very "+
      "serious rounds. Bullets are loaded individually into it, and they, along with spent "+
      "shells, remain in the cylinder until unloaded.");
    SetCaliber(357);
    SetPistolType("revolver");
    SetAmmoType("magnum");
    SetMaxAmmo(6);
    SetMass(20);
    SetValue(10);
    SetVendorType(VT_WEAPON);
}
void init(){
    ::init();
}
