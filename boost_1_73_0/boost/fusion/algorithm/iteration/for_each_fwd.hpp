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
HFOpD0x/pb/W1cG1IFlDdLwSlk8v+lG+vSS+I/NZL5NHdyWExi9y1gLhDd9ns1Lnu5/QdmOz8mSS0cMfEg559ghyRSJqfdYzETfM85LPOvH7ShWdQzfzKWm2e7sTOZ+Cu8TRv9/+YFbqkS2OWa1z0CPdda5dy57slXH0UtELK1OYlbxDeUBfyoOxT15CT/KS5IVu2j4c7av3ASE28qz2r61Tke1DvvMeDgbQL/bd5hU0raPE
*/