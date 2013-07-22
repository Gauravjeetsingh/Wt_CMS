#ifndef WT_CMS
#define WT_CMS

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WServer>
#include <Wt/WStackedWidget>
#include <Wt/WAnchor>
#include <Wt/WLink>

#include "addpost.h"
#include "showpost.h"

using namespace Wt;

class fApplication: public WApplication
{
public:
	fApplication(const WEnvironment& env);
	addPost *add;
	showPost *show;
};

#endif
