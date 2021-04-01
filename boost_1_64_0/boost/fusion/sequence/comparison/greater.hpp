/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_0432)
#define FUSION_GREATER_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return (b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater(a, b);
        }
    }
    using operators::operator>;
}}

#endif

/* greater.hpp
XodcRSLeln1MsFbzLXiQlHvEm7g8f0W/AMn4k4z2DF8AIASgvAgegFK5GnrqHtHYgFkoC6CMNnkPxoZCbLxQdEu8/TgpeDRNVZfZ1aq7N7sJ1xiDs7zWYtxM6OdmPArWTEY7847ju8MjZ7jwwyTbLrKxbNJLfgFd0qiKSetUa4NQhmqdK3ZqRGGVMND9GWGX28P9lWdcQTycxNLMDDPKoszaG4uMzaMFO+AfJdOPEmIxLJizc7jXmmLVwLU5PFOdP0rhY0GwzrjI51CIF1eZmmtY8mKIgYjgbl3xyaMF6QyCLT1ZzP+BUMUj0LuTSYlWAldIhviIW9wB4Jhe9wSh+necasxqxEzsY1gCOQfxreVCNAD5eBiKs806nJ0IVpbpzBZqJLt0shf4HlKCLuwob67oFwqoE6cjdS+WgjcFt8hWu4JbsQxT9MxGjsYLHmzErlUZTWNoH9lhMpOVz5JM2gPndtyuYM+tAMhAIg/GlnaW47w4WTwQbw7IZOaoyWR3JDwiJrfBDjI5ONxMkamCh5ka9SHzJB7KLT6iQ1V90lgBeTPBGMNBiOENrg==
*/