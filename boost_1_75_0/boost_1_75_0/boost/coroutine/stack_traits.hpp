
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_TRAITS_H
#define BOOST_COROUTINES_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct BOOST_COROUTINES_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT;

    static std::size_t page_size() BOOST_NOEXCEPT;

    static std::size_t default_size() BOOST_NOEXCEPT;

    static std::size_t minimum_size() BOOST_NOEXCEPT;

    static std::size_t maximum_size() BOOST_NOEXCEPT;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_TRAITS_H

/* stack_traits.hpp
HZRZ714MrVbFzkm5jZENkElCkXmy8k22/ceoo5HfqNzkpby4GhSh5V9MErY/Djml7fArOlOOrxfwtip8VHb1guMkSPzK5B0G0vS+6RUJ4C1YgRR3/+SVAb3u2G/vBcRAF7BHduNen/E5EY/z72LmgFb4YQe+DdeVGpZjCzqHXZmogPED4VIBkLiZxsrAHvHCwDvz2pmNmRzgssNhj8CumIDszZi7HSI9w0pJ92LYErAc4Nsh73iaNWw1Woa4MK6NcbLWLTMcaOUdv99le+ekSbYBLWPIw/6Gda4Z/HW/co1awiAlSC3kw7GljIyt+69LW3GZLHhq6dwfLpR9O7JWCah7jg5E6XWXjPTCEo/7uNL9ny2o1qHXgqCrfqqglv728ztIYaWAG9vaYQNhkyg3zH5ixtrnDQMZ6ElwBc1LqSOP16FXJs6MFHXM7P1PoBqcQYKUyruBfao7NOBizFfqgfKv3w4NttL6VuttBwvpp/UGD6vP0O6HtWUYybTYFEU76OTHn0NjJX2HL0cT6CrrcaGrFL+eHMWG4YYpa3ws10fbIJtl/z/T6N6r7rmze56y3pr0okvvDuiXdTCrCVc7B0UNw+3Ze10Dhin01imzkSCWaQi+a9ec07JsmQO7nQ64KwOhOC/+Mh3CkzVzcH4Fl6rh0TCJV9Lx1DXbYfDoKY5PZc0+J4+Ok5TyofXm0XTyXmXyC/Ng7EWY+3j6
*/