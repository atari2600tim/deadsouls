#include <lib.h>
#include <dirs.h>
#include <daemons.h>
#include <sockets.h>

inherit LIB_DAEMON;
inherit LIB_CGI;
mapping UploadsMap = ([]);

void validate(){
    if(!(int)master()->valid_apply(({ "SECURE", "ASSIST" })) &&
      strsrch(base_name(previous_object()), SOCKET_HTTP)){
        string offender = identify(previous_object(-1));
        debug("upload.c SECURITY VIOLATION: "+offender+" ",get_stack(),"red");
        log_file("security", "\n"+timestamp()+" upload.c breach: "+offender+" "+get_stack());
        error("upload.c SECURITY VIOLATION: "+offender+" "+get_stack());
    }
}

string gateway(mixed args) {
    string err, full_name, path, junk1, junk2;
    int i;
    object ob = previous_object();
    string current_page = ob->GetReferer();
    mapping cookie = ob->GetCookie();
    string name = cookie["name"];
    string shib = cookie["shib"];
    string ret = "";

    //tc("CHANLOGS GATEWAY","red");

    if(ENABLE_CREWEB){
        string *logfiles = ({});
        validate();

        //tc("ob: "+identify(ob),"yellow");
        //tc("current_page: "+current_page,"white");

        if(!name || !shib || !WEB_SESSIONS_D->authenticate(name, shib)){
            ret += "Bad session. <br>";
            ret += "<META http-equiv=\"refresh\" content=\"1;URL=login.html\">";
            return ret;
        }

        foreach(string file in get_dir(DIR_CHANNEL_LOGS+"/")){
            if(!file_exists(DIR_CHANNEL_LOGS+"/"+file)) continue;
            ret += "<a href=\"/cgi/showlog.html?"+file+"+20\"";
            ret += ">"+file+"    (last modified "+ctime(stat(DIR_CHANNEL_LOGS+"/"+file)[1]);
            ret += ")</a><br>";
        }

        ret += "<br>";
    }

    else {
        ret += "CreWeb is disabled. To enable it: mudconfig creweb enable<br><br>";
    }
    ret += "<a href=\"/index.html\">Home</a><br>";
    ret += "<a href=\"http://dead-souls.net\">Dead Souls Home</a><br>";

    return ret;
}
