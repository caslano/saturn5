/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
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
*/