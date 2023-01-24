/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1341)
#define FUSION_CONVERT_IMPL_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct set_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<set_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::as_set<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
0HY0glnZkfytMbZvjRPtWntEnYa2WPWS7RU6REZB7jGVcgnOfvbQ25dcglsrcAm81Sh/7AipLxStWm6P7Wh2F036v4DUKbGHmN6f7446vd/F8PR6yo9BTS5mjSPCNEhK3s08jatiVGfT79anMbjvf6lh5+p1c/U6K0FeP9EnfMV+wBRIeA9Ae2mMmtNCy1BzApBn4kn0mXME6pP9fyUY5oRBbsTCiiOpW9sE3x5Kwgm23sjU9t6K7vqcqre09qNIqY/e5bFprjvZNdcwYvRJgckA0l9Jul+guxDIdT2Z9tEWgZ6s5G+cKq0L4EUn3sXyjI513SxIFmdmezmdmQHdJsAd8jWXA3HnDi7mWbYkdDaOHjkYQcNdPYSsvY1oauyG6ZJmm6J+TVC/xqlfJerXVdOJlruMyz8epfL86cjmnzudtNffPIqq5I3mDq7fOItpwEex3WoqllPxBhUvUzGfH5kDl+vNWXBpPsw3p8wi+R81nSBfcydX30DV1+HlenP0ozSckdQ8j2qHzopCh5YiYeG8eLeiQ4uBWGA+aA+QokR/foWWy0BlbnaTXE3Gl9nO1xSCbHl6sxsERu136KHGYm4l4SIYJQIRelccEqFHTkQidOEUJEKvb06yrFBLbyPhIlyEfM/cwcJFrJtwKYUaa2JqtIkBbcOdBNFNhh5qDK5ys8j9wluzNpFiXBUrtwt7om+ZGxcI0fPiIeP7
*/