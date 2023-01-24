/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_END_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_END_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, Sequence::next_up::value>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
X9iz6Y+AmSeMnYy2ZheOpLeushQfC7AUVXUDe0N4yT7bnZYKlALwKxEy5h1BZDzeAMl3v8mXg7rgSnjnujB38hRuxhxbX+R5k4JPrhfY+nE9Yatos3cZ3tlai5sjDfKfLuO6c0UgdgmBGHGD0xlUSJAoUBqQTyauHTMSbM8VXwyd0cc2iUF/AxDlWPhzM/zJhj/3C7uWbRBQa+b2wCAuWScuA3q7d3tgUyDW08W1YbbboN9N8KcN/GkJf5rBnyh2b+HW7YFGwPnm7YGoSlq3PfAhOH7aiKb+6Ue8ofDtSoHChZVe5u/Q633S1OSlDdctqwGMDi7bRKs0V1jPm1l5Qd/ZlJGlSV2g1WFSyKLLUn+Whfce9jZzjq4TL7J3XbiXeP3iUwXsfUpbKe+Tz1OHQqS+4iG+YolOy5ubJrlSk6ZbTaWjAnlE2+hALQWY5gWwc9uASvBlTdllmncnE6lt9wCbqg3gdsxi8WOkkf+oFSbOfGqyjYI/Yewrm0o/DeAm4G4MFPQWzbM4orXzcS18fjYpO+7tuMlUMpz1L9lnKrEEwKxFHrnPVHoTqJwd00Nr79cGWaTSEulEh+B9b+BaMeAMl8ZT+WpXBreSY2tiFaW6pBtq34giyMreIJHskQDKYZJqEUJY9t8WksKmsj2a5MLQ9LzkDbCa2dIQ7uS5AGLhXXnJo+2Fd1BMNemSyVAysjKMHpLIHsLevB3y
*/