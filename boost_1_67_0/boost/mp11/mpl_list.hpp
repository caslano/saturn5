#ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED
#define BOOST_MP11_MPL_LIST_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<mp11::mp_list<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED

/* mpl_list.hpp
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
*/