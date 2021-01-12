#ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED
#define BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>
#include <tuple>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<std::tuple<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

/* mpl_tuple.hpp
CQ/hDPwQH8DD+Dh+hKvwCG7EY7gLP8Z/4Cf4MX6GX+LneAa/wB/xS6zCDuMENsCT2BK/xi54CiPxG8zB79CM3+MiPIur8RwewIv4GV7CKtXYn2EbvIKR+CsOQKV/iXh0x2SshnOwOr6MNfEtrIUn0AurcJBYD9thAwxHbxyHjTAHG+NC9MUN2AxfRT98H1vgIWyLn2NHPImd8WvsgupxYzW5RivXbH1kfxgrv/uGM157jMCu
*/