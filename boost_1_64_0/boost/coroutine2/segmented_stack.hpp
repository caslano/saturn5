
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_SEGMENTED_H
#define BOOST_COROUTINES2_SEGMENTED_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_SEGMENTED_H

/* segmented_stack.hpp
pTfB150Q59+cl/mRTrthUs7hCJj0z6/9UieRx64uzLeGVCv/huSoQf7grUYbpx/LPs2m8WHiaqAvNTrFmCCvjmRGv4P4RDTw8QfVv5oB/dMgLqhk96sAnFLHN11MsMASJmerB6+mQDLZh1j6Hhoak0Cp2XytV1+QbewEE/C2E7SbR9737bIPNhJkepgyP3T02HoIlVwoD/EE2c/N1kP8ID+gZwqiSY/NEMekmcgfAQc7pMnqS6g2LxApbWoagWes8VKe/h2wQ/6IghRE6dztM4hk34qQHLSnRhsZaFbVUGyoB8gZmsQzDjiCJ1PDfxzyruxD7PFMgti9FCQORs9l9+g8OM0b/krRPcdEnK+KHXhdHJC3uOZvIJJXCpW9obxHUeTNC6ah/t4YJ5+u5qE/tNC+KKb97T1BoDE10pJN6d8KFFQ9QfBqDfxdm2cCf42BctDyau0GSvx5eibZGnbrauJMlT1e4qT2j9GQZB8C5V07rX/TaOhqInIMc9Z5UAtj7Y0kO2hfXaul+dlwgurvIJ4nI3DcMmoc6QOA0+/g+ZRkS5CdMzSJ4KeCwiOokacPxPatgdp+zQl5a4LXQEr8ViUQvA2yn/21v5nQb67DtJ8nIHm9NhSUnY6o9ydQbfdNB/gzJRlXVedLU5CtMhjAw+uAvPcp/VvnHLws/kRrjitIhg9AG79lUMMkGKiboTCZs5NqUb5UuzVb88OThi6qp4P9yHtqRl6MVrO5QRB3DkJXI6TOdgUJZuYDuYyTE3jr6d9VtSG20MJTRQ6m0zIqn+gEHn3UAv7CiXW6iK7+YAry2k5wX3QuxNUzqWt8Bv6e99R5sDDCzG9NwamGEC81RwemdyF+OYXWap2GLm4EKhlY15zxrIFp1g/ivdUpHasxPiII1tYt1/riSGxJMDzfm0dB+QCCpZMArSLGiznC7pc0mnxQmSb3NNJ6dUb7rwuMt90GQL+lFCweRI2Gn/3BmwCnBU/rfHmBIFH79KgHlE46THJ3BdnPO6Gb/BNQ+/5I2VznqA8ySB1y4HTFRWKHR5JX3MqC/pAb43JpB+QVa6s0Vz/L+2aaBujLl8S+5JK/pIbOg10gHjMWukP5pb/IAPQXQLB4hR/yakx67bBGXrV2rz/Vbqo/ambTWpXBsl92g9IsReuBrPqKH4B/qrr5LQlCfoearDtCnFvIye8obTld/aHx/LYryVM6J2evcwZPa+yEBVTrONIBeYtQt+tSSqfLT5PVmNIGZXMh7zgaKrCBuusS8sDfU9lrb6lxbyZ0L3TGzmmAqO3nwd+tM1pPf0h/s0AONkCXehixYtaB51DHF7zjcN94NctIZXXZ7+QwGFkLsUzKBdIfRSHJiZX/QENgd3titV7Abh7JG6xzbfNU4Bd9cWG9cqU/Wjwg2bgXgeM1jb+3sg806SKC4Mr2hfxhvsSGboO/1kIp7Iw2hpUJBG+uzgtbSWapwOG7/EPNKZjSn6SxTNOTbaiWEgvAvUga974KnsU9Yhv8qVYsXf5EmdMLo2myaz1k89DY2JSdF/4mElsx2Y7x0kh4hYBvaYxOt2yD3be1QdnVhRFbqBp5G2QFvfSzV//SZT37UaONdgirfabgvQdl7iqUGLaSNlwKOoOXCskNiTo1EP2V+EG1XYkUNE2FoZK3aWP1TK33M0DJ1w2U+lqbpsvY6WBsjLwywItqV6ueCAfzVPdkO4gL9qFa7H5EsM0hSKig/fwoyj4tyWtpkS4V5cl+tF/n876w8WEFimi70Q48nYCm9EGsfZep8d2N0jLzAHBS5yXugmRre0rvb6CNCrfIW1aeYFh1rfeboFseRizvSKrtvUPBjrsE1YMI/OUQOlmCTjY=
*/