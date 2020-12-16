//---------------------------------------------------------------------------//
// Copyright (c) 2017 Denis Demidov <dennis.demidov@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

// size_t and ptrdiff_t need special treatment on OSX since those are not
// typedefs for ulong and long here:
#if defined(__APPLE__) && !defined(BOOST_COMPUTE_TYPES_SIZE_T_HPP)
#define BOOST_COMPUTE_TYPES_SIZE_T_HPP

#include <sstream>

#include <boost/mpl/if.hpp>

#include <boost/compute/type_traits/is_fundamental.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {

template <> struct is_fundamental<size_t>    : boost::true_type {};
template <> struct is_fundamental<ptrdiff_t> : boost::true_type {};

namespace detail {

template <> struct type_name_trait<size_t>
    : type_name_trait<
        boost::mpl::if_c<sizeof(size_t) == sizeof(cl_uint), cl_uint, cl_ulong>::type
        >
{};

template <> struct type_name_trait<ptrdiff_t>
    : type_name_trait<
        boost::mpl::if_c<sizeof(ptrdiff_t) == sizeof(cl_int), cl_int, cl_long>::type
        >
{};

inline meta_kernel& operator<<(meta_kernel &k, size_t v) {
    std::ostringstream s;
    s << v;
    return k << s.str();
}

inline meta_kernel& operator<<(meta_kernel &k, ptrdiff_t v) {
    std::ostringstream s;
    s << v;
    return k << s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif

/* size_t.hpp
DPoxj4vXL67E5eWNg9G60UnEt0RZK41rZvSuhzgOXIF5AMQXRBnV0LoSmYKu5c+bA7v4y9J/K91wVhrPYzMpG3wY4jbEN7zRlaAz7jQWlqOc4znRd/8Sr01zV1M6nR7q7nhbnh02tAL3bSG7lChqlahFPZCgvKe8DYjlRTxHjFRMBMni2v3Tt7rFoAvRjT1tJW4PG1dWPh9QlJmtfd1y24D9cZkdwN3Vv8KxEVo1nNdA7YosltdoHHHHnMckMUwEXXPdX2o/L8VgcwlxGWmpaB0dfE7yNXEH1LmLMWQB+9OQ8zxxnnvHhnWm6O/6vXTYTyFbnLCWOiZdKMomjmjbR5fnr19CXE0sd8yIakRlJ0O3a6w8g/RtiC8Ib6s0TJOjwl3mj26LuYaPFulWddO4qlVj7rmFcnz4+cKuaJ22lfZjbhyHF3YvF/WqKm6dMu2Mq/uOwIW9rYL7p4LLqGONE9Ww2Ls+7g0QWA/8NapbraSoGyvAbMxmjIbEdXvHX+MyarlRLFSKwFlmZxa7b+yZxVEZLSGuIFoI7lvHc4PdZtwDcMzADYVdKWWjTFuRjpA+1EfbvVhwa2UqpylFjcpyHuc4xuczIq4hqmkVM5RE+JnFnb1otGuPi/s4bOMMzF8Vto1tghSGzWzHro9Yfyq0ivxMT8S1hLWicdZast+vl6+tp/MnkHE031mUt2SCGsXrfPV12dJzcTtz/ANzf4W4jLSVby3zLeKKjdjGZr6RDf7tNzie3WnDg1UV4tKt1Fdd2Y6HI0BEV/YdvmeuwxMvlKgr65CKirPR+UFLOS+QmopatjVO9qM34O6WXdjfgtKsiKw5M7zWiNjGoML1vTTfMhrH7CI+JZXx2kQNiO92nnq4X+y5zHlL1jTeNoETkbb+cNGq8oyMtyF8CI1vqBcknpKZ7hTbOj/gYU96mS9rBavbNh2Y4qkMsw3pZ+W5Yn/HZ3PuYlNp67ylxJ571JnlHrsHZzwgrKwbYQL3ZOPgMPbSeiys6xRl5ULFg3Wk8tadiy3yrI9/gJGsTRY8IXjVUkHJk3Y2ttMRu/txC3BmMVIItMnf4vFeYEx6RgPZ6C4lX+m77ct5KN1+cXboyVKHbpm0piEW6Vj0c3RA/Ndvy/cqtEIbRbb2z25FR7YaG1ezAzeVwfmfu4hXEWaaRnGbb2sF/uaMT+Huq5y/2NQN1Y1uo9VHBdcX1lm4+yrHckGCr0zVKp0be9R2ulFsP2U3xCjzeIxm+qtbye9E/nyux5G6ci2VzuN9ocW5a9/AHOca5pzzeF9owfkR5ijaamlajfc3Fpw/YQ6XdVP5VuP9jQXnWr9DnLauG1mrgPfpFZxbYk4TbVRC5fsbx3buiTnGMt+EyuByW8KcpSJtRmhdGVxsPQU4BnMsozK0NqByK+08FnOC0hVXNuByKzgXMYc1ugqMaVxuBecS5uhAJbdM43JbKnxpzlmSulK+MSr5UqgZFNf+NoSvG8aCbHXypVArCP9BhK+MMoqKFvQvlfhPILypnZDBBtAPeDifMsd7YloVc6zF1IAU8hTKxrEA/rTgGWZcI6upofW19VOQHcz7EebVrqprx+vC3tKI96eCp53SlNLC3owHdwn8HsUKKqpqmaIlUsxs77FXoW/6+6JvWlHHuOjBKAycwD6FnNMQx4WpeKvIbhc6PtuVCucYovRwSoMWw4mcu5vF+4XT03jrjGGKdGezdIt6sEMHzgg3OYd1gelKM+FJiKR0/kgeQjc6USSL90B6BDGO10LRFlK6vLIdd1FtXziEOKcViFfLuY4wyZTUDSdp4mxxE3EuwBgK2eMkcFlZq2bmNrYvxs7bAd3cHN2n+dGc2xKlGhrSFJU=
*/