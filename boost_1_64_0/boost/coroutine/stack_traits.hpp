
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
TmWDa6WJ/zbgnzXYfyBH/7BeCW/48sWggVzGzNazCMR2QZ4AhAH7Tlk13Iuc6QdhpvXhHvnNubmH4dWcPOKI40WDOrJXpUgkte/X/bjCdUhVQyGgZiY8xMCEtrWrHNhpvCkGXgyU0vYZi9MJ5NNFDXv4rSszQoEk4pAhILe0hdP2ABd3qLMP/9IX6r9NmwO3FuJax0RbvKuISZEJHT75p4D9IuLVY8eCUQisCpUbNu0n6huU2SqIXtwHABEgM1+K4y0VFIM3dgY9U+iKcpt2NMdOavj6DGfzZI1M7o11WEJehHX3XeRE5ocIEyWoo0VwfLFRs09qrAcWIp9VkIvugNj1e5UfiIZBDL6FXKo4ov/XvhdseAh/jScHh+aWEhzx5cJGpjWV7PCNsmQuLUCsclcv8Yl3NakOkHzGcFFMG8vL7asmON3LpF13vnpthoj+BCX2z4WsYclawcyNGZrdD0isxvNOj5KsW22F7DSOkDbeKqKTlfDzzxz4wKs4bdvr+hRhf3OoYiBgxmZkY+asNlu6Hze7cKqfAP6GB+TpnEJfyMEh8pfBGDhbpg==
*/