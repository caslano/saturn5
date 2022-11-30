/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_20061101_0745)
#define BOOST_FUSION_VALUE_AT_IMPL_20061101_0745

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        template<>
        struct value_at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::value_at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
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
*/