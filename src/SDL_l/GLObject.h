#pragma once

template <typename T> class GLObject
{
	protected:
		T value;

	public:
		/*GLObject(void);
		~GLObject(void);*/
		operator T (void)
		{
			return value;
		}

		virtual void dispose(void) = 0;
};