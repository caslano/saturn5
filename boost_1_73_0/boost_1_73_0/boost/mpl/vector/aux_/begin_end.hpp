
#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/begin_end_fwd.hpp>
#   include <boost/mpl/vector/aux_/iterator.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
BduFbu+INkv7/t53tcHO7U3lfkB7XeH23oOFPnhz9HYg96V1wmBrzQc7J1zFK312WC7s2NHKMoZ5j/be/WA7S5uVl/PS3ulN06VWF9ahoq/m74k1F6mje6ml1fereSVedUpvjlYJydwruWG3SOb1tB8VP6l5aTSwYto2bkGTNBK+S4TPIrwmfkA9oP8LvYZ64jwToxP44H8Sw80mZzWaKGaxfo5uImxEJKTHUwEKARbWCkX87YtY3zPMlFNMEuwyKCVKs1ogWD1GY8NlYUgi75j/XlXzj8PxpD+6P8ul3t3VsZJiqS5WFCa10xTnn+JBfed88HlqIWtuRrm/PmCPCILJWkAssIPleccbKM+hNMK5ZMNEDhm7zLcJUdUaVnBnalvmqzXs9QevD+agbz4gg3LOuMs86KFaA6wvc4k2gdxhGggf+xFgrYlLJQOSWp5ggh3OthKwMxwMzM4kJxkiOOY0JAIICw4nD0glOImSNdQLXeEkdTfgCKki6may7v0gwBET+BcVsJN7mfYn0ELMmWAuC5qo0xq1rv66SFfov10bAIMzeAWkXIow1E9ODfXyj/kDUEsDBAoAAAAIAC1nSlIhBQnatgQAAEARAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0
*/