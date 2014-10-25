#pragma once
#include "IncludeForHeader.h"
#include "ui/UICheckBox.h"

Button * initButton(int iTag, Widget* root, Widget::ccWidgetTouchCallback callback);
ImageView * initImageView(int iTag, Widget* root);
CheckBox * initCheckBox(int iTag, Widget* root, const CheckBox::ccCheckBoxCallback& callback);
Layout * initRoot(const std::string& filename, Layer *layer);
Layout * initRootForCell(const std::string& filename, Layer *layer);
Layout * initLayout(int iTag, Widget* root, Widget::ccWidgetTouchCallback callback);

string itostr(int i);
string getString(char *sz);
Button* initUIButton(int tag, SEL_TouchEvent selector, Layout* root, Ref* target);

Time getCurrentTime();
Time str2MTime(const string &str);
Time str2MTimeForDB(const string &str);
string getShowTime(Time &mtime);
int cycleNum(bool bAdd, int iCount, int *idx);
