
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
bXhBvCXrX4L+uT7aknB9m/Zm34ufzjG/pSXL8MgvbB7mp9lrEZbsccSvxePmn6ik/jQOko9k6+r1t3rXPcjnvMcX4vBs8qAT6B2L3FwZtfqbf3ppNQsV9MtO4CN+enU1N0eiG2sCuzorsulkFSPeZvXJeRfgSVgx6g9Z4xAGKlZ782SZvSJ8bxfXHg/yD7s9Y3cm8CknsOmffDptnf4MGQiB3CBqMaOXz5wV2bbX7LFPvyhM
*/