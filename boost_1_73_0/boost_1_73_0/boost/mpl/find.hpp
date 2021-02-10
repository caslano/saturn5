
#ifndef BOOST_MPL_FIND_HPP_INCLUDED
#define BOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // BOOST_MPL_FIND_HPP_INCLUDED

/* find.hpp
1hnq6/D89MBuH+9B8rko+ciHBSzYnTXo6DKYAkGqIYmMgM0RmwycdxHmUyo15tQ2GIdoYxFKojoMEWpfX0Go4s1UeQ22iKEwikD3UH3cxDFzN5Mur6LzyR6TfAQkeW8zsOawWm+S2DPmkk/WQEYnRp96k1T4NkIdshdPbKfxJhEiTZRIt1oLjVslrpPtYT8xBruC850Qqz0v0Vq/LKmy3+v4lle1xaXy1RnWr3oX6RqpTH5S+Ntj3/kfJWV9575IhVYpDKF/to8FSf65Mz7/mndQSwMECgAAAAgALWdKUjJx++NCAwAAaQsAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTYxVVQFAAG2SCRgzVZRb9owEH6OJf7DrVM1aVpwEtpuDQGpaumo1pWqyfaK3MSUjBBHsRnj3+/sQKGU0rL2YVKUxPbd57vzd3cOFJcqZpK3SZDmA4GfEZ9NRZnINulG0XVo3uYFXzsRiYUYpVzOv79YWS2VvMhYzBMYcpbwUpKALnECWkGT9xDy8jcvbZkmnARaaYbLCVPMrbajbt0Fz3Gg942cMcV9iCb8EzjHcCV+44LrgHvgHxz7KPL1e0QqPB+0G7Y0AzpgI44Lyj41NvogJwUvW5LHJVdNSMSYpXmL
*/