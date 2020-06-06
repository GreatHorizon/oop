#pragma once
#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(std::string const data, Node* pPrev, std::unique_ptr<Node>&& pNext)
			: m_data(data)
			, m_pPrev(pPrev)
			, m_pNext(std::move(pNext))
		{
		}

		std::string m_data;
		std::unique_ptr<Node> m_pNext;
		Node* m_pPrev;
	};

public:
	class CIterator
	{
		friend CStringList;
		CIterator(Node* node, bool isReversed);

	public:
		CIterator() = default;

		CIterator& operator ++();
		CIterator& operator --();
		std::string& operator *() const;
		bool operator == (CIterator const& rightIterator);
		bool operator != (CIterator const& rightIterator);
		bool IsReversed() const;

	private:
		Node* m_node = nullptr;
		bool m_isReversed;
	};

	CIterator begin();
	CIterator back();
	CIterator end();

	CIterator rbegin();
	CIterator rback();
	CIterator rend();

	CIterator const begin() const;
	CIterator const back() const;
	CIterator const end() const;

	CIterator const rbegin() const;
	CIterator const rback() const;
	CIterator const rend() const;

	void Append(std::string const& data);
	void Prepend(std::string const& data);
	void Insert(CIterator& iterator, std::string const& data);
	void Delete(CIterator& iterator);
	void Clear();

	std::string const& GetBackElement() const;
	std::string const& GetBeginElement() const;
	size_t GetSize() const;
	bool IsEmpty() const;
	~CStringList();

private:
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
	size_t m_size = 0;
};

