/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
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
HNwsh7S7om+h+oFwJSyFF8HF8GJ4AVwNr4SXwNvhGrgNXgbpN4t5BrwC3gCvgvfCq+HMIP1GOA+ugwvhdXAlXA9/Dm+E18Kb4Hq4Gd4Ot8An4O/g0/BO+BLcCvfBe+G7cAN8H94MP4e3wG/hAzAhxPsDZsKHYAf4MDwO7oCnwMfgPPg4rIAfwZXwE7gatqRcXwrz4OWwNbwSHuT+r2AI/Z2wMXwF5sJ3YVP4sdr/VN3/TfXf
*/