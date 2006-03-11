// By Magnafix 10-14-96
// required addition of list_new_posts() in bboard daemon
#include <daemons.h>
#include <lib.h>

inherit LIB_COMMAND;


int cmd(string str){
    write("You snap your fingers, and permit hostilities to resume.");
    say(this_player()->GetCapName()+" snaps "+possessive()+" fingers "+
      "and permits hostilities to resume.");
    foreach(object combatant in get_livings(environment(this_player()))){
	combatant->eventUnQuell();
	if(combatant->GetInCombat()) tell_object(combatant,"You resume fighting.");
    }

    return 1;
}



string GetHelp(string str) {
    return "Syntax: <unquell>\n"
    "Allows quelled combat to resume.\n"
    "See also: quell\n";
}