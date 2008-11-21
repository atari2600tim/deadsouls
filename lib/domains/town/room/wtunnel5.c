#include <lib.h>
inherit LIB_ROOM;

static void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("copy of wtunnel4.c");
    SetLong("This tunnel has very smooth stone walls and runs north and south.");
    SetItems(([
        ({ "hole", "holes", "floor" }) : "These holes appear to be where spring water enters to flood the chamber and fill the well east of here. ",
        ({ "dirt", "dust" }) : "There's plenty of that here. Empty wells rarely get much priority on cleaning day.",
        ({ "bottom", "well" }) : "Dirty, musty, and unpleasant.",
        ({ "vermin", "rats", "bugs" }) : "Looks like they're hiding from you at the moment.",
        "haven" : "A nice place for vermin.",
        ({ "rock", "bedrock" }) : "This is dense, hard stuff deep underground.",
      ]));
    SetExits( ([
        "south" : "/domains/town/room/wtunnel4",
        "north" : "/domains/town/room/wtunnel6.c",
      ]) );

}
void init(){
    ::init();
}