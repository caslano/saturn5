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