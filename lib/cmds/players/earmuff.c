#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!str || str =="") {
	if(!sizeof(this_player()->GetMuffed())) write("You are ignoring no one.");
	else {
	    write("You are ignoring the following name(s):\n");
	    write(implode(filter(this_player()->GetMuffed(), (: capitalize($1) :)), "\n")+"\n");
	}
	return 1;
    }
    else this_player()->AddMuffed(str);
    write("You add "+capitalize(str)+" to your earmuffed list.");
    return 1;
}

void help() {
    message("help",
      "Syntax: earmuff\n"
      "        earmuff <name>\n\n"
      "This command allows you to ignore channel messages from the name specified.\n"
      "See also: whomuffed, unmuff\n\n",
      this_player() );
}
