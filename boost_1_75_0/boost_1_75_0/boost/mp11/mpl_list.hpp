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
NKuS/dfOUJpb9sgawO9ooO/w9coI2yVnfTv1ViP8Qyl8LfJHCM7zaA1H6WtM2nxGCNSNftdboVJvhgj1fJAMMxxh9kSYTgpzZdcws88LSPN0CvMuTZujCfkNOnm9rE+318sazuO0XA+h8TwqK8cQLCGs03VtUqh8bbuan6Os5DWlDad46L0wtl26fFaqmNKXeMrIAef0M43Uur83bx+C/V1Puv4JwT7aLs4aTffObUUXYtJS0mZQ5luvNqy0eOg7mhTDMWi0VILRqTZxlZWFSeHOOPGJRX/PYnvP4rglRKTqkbZIR98zLKhLu9bLZNWMMSrWadxfNwrr6MSg69Uek3q/jZGPcsoHhsVB3eRC7n8hKSt70v4XhOdHU7+Usk1DbdHvTnuy+HuI/rqu9bdjQSjvn8cAFnC/QOd4Sl9Fhh5lDUi+Q0Rl9DKtDJ6dq+9/nW8X12CMTBkIIREm/Xya2ykdoWJqS0zRdN2acr4snitQKmfYHC9pen+L9QH9K5GtR1pVHNkmimNsN7raFmr0J070J6eijMLo+xge5QY5rwfcHHSvk6dvrAXz4mh5n7FRfq1yfU/j3ViMd/L7zkFr2z1I2wbaE/oQwtfnU3mtLw7BuNVagA5Ttw4z60+YtRmi7/BQ0d81TvRPThX9EU7gnm90akAYZ8CiX2um+2DU/RgJ3d6TmAtvM+icORBKUkmfKUaTWe+haRdrv3ju
*/