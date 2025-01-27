#ifndef _MY_LIST_H_
#define _MY_LIST_H_

// Односвязный список
#include <memory>

template<typename T>
struct Node
{
	T val;
	Node* next = nullptr;

	Node(const T& val_, Node* next_)
		: val(val_)
		, next(next_)
	{}

	/// Получить указатель на элемент списка
	T* ptr() noexcept
	{
		return &val;
	}
};

template<typename T, typename Alloc = std::allocator<T> >
class MyList
{
	using Node_ = Node<T>;
	using NodeAlloc = typename Alloc::template rebind<Node_>::other;

public:
	struct Iterator : public std::iterator<std::forward_iterator_tag, Node_>
	{
		Iterator(Node_ *node_) noexcept : node(node_) {}

		T operator*() const noexcept
		{
			return *node->ptr();
		}

		T* operator->() const noexcept
		{
			return node->ptr();
		}

		Iterator& operator++() noexcept
		{
			node = node->next;
			return *this;
		}

		friend bool operator==(const Iterator& x, const Iterator& y) noexcept
		{
			return x.node == y.node;
		}

		friend bool operator!=(const Iterator& x, const Iterator& y) noexcept
		{
			return x.node != y.node;
		}

		Node_ *node;
	};
	 
	MyList()
	{
		before = new Node_(T(), head);
	}

	~MyList()
	{
		Node_* nodeCur = head;
		while (nodeCur)
		{
			Node_* next = nodeCur->next;
			alloc.destroy(nodeCur);
			alloc.deallocate(nodeCur, 1);
			nodeCur = next;
		}
		delete before;
	}

	Iterator begin() noexcept
	{
		return Iterator(head);
	}

	Iterator end() noexcept
	{
		return Iterator(nullptr);
	}

	Iterator begin_() noexcept
	{
		return Iterator(before);
	}

	void push_front(const T& val)
	{
		Node_* nodeCur = alloc.allocate(1);
		alloc.construct(nodeCur, val, head);
		head = nodeCur;
	}

	Iterator insert_after(Iterator pos, const T& val)
	{
		Node_* nodeCur = alloc.allocate(1);
		alloc.construct(nodeCur, val, pos.node->next);
		pos.node->next = nodeCur;

		if (pos == Iterator(before))
			head = nodeCur;
		return Iterator(nodeCur);
	}

private:
	Node_*										before = nullptr;
	Node_*										head = nullptr;
	NodeAlloc									alloc;
};

#endif /* _MY_LIST_H_ */
