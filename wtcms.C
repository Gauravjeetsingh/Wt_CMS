#include "wtcms.h"

static const char *blogurl = "/blog";

fApplication::fApplication(const WEnvironment& env) : WApplication(env)
{	
	WAnchor *add_post = new WAnchor((WLink::InternalPath, "/blog/add-new"), "Add post", root());
	WAnchor *show_post= new WAnchor((WLink::InternalPath, "/blog/post-archives"),"Posts", root());
	
	std::string pathstring = internalPath();

	if(pathstring == "/add-new") {
	add = new addPost(root());
	}

	else if(pathstring == "/post-archives") {
	show = new showPost(root());
	}

	else {
	WText *declare = new WText("You are awesome", root());
	}

}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
return new fApplication(env);
}

int main(int argc, char **argv)
{
try{
Wt::WServer server(argv[0]);

server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
server.addEntryPoint(Wt::Application, createApplication, blogurl);

if(server.start()){
Wt::WServer::waitForShutdown();
server.stop();
}
}
catch(Wt::WServer::Exception& e){
std::cerr<<e.what()<<std::endl;
}
catch(std::exception &e){
std::cerr<<"exception:"<<e.what()<<std::endl;
}
}
                                           

