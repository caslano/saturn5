/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
kAxHv9DaMmTBCC/mwM/lQvvv7Hrt40Zv7/nH4obvye/83CjSdaJHvZXn8ZgBCvUl4CBCAcGkLdsl5z91wcXzn0yPwBUk3poSaOugfCXrOGu81dkig9E57CSkoD0WBnidmUOSvZirgWtPcfmWXUxhF2s/QoIIM5UEXHO5kDIuXsUftgz4kwZ/7oE/PZFG5oJAEtPPLqKL5yqpY7LhRbOk6jRp9la+NqXKQfvCDHVZnlBXCQwksXiHK2WvKW1TXWe669+a1jvB9lzXirH3aLrWdRO7WlUXyPrCOylBaBMWwdSNJO027lzitGFlfE9Deyc2h3/LJfG6wEuwedM1YiY3WUNc/YP1uOq9zZn8Yn58mR9fWN9Q/6xXMbxoVk07mWpG2Co25avQ/rtQazfNgYywbL53CdJP8wMwzbMtG2GeW1J2m+ZdUyY6fH78ZteLHyFiooeKKy4+0Z9SJ/os1lZBlJMcYiodh2lOHzhDpYCkTbjy1gbMPM5WXlPJjay1hD0rHJwVpQGh8Fxl8ObwA4Zsj36RIZCqkgmi+bV/es1x8/3r6LMiLFUXXqcZ3QuGJxd1mvu5vMNp1sFbChxlZiWwZxJdXYEkEZsZFtYF0AteZyo9RL9Gh5peqMBt9lz0ueg6Fzfdmy7q3ba+sZg29gtN2WRySkZvLxGDLwH9rM7IVD7pGKntiLGyXR8sOy7zrwvUsiETuc2M3fr1AuDz
*/