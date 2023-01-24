
#ifndef BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 25/apr/04: technically, the ADL workaround is only needed for GCC,
// but putting everything expect public, user-specializable metafunctions into
// a separate global namespace has a nice side effect of reducing the length 
// of template instantiation symbols, so we apply the workaround on all 
// platforms that can handle it

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        || BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) \
        )

#   define BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#endif

#endif // BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

/* adl.hpp
DerFwcKUcbVAqKbo6Ug0+9lqPnkIJwzwwYY7JQjsW042Wq2TLzjeRPyBI/9VIp/re9rxsRBJhUFKc7o7afmsjGudE/KrRLQkv5EvLd6yWwObuVjrRubPDpMIC2nDe5WNjUbbfqvr+dgKxEN2tUVNBHtbGrPkO2D0zi21maAHyOVwFOWTvF92VKaNDkvb8btmfvs1kGMtftJmkkRCbZNbSwVoxRFquwIyI3/dFtJpVm9zu68eK9wjXZdpFEmv5GHwoYY/eNdOEbgSS954y/bpznvNp+OJPtnLfKKVGZoigGaH4UJjzMCTgD+xxbAa78l9MwiPo81R6Ej0FDpL/ywI4nLiu9wadpVonmbNVenI8fzoxAYlON+PxcWmgyq505wPTpET7T5I8V3ab430l2zFJq2T8E5m3t0Ic3HMkPqZeF78ot6XmrDiJLCcuTeTJ9xhrqKeA/Dk3wMS5Rk2QkZ83L0rf7dr+VI297VQGIUdjElwcbCTttoQcyvrrKumxR9oYGQpvPxyx6fCyDL8UXyQ8Z1x43cyIjOKqkUZK54AjmOR9LaWypT7j0ftsqtDkHnpO78xLSNBqgXnYZ0wjzc1JJ3F6Nkp+0+ExVy+m3DmMJa3Tux9r9/Wnvd7Z9v+0Cp8cs5nBmYtbJc4X5veABTmpxbM79OLlo3pVPDOz3n8MB5zGbR6hGaTX5xyy1pembRlpfdeC170L12M4vIG
*/