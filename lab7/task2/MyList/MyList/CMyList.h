#pragma once
#include <stdexcept>
#include <optional>
#include <memory>
#include <algorithm>

template <typename T>
class CMyList
{	
	struct Node
	{
		Node(std::optional<T> data, Node* pPrev, std::unique_ptr<Node>&& pNext)
			: m_data(std::move(data))
			, m_pPrev(pPrev)
			, m_pNext(std::move(pNext))
		{
		}

		std::optional<T> m_data;
		Node* m_pPrev;
		std::unique_ptr<Node> m_pNext;
	};

public:
	class CIterator
	{
		friend CMyList;

		CIterator(Node* node, bool isReversed)
			: m_node(node)
			, m_isReversed(isReversed)
		{
		}

	public:
		CIterator() = default;

		CIterator& operator++()
		{
			if (IsReversed())
			{
				if (!m_node->m_pPrev)
				{
					throw std::runtime_error("Iterator cant be incremented\n");
				}

				m_node = m_node->m_pPrev;
			}
			else
			{
				if (!m_node->m_pNext)
				{
					throw std::runtime_error("Iterator cant be incremented\n");
				}

				m_node = m_node->m_pNext.get();
			}

			return *this;
		}

		CIterator& operator--()
		{
			if (IsReversed())
			{
				if (!m_node->m_pNext)
				{
					throw std::runtime_error("Iterator cant be incremented\n");
				}

				m_node = m_node->m_pNext.get();

			}
			else
			{
				if (!m_node->m_pPrev)
				{
					throw std::runtime_error("Iterator cant be incremented\n");
				}

				m_node = m_node->m_pPrev;
			}

			return *this;
		}

		bool operator ==(CIterator const& rightIterator)
		{
			return this->m_node == rightIterator.m_node;
		}

		bool operator !=(CIterator const& rightIterator)
		{
			return !(*this == rightIterator);
		}

		T const operator *() const
		{
			if (!m_node->m_pPrev || !m_node->m_pNext)
			{
				throw std::runtime_error("Empty iterator cant be dereferenced\n");
			}

			return m_node->m_data.value();
		}

		bool IsReversed() const
		{
			return m_isReversed;
		}

	private:
		Node* m_node = nullptr;
		bool m_isReversed;
	};

	CIterator begin()
	{
		return CIterator(m_firstNode->m_pNext.get(), false);
	};

	CIterator const begin() const
	{
		return CIterator(m_firstNode->m_pNext.get(), false);
	}

	CIterator back()
	{
		return CIterator(m_lastNode->m_pPrev, false);
	}

	CIterator const back() const
	{
		return CIterator(m_lastNode->m_pPrev, false);
	}

	CIterator end()
	{
		return CIterator(m_lastNode, false);
	}

	CIterator const end() const
	{
		return CIterator(m_lastNode, false);
	}

	CIterator rbegin()
	{
		return CIterator(m_lastNode->m_pPrev, true);
	} 

	CIterator const rbegin() const
	{
		return CIterator(m_lastNode->m_pPrev, true);
	}

	CIterator rback()
	{
		return CIterator(m_firstNode->m_pNext.get(), true);
	}

	CIterator const rback() const
	{
		return CIterator(m_firstNode->m_pNext.get(), true);
	}

	CIterator rend()
	{
		return CIterator(m_firstNode.get(), true);
	}

	CIterator const rend() const
	{
		return CIterator(m_firstNode.get(), true);
	}

	size_t GetSize()
	{
		return m_size;
	}

	T const GetBackElement() const
	{
		if (m_lastNode)
		{
			return m_lastNode->m_pPrev->m_data.value();
		}

		throw std::runtime_error("Element cant be got. List is empty\n");
	}

	T const GetBeginElement() const
	{
		if (m_firstNode->m_pNext)
		{
			return m_firstNode->m_pNext->m_data.value();
		}

		throw std::runtime_error("Element cant be got. List is empty\n");
	}

	CMyList()
	{
		m_firstNode = std::make_unique<Node>(std::nullopt, nullptr, nullptr);
	};

	~CMyList()
	{
		while (!IsEmpty())
		{
			Delete(begin());
		}

		m_firstNode = nullptr;
	}

	CMyList(CMyList const& list)
		: CMyList()
	{
		for (const auto& element : list)
		{
			Append(element);
		}
	}

	CMyList(CMyList& list)
	{
		std::swap(list.m_firstNode, m_firstNode);
		std::swap(list.m_lastNode, m_lastNode);
		std::swap(list.m_size, m_size);
	}

	CMyList& operator =(CMyList const& list)
	{
		if (std::addressof(list) != this)
		{
			CMyList tempList(list);
			std::swap(tempList, *this);
		}

		return *this;
	}

	CMyList& operator =(CMyList && list) noexcept
	{
		if (std::addressof(list) != this)
		{
			m_firstNode = std::move(list.m_firstNode);
			m_lastNode = list.m_lastNode;
			m_size = list.m_size;

			CMyList emptyList;
			list.m_firstNode = std::move(emptyList.m_firstNode);
			list.m_lastNode = emptyList.m_lastNode;
			list.m_size = emptyList.m_size;
		}

		return *this;
	}

	void Insert(CIterator iterator, T const data)
	{
		if (iterator == rend())
		{
			throw std::runtime_error("Invalid insert position\n");
		}

		if (IsEmpty())
		{
			m_firstNode->m_pNext = std::make_unique<Node>(std::nullopt, m_firstNode.get(), nullptr);
			m_lastNode = m_firstNode->m_pNext.get();
			iterator.m_node = m_lastNode;
		}

		auto newNode = std::make_unique<Node>(data, iterator.m_node->m_pPrev,
			std::move(iterator.m_node->m_pPrev->m_pNext));
		newNode->m_pNext->m_pPrev = newNode.get();
		newNode->m_pPrev->m_pNext = std::move(newNode);
		m_size++;
	}

	void Append(T data)
	{
		Insert(end(), data);
	};

	void Prepend(T data)
	{
		if (IsEmpty())
		{
			Insert(end(), data);
		}
		else
		{
			Insert(begin(), data);
		}
	}

	void Delete(CIterator iterator)
	{
		if (iterator == rend() || iterator == end())
		{
			throw std::runtime_error("Invalid element to be deleted\n");
		}

		if (GetSize() == 1)
		{
			m_firstNode->m_pNext = nullptr;
			m_lastNode = nullptr;
		}
		else
		{
			iterator.m_node->m_pNext->m_pPrev = iterator.m_node->m_pPrev;
			iterator.m_node->m_pPrev->m_pNext = std::move(iterator.m_node->m_pNext);
		}

		m_size--;
	}

	bool IsEmpty() const
	{
		return m_size == 0;
	};

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};