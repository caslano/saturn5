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
Jfw5txJAdQipMvL2YmMmW5JfoQ51MVU0+RRHvUD5EEH5v18hG3NJ36rn6/qmjfTyQW4B32pblrPfGShjGx+reihZKhWfHyEhVbqgRx+Bm4rKjqGhOt8I1UmH6kxl1XkkSnVGXRGjOkhwBi3/avfvuXBO270ooj6H6w4hVqrOM2Lpl1LZriNrnrVAkqjkP976Qw3iwouFf0UiygY8Ihj67eekdqwsl/hXYOO/UKFRm4GEivsYFkvl6EfBlHjPQl0/wrXm8GiXMPygFryEd+XTiLifgTg+lTL7Qhb7nIjYR81gsaM8hgmgCexEDmJdt5pUYPDlFJ/7L1aBCnHfzKAkAyo9sXI/75nPahKL7Z8vHQ2CMxZJdgwmeTQvkHvBpzQXWNoO9rY/RfoOp9K78NxcYD2AH43/6VOlZ7CerVRr/jiEGB4Az6n3obxbrupTDtupc0Te4ux23PLQuaLpiVqRUKDE6pSmWU3+CYaayerl1BiRwYeNLiJb55YW91m8jimbmLloYj6/kJsYrSTTp2glIeZ4HtNhU1Xf/IjXiCGexztgeVRgma2hSYlCw1OAJO6di83cWRdbeKwOcw9aiimGGQH4/bVL0pjv+UMH7NOB3fOMDHSpu8p5LVTmdndpJDeqSeCeKzgzXIHnq5iTdgm5WEL2TE7H+xHtS/jiTtsX6tJK3dy64Fwfen01aJLtCx+rqL4QYCNRWb72ispS4QpcRb73ll+hu6hdPsP/FbU3ddzevM2Tl7uj2pvtXn2rxjc453MkGMgDDNneoC947zJqcDZxg/Mp91dSCc7FGF/kMrw+jF7pgyhxLIA4mmbJ/aZZOq1OjVbO6zzFvAm6N9G/FNeEjxO90QCn+szlsobZmYK5l4mT5C1ob3YgCTneg+t3OP4spyaH2xui7TFqa/La0dIclpS41RfOkx3MJF50J1pAR8sl/4YGhu2rqOL9UD28QFQ8eFZZENWZzwPb1lygG1NVUAuz4TKe06UpbcSUT1ecwPXgswr9/CLKvryVul3S5MeZWVZZ1iZPbQf0Qy/QpXKs9lHeGYyIG0nftKMtKlzPPAG9mKePjz1tam+y8fwENAnjLFCMFaCVRz4EXN0BTY/21AkT0ES8dekVShycVi+7lLNWv5hF2wv3USryaRHCHnin8OM0+OYO8IE+j+Kxi/uUxGO8d+kf6Eif2umedWjlPQ9Tadov0e/lq0+kDHD3YL4UwEII4OGZuuecXwpafD90qiGx2xo0P0k8hLnpaJEmmdMsFWl64KMjZv/x+g77iXMvjX2fOT/2/Z7y2Pd5HeD3XRL7PnF07PvpHfL7zBv7PqED/qQO+H8ai5/vczrqfrqRWg9DO1mn8hEzX0oYt6vdPooZD+tpHg2bj2YVOUgz+ZLEWQ0ayzQb1mFtOq7VFme37VLG5uSXRu1FHTG+E4fzLvWkcUQbmxiXsWWcHcNkNZOBrVRXXR63SfMk3n6RDNWtjtV9HGaO15+73JxyBKigU9986xwym0iG2Gd4KzzrRqJ2jlbb5jJmNspOribr61lNOftbE2lkgrYDc0pUyvoNyQYx0DQrycYkJbnb69VfcHlP81SdDaVMU4/Mixh2DoTPJ7Y8rBpLzp5oRpXqdTCkSy2byrRQidg0YkFqc4GDKnkP7uoV8vZPicj77PCSVLUW3bx3GuOH1SUZYI5AJt7ztBz3Ad7Ljp/VD7nxz5zd1G15hnVWnjVjji5P3RS9PDwDsLOJf21qcwmXSn0VQwcyoXwRv0pfZW8gBSSHF6eq7VWUkGq7Q/PIAuKdwYlQJku+1IRe1bM0vrjVI1BT1oXqWcdU6+VHtxclW162XvRvQWZfjJEWyoecEWW8tDo=
*/