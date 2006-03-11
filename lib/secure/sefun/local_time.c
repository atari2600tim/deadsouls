#include <lib.h>
#include <config.h>
#include <daemons.h>

string tz;

string query_tz(){
    string zone;
    zone = read_file("/cfg/timezone.cfg")[0..2];
    if(!zone) zone = "GMT";
    return zone;
}

mixed local_ctime(int i){
    return ctime(i + ((TIME_D->GetOffset(query_tz()) ) * 3600));
}

mixed local_time(mixed val){
    string *zonearray;
    string tzone,l_time, os;
    int timediff,offset;

    os = query_os_type();

    if(stringp(val)) {
	tzone =  upper_case(val);
	zonearray = explode(read_file("/cfg/timezones.cfg"),"\n");
	if(member_array(tzone,zonearray) == -1) tzone = query_tz();
	if(!tzone || tzone == "") tzone = query_tz();
	offset = "/daemon/time"-> GetOffset(tzone);
	offset += EXTRA_TIME_OFFSET;
	timediff = offset * 3600;
	if(os != "windows") l_time=ctime(time() + timediff);
	else l_time=ctime(time());
	return l_time;
    }
    if(intp(val)){
	mixed *stuff;
	offset = "/daemon/time"-> GetOffset(query_tz());
	offset *= 3600;
	stuff = localtime(time()+offset);
	stuff[9] = query_tz();
	return stuff;
    }

}

string set_tz(string str){
    string *zonearray;

    if(!str) return "Time zone unchanged.";

    tz = upper_case(str)[0..2];
    zonearray = explode(read_file("/cfg/timezones.cfg"),"\n");
    if(member_array(tz,zonearray) == -1) {
	return "Invalid time zone. Valid zones are: "+ implode(zonearray," ");
    }

    if(!archp(this_player())) return "You're not permitted to do this.";

    unguarded( (: write_file("/cfg/timezone.cfg",tz,1) :) );
    return "Mud time zone is now "+read_file("/cfg/timezone.cfg");
}