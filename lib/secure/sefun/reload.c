#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include <rooms.h>
#include <commands.h>
mixed mx;
object next;
object *dudes;
string filename, args;

varargs mixed reload(mixed ob, int recursive) {
    mapping StringFellows = ([]);
    int stringed;
    object env;
    mx = 0;

    if(!ob) return 0;

    if(objectp(ob) && environment(ob)) env = environment(ob);

    if(stringp(ob)) {
	stringed = 1;
	filename = ob;
	if(!grepp(filename,"#") && last(filename,2) != ".c") filename += ".c";
	ob = find_object(filename);
	if(!ob) ob = load_object(filename);
    }
    if(!ob || !objectp(ob)) {
	write("No such object.");      
	return 0;
    }

    if(ob->GetDoor()) ob = load_object(ob->GetDoor());

    if(!file_exists(base_name(ob))) filename = base_name(ob)+".c";
    else filename = base_name(ob);

    if(recursive) args = "-a -r ";
    else args = "-a "; 

    if(!grepp(unguarded( (: read_file(filename) :) ),"void init()" || !grepp(unguarded( (: read_file(filename) :) ),"::init()"))) { 
	write("This object lacks a working init function. Please run initfix on it as soon as possible.");
    }

    if(inherits(LIB_ROOM,ob)){
	dudes = get_livings(ob,1);
	if(dudes) {
	    foreach(object fellow in dudes){
		string ubi = fellow->GetProperty("LastLocation");
		if(ubi) StringFellows[fellow->GetKeyName()] = ubi;
	    }
	}

	unguarded( (: mx = catch(load_object(CMD_UPDATE)->cmd(args + filename)) :) );
	if(mx) {
	    write("There appears to be a problem updating one or more files.");
	    write("Reload failed.");
	}
	else {
	    if(dudes) {
		dudes->eventMove(filename);
		foreach(object fellow in dudes){
		    if(sizeof(StringFellows[fellow->GetKeyName()])){
			fellow->SetProperty("LastLocation",StringFellows[fellow->GetKeyName()]);
		    }
		}
	    }
	    write("Reload complete.");
	}
	StringFellows = ([]);
	return 1;
    }
    unguarded( (: mx = load_object(CMD_UPDATE)->cmd(args + filename) :) );
    if(!mx || !intp(mx) || mx == 0) {
	write("There appears to be a problem updating one or more files.");
	write("Reload failed.");
	return 0;
    }

    if(ob && !inherits(LIB_DOOR, ob) && !stringed && env) {
	unguarded( (: next = new(filename) :) ); 
	ob->eventMove(ROOM_FURNACE);
	next->eventMove(env);
    }
    write("Reload complete.");
    return 1;
}