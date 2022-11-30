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

#include <boost/core/allocator_access.hpp>
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

    std::vector<HandleType, typename boost::allocator_rebind<Alloc, HandleType>::type> data_;
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
                        std::vector<HandleType, typename boost::allocator_rebind<Alloc, HandleType>::type>,
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