/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1108)
#define FUSION_FIND_IF_05052005_1108

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find_if.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find_if<Sequence, Pred>
              , detail::result_of_find_if<
                    Sequence,
                    mpl::bind1<
                        typename mpl::lambda<Pred>::type
                      , mpl::bind1<mpl::quote1<value_of>, mpl::_1>
                    >
                >
            >::type
        {};
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq)
    {
        typedef typename result_of::find_if<Sequence, Pred>::filter filter;
        return filter::call(seq);
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq)
    {
        typedef typename result_of::find_if<Sequence const, Pred>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find_if.hpp
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
*/