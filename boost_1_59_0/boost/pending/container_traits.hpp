//  (C) Copyright Jeremy Siek 2004
//  (C) Copyright Thomas Claveirole 2010
//  (C) Copyright Ignacy Gawedzki 2010
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H
#define BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H

// Sure would be nice to be able to forward declare these
// instead of pulling in all the headers. Too bad that
// is not legal. There ought to be a standard <stlfwd> header. -JGS

#include <boost/next_prior.hpp>

#include <algorithm> // for std::remove
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
#include <unordered_set>
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
#include <unordered_map>
#endif

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_PENDING_FWD_TYPE(type) const type&
#define BOOST_PENDING_FWD_VALUE(type, var) (var)
#else
#define BOOST_PENDING_FWD_TYPE(type) type&&
#define BOOST_PENDING_FWD_VALUE(type, var) (std::forward< type >((var)))
#endif

// The content of this file is in 'graph_detail' because otherwise
// there will be name clashes with
// sandbox/boost/sequence_algo/container_traits.hpp
// The 'detail' subnamespace will still cause problems.
namespace boost
{
namespace graph_detail
{

    //======================================================================
    // Container Category Tags
    //
    //   They use virtual inheritance because there are lots of
    //   inheritance diamonds.

    struct container_tag
    {
    };
    struct forward_container_tag : virtual public container_tag
    {
    };
    struct reversible_container_tag : virtual public forward_container_tag
    {
    };
    struct random_access_container_tag : virtual public reversible_container_tag
    {
    };

    struct sequence_tag : virtual public forward_container_tag
    {
    };

    struct associative_container_tag : virtual public forward_container_tag
    {
    };

    struct sorted_associative_container_tag
    : virtual public associative_container_tag,
      virtual public reversible_container_tag
    {
    };

    struct front_insertion_sequence_tag : virtual public sequence_tag
    {
    };
    struct back_insertion_sequence_tag : virtual public sequence_tag
    {
    };

    struct unique_associative_container_tag
    : virtual public associative_container_tag
    {
    };
    struct multiple_associative_container_tag
    : virtual public associative_container_tag
    {
    };
    struct simple_associative_container_tag
    : virtual public associative_container_tag
    {
    };
    struct pair_associative_container_tag
    : virtual public associative_container_tag
    {
    };

    //======================================================================
    // Iterator Stability Tags
    //
    // Do mutating operations such as insert/erase/resize invalidate all
    // outstanding iterators?

    struct stable_tag
    {
    };
    struct unstable_tag
    {
    };

    //======================================================================
    // Container Traits Class and container_category() function

    // don't use this unless there is partial specialization
    template < class Container > struct container_traits
    {
        typedef typename Container::category category;
        typedef typename Container::iterator_stability iterator_stability;
    };

    // Use this as a compile-time assertion that X is stable
    inline void require_stable(stable_tag) {}

    // std::vector
    struct vector_tag : virtual public random_access_container_tag,
                        virtual public back_insertion_sequence_tag
    {
    };

    template < class T, class Alloc >
    vector_tag container_category(const std::vector< T, Alloc >&)
    {
        return vector_tag();
    }

    template < class T, class Alloc >
    unstable_tag iterator_stability(const std::vector< T, Alloc >&)
    {
        return unstable_tag();
    }

    template < class T, class Alloc >
    struct container_traits< std::vector< T, Alloc > >
    {
        typedef vector_tag category;
        typedef unstable_tag iterator_stability;
    };

    // std::list
    struct list_tag : virtual public reversible_container_tag,
                      virtual public back_insertion_sequence_tag
    // this causes problems for push_dispatch...
    //    virtual public front_insertion_sequence_tag
    {
    };

    template < class T, class Alloc >
    list_tag container_category(const std::list< T, Alloc >&)
    {
        return list_tag();
    }

    template < class T, class Alloc >
    stable_tag iterator_stability(const std::list< T, Alloc >&)
    {
        return stable_tag();
    }

    template < class T, class Alloc >
    struct container_traits< std::list< T, Alloc > >
    {
        typedef list_tag category;
        typedef stable_tag iterator_stability;
    };

    // std::set
    struct set_tag : virtual public sorted_associative_container_tag,
                     virtual public simple_associative_container_tag,
                     virtual public unique_associative_container_tag
    {
    };

    template < class Key, class Cmp, class Alloc >
    set_tag container_category(const std::set< Key, Cmp, Alloc >&)
    {
        return set_tag();
    }

    template < class Key, class Cmp, class Alloc >
    stable_tag iterator_stability(const std::set< Key, Cmp, Alloc >&)
    {
        return stable_tag();
    }

    template < class Key, class Cmp, class Alloc >
    struct container_traits< std::set< Key, Cmp, Alloc > >
    {
        typedef set_tag category;
        typedef stable_tag iterator_stability;
    };

    // std::multiset
    struct multiset_tag : virtual public sorted_associative_container_tag,
                          virtual public simple_associative_container_tag,
                          virtual public multiple_associative_container_tag
    {
    };

    template < class Key, class Cmp, class Alloc >
    multiset_tag container_category(const std::multiset< Key, Cmp, Alloc >&)
    {
        return multiset_tag();
    }

    template < class Key, class Cmp, class Alloc >
    stable_tag iterator_stability(const std::multiset< Key, Cmp, Alloc >&)
    {
        return stable_tag();
    }

    template < class Key, class Cmp, class Alloc >
    struct container_traits< std::multiset< Key, Cmp, Alloc > >
    {
        typedef multiset_tag category;
        typedef stable_tag iterator_stability;
    };

    // deque

    // std::map
    struct map_tag : virtual public sorted_associative_container_tag,
                     virtual public pair_associative_container_tag,
                     virtual public unique_associative_container_tag
    {
    };

    template < class Key, class T, class Cmp, class Alloc >
    struct container_traits< std::map< Key, T, Cmp, Alloc > >
    {
        typedef map_tag category;
        typedef stable_tag iterator_stability;
    };

    template < class Key, class T, class Cmp, class Alloc >
    map_tag container_category(const std::map< Key, T, Cmp, Alloc >&)
    {
        return map_tag();
    }

    template < class Key, class T, class Cmp, class Alloc >
    stable_tag iterator_stability(const std::map< Key, T, Cmp, Alloc >&)
    {
        return stable_tag();
    }

    // std::multimap
    struct multimap_tag : virtual public sorted_associative_container_tag,
                          virtual public pair_associative_container_tag,
                          virtual public multiple_associative_container_tag
    {
    };

    template < class Key, class T, class Cmp, class Alloc >
    struct container_traits< std::multimap< Key, T, Cmp, Alloc > >
    {
        typedef multimap_tag category;
        typedef stable_tag iterator_stability;
    };

    template < class Key, class T, class Cmp, class Alloc >
    multimap_tag container_category(const std::multimap< Key, T, Cmp, Alloc >&)
    {
        return multimap_tag();
    }

    template < class Key, class T, class Cmp, class Alloc >
    stable_tag iterator_stability(const std::multimap< Key, T, Cmp, Alloc >&)
    {
        return stable_tag();
    }

    // hash_set, hash_map

    struct unordered_set_tag : virtual public simple_associative_container_tag,
                               virtual public unique_associative_container_tag
    {
    };

    struct unordered_multiset_tag
    : virtual public simple_associative_container_tag,
      virtual public multiple_associative_container_tag
    {
    };

    struct unordered_map_tag : virtual public pair_associative_container_tag,
                               virtual public unique_associative_container_tag
    {
    };

    struct unordered_multimap_tag
    : virtual public pair_associative_container_tag,
      virtual public multiple_associative_container_tag
    {
    };

    template < class Key, class Eq, class Hash, class Alloc >
    struct container_traits< boost::unordered_set< Key, Eq, Hash, Alloc > >
    {
        typedef unordered_set_tag category;
        typedef unstable_tag iterator_stability;
    };
    template < class Key, class T, class Eq, class Hash, class Alloc >
    struct container_traits< boost::unordered_map< Key, T, Eq, Hash, Alloc > >
    {
        typedef unordered_map_tag category;
        typedef unstable_tag iterator_stability;
    };
    template < class Key, class Eq, class Hash, class Alloc >
    struct container_traits< boost::unordered_multiset< Key, Eq, Hash, Alloc > >
    {
        typedef unordered_multiset_tag category;
        typedef unstable_tag iterator_stability;
    };
    template < class Key, class T, class Eq, class Hash, class Alloc >
    struct container_traits<
        boost::unordered_multimap< Key, T, Eq, Hash, Alloc > >
    {
        typedef unordered_multimap_tag category;
        typedef unstable_tag iterator_stability;
    };

    template < class Key, class Eq, class Hash, class Alloc >
    unordered_set_tag container_category(
        const boost::unordered_set< Key, Eq, Hash, Alloc >&)
    {
        return unordered_set_tag();
    }

    template < class Key, class T, class Eq, class Hash, class Alloc >
    unordered_map_tag container_category(
        const boost::unordered_map< Key, T, Eq, Hash, Alloc >&)
    {
        return unordered_map_tag();
    }

    template < class Key, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const boost::unordered_set< Key, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }

    template < class Key, class T, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const boost::unordered_map< Key, T, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }
    template < class Key, class Eq, class Hash, class Alloc >
    unordered_multiset_tag container_category(
        const boost::unordered_multiset< Key, Eq, Hash, Alloc >&)
    {
        return unordered_multiset_tag();
    }

    template < class Key, class T, class Eq, class Hash, class Alloc >
    unordered_multimap_tag container_category(
        const boost::unordered_multimap< Key, T, Eq, Hash, Alloc >&)
    {
        return unordered_multimap_tag();
    }

    template < class Key, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const boost::unordered_multiset< Key, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }

    template < class Key, class T, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const boost::unordered_multimap< Key, T, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    struct container_traits< std::unordered_set< Key, Eq, Hash, Alloc > >
    {
        typedef unordered_set_tag category;
        typedef unstable_tag iterator_stability;
    };
#endif
#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    struct container_traits< std::unordered_map< Key, T, Eq, Hash, Alloc > >
    {
        typedef unordered_map_tag category;
        typedef unstable_tag iterator_stability;
    };
#endif
#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    struct container_traits< std::unordered_multiset< Key, Eq, Hash, Alloc > >
    {
        typedef unordered_multiset_tag category;
        typedef unstable_tag iterator_stability;
    };
#endif
#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    struct container_traits<
        std::unordered_multimap< Key, T, Eq, Hash, Alloc > >
    {
        typedef unordered_multimap_tag category;
        typedef unstable_tag iterator_stability;
    };
#endif
#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    unordered_set_tag container_category(
        const std::unordered_set< Key, Eq, Hash, Alloc >&)
    {
        return unordered_set_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    unordered_map_tag container_category(
        const std::unordered_map< Key, T, Eq, Hash, Alloc >&)
    {
        return unordered_map_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const std::unordered_set< Key, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const std::unordered_map< Key, T, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }
#endif
#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    unordered_multiset_tag container_category(
        const std::unordered_multiset< Key, Eq, Hash, Alloc >&)
    {
        return unordered_multiset_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    unordered_multimap_tag container_category(
        const std::unordered_multimap< Key, T, Eq, Hash, Alloc >&)
    {
        return unordered_multimap_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_SET
    template < class Key, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const std::unordered_multiset< Key, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }
#endif

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
    template < class Key, class T, class Eq, class Hash, class Alloc >
    unstable_tag iterator_stability(
        const std::unordered_multimap< Key, T, Eq, Hash, Alloc >&)
    {
        return unstable_tag();
    }
#endif

    //===========================================================================
    // Generalized Container Functions

    // Erase
    template < class Sequence, class T >
    void erase_dispatch(Sequence& c, const T& x, sequence_tag)
    {
        c.erase(std::remove(c.begin(), c.end(), x), c.end());
    }

    template < class AssociativeContainer, class T >
    void erase_dispatch(
        AssociativeContainer& c, const T& x, associative_container_tag)
    {
        c.erase(x);
    }
    template < class Container, class T > void erase(Container& c, const T& x)
    {
        erase_dispatch(c, x, container_category(c));
    }

    // Erase If
    template < class Sequence, class Predicate, class IteratorStability >
    void erase_if_dispatch(
        Sequence& c, Predicate p, sequence_tag, IteratorStability)
    {
#if 0
    c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#else
        if (!c.empty())
            c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#endif
    }
    template < class AssociativeContainer, class Predicate >
    void erase_if_dispatch(AssociativeContainer& c, Predicate p,
        associative_container_tag, stable_tag)
    {
        typename AssociativeContainer::iterator i, next;
        for (i = next = c.begin(); next != c.end(); i = next)
        {
            ++next;
            if (p(*i))
                c.erase(i);
        }
    }
    template < class AssociativeContainer, class Predicate >
    void erase_if_dispatch(AssociativeContainer& c, Predicate p,
        associative_container_tag, unstable_tag)
    {
        // This method is really slow, so hopefully we won't have any
        // associative containers with unstable iterators!
        // Is there a better way to do this?
        typename AssociativeContainer::iterator i;
        typename AssociativeContainer::size_type n = c.size();
        while (n--)
            for (i = c.begin(); i != c.end(); ++i)
                if (p(*i))
                {
                    c.erase(i);
                    break;
                }
    }
    template < class Container, class Predicate >
    void erase_if(Container& c, Predicate p)
    {
        erase_if_dispatch(c, p, container_category(c), iterator_stability(c));
    }

    // Push
    template < class Container, class T >
    std::pair< typename Container::iterator, bool > push_dispatch(
        Container& c, BOOST_PENDING_FWD_TYPE(T) v, back_insertion_sequence_tag)
    {
        c.push_back(BOOST_PENDING_FWD_VALUE(T, v));
        return std::make_pair(boost::prior(c.end()), true);
    }

    template < class Container, class T >
    std::pair< typename Container::iterator, bool > push_dispatch(
        Container& c, BOOST_PENDING_FWD_TYPE(T) v, front_insertion_sequence_tag)
    {
        c.push_front(BOOST_PENDING_FWD_VALUE(T, v));
        return std::make_pair(c.begin(), true);
    }

    template < class AssociativeContainer, class T >
    std::pair< typename AssociativeContainer::iterator, bool > push_dispatch(
        AssociativeContainer& c, BOOST_PENDING_FWD_TYPE(T) v,
        unique_associative_container_tag)
    {
        return c.insert(BOOST_PENDING_FWD_VALUE(T, v));
    }

    template < class AssociativeContainer, class T >
    std::pair< typename AssociativeContainer::iterator, bool > push_dispatch(
        AssociativeContainer& c, BOOST_PENDING_FWD_TYPE(T) v,
        multiple_associative_container_tag)
    {
        return std::make_pair(c.insert(BOOST_PENDING_FWD_VALUE(T, v)), true);
    }

    template < class Container, class T >
    std::pair< typename Container::iterator, bool > push(
        Container& c, BOOST_PENDING_FWD_TYPE(T) v)
    {
        return push_dispatch(
            c, BOOST_PENDING_FWD_VALUE(T, v), container_category(c));
    }

    // Find
    template < class Container, class Value >
    typename Container::iterator find_dispatch(
        Container& c, const Value& value, container_tag)
    {
        return std::find(c.begin(), c.end(), value);
    }

    template < class AssociativeContainer, class Value >
    typename AssociativeContainer::iterator find_dispatch(
        AssociativeContainer& c, const Value& value, associative_container_tag)
    {
        return c.find(value);
    }

    template < class Container, class Value >
    typename Container::iterator find(Container& c, const Value& value)
    {
        return find_dispatch(c, value, graph_detail::container_category(c));
    }

    // Find (const versions)
    template < class Container, class Value >
    typename Container::const_iterator find_dispatch(
        const Container& c, const Value& value, container_tag)
    {
        return std::find(c.begin(), c.end(), value);
    }

    template < class AssociativeContainer, class Value >
    typename AssociativeContainer::const_iterator find_dispatch(
        const AssociativeContainer& c, const Value& value,
        associative_container_tag)
    {
        return c.find(value);
    }

    template < class Container, class Value >
    typename Container::const_iterator find(
        const Container& c, const Value& value)
    {
        return find_dispatch(c, value, graph_detail::container_category(c));
    }

    // Equal range
#if 0
  // Make the dispatch fail if c is not an Associative Container (and thus
  // doesn't have equal_range unless it is sorted, which we cannot check
  // statically and is not typically true for BGL's uses of this function).
  template <class Container,
            class LessThanComparable>
  std::pair<typename Container::iterator, typename Container::iterator>
  equal_range_dispatch(Container& c,
                       const LessThanComparable& value,
                       container_tag)
  {
    // c must be sorted for std::equal_range to behave properly.
    return std::equal_range(c.begin(), c.end(), value);
  }
#endif

    template < class AssociativeContainer, class Value >
    std::pair< typename AssociativeContainer::iterator,
        typename AssociativeContainer::iterator >
    equal_range_dispatch(
        AssociativeContainer& c, const Value& value, associative_container_tag)
    {
        return c.equal_range(value);
    }

    template < class Container, class Value >
    std::pair< typename Container::iterator, typename Container::iterator >
    equal_range(Container& c, const Value& value)
    {
        return equal_range_dispatch(
            c, value, graph_detail::container_category(c));
    }

}
} // namespace boost::graph_detail

#undef BOOST_PENDING_FWD_TYPE
#undef BOOST_PENDING_FWD_VALUE

#endif // BOOST_GRAPH_DETAIL_CONTAINER_TRAITS_H

/* container_traits.hpp
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
*/