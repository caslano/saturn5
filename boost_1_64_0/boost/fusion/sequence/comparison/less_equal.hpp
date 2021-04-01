/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_0432)
#define FUSION_LESS_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/less_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_less_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(b < a);
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
        operator<=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less_equal(a, b);
        }
    }
    using operators::operator<=;
}}

#endif

/* less_equal.hpp
CwGfEuH0D4rbsjfC/flT76GpQDR59OzeV6W7tDDYl0tjwTXTMcDEQfhJ6srJkcY/bnBmxppgGCb7yxVIva4fKPHdO5Rxy2qm7cpisvQX8oTQ4c8Xw4RD2G4wniy0LJqen5oMAj5Q9o6vNvOQf+ognK7PwVWEcZmH8o0gUtUEJzBo67LKPYDQAWsD9/EIJWbWRoT68FzuWevWaPzQChUXDyt8fXfpqw4+oxB7U8rs825EiLdBws/GV0VGrQtHl6vUI81IQQqwdkTcmomNcMILIK7O2rPKnMKyp2keG0D+W4n2tT5fathTW/xZJTTOIh30w+zJNsbxj7OYTiR30tq0up1C1Z/h8hkKCwUvNj7ym4ImNYEf8zY1rTbdTTk/Ki9Smj0kbqxQBHL+3rPbNYjW4JTUc9Qb9UJ/hftfUBoa0FE/Njk4/6Ttk9tgYDTs43nYk1KCANXXfyopBC0MIATRCWL+VQe2t+dIWry3007VwMZRk8hG5CtITJnZ5UHOi5FmGAFMEbuhj5686Q15KUZUeet7oOqZEbDNub9x//0qFuqFU/sDnZLY1keEbg==
*/