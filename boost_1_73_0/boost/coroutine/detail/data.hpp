
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
DcOVWU57XeYCTJkelubu55r6E8tUZd25hp3JT+xejWtUL0Tb6DsX5kfCaPF6TFmrWLt/O0mHbcR9S992Qli1lnNv8fpPW1vh5rd62fbumtdZWmh9NV29MDvwPyo2r47waLX9Yay47eKbT8LxyOjvs96G+ecjtn7aqO6EAyx3zfo5WdxnYtNcVFKWJ5NafulOg5eJ+8b+MoP7LvNapbW97sfN864lsqxwC25XxKbVmU8QOS2V
*/