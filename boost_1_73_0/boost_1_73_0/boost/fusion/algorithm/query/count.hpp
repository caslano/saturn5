/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_09162005_0150)
#define BOOST_FUSION_COUNT_09162005_0150

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/detail/count.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count(Sequence const& seq, T const& x)
    {
        detail::count_compare<T> f(x);
        return fusion::count_if(seq, f);
    }
}}

#endif


/* count.hpp
3h+z/fLKslIceFslqgNYN3/s5IbU/B65L1ibX6jUOL+C9Pi6O4cGlpw0A7u8kUtOmm9N61li2Dxkqfn1CJvsqoYsNUUestTcccCSw7SBzeK5KcWutjds112/QweyD33LphvRAUtW7D6EA0sl9W7WEA+jVI4a6EAmnu6YG1gcvMlCMJwTjrBxrBpZOMCHySLUi+EGDnRwlV2sUh7UjR87FuNt3MRv5aIpnrUZqa9v2eG0h2IvyfQ7YL3QGfvXaDa5SSR4Mk5/utruWdfCnmEVbMakhsMLWUo6oWHg8qXVDnvRv6dTXu6FGq5KXZPtYBh+AnhEiWYqidKj+ns1jYDGzltTpE/OXqioYUExHQRvnbE/fbgXGg8NkY3QX8fvfwYgOnZC090tG1v8f4zv0s6DX1pMbzP2n9SSNlGiB5nj5piY5IHj5ZG1uqIGxLFn9zsKPfvEIdsn2Y7FtTNhjB7N9bD7i6gDsngRB7vWjl4ZdoES2FJUnLjcudOhOz+RrOU2nEm/Ev11bOs8S/Sgnl2FtZFp8MrGZGhPkAG9uWCP/zm6x7n3BAsxpdAR7ETDjDfvlrjXzm7GAoHlE+zHXm56PDjCkv1M542RPVrLm8Q13zgL5XFEeJcJ79m4JzSLU9DUpvVra4QowzwHduO/
*/