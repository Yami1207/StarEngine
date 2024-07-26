#ifndef __CORE_COLOR_H__
#define __CORE_COLOR_H__

namespace StarEngine
{
	class Color
	{
	public:
		Color();
		Color(const Color& other);
		Color(F32 _r, F32 _g, F32 _b, F32 _a = 1.0f);
		Color(uint32 argb);
		explicit Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255);
	public:
		void		Set(const Color& other);
		void		Set(F32 _r, F32 _g, F32 _b, F32 _a = 1.0f);

		/**
		*	设置颜色值
		*	@param value	颜色值(ARGB)
		*/
		void SetARGBPack(uint32 value);

		/**
		*	设置颜色值
		*	@param value	颜色值(RGBA)
		*/
		void SetRGBAPack(uint32 value);

		/**
		*	设置颜色值
		*	@param value	颜色值(ABGR)
		*/
		void SetABGRPack(uint32 value);

		void		Saturate();
		void		Lerp(const Color& from, const Color& to, F32 t);

		sBoolean	IsValidColor() const;

		uint32		GetARGBPack() const;
		uint32		GetRGBAPack() const;
		uint32		GetABGRPack() const;
	public:
		Color		operator +(const Color& other) const;
		Color		operator -(const Color& other) const;

		Color&		operator +=(const Color& other);
		Color&		operator -=(const Color& other);

		Color&		operator *=(F32 value);
		Color&		operator *=(const Color& other);
		
		Color		operator /(F32 value) const;
		Color&		operator /=(F32 value);

		Color		operator -() const;

		Color&		operator =(const Color& other);

		bool		operator ==(const Color&) const;
		bool		operator !=(const Color&) const;

		F32&		operator [](int32 nIndex);
		const F32&	operator [](int32 nIndex) const;
	public:
		union
		{
			F32 value[4];
			struct 
			{
				F32 r, g, b, a;
			};
		};
	public:
		static Color white;
		static Color black;

		static Color red;
		static Color green;
		static Color blue;
	};

	//////////////////////////////////////////////////////////////////////////
	Color operator *(F32 value, const Color& color);
	Color operator *(const Color& color, F32 value);
	Color operator *(const Color& c0, const Color& c1);
	
	bool operator <(const Color& c0, const Color& c1);
}

#include "Color.inl"

#endif
