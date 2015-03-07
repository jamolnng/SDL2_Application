#pragma once

#include <vector>
#include <deque>

template< typename T > class CMemoryPool
{
	public:
		CMemoryPool(size_t preAllocated = 0)
		{
			m_nPoolIndex = 0;
			//m_fResizeRequired = false;
			//pre-allocate memory
			init(preAllocated);
		};

		~CMemoryPool(void) {};

		std::vector< T > pool(void)
		{
			return m_vecPool;
		}

		T& operator[](size_t i)
		{
			return m_vecPool.at(i);
		}

		T& at(size_t i)
		{
			return m_vecPool.at(i);
		}

		void dispose(void)
		{
			resetPool();
			m_vecPool.clear();
			init(0);
		}

		unsigned int size(void)
		{
			return m_vecPool.size();
		}

		void init(size_t nSizeOfPool)
		{
			m_vecPool.resize(nSizeOfPool);
		};

		void resetPool(void)
		{
			m_nPoolIndex = 0;

			/*if(m_fResizeRequired)
			{
				init(m_vecPool.size() + (m_deqOverspill.size() * 2));

				m_deqOverspill.clear();

				m_fResizeRequired = false;
			}*/
		};

		size_t getUsedIndex(void)
		{
			return m_nPoolIndex;
		}

		T* getNextPoolEntity(void)
		{
			if(m_nPoolIndex + 1 >= m_vecPool.size())
			{
				/*if(!m_fResizeRequired)
				{
					m_fResizeRequired = true;
				}*/

				init(m_vecPool.size() + 1);
				m_vecPool.push_back(T());

				//m_deqOverspill.push_back(T());
				//T* pNextElement = &m_deqOverspill.back();

				////pNextElement->Reset();
				//return pNextElement;
			}

			// Get next index
			++m_nPoolIndex;

			T* pNextElement = &m_vecPool[ m_nPoolIndex ];
			//pNextElement->Reset();

			return pNextElement;
		};

	private:
		//bool m_fResizeRequired;

		size_t m_nPoolIndex;
#pragma warning (push)
#pragma warning (disable : 4251)
		std::vector< T > m_vecPool;
		std::deque< T > m_deqOverspill;
#pragma warning (pop)
};