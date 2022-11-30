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
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
*/