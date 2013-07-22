#include "addpost.h"

//#include <Wt/WTextEdit>
//#include <Wt/WLabel>
//#include <Wt/Utils>

////////////////////////////////////////
//Constructor addPost starts here     //
////////////////////////////////////////

addPost::addPost(WContainerWidget *parent) : WContainerWidget(parent), sqlite3("blog.db")
{

//setting database connection 
    sessionpost.setConnection(sqlite3);

//mapping classes Post to table post
//	      category to table category_table

    sessionpost.mapClass<Post>("post");
    sessionpost.mapClass<Category>("category_table");

//To see the sql queries in terminal during run time    
    sqlite3.setProperty("show-queries", "true");
    
//Creating tables
   try {
	sessionpost.createTables();
	cerr<<"created database" <<endl;
  }

//if tables already exists then this 
  catch(exception& e) {
	cerr<<e.what() <<endl;
	cerr<<"Using existing database"<<endl;
  }

   add_new = new WContainerWidget(this);

//title of post
   WText *title_text = new WText("Title",add_new);
   
   name_edit = new WLineEdit(add_new);
   add_new->addWidget(new WBreak());


/*///////////////////  UNDER CONSTRUCTION  ////////////////////////////////////
     post_label = new WLabel("Comments:",add_new);			      |
     content_edit = new WTextEdit("", add_new);				      |
     post_label->setBuddy(content_edit);				      |
//____________________________________________________________________________|
*/ 
 
// content of post 
   content_edit = new WTextArea(add_new);
   add_new->addWidget(new WBreak());

   catgroup = new WButtonGroup();
   try{
   {
	dbo::Transaction transaction(sessionpost);
	dbo::ptr<Category> category_ptr = sessionpost.find<Category>().where("categoryname=?").bind("Music");
	std::string music = category_ptr->categoryname;

	showcategory();

	transaction.commit();
   }}

   catch(exception &e){
	entercategory();
	showcategory();
}
 

   WPushButton *submit_button = new WPushButton("Publish", add_new);
   submit_button->clicked().connect(this, &addPost::enterpost);
   add_new->addWidget(new WBreak());
}

void addPost::stringcategory()
{
	for(auto i: category_btn)
	{

		if(i->isChecked())
		string_cat = i->text().toUTF8();
	}
}

void addPost::enterpost()
{
	stringcategory();

        {
        dbo::Transaction transaction(sessionpost);
	
        Post *post = new Post();
        post->postname    = name_edit->text().toUTF8();
        post->postcontent = content_edit->text().toUTF8();
	
        dbo::ptr<Post> ptrpost = sessionpost.add(post);

	dbo::ptr<Category> checked_category = sessionpost.find<Category>().where("categoryname = ?").bind(string_cat);
	ptrpost.modify()->category_ptr = checked_category;

        transaction.commit();
        }
	add_new->addWidget(new WText("post updated successfully"));
}

void addPost::entercategory()
{
	{
	dbo::Transaction transaction(sessionpost);
	
	Category *cat_name = new Category();
	cat_name->categoryname = "Music";
	Category *cat_name2 = new Category();
	cat_name2->categoryname = "Education";
	
	dbo::ptr<Category> catptr = sessionpost.add(cat_name);
	dbo::ptr<Category> cat2ptr= sessionpost.add(cat_name2);
	transaction.commit();
	}
}

void addPost::showcategory()
{
	{
	dbo::Transaction transaction(sessionpost);
	
	cat kat = sessionpost.find<Category>();

	for(auto i: kat){

		WRadioButton* btn = new WRadioButton((i)->categoryname, add_new);
	
		category_btn.push_back(btn);		
	
		catgroup->addButton(btn);
	      }
	}
}
