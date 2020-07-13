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
	template <typename T, bool IsConst>
	class CIterator
	{
		friend class CIterator<T, true>;
		friend CMyList;
		
		CIterator(Node* node)
			: m_node(node)
		{
		}

	public:
		using MyType = CIterator<T, IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;

		MyType& operator++()
		{
			if (!m_node->m_pNext)
			{
				throw std::runtime_error("Iterator cant be incremented\n");
			}

			m_node = m_node->m_pNext.get();
			return *this;
		}

		MyType operator++(int)
		{
			MyType& copy = *this;
			++*this;
			return copy;
		}

		MyType& operator--()
		{
				if (!m_node->m_pPrev->m_pPrev)
				{
					throw std::runtime_error("Iterator cant be incremented\n");
				}

				m_node = m_node->m_pPrev;
				return *this;
		}

		MyType operator--(int)
		{
			MyType& copy = *this;
			--*this;
			return this;
		}

		bool operator==(const MyType& other) const
		{
			return this->m_node == other.m_node;
		}

		bool operator !=(CIterator const& rightIterator)
		{
			return !(*this == rightIterator);
		}

		reference& operator *() const
		{
			if (!m_node->m_pPrev || !m_node->m_pNext)
			{
				throw std::runtime_error("Empty iterator cant be dereferenced\n");
			}

			return *m_node->m_data;
		}

	private:
		Node* m_node = nullptr;
	};

	using iterator = CIterator<T, false>;
	using const_iterator = CIterator<T, true>;

	iterator begin()
	{
		return { m_firstNode->m_pNext.get()};
	};

	const_iterator begin() const
	{
		return { m_firstNode->m_pNext.get() };
	}

	iterator end()
	{
		return { m_lastNode };
	}

	const_iterator end() const
	{
		return { m_lastNode };
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	} 

	std::reverse_iterator<const_iterator>  rbegin() const
	{
		return std::reverse_iterator<iterator>(end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}

	std::reverse_iterator<const_iterator> rend() const
	{
		return std::reverse_iterator<iterator>(begin());
	}

	size_t GetSize()
	{
		return m_size;
	}

	T const GetBackElement() const
	{
		if (!IsEmpty())
		{
			return m_lastNode->m_pPrev->m_data.value();
		}

		throw std::runtime_error("Element cant be got. List is empty\n");
	}

	T const GetBeginElement() const
	{
		if (!IsEmpty())
		{
			return m_firstNode->m_pNext->m_data.value();
		}

		throw std::runtime_error("Element cant be got. List is empty\n");
	}

	CMyList()
	{
		m_firstNode = std::make_unique<Node>(std::nullopt, nullptr, nullptr);
		m_firstNode->m_pNext = std::make_unique<Node>(std::nullopt, m_firstNode.get(), nullptr);
		m_lastNode = m_firstNode->m_pNext.get();
	};

	~CMyList()
	{
		Clear();
	}

	CMyList(CMyList const& list)
		: CMyList()
	{
		for (const auto& element : list)
		{
			Append(element);
		}
	}

	CMyList(CMyList&& list)
	{
		if (std::addressof(list) != this)
		{
			Clear();
			std::swap(m_size, list.m_size);
			std::swap(m_firstNode, list.m_firstNode);
			std::swap(m_lastNode, list.m_lastNode);
		}
	}

	CMyList& operator =(CMyList const& list)
	{
		if (std::addressof(list) != this)
		{
			Clear();
			CMyList tempList(list);
			std::swap(m_size, tempList.m_size);
			std::swap(m_firstNode, tempList.m_firstNode);
			std::swap(m_lastNode, tempList.m_lastNode);
		}

		return *this;
	}

	CMyList& operator =(CMyList && list)
	{
		if (std::addressof(list) != this)
		{
			Clear();
			std::swap(list.m_firstNode, m_firstNode);
			std::swap(list.m_lastNode, m_lastNode);
			std::swap(list.m_size, m_size);
		}

		return *this;
	}

	void Insert(iterator it, T const data)
	{
		auto newNode = std::make_unique<Node>(data, it.m_node->m_pPrev,
			std::move(it.m_node->m_pPrev->m_pNext));
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
		Insert(begin(), data);
	}

	void Delete(const iterator& it)
	{
		if (it == end())
		{
			throw std::runtime_error("Invalid element to be deleted\n");
		}

		it.m_node->m_pNext->m_pPrev = it.m_node->m_pPrev;
		it.m_node->m_pPrev->m_pNext = std::move(it.m_node->m_pNext);
		m_size--;
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			Delete(begin());
		}
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