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