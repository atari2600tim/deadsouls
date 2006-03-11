#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
static void create(){
    armor::create();
    SetKeyName("leather boot");
    SetId(({"boot","right boot"}));
    SetAdjectives(({"military","military-style","black","leather","combat"}));
    SetShort("a black leather boot");
    SetLong("A military style combat boot, made of black leather. It is "+
      "designed for wear on the right foot.");
    SetMass(60);
    SetBaseCost("silver",25);
    SetDamagePoints(5);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_BOOT);
    SetRestrictLimbs(({"right foot"}));
}