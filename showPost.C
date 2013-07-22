#include "showpost.h"

showPost::showPost(WContainerWidget *parent) : WContainerWidget(parent), sqlite3("blog.db")
{
  sessionpost.setConnection(sqlite3);
  sessionpost.mapClass<Post>("post");
  sessionpost.mapClass<Category>("category_table");

   post_content = new WContainerWidget(this);
   {
	dbo::Transaction transaction(sessionpost);
	Posts posts = sessionpost.find<Post>();

	for(auto i: posts) {
	   titleOut=new WText ((i)->postname, post_content);
           post_content->addWidget(new WBreak());

           contentOut = new WText ((i)->postcontent, post_content);
           post_content->addWidget(new WBreak());
	   
	   post_content->addWidget(new WText("posted in "));
	
	   dbo::ptr<Category> findCategory = sessionpost.find<Category>().where("id = ?").bind((i)->category_ptr);
	   string outString = findCategory->categoryname;
	   categoryOut = new WText(outString, post_content);
	   
	  post_content->addWidget(new WBreak());
	  post_content->addWidget(new WBreak());
 
           }

        transaction.commit();
     }
}
