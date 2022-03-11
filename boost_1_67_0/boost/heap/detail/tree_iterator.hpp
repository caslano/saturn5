// boost heap: node tree iterator helper classes
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP
#define BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP

#include <functional>
#include <vector>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/conditional.hpp>
#include <queue>

namespace boost  {
namespace heap   {
namespace detail {


template<typename type>
struct identity
{
    type& operator()(type& x) const BOOST_NOEXCEPT
    { return x; }

    const type& operator()(const type& x) const BOOST_NOEXCEPT
    { return x; }
};

template<typename Node>
struct dereferencer
{
    template <typename Iterator>
    Node * operator()(Iterator const & it)
    {
        return static_cast<Node *>(*it);
    }
};

template<typename Node>
struct pointer_to_reference
{
    template <typename Iterator>
    const Node * operator()(Iterator const & it)
    {
        return static_cast<const Node *>(&*it);
    }
};


template <typename HandleType,
          typename Alloc,
          typename ValueCompare
         >
struct unordered_tree_iterator_storage
{
    unordered_tree_iterator_storage(ValueCompare const & cmp)
    {}

    void push(HandleType h)
    {
        data_.push_back(h);
    }

    HandleType const & top(void)
    {
        return data_.back();
    }

    void pop(void)
    {
        data_.pop_back();
    }

    bool empty(void) const
    {
        return data_.empty();
    }

#ifdef BOOST_NO_CXX11_ALLOCATOR
    std::vector<HandleType, typename Alloc::template rebind<HandleType>::other > data_;
#else
    std::vector<HandleType, typename std::allocator_traits<Alloc>::template rebind_alloc<HandleType> > data_;
#endif
};

template <typename ValueType,
          typename HandleType,
          typename Alloc,
          typename ValueCompare,
          typename ValueExtractor
         >
struct ordered_tree_iterator_storage:
    ValueExtractor
{
    struct compare_values_by_handle:
        ValueExtractor,
        ValueCompare
    {
        compare_values_by_handle(ValueCompare const & cmp):
            ValueCompare(cmp)
        {}

        bool operator()(HandleType const & lhs, HandleType const & rhs) const
        {
            ValueType const & lhs_value = ValueExtractor::operator()(lhs->value);
            ValueType const & rhs_value = ValueExtractor::operator()(rhs->value);
            return ValueCompare::operator()(lhs_value, rhs_value);
        }
    };

    ordered_tree_iterator_storage(ValueCompare const & cmp):
        data_(compare_values_by_handle(cmp))
    {}

    void push(HandleType h)
    {
        data_.push(h);
    }

    void pop(void)
    {
        data_.pop();
    }

    HandleType const & top(void)
    {
        return data_.top();
    }

    bool empty(void) const BOOST_NOEXCEPT
    {
        return data_.empty();
    }

    std::priority_queue<HandleType,
#ifdef BOOST_NO_CXX11_ALLOCATOR
                        std::vector<HandleType, typename Alloc::template rebind<HandleType>::other>,
#else
                        std::vector<HandleType, typename std::allocator_traits<Alloc>::template rebind_alloc<HandleType> >,
#endif
                        compare_values_by_handle> data_;
};


/* tree iterator helper class
 *
 * Requirements:
 * Node provides child_iterator
 * ValueExtractor can convert Node->value to ValueType
 *
 * */
template <typename Node,
          typename ValueType,
          typename Alloc = std::allocator<Node>,
          typename ValueExtractor = identity<typename Node::value_type>,
          typename PointerExtractor = dereferencer<Node>,
          bool check_null_pointer = false,
          bool ordered_iterator = false,
          typename ValueCompare = std::less<ValueType>
         >
class tree_iterator:
    public boost::iterator_adaptor<tree_iterator<Node,
                                                 ValueType,
                                                 Alloc,
                                                 ValueExtractor,
                                                 PointerExtractor,
                                                 check_null_pointer,
                                                 ordered_iterator,
                                                 ValueCompare
                                                >,
                                   const Node *,
                                   ValueType,
                                   boost::forward_traversal_tag
                                  >,
    ValueExtractor,
    PointerExtractor
{
    typedef boost::iterator_adaptor<tree_iterator<Node,
                                                  ValueType,
                                                  Alloc,
                                                  ValueExtractor,
                                                  PointerExtractor,
                                                  check_null_pointer,
                                                  ordered_iterator,
                                                  ValueCompare
                                                 >,
                                    const Node *,
                                    ValueType,
                                    boost::forward_traversal_tag
                                   > adaptor_type;

    friend class boost::iterator_core_access;

    typedef typename boost::conditional< ordered_iterator,
                                       ordered_tree_iterator_storage<ValueType, const Node*, Alloc, ValueCompare, ValueExtractor>,
                                       unordered_tree_iterator_storage<const Node*, Alloc, ValueCompare>
                                     >::type
        unvisited_node_container;

public:
    tree_iterator(void):
        adaptor_type(0), unvisited_nodes(ValueCompare())
    {}

    tree_iterator(ValueCompare const & cmp):
        adaptor_type(0), unvisited_nodes(cmp)
    {}

    tree_iterator(const Node * it, ValueCompare const & cmp):
        adaptor_type(it), unvisited_nodes(cmp)
    {
        if (it)
            discover_nodes(it);
    }

    /* fills the iterator from a list of possible top nodes */
    template <typename NodePointerIterator>
    tree_iterator(NodePointerIterator begin, NodePointerIterator end, const Node * top_node, ValueCompare const & cmp):
        adaptor_type(0), unvisited_nodes(cmp)
    {
        BOOST_STATIC_ASSERT(ordered_iterator);
        if (begin == end)
            return;

        adaptor_type::base_reference() = top_node;
        discover_nodes(top_node);

        for (NodePointerIterator it = begin; it != end; ++it) {
            const Node * current_node = static_cast<const Node*>(&*it);
            if (current_node != top_node)
                unvisited_nodes.push(current_node);
        }
    }

    bool operator!=(tree_iterator const & rhs) const
    {
        return adaptor_type::base() != rhs.base();
    }

    bool operator==(tree_iterator const & rhs) const
    {
        return !operator!=(rhs);
    }

    const Node * get_node() const
    {
        return adaptor_type::base_reference();
    }

private:
    void increment(void)
    {
        if (unvisited_nodes.empty())
            adaptor_type::base_reference() = 0;
        else {
            const Node * next = unvisited_nodes.top();
            unvisited_nodes.pop();
            discover_nodes(next);
            adaptor_type::base_reference() = next;
        }
    }

    ValueType const & dereference() const
    {
        return ValueExtractor::operator()(adaptor_type::base_reference()->value);
    }

    void discover_nodes(const Node * n)
    {
        for (typename Node::const_child_iterator it = n->children.begin(); it != n->children.end(); ++it) {
            const Node * n = PointerExtractor::operator()(it);
            if (check_null_pointer && n == NULL)
                continue;
            unvisited_nodes.push(n);
        }
    }

    unvisited_node_container unvisited_nodes;
};

template <typename Node, typename NodeList>
struct list_iterator_converter
{
    typename NodeList::const_iterator operator()(const Node * node)
    {
        return NodeList::s_iterator_to(*node);
    }

    Node * operator()(typename NodeList::const_iterator it)
    {
        return const_cast<Node*>(static_cast<const Node*>(&*it));
    }
};

template <typename Node,
          typename NodeIterator,
          typename ValueType,
          typename ValueExtractor = identity<typename Node::value_type>,
          typename IteratorCoverter = identity<NodeIterator>
         >
class recursive_tree_iterator:
    public boost::iterator_adaptor<recursive_tree_iterator<Node,
                                                           NodeIterator,
                                                           ValueType,
                                                           ValueExtractor,
                                                           IteratorCoverter
                                                          >,
                                    NodeIterator,
                                    ValueType const,
                                    boost::bidirectional_traversal_tag>,
    ValueExtractor, IteratorCoverter
{
    typedef boost::iterator_adaptor<recursive_tree_iterator<Node,
                                                            NodeIterator,
                                                            ValueType,
                                                            ValueExtractor,
                                                            IteratorCoverter
                                                           >,
                                    NodeIterator,
                                    ValueType const,
                                    boost::bidirectional_traversal_tag> adaptor_type;

    friend class boost::iterator_core_access;


public:
    recursive_tree_iterator(void):
        adaptor_type(0)
    {}

    explicit recursive_tree_iterator(NodeIterator const & it):
        adaptor_type(it)
    {}

    void increment(void)
    {
        NodeIterator next = adaptor_type::base_reference();

        const Node * n = get_node(next);
        if (n->children.empty()) {
            const Node * parent = get_node(next)->get_parent();

            ++next;

            while (true) {
                if (parent == NULL || next != parent->children.end())
                    break;

                next = IteratorCoverter::operator()(parent);
                parent = get_node(next)->get_parent();
                ++next;
            }
        } else
            next = n->children.begin();

        adaptor_type::base_reference() = next;
        return;
    }

    ValueType const & dereference() const
    {
        return ValueExtractor::operator()(get_node(adaptor_type::base_reference())->value);
    }

    static const Node * get_node(NodeIterator const & it)
    {
        return static_cast<const Node *>(&*it);
    }

    const Node * get_node() const
    {
        return get_node(adaptor_type::base_reference());
    }
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP */

/* tree_iterator.hpp
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
*/