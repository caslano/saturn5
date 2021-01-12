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
GV9Tc755rGIFyzCo2hSrBuN7M+dbBUURtkVo45WunWqrFfFCC2zC/xDHB1pi2rrOkkABe4rFFeOo4nr0WVG/Bq2PbUWn+eqUYXJ8ieNhu6igHqikQzx5HFIbCE55+SR+GidNmMUI2+hao2rj7qldli+a419TYJyWLdzEVmQIjucT2d3N30jeLVQAfqgm6Fi3CbIm6hjXwoSv4S+yHVODfbppgmkYhzHG96kc6AP/f3JcE9Sp
*/