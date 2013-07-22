#ifndef ADD_POST
#define ADD_POST

#include <Wt/WLineEdit>
#include <Wt/WTextArea>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>
#include <Wt/WPushButton>

#include "Post.h"

#include <vector>


class addPost : public WContainerWidget {
public: addPost(WContainerWidget *parent);

	void enterpost();
	void entercategory();
	void showcategory();
	void stringcategory();

	vector<WRadioButton*> category_btn;

	WContainerWidget *add_new;
	WLineEdit *name_edit;

	WTextArea *content_edit;
	WButtonGroup *catgroup;
//	WLabel *post_label;
	
	string string_cat;
	
	dbo::Session sessionpost;
	dbo::backend::Sqlite3 sqlite3;

};

#endif
