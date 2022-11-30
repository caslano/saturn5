/*=============================================================================
    Copyright (c) 2004 Angus Leeming
    Copyright (c) 2004 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CONTAINER_DETAIL_CONTAINER_HPP
#define BOOST_PHOENIX_CONTAINER_DETAIL_CONTAINER_HPP

#include <utility>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace phoenix { namespace stl
{
///////////////////////////////////////////////////////////////////////////////
//
//  Metafunctions "value_type_of", "key_type_of" etc.
//
//      These metafunctions define a typedef "type" that returns the nested
//      type if it exists. If not then the typedef returns void.
//
//      For example, "value_type_of<std::vector<int> >::type" is "int" whilst
//      "value_type_of<double>::type" is "void".
//
//      I use a macro to define structs "value_type_of" etc simply to cut
//      down on the amount of code. The macro is #undef-ed immediately after
//      its final use.
//
/////////////////////////////////////////////////////////////////c//////////////
#define MEMBER_TYPE_OF(MEMBER_TYPE)                                             \
    template <typename C>                                                       \
    struct BOOST_PP_CAT(MEMBER_TYPE, _of)                                       \
    {                                                                           \
        typedef typename C::MEMBER_TYPE type;                                   \
    }

    MEMBER_TYPE_OF(allocator_type);
    MEMBER_TYPE_OF(const_iterator);
    MEMBER_TYPE_OF(const_reference);
    MEMBER_TYPE_OF(const_reverse_iterator);
    MEMBER_TYPE_OF(container_type);
    MEMBER_TYPE_OF(data_type);
    MEMBER_TYPE_OF(iterator);
    MEMBER_TYPE_OF(key_compare);
    MEMBER_TYPE_OF(key_type);
    MEMBER_TYPE_OF(reference);
    MEMBER_TYPE_OF(reverse_iterator);
    MEMBER_TYPE_OF(size_type);
    MEMBER_TYPE_OF(value_compare);
    MEMBER_TYPE_OF(value_type);

#undef MEMBER_TYPE_OF

///////////////////////////////////////////////////////////////////////////////
//
//  Const-Qualified types.
//
//      Many of the stl member functions have const and non-const
//      overloaded versions that return distinct types. For example:
//
//          iterator begin();
//          const_iterator begin() const;
//
//      The three class templates defined below,
//      const_qualified_reference_of, const_qualified_iterator_of
//      and const_qualified_reverse_iterator_of provide a means to extract
//      this return type automatically.
//
///////////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct const_qualified_reference_of
    {
        typedef typename
            boost::mpl::eval_if_c<
                boost::is_const<C>::value
              , const_reference_of<C>
              , reference_of<C>
            >::type
        type;
    };

    template <typename C>
    struct const_qualified_iterator_of
    {
        typedef typename
            boost::mpl::eval_if_c<
                boost::is_const<C>::value
              , const_iterator_of<C>
              , iterator_of<C>
            >::type
        type;
    };

    template <typename C>
    struct const_qualified_reverse_iterator_of
    {
        typedef typename
            boost::mpl::eval_if_c<
                boost::is_const<C>::value
              , const_reverse_iterator_of<C>
              , reverse_iterator_of<C>
            >::type
        type;
    };

///////////////////////////////////////////////////////////////////////////////
//
//  has_mapped_type<C>
//
//      Given a container C, determine if it is a map, multimap, unordered_map,
//      or unordered_multimap by checking if it has a member type named "mapped_type".
//
///////////////////////////////////////////////////////////////////////////////
    namespace stl_impl
    {
        struct one { char a[1]; };
        struct two { char a[2]; };

        template <typename C>
        one has_mapped_type(typename C::mapped_type(*)());

        template <typename C>
        two has_mapped_type(...);
    }

    template <typename C>
    struct has_mapped_type
        : boost::mpl::bool_<
            sizeof(stl_impl::has_mapped_type<C>(0)) == sizeof(stl_impl::one)
        >
    {};

///////////////////////////////////////////////////////////////////////////////
//
//  has_key_type<C>
//
//      Given a container C, determine if it is a Associative Container
//      by checking if it has a member type named "key_type".
//
///////////////////////////////////////////////////////////////////////////////
    namespace stl_impl
    {
        template <typename C>
        one has_key_type(typename C::key_type(*)());

        template <typename C>
        two has_key_type(...);
    }

    template <typename C>
    struct has_key_type
        : boost::mpl::bool_<
            sizeof(stl_impl::has_key_type<C>(0)) == sizeof(stl_impl::one)
        >
    {};

///////////////////////////////////////////////////////////////////////////////
//
//  is_key_type_of<C, Arg>
//
//      Lazy evaluation friendly predicate.
//
///////////////////////////////////////////////////////////////////////////////

    template <typename C, typename Arg>
    struct is_key_type_of
        : boost::is_convertible<Arg, typename key_type_of<C>::type>
    {};

///////////////////////////////////////////////////////////////////////////////
//
//  map_insert_returns_pair<C>
//
//      Distinguish a map from a multimap by checking the return type
//      of its "insert" member function. A map returns a pair while
//      a multimap returns an iterator.
//
///////////////////////////////////////////////////////////////////////////////
    namespace stl_impl
    {
        //  Cool implementation of map_insert_returns_pair by Daniel Wallin.
        //  Thanks Daniel!!! I owe you a Pizza!

        template<class A, class B>
        one map_insert_returns_pair_check(std::pair<A,B> const&);

        template <typename T>
        two map_insert_returns_pair_check(T const&);

        template <typename C>
        struct map_insert_returns_pair
        {
            static typename C::value_type const& get;
            BOOST_STATIC_CONSTANT(int,
                value = sizeof(
                    map_insert_returns_pair_check(((C*)0)->insert(get))));
            typedef boost::mpl::bool_<value == sizeof(one)> type;
        };
    }

    template <typename C>
    struct map_insert_returns_pair
        : stl_impl::map_insert_returns_pair<C>::type {};

}}} // namespace boost::phoenix::stl

#endif // BOOST_PHOENIX_STL_CONTAINER_TRAITS_HPP

/* container.hpp
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
*/