/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
            : detail::as_deque<result_of::size<Sequence>::value>
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* build_deque.hpp
XN+E2DHIxcQvDffhy8Tucc/NSECAfnkal4+sRcLamq9mtvId56SlFfTUJcZazomdphkOOn3HyFcOcstScNPoZ8JirVtFl2TE7+BLIK7M1nIqBg26NDduGkHbVbdqrm7hp88qkZVGl8owgjBZnbBQ+iu6PHUG16I5kZvm0JiZTIKCjh+Z/UZqAKPJy0F4FfhCR3DR6HIAJnJy83fWTZcDgFtDE2UMuugY0+qBXXb45mynKedl57rBSgm6BbJT1eWg0e3qm6d1f9blQJ4lLGPK9SlGY6xOBMs/HHSu/b6936q6HADwiVBMh0HL0Z5Dk6bZDmB+NyP/n/Zyjmzl9ABT3k1zbCknIsCWG4ccVE+s49MNe32n7NR0ORChlgvXg1rZQiNLcZST09OyM4B7TGu6HDRQfVRmg1o3SmU0NbMcfgZxl1M31zeBdeZsz6G5Vr28XzO6ozwdwvwXrle1nC7VvPSV/d0xRrosZHrx0Og72u2YwqqLQk4vtu3NjKacn3Zybts3VUZSyfWArhg7ytFFwdyIHWQ1+yon6mcjqRctWI5icouCD4tv47zvm0InSXQ5yE5HbLW6DFvWMa0fW2QOo0LaZYdRnEjfGLmdALSMIjr1E37dCxk4OFnWEPUANs6uNmW0OrTWpZc65TKQ
*/