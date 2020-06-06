#include "stdafx.h"
#include "CStringList.h"

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Append(std::string const& data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();

	if (m_lastNode)
	{
		m_lastNode->m_pNext = std::move(newNode);
	}
	else
	{
		m_firstNode = std::move(newNode);
	}

	m_lastNode = newLastNode;
	m_size++;
}

void CStringList::Prepend(std::string const& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	if (newNode->m_pNext)
	{
		newNode->m_pNext->m_pPrev = newNode.get();
	}
	else
	{
		m_lastNode = newNode.get();
	}

	m_firstNode = std::move(newNode);
	m_size++;
}

std::string const& CStringList::GetBackElement() const
{
	if (m_lastNode)
	{
		return m_lastNode->m_data;
	}

	throw std::runtime_error("Element cant be got. List is empty\n");
}

std::string const& CStringList::GetBeginElement() const
{
	if (m_firstNode)
	{
		return m_firstNode->m_data;
	}

	throw std::runtime_error("Element cant be got. List is empty\n");
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

CStringList::~CStringList()
{
	Clear();
}

CStringList::CIterator::CIterator(Node* node, bool isReversed)
	: m_node(node)
	, m_isReversed(isReversed)
{
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get(), false);
}

CStringList::CIterator const CStringList::begin() const
{
	return CIterator(m_firstNode.get(), false);
}

CStringList::CIterator CStringList::back()
{
	return CIterator(m_lastNode, false);
}

CStringList::CIterator const CStringList::back() const
{
	return CIterator(m_lastNode, false);
}

CStringList::CIterator CStringList::end()
{
	return CIterator(nullptr, false);
}

CStringList::CIterator const CStringList::end() const
{
	return CIterator(nullptr, false);
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator const CStringList::rbegin() const
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator CStringList::rback()
{
	return CIterator(m_firstNode.get(), true);
}

CStringList::CIterator const CStringList::rback() const
{
	return CIterator(m_firstNode.get(), true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(nullptr, true);
}

CStringList::CIterator const CStringList::rend() const
{
	return CIterator(nullptr, true);
}

void CStringList::Insert(CIterator& iterator, std::string const& data)
{
	if (!iterator.m_node)
	{
		throw std::runtime_error("Invalid position to insert element\n");
	}

	if (iterator == begin())
	{
		Prepend(data);
	}
	else if (iterator == back())
	{
		Append(data);
	}
	else
	{
		auto newNode = std::make_unique<Node>(data, iterator.m_node->m_pPrev, 
			std::move(iterator.m_node->m_pPrev->m_pNext));
		newNode->m_pNext->m_pPrev = newNode.get();
		newNode->m_pPrev->m_pNext = std::move(newNode);
		m_size++;
	}
}

void CStringList::Delete(CIterator& iterator)
{
	if (!iterator.m_node)
	{
		throw std::runtime_error("Invalid element to be deleted");
	}

	if (iterator.m_node == m_lastNode)
	{
		if (m_lastNode->m_pPrev)
		{
			m_lastNode = iterator.m_node->m_pPrev;
			iterator.m_node->m_pPrev->m_pNext = nullptr;
		}
		else
		{
			m_firstNode = nullptr;
			m_lastNode = nullptr;
		}
	}
	else if (iterator.m_node == m_firstNode.get())
	{
		m_firstNode = std::move(iterator.m_node->m_pNext);
		m_firstNode->m_pPrev = nullptr;
	}
	else
	{
		iterator.m_node->m_pNext->m_pPrev = iterator.m_node->m_pPrev;
		iterator.m_node->m_pPrev->m_pNext = std::move(iterator.m_node->m_pNext);
	}
	m_size--;
	iterator.m_node = nullptr;
}

void CStringList::Clear()
{	
	for (auto it = begin(); it != end(); it = begin())
	{
		Delete(it);
	}
}


std::string& CStringList::CIterator::operator*() const
{
	if (m_node)
	{
		return m_node->m_data;
	}

	throw std::runtime_error("Empty iterator cant be dereferenced\n");
	
}

bool CStringList::CIterator::IsReversed() const
{
	return m_isReversed;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (!m_node)
	{
		throw std::runtime_error("Iterator cant be incremented");
	}

	if (IsReversed())
	{
		m_node = m_node->m_pPrev;
	}
	else
	{
		m_node = m_node->m_pNext.get();
	}

	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (!m_node)
	{
		throw std::runtime_error("Iterator cant be incremented\n");
	}

	if (IsReversed())
	{
		m_node = m_node->m_pNext.get();
	}
	else
	{
		m_node = m_node->m_pPrev;
	}

	return *this;
}

bool CStringList::CIterator::operator==(CIterator const& rightIterator)
{
	return this->m_node == rightIterator.m_node;
}

bool CStringList::CIterator::operator!=(CIterator const& rightIterator)
{
	return !(*this == rightIterator);
}
