/*    /secure/cmds/adm/decre.c 
 *    from the Dead Souls LPC Library
 *    turns a creator into a player
 *    created by Descartes of Borg 950323
 */

#include <lib.h>
#include <rooms.h>

inherit LIB_DAEMON;

string PlayerName;

mixed cmd(string args) {
    object ob, player_ob;
    object *inv;
    string nom, file;

    if( args == "" || !stringp(args) ) 
	return "Who do you want to make a player?";
    nom = convert_name(args);
    if( !user_exists(nom) ) return capitalize(nom) + " is not a member of " +
	possessive_noun(mud_name()) + " reality.";
    if( !strsrch(file = save_file(nom), DIR_PLAYERS) )
	return "You cannot make "+capitalize(args)+" a player.";
    if( file_size(DIR_PLAYERS+"/"+nom[0..0]) != -2) 
	mkdir(DIR_PLAYERS+"/"+nom[0..0]);
    if(rename(file+__SAVE_EXTENSION__, DIR_PLAYERS+"/"+nom[0..0]+"/"+nom+__SAVE_EXTENSION__))
	return "You failed due to lack of write access to "+DIR_PLAYERS+".";
    if( ob = find_player(nom) ) {
	PlayerName = nom;
	inv = deep_inventory(ob);
	if(sizeof(inv)) inv->eventMove(ROOM_FURNACE);
	catch(player_ob = (object)master()->player_object(nom));
	PlayerName = 0;
	if( !player_ob ) {
	    message("system", "Failed to create a player object.", 
	      this_player());
	    message("system", "Please log out and log back in.", ob);
	    return 1;
	}
	exec(player_ob, ob);
	inv=deep_inventory(ob);
	if(sizeof(inv)) inv->eventMove(ROOM_FURNACE);
	player_ob->Setup();
	ob->eventDestruct();
	inv=deep_inventory(player_ob);
	if(sizeof(inv)) inv->eventMove(ROOM_FURNACE);
	message("system", "You are now a player.", player_ob);
	message("system", (string)player_ob->GetName() + " is now a player!",
	  this_player());
	if( file_size(file+__SAVE_EXTENSION__) > -1 ) rm(file+__SAVE_EXTENSION__);
    }
    return 1;
}

string GetKeyName() { return PlayerName; }
