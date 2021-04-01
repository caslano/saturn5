
#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/aux_/back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct back
    : back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, back)

}}

#endif // BOOST_MPL_BACK_HPP_INCLUDED

/* back.hpp
Iq+IbIeptVN6rSgUSUc42CKFUP21VeHapY6Eg51Zf8jtvt345ZRHP5T8Mfo/c2NCrdjE9vMSjiFigB9eSYx0jXDjjezNwlJMEvxJARKfAjyIESzXzzTUbkhzQdqQHAu6rA5p3nE1Yx8/XX3AK4gT17orcDpiwJa3F+cIo0hsFRrlGeoVSULNxkQRMfwR27GgxWlx+MQQBWWOoGrDiArbodFh+ypJ1+MfciM8mBN+FXKgx6MFmmWHNYYMds0VIpV10e9iqH+D+Cp2a12fLHn/Azee5ue0eg5ZYZAwXt/UdovtzsAKl6Xt9vdG9pVVft2INwJjMuz0nb+/pwPHE94l3Hwc4UQ10lHTnJO7Jt6dAOtsydYn330AirjTGXMcKVPq2YqS+4GuDD9EbyzKgqvi+hucLMUmdGgQQSawqmwW8wlEnrXLGHtIjVSGqmHYCAu8SvzFKG1eQNBWYJeHUYCqwixw4dLuSS8biSH6l0B1hoj8Ge3YDONiUqxP6icG/lySvLHVHTuiOXqTGfVspR4kBLQeUXwravDfff7CUYUxRMaO74hpX3SyQmP8OQ==
*/