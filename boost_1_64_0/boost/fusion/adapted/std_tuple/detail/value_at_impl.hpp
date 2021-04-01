/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
ZHhW6rEDMsTXLvJD/kb/YDWb7IUx4mHH2O/A79tNK+9U/b2WTonAw9xMYQ/ivQCe9OHiTDNNrs7sXE801xBAJbbfa3g/DUZFpKpSHWhPS1HWD/aQIhK+frwA6fqibplKDaDKspHcxoh+ny9Ykf59X+1qTxzWZH0UhdYlAeECzA3Nvf0CUQZgiE4XeC1fNsqm14SQtNA/6u26e3R3Ys8vo1SQM9SE4szeVJHwKMv2BU1UJC0j+M4+GU6ae9CrrKegqGQ7OoZX2y1IZ6isz5vYnnWPW4MPAlImiQ6qX6cNbQOYQkBjFdBdYci+arbTv7/Vfc4aSV65CHfkHcAZbujgqry6TMpbUw8WFMGgzZ6fFalA7jttQLutQuN9P4WqOs3h9sv+zmp6KgkRMkIHmtn1W+3302Evoyylx3R0R1X+Nb+W94FqahAxBO4BknUiX+IYtggvpopjt9iyWM3qI1dzw7ife2CPGvznVZn/ebEpL4mxP6zHoYrzkHMMnm6rjr5j63RPP3wgmmgvW5eel/8k6zQI4KBF9XrtPBzMS/qROdX4m2eyeJ5XfK8Rcg==
*/