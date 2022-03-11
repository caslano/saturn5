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