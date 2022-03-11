/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_20061029_1946)
#define BOOST_FUSION_AT_IMPL_20061029_1946

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq));
                }
            };
        };

        template<>
        struct at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq1), boost::fusion::at<N>(seq.seq2));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
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
*/