// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/functor_bag.hpp
/// \brief Defines a EBO optimizacion helper for functors.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
// This bogus warning will appear when add_const is applied to a
// const volatile reference because we can't detect const volatile
// references with MSVC6.
#   pragma warning(push)
#   pragma warning(disable:4181)
// warning C4181: qualifier applied to reference type ignored
#endif

#include <boost/mpl/placeholders.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/inherit.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief EBO optimizacion helper for functors
/**

This class is a generalization of a helper class explained in an article by
Nathan C. Myers.\n
See it at \link http://www.cantrip.org/emptyopt.html
                                                                                    **/

template < class Data, class FunctorList >
struct data_with_functor_bag :

    public mpl::inherit_linearly<

        FunctorList,
        mpl::if_< is_base_of< mpl::_2, mpl::_1 >,
        //   {
                 mpl::_1,
        //   }
        //   else
        //   {
                 mpl::inherit< mpl::_1, mpl::_2 >
        //   }
        >

    >::type
{
    Data data;

    data_with_functor_bag() {}

    data_with_functor_bag(BOOST_DEDUCED_TYPENAME add_reference<Data>::type d)
        : data(d) {}

    template< class Functor >
    Functor& functor()
    {
        return *(static_cast<Functor*>(this));
    }

    template< class Functor >
    const Functor& functor() const
    {
        return *(static_cast<Functor const *>(this));
    }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost

#if defined(BOOST_MSVC)
#   pragma warning(pop)
#endif

#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP



/* functor_bag.hpp
XIeOx74waUe8bI3RMTN4o/ohNkSqzCxLty0mXvD0DsELjplC27v6bBPKA3lBg7tEYGYLOTPLEh+JF3hNjfACGwOi2KnnBUiD6DUpgxX0bvOPLXqNc79MSVVhjLqBqz84UhgaBZeEDYcQO3I0ttLSxPV2kMea35lJIHrhKYe02I/YWL36V5Iyr0PQq1Tl8/acXSTr3ycrj3XkfGdhQMXc7PkbGy+VqC+VqEy9RMetNB1tniFIIYiBlYdF6BceLaBmsUF/l70vCe0WFw/jJO9Xei4OB1Ip5sZnyAlvHcpVK2KRYpLbmG2kmU2umm0gzWsyal7RkwOtRQRnJYdoS8BSGKBwVeH5OLwePM8vqg/PTnt9ePZuJe0UoLA6WdVGMBZ5PbeCLhSKBWHcMIR2AlT1fuW224wodCdWkaewe1Db7L6F20aomnLsTTu8QZE+kR9lI+bRrxCv+yyoViK4IIr6iin1B+lgmN64zsWDK4uDcdxWgeNwgRF4zWOwKtNfD4f2Mxpqfz4rVz1FZf4z6jfuCWo8NaDxLF7PnQ20f/61+sPS1WUMPBU3+239twQp9dv4bfFbzJpM0fiSVl+LE2ItExjGt1LjaiGdoaE1kFmKNfHNCmI1ukVOqAkfDDSyrL6jGdXd3nB1bQKrK4kyRORWJ6qaJlx2IioaXDp1uqRSvnRG3gIWGq+h1tEp3812Z1MkjBDNl1G+iHbJp4Vy
*/