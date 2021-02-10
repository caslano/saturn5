/*=============================================================================
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_TIE_06182015_0825
#define FUSION_LIST_TIE_06182015_0825

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct list_tie
        {
            typedef list<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T&...>
    list_tie(T&... arg)
    {
        return list<T&...>(arg...);
    }
}}

#endif

#endif


/* list_tie.hpp
0RB/N5PzgXavqRq0EG8wuuoPTXjXHw0VKkaId9vtD8zunWrILMa7nIxuG8IbasakZzYXL4cj8PQfPzXWfpmxjCaK5lKA1x8OtYvx3fmgD15Lmk8x3kQzK0hcgFdBe2V46kosxkOPN+zeNhF/t3hjJZdQjKee9ZbiKWa9ZXiqWVsJnrKXLsFT9tIleMqtrgQPM6J+TzOljbAMTx+ohTg5POwZy2GW4yk4K1k8efYk8Mxef3ytTUy5rk0JnjHQfzgNEaWicDkexmD5aCKJJ61BSTxpxyrEm3SHF6Nb5YBehHel3j0vwNMutUl5vqyAx3qqptGdXCl0QsR4hj4G96LrkP+Z/fr+j+MZE617C/2ufjN4BtSKrtRNEuLpXZ3np/+QF7YQT9Uzl+FB51J/bV7penfcj9Br+BddvzavR2AwPBhhpDNvL15X7r8h3s1w9GGIoPIdhkK88aR/3zU05E22HRfjbUWVdgsFeIqRUg5PIRSV4mlD6MI11f9VjrxSeKriFuKpRd4SPOXIW46nFnkl8RQ1WIqn2KUR4iWmFUyFPoMYT32srhgP5OxeaWqjYSV4ir6+EK/7QTf1/tW9wlhsKX9qXctivI8jNJcT81zrqqQxhe1X6+GCjXtNtb29UphvK1pdmzv7lj3NSW7+
*/