
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_DATA_H
#define BOOST_COROUTINES_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/coroutine_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct data_t
{
    coroutine_context   *   from;
    void                *   data;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_DATA_H

/* data.hpp
i7xPDSAhUWuRrCuXPWq4jaBFho7wd9lXQwuqqpXJ18WMDoq8+cCcBtwgp7K7M3LoZFatnD7SVCZ9qztkdIebNWlQ01FqDOdxMT7IOsDwkUMGTeUOzqAEND6oolTgQ1xKrORmAc40CrNJzaFaUtNPwpsv95skIoGcZxIzHwQUbvDq0f5LC4G0zyN4Ihe/Fk1hp+AAwQEt+3NyFZr63dVX+YIa5ryZS4aIKjQsBBwI19CuAs3vfIF608e9ObKlfGxP2RKgvaTf6u1cVzCYdOR8DpGmls/wip2K/GM/pbVSD/24SR/OlBDglpPlpFYxtm2NRP6k/rGUbQHWsd/c36PYbBszp8lXhloyhDskEZQM258rGSFLYXWK4BNsMqouKfuwyv4lH8zCbfOC2ytZjA+yiLj/7UCfGk3xTs0kgd3X3mqUTT46GvMLy4fQ/pa5yH+9F9LqIeDA9f33slk6vxvOXbdHuj+AptsBf5h46QEGxW/5r0Jq3Xj9hQRJLprWvzZMXsu1pgco/K2Npt0hJmiEuQEgY0aDNGYeb4uGcws/fnIdpFPpNZYn6YFORg==
*/