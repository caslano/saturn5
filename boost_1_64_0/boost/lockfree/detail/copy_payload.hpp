//  boost lockfree: copy_payload helper
//
//  Copyright (C) 2011, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED
#define BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

struct copy_convertible
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = t;
    }
};

struct copy_constructible_and_copyable
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = U(t);
    }
};

template <typename T, typename U>
void copy_payload(T & t, U & u)
{
    typedef typename boost::mpl::if_<typename boost::is_convertible<T, U>::type,
                                     copy_convertible,
                                     copy_constructible_and_copyable
                                    >::type copy_type;
    copy_type::copy(t, u);
}

template <typename T>
struct consume_via_copy
{
    consume_via_copy(T & out):
        out_(out)
    {}

    template <typename U>
    void operator()(U & element)
    {
        copy_payload(element, out_);
    }

    T & out_;
};

struct consume_noop
{
    template <typename U>
    void operator()(const U &)
    {
    }
};


}}}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif  /* BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED */

/* copy_payload.hpp
OjY3PLXynZ4i4/MvZqu9gbKshLy90YOwbSIX0yjSx2UUsia8AfPu6MXJOG8s/03jLvLNMzJwdKuEgpJ7Nm4ZHAhLusuAUnfktV8k0koGYRnGnFhy6jm0+drwktBLME22OZXmjCxlksGmMXaWMrhBcqwuvu5S/g0UabvAIWIKmWVIee9JVQv995OgIWDUHaY8nwRnronFD4xXJeuo2i63gJbuxttIrphQ4DiZhNoVkV1WhaCsa1Xt4bjiGNVVy0LSMdPmhEntpVAFKxfmNuZTZc2jH3FuGwzv+pHgNq0Az1/HO+kDhXiYYEy08KtgPKwVapb5vAhs5fhtJX0L2eTA4KLgxc4lHcevx3verVpeBEUI9yAVKPeQzBp6tCkgZzCYGkK0KxGZz50+DfBBQ+KDF/7e0ALHM2Ymhm5/AMbteWnPxrUkS/qfGyAx1YE1zAlZylkJct7TLpk2a5g+ah1XH6xFekRpvQu6b6yzjNlJvM7vLwwzjeB9+Gxtl6ShADYuTXTR3P92ggJzYJPS9xIMg6ZAzSF0BlOihKqDyyIBDJ5NiQuPLrAIKmOh+w==
*/