/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    //auto segmented_fold_until(seq, state, fun)
    //{
    //  return first(segmented_fold_until_impl(seq, state, nil_, fun));
    //}

    namespace result_of
    {
        template <typename Sequence, typename State, typename Fun>
        struct segmented_fold_until
        {
            typedef
                detail::segmented_fold_until_impl<
                    Sequence
                  , State
                  , fusion::nil_
                  , Fun
                >
            filter;

            typedef
                typename filter::type
            type;
        };
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segmented_fold_until<Sequence, State, Fun>
        >::type
    segmented_fold_until(Sequence& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segmented_fold_until<Sequence const, State, Fun>::type
    segmented_fold_until(Sequence const& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence const, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }
}}

#endif

/* segmented_fold_until.hpp
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
*/