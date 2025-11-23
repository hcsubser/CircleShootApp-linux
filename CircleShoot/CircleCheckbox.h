#ifndef __CIRCLECHECKBOX_H__
#define __CIRCLECHECKBOX_H__

#include <../SexyAppFramework/widget/Checkbox.h>

namespace Sexy
{

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	class CircleCheckbox : public Sexy::Checkbox
	{
	public:
		int mClickSound;

		CircleCheckbox(Image *theUncheckedImage, Image *theCheckedImage, int theId, CheckboxListener *theCheckboxListener);
		virtual ~CircleCheckbox();

		virtual void MouseDown(int theX, int theY, int theBtnNum, int theClickCount);
	};
}

#endif