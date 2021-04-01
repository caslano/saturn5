
#ifndef BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct erase_key_impl
{
    template< typename Sequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, erase_key_impl)

}}

#endif // BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
mTLgat3IXA/3ZiDjG9xDSS4nSv16f2LGJSVwyJDBCzJfSEYB/iHBc0JBJTFUAQUCKaJUUPUGgUkCLnTt7zTz2o+DjaKq7Snnbs9V3kfDCzhvcfi0sy4WdBGIJGsPou2vBF+YRgxqob9i/P5n9u8OYmv42lUBOez6O9qyYRBW972MhhmUlaq8+i4bkycS3pNyCBCWDn0du44+918sWoHu9WhrMlf4TSfgtTtvs7TyYKXvreq+bFMEq/+zWmgOw3TMplIpS1uFs50JczEtR6JlN063AdqTopN7rD6PBxr7+IGp1dCsKWTdF1EsKdLxTVSEYHfp/i3iKJiOqkpt/bnAUCvpt7vfeojHtfoZuRHBrvGDerPjnJcSzNSfC0SsteQ0ycGDV0ZxgLS/DRMXLCgriobnoaa+TZTj+Oe+1eLc4e4sgbYeWidFgYvPZraKW2niN5t8FDSQqt1wgFwD2jmWNESyOmtBJUjVPqeJsEaHN057HCR58lr4LZH6A722cymT0Y4q2iEXtRTHlo+eI8I/MaBJVCiBsgg2jmnCpp0bMX+bberOT2drrmWylQ==
*/