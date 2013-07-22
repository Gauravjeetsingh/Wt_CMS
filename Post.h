#ifndef POST_H_
#define POST_H_

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/SqlConnection>

#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>

#include <string>

using namespace std;
using namespace Wt;
namespace dbo = Wt::Dbo;

class Post;
class Category;

typedef dbo::collection< dbo::ptr<Post> > Posts;
typedef dbo::collection< dbo::ptr<Category> > cat;

class Post {
public: string postname, postcontent;
	
	dbo::ptr<Category> category_ptr;

	template<class Action>
	void persist(Action& a) {
	dbo::field(a, postname,    "postname");
	dbo::field(a, postcontent, "postcontent");
	
	dbo::belongsTo(a, category_ptr, "category");
	}
};

class Category {
public: string categoryname;
	
	dbo::collection< dbo::ptr<Post> > post_ptr;

	template<class Action>
	void persist(Action& a) {
	dbo::field(a, categoryname, "categoryname");

	dbo::hasMany(a, post_ptr, dbo::ManyToOne, "category");
	}
};

#endif
