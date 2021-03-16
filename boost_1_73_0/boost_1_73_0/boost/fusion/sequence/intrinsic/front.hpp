/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_09162005_0343)
#define FUSION_FRONT_09162005_0343

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct front
            : result_of::deref<typename result_of::begin<Sequence>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }
}}

#endif

/* front.hpp
F3DHJR6HTtXkbTJUVlviYV0ngXYN/7Dp30gNa0s8rOvfQLfX/XdkLUaqsS3xsK5fgXY9M6judqSWtCUe1nVKUkmamtrncTKuTW2Jh3X9BrTryZ+3d0Bqb1viYV2nge4bIx7ueA1Sx9sSD+s6A7Rr9YsrtiLljyce1gUeQSVrqsuYIy8i1T2eeFiXx8O2V8f7cv9D2dmA11GVefyGj+JChS6CNmnapGk+mhRokpuEXKC98/09d4Y2gAXcy21y294=
*/