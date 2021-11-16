#pragma once

#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW

#include "vo_transformed_view.hpp"


class ViewInterface :
	public olc::PixelGameEngine 
{
private:
	olc::TileTransformedView tv;
public:

	ViewInterface(std::shared_ptr<interpreter> i, std::shared_ptr<callable> onUserUpdate)
		:m_interpreter{ i }, m_onUserUpdate{ onUserUpdate }{}

	bool OnUserCreate() override
	{
		tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 8, 8 });

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Handle Pan & Zoom
		if (GetMouse(1).bPressed) tv.StartPan(GetMousePos());
		if (GetMouse(1).bHeld) tv.UpdatePan(GetMousePos());
		if (GetMouse(1).bReleased) tv.EndPan(GetMousePos());
		if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(1.5f, GetMousePos());
		if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.75f, GetMousePos());

		// Clear World
		Clear(olc::BLACK);
		
		if (m_onUserUpdate != nullptr) {
			std::vector<std::any> arguments = { fElapsedTime };
			 return m_onUserUpdate->safeCall(m_interpreter, _args(arguments), nullptr);
		}

		return true;
	}
private:
	std::shared_ptr<interpreter> m_interpreter;
	std::shared_ptr<callable> m_onUserUpdate;
};