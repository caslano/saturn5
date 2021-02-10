
#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/aux_/at_impl.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct at
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,N >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,mpl::long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, at)

}}

#endif // BOOST_MPL_AT_HPP_INCLUDED

/* at.hpp
Gb0rptI5YCrIZPKHkNoabsipURmTiDoGnEJJ3ttCWLPNrrIrLoyxdKplqw4mMO4FfA2tcr2y/M5b3Qd7tAg3DmYwxdFu/5iGm41dpPYt06tCdIqaZBgEH+9Xm/JhzV++8vXqqWT0DOPjJFtIVmlqXkViCD5oX3HDlBFnoUxOoEH//J/9AVBLAwQKAAAACAAtZ0pSh0LQILsBAABnAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MTZVVAUAAbZIJGClU11P3DAQfN9fsVVV8VJIcgUqRVakCkpBpb0Tl6rPvmRDLBz7am+g9+/ZfHBAn1r1KVl7dmYyu1FMkSsdqQBQxjW+AHVHuwcf6ljAZVmuoOstG7j4dHX94+YzBIre3hOo5BmmkqkTVKCt3RXwFs+sj4TcElbeOarYeIe6YQrjYWNCZAz0qxd53PSMtXcHjEzWTl3WkJPay4XQRf8Gf7bkMLIObNztCIok5PWexvCBdNfEIodaXnT9Sl2gXR9Z6JxnUSDtRprz72sUsWAooq5rEph2vbZ2dwSq1qyzKYkkO8pwkaa4/ArnminHsu3fY/oBL2gjF9kxZh/z9DgXyJdvJawp3FPIcYj4MI5F0ug78f0QqyEfOPOORfmw3G1pwP3m
*/