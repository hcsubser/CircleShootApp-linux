#ifndef __HELPSCREEN_H__
#define __HELPSCREEN_H__

#include <../SexyAppFramework/widget/HyperlinkWidget.h>
#include <../SexyAppFramework/widget/Widget.h>
#include <../SexyAppFramework/widget/ButtonListener.h>
#include <../SexyAppFramework/widget/CheckboxListener.h>

namespace Sexy
{
    class CircleCheckbox;
    class CircleButton;

    class HelpScreen : public Widget, public ButtonListener, public CheckboxListener
    {
    private:
        Widget *mHelpWidget1;
        Widget *mHelpWidget2;
        Widget *mHelpWidget3;
        Widget *mHelpBack;
        CircleCheckbox *mShowHelpCheckbox;
        CircleButton *mOKButton;

    public:
        HelpScreen();
        virtual ~HelpScreen();


		virtual void					ButtonPress(int){}//virtual_fixme
		virtual void					ButtonDownTick	(int){}
		virtual void					ButtonMouseEnter(int){}
		virtual void					ButtonMouseLeave(int){}
		virtual void					ButtonMouseMove(int, int, int){}



        virtual void Resize(int theX, int theY, int theWidth, int theHeight);
        virtual void Draw(Graphics *g);
        virtual void AddedToManager(WidgetManager *theWidgetManager);
        virtual void RemovedFromManager(WidgetManager *theWidgetManager);
        virtual void ButtonDepress(int theId);
        virtual void CheckboxChecked(int theId, bool checked);
        virtual void KeyChar(char theChar);
    };

};

#endif