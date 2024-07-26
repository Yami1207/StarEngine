#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

namespace StarEngine
{
	template<class T>
	struct Size
	{
		T	width;
		T	height;
	};

	template<class T>
	class Rect
	{
	public:
		Rect() : x(0), y(0)
		{
			size.width = x;
			size.height = y;
		}

		Rect(T x, T y, T width, T height)
		{
			this->x = x;
			this->y = y;
			size.width = width;
			size.height = height;
		}

		Rect(const Rect<T>& other)
		{
			this->x = other.x;
			this->y = other.y;
			size.width = other.width;
			size.height = other.height;
		}
	public:
		/**
		* @brief Set	���þ���
		* @param x		x������
		* @param y		y������
		* @param width	���
		* @param height	�߶�
		* @return
		*/
		INLINE void Set(T x, T y, T width, T height)
		{
			this->x = x;
			this->y = y;
			size.width = width;
			size.height = height;
		}

		/**
		* @brief Top	���ض�������
		* @return
		*/
		INLINE T Top() const
		{
			return y;
		}

		/**
		* @brief Bottom	���صײ�����
		* @return
		*/
		INLINE T Bottom() const
		{
			return y + size.height;
		}

		/**
		* @brief Left	�����������
		* @return
		*/
		INLINE T Left() const
		{
			return x;
		}

		/**
		* @brief Right	�����ұ�����
		* @return
		*/
		INLINE T Right() const
		{
			return x + size.width;
		}

		/**
		* @brief Width	���ؿ��
		* @return
		*/
		INLINE T Width() const
		{
			return size.width;
		}

		/**
		* @brief Height	���ظ߶�
		* @return
		*/
		INLINE T Height() const
		{
			return size.height;
		}

		/**
		* @brief ContainsPoint	�����Ƿ�����ھ���
		* @param x	x������
		* @param y	y������
		* @return
		*/
		INLINE sBoolean ContainsPoint(const T& x, const T& y) const
		{
			if (x >= this->x && x < this->x + size.width && y >= this->y && y < this->y + size.height)
				return sTrue;
			return sFalse;
		}

		/**
		 * @brief IntersectsRect	�����Ƿ��ཻ
		 * @param rect	���ζ���
		 * @return
		 */
		sBoolean IntersectsRect(const Rect<T>& rect) const
		{
			if (ContainsPoint(rect.x, rect.y))
				return sTrue;

			if (ContainsPoint(rect.x, rect.y + rect.size.height))
				return sTrue;

			if (ContainsPoint(rect.x + rect.size.width, rect.y))
				return sTrue;

			if (ContainsPoint(rect.x + rect.size.width, rect.y + rect.size.height))
				return sTrue;

			return sFalse;
		}

		INLINE Rect<T>& operator =(const Rect<T>& other)
		{
			x = other.x;
			y = other.y;
			size.width = other.width;
			size.height = other.height;
		}

		INLINE sBoolean operator ==(const Rect<T>& other)
		{
			if (x == other.x && y == other.y && size.width == other.size.width && size.height == other.size.height)
				return sTrue;
			return sFalse;
		}

		INLINE sBoolean operator !=(const Rect<T>& other)
		{
			if (x != other.x || y != other.y || size.width != other.size.width || size.height != other.size.height)
				return sTrue;
			return sFalse;
		}
	public:
		T		x, y;
		Size<T>	size;
	};

	typedef Rect<int32>	RectI;
	typedef Rect<F32>	RectF;
}

#endif
