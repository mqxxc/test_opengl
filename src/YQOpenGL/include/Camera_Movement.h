#pragma once
namespace YQ
{
	enum class Camera_Movement
	{
		eNone,
		eFORWARD = 1,
		eBACKWARD = eFORWARD << 1,
		eLEFT = eBACKWARD << 1,
		eRIGHT = eLEFT << 1,
		eTop = eRIGHT << 1,
		eBottom = eTop << 1
	};
}