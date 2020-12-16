
#ifndef BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : not_< typename Set::size >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
P8rbW5koqVYf0HS75speXnDULjvT+7h17XZqzwrRVjWr3JoLJmsHzv9DJNWe07XV/y1vkakpTJgwYcKE/dssBmkor5kzC6YfXFFVWl40bkJmIS+cm8Xvq7P2w1wzTVyPMGHChAkTJkyYMGHChAkTJsxc22L7/w/0myeHzAFYro+PzKvz+fxepb88KnqdXHqFrgexaOjpY3pVjLtfYtDz1jV4kWW6pr6NS6m5uFsTkuZvo643gTH3t+t6jXKjT/abrqfX6SLqPWPQa3TPlaNZp4kscJNBs87TEjW9M1jgIaNeoydqehtZoMOgF41jJot68xnT/5auxyf9WbUQe+8Ea50bO9UVjX2aTR9iGF/fGfDB6vPb1Xcra2/Ttsv457hbrE4Ec4oxPGHChAkTJkyYMGH/IzPO/1fe3Fdr88n2LYzZp4YbszdpHcKECRMmTJgwYcKECRP2O3vnHSdVdcXxoasUR0B6GZAmUoYiiqIOiooGcUQURMou7AIry+6wu/Q2EAmClFEQBSwLSm8D0kEcEAUFwtC7jAoKijggKCpqzo/MLvx+Sf5IPrt/hU0ySb7ee885v3Pffe/dd9991/+u/13/y52/f3v//z8+f8t65pgcK912/9Vn/8mJKXjOluO2DsZKX9h31ZY9v80VWy1iz99bXxOXPbvNUVtVY7aWx2w1zoorIzU5tf+VVyxzxV612LP3mfuz7GXtP5c79ibH7N207+pahozUvsk5HV8sd9kVPGQvOVdsJccqVNp/zVoUX872/ywdj8YqfHlNXCl2AOS0jln2WsWe75cie719OW0vS8vVMXuXrlnzktNjSVZstWLrBgpek7dE7F3SJT1X7L0Rs1fmGnvdrKPklpb5Y8scWl2Tu9waK30xW85rbOX0WJll62jM1iPX2orPyBVbLWN77TXLzllSj5T43BlHlsdsVcu2lZjRtW/3HLWVPf7H9tM7m6WhvVOP7U5zqy8GYvb2Z9uLT0rP4XNNlq3LMVv3ZNnqk56alpE7tnrG9uvrnGXLd2UEyRVbe2O2NmTZ6n0lZTlqq2rMVovYXnyzs2wlpQ9ISOqRlJHD/SP7+idmr9ZVe319vly8/ontu1fvqr10X3y3xNyyNzlm74+92fauyJlb9vLH9tQrvj/bXnxySt/eOW0ve/yP2VuYpad9GjoxpV+u2Doas5U/y1b3/thwPFdstYzt0zc521ZGYnJy7mi4PGZrQrat9MTEXrljyxXbl291tq20xMRc6hvjYrZeusZWfELu2LoUs9U+25btjJueO7YSbo4V359lK9WXmJI7tsIxW0Oy4+qRmFtxNXPGvuOabat7ct/0nrlia27Mli/bVu6dP0vaL/5euGortXsu9Xl/zFZCtq1uyanpuTNGnYnZOpplKz4jNSmH46oas9Uxti/fr1m2uvRHr8/xe5gse9tj9r7em20vPj09MS23rkOaxfbiq5AdX0ZS78QmjXMrvoUxe1Wz7eEGO8lunXLHXoXYHnwP7r/GHszlUnzjYvaWXRtfQt8cnz/Isnc5Zq/JNfHFZzRpnNSoYa7YS47tvZd5Nb7EjN6pCTl9Lq0ds3ciZi9u/1V7Pbt0v/L9gi4JyTk+n9YwZjchtufegGy7aYk9ktJhNTUl0fYb7NK9bwr2wMut81/M/vnscSA5LTUjd84TzWL77Z0hWzl7z18jZisYs/Vmtq5JKUkZmIztkmv3Iq4yse9R/IvNnLXXMGYvM2Yv7Vp7sU3Os3pPhu2gm9PHTJOY/WqxPf2S/539lHi73ujfJTF7P9+cnUfKvv+L+VAk24cevf95ZsnZmLP3vy73z9LubHvdswfC3OpXA2I2R+7Ltplkc7epOW0=
*/