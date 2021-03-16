/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each;
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f);

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f);
}}

#endif

/* for_each_fwd.hpp
YXQ8N8A2D7bnYNsJW08vHTmZxtvko4wmOmf12hFqC80N7mL+b4xNzi/vKefbF9Wbsv9ss1ZpdJxy84SWm99ouXlKy83TWm4ORK0bKGrTGtjWwiY6ZPMyLS3RvhuK3tvMk1u+9ArmX0EjIT5d606gDrlhQBFNV6+I1pdGvy44Hpmx/JddRLZN9r/4cUpLit7Vjg5FlwtieUeIRYpC0SgJykS0b6K/5x04Wc+UUw/vU31KV3xOPWZRx7DvHW/7rkY=
*/