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
KuUm29RfRmPmEzqxIy7EbpiNPTEHR+AiHIP5OAGXoDr+yAjP418u418p4y+Q8a+S8d8k418n4y+U8a9HbbojPG9npEo7T8MgnK8rVxrhebn6UMp9hK3x76geZ6mQcgNtjrOcrEM5fA+b4ylsi6exD76PUfgBascxuntuJ1myneTE5rgQ1eUzobvn5ft+6VceQH98EFviQ6iWL6qi/DYpf4uUv1XKb0et/qrIe6XkXSB5r9Zv30m5njbluvrL/ix2w26orZd6UA4DbcpNlXix6I/Xo1a/VZRLkXLzpFwqastvD8/L/UWZz79jGP6hm59FVcRrLO2qCfqjv649lvTwXJ91ZP1XF5tjPV29lFVR7ieZvp9lPvyC6nJZIeXibJbLAzJ9z2FDfB474wvYDV/E/vgSTsbDOA1fRnX8CT0ZP66xGf9/ajOf8SI2xz9wBNam/HSsg4uxLi7D+liAl6G23R7pebpry3TXkemui1p/Hul5vl5WV/pXDMMGqC1vkZ6Xl/7Sv0ahPw7AljgQtXZRRdzBUn4IhuFQVPubUim3wqa/OSTb/aUYiYexLx7BRHwVl+JreA4LGBJ6MT48JONrjLkyviZSb/7YCgNwIAbiEGyKCdgMU7A5bsRg3I0huAdDcS+G4TPYAg9iS5kPqQwxvckDJ0oeV+AsyeOwLCcvox8ewQB8DYPxKF6Jx7Arvo698Q0ci2/ieDyuO05QKvE62RwneESOZz+Kfvg3DMUnsAM+idp+poynhd3+vrSfYAzFEFTnY0AfyuFYm/n4oRx3/ghb4hnsgOXYDT/HUfglasd5+nhu/y9KHi9hcyyVPPIZiqTcs1LOD9Ol3I1SDyuwIa6U6S/Abrgar8GbcDquwdm4DjPxZtyEhViEG/Bp3CT1F01g5QAxsIy743dU5oMcf3+hNvHxEPrhi3gVvoS98GUchq/gVDyCCXgUM/AYLsbXcRW+iZvxOD6Ib+HjWIYH8V08hifxNL6H5Xgaf8D38T/4AdYnxw8xCM9gG/wYI/AfOAQ/weuwHOPwc0zDb3EnfocP41k8iN/jO/gvPIU/4PtYgd/gOfwNz2Mt6uon1Pq//p7Pm0TJenQA9sSBqB1/6O95OzFSlrte6Ie9dcuPs7/n5edpaTfPoB8ewFA8KO3nBZn/RQzFMp7/yHj8cY2MZ3J98sZYvAqvx144E4fiLJyMs6XdzcEcjMfFOBf3YRI+g8l4DB14FlOwAtPwJ5yP2nZJlOfzSV3k+HhXjMCr8ByWUCB8gLvcDxSgnGt+7JP2fLMs1xuwP27CUbgFJ+NWnI1F6MBbMRO3Yz7uwDtxF76Md2IZ7sYzeDd+jfdgBe7BOsS+FxviXmyO+7Ar3ofX4P04Ch/E6fgQJuDDmI6P4CJ8DFfj33A9Po63YQneiU/gg/gkPon78SA+jW/js3gKn8M/8CB2o45exF74EkZjKY7GwxiHL2MavoIL8Ajm4VHcg8fwIXwdD+Eb+BoexzfwbazAdzCY+fIe9sXTqJ0PGuL5fFC6nFfJwDDMwkh0Yh9ciOfwA4YEGc/82u7xhNYiDxnPABnPQAzFQRiBg3EcDsHJGI0zcBjm43BcieNwI16He3E8HsYJ+DpOwc9wKipJxGJ9vAH9MQ7DcDp2xxkYhbNwGM7GWTgHEzEBUzAR1XqKjPZ8/ilZps8h9TQPe2Aq9sI0/fkvGU8Pm+XrHllfFUv97JFyhQylUu6YlGuCy6Xc0UbEx2PYDN/A1vgmXoPHcQSewOvxHczDd3ErnsLb8H18DD/Ax/FDPIxn8Ah+jOcwVWmrw9z5bJfjsMp8nIXKn/Z+sv+C3bEbTsIIvAF7Yx72weXYDwtxIN6F1+AeHIQ=
*/