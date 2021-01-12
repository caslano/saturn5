/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_IMPL_07162005_0132)
#define FUSION_VALUE_IMPL_07162005_0132

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<joint_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
7B+U300Haricf7Y4gSCd/IbS0cchKZ//NrzdC9TGyEYMP4/GIb2O3bpD1wE+3Aa2bYHpsT7q9yadTuAIK+sljRy65ZDr4o8kg0XzkE7/ZOgjLxkwci5t0uHHxiidy0i69nJROn8dk3TpoSbc37bERSWfF/x9Mw6wWbH2vLzM04gRhbBX2AJLIwvl8YoSK0cYvmcpcdqzSnZy5dF0iKH+audmDBoo6eEqI+lyrLuqxNCOHivT
*/