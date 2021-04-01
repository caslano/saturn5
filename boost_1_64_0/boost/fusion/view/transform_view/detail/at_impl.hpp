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
SDzxjPS6lf/JcxfPyWSsxLBjfPdxm8znuwj5/YfHMRxIUtRXwH95JTQDDxGe0RrMEXK9trslPkYZXKH4U/VxyYvapkpAJ6gMmMis5comO1QU/A3RSZbKnGNT9gq43xC4rh7hP4Fz2QHo6PTJQBbnDO6YohvUzkrhD9JY9/ig+PV26FBR6RjUsSa/VTqj4lPOKRsRlaGWhTWyt8GvvlYvWl9B/HxBFNijtwXg5g/gz2svZWuUdq8APNhhANVMiVPlS/1Q5gmFKk/qkTnXf2kp396mZPStCV4dwc4ZJPpBw0N9WJi6vlPz+rR8w/mUnJ94QRgBhvqpRmyDYcIepRa/luN1tVwRVI7VIEeAiOD9gphhUXUDnqLL1PuCXD81DXE0GAroW3xukrtjPnxRmpylDGJCxiNJvi+iLZ39ms9xDoRm46roKvkAxdJ8qC6cn5XTa1NTEttNwVWIv8NR22mijlk7/iDLTyxvEs0ezpkmXFbAOx2E2hL8WnlaVV6l8sp3ChnTwqDVLSolOq2y7DT3DBfH07ieraBGziTbeVKth370Tb50dmxLPBWf0g==
*/