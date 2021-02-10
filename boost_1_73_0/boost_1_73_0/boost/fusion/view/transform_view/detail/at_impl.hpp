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
ra8VLw84TWbgGlEPZQdoX1GFMlXGwVFegV2pMtHkNClKLnEd0X5uyf6jE5ygq4lBpVmGStMDTjLLQdNAEK8aVcNBF1e3QHsOR9XKA94VwJJvCk0qe1AeOD17WmbRFIg0BNXYuLf1a47JwhhG+Xrgx+Zfwb+U7ZwEYoPUfpsEYwCHmYNpkbCeNFOlGLGqU+64kJT3SO/AmJpkjNIwmBqCJpP3KnBgJ/reboMdJ4BrBvj4Ue+027VP98BE+/DHTf5QTWB33B/cl4HwIsHq0gI3JHU9kyMqKhtjdXODJ+zA7+TymuqndrCOGsHCAp74qNkdqU1VwPmdrFWjyEGJI6zZgTii69k6I2FhW5ZLtIBbo5QXGrfTmkYC44pCpZShxEqZGxm15tVTo1toBvTUxBSauqlr2uDH03LPfGfdiGx4WMpqJ7BhBy9OwdN1Xe9DYI4ucC8MLBMxfsxi3t9tfLn8he0qLvMY81lirh3JggFfveGCxcrrg8NNIszH5TssxFyxEDEWvwX+VRZ3mK/OmrAqoEQJ12hATCjKkBuGm1H5OvIe02KwEQ7O5dDwVn7jWj8IC+1VfclzqvpphFNrCPo1TM2nezY4iCp941Qws/WXfIAscD8uyQtVJTz5xJ1kg2+eW+nVLuWY6sMnflAt
*/