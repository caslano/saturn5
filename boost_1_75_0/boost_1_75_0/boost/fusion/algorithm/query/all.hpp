/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ALL_05052005_1238)
#define BOOST_FUSION_ALL_05052005_1238

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/all.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct all
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* all.hpp
T1dEKIKlrn2/1aXenkjLOAUWWZ3ckX5N6ISLmq805CmfgD3E051MTSc7QwRt5zUQx7lic/Cgbe31joqA2Xsa6cUrZv81ZnHOw0El8GrFeseN64x1/PWUqGMV1qGl7YJ6X8Y0LUa0E0Rfgi9KPnxvN5Oyh06ULMt/xS9vF5eyXVDD9eJd7ZsCgtvkLeIdymSDBBhQQ7ayLk8RjNSubFtdHsUFzjR6ssmQomJ2awPXUz4Uwl5dSBgLFTVEM9eLqpvqOzQHacy5ytdVX5TGrUg0RZUHRoA0NG4FEMeBIaIbOaKs6LWAQdHHbeLjntDH+23Yx3Tooy9RvPXi3sbjGsWLL+Q8tRz/O1ON439vqj7+8qkwfqp7/tT/Z+PvNhXGn9Cu8Vumho1/3xQYvxX7qE6R4/92SvvHP3WKcfylU/TxO6HuvlR33pT/Z+P/2gPjj2/X+Dd4wsb/tAfGn4x9XOaR43/W0/7xX+Axjv9Cjz5+E9Tdl+pO8vw/G/8Tk2H8ce0af9XksPGPmwzjT8I+lkyW47958inH7xDcxoA+NtMmF9zni+/MYhL8li1wSQEqUa548Ws4Xlm4UsRrD3pNPRhMnnhEtLm3v9nUvM5cmrwKPR0oW9UNy0munQGB6o2xy7X2RveG9lKM7fXsrbUnau4ANS8WRC7VzGof6qSWNYfUe3uvFvVe2MtY7zv/FfX2+VzWW8b1dmpZL61B+XQw
*/