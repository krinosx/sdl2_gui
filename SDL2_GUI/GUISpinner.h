#pragma once
#include "GUIPanel.h"
#include "GUIScrollbar.h"
#include "GUITextField.h"
class GUISpinner :
	public GUIPanel
{

private:
	int currentValue = 0;
	int minValue = 0;
	int maxValue = 10;
	int pace = 1;
	GUITextField * editingField = nullptr;
	GUIScrollbar * scrollbar = nullptr;
	TTF_Font * font = NULL;

	std::function<void(GUITextField * editingField)> notifyEditing;

	void increment();
	void decrement();

public:
	GUISpinner(int x, int y, int w, int h, TTF_Font * font, int minValue, int maxValue );
	~GUISpinner();

	int getCurrentValue();
	void setCurrentvalue(int value);

	void draw(SDL_Renderer * renderer);
	void setMinValue(int minValue);
	void setMaxValue(int maxValue);
	void setPace(int pace);
	void setNotifyEditingListener(std::function<void(GUITextField * editingField)> editingListener);
};

