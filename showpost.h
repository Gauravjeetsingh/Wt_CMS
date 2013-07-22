#ifndef SHOW_POST_H
#define SHOW_POST_H

#include "Post.h"


class showPost : public WContainerWidget
{
public: showPost(WContainerWidget *parent);
	
	WContainerWidget *post_content;
	WText *titleOut, *contentOut, *categoryOut;

	dbo::Session sessionpost;
	dbo::backend::Sqlite3 sqlite3;

};
#endif
