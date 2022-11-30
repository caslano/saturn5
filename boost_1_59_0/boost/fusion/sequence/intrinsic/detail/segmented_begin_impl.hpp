/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    struct segmented_begin_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            range_type;

            typedef cons<range_type, Context> type;
            typedef mpl::false_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const& context, segmented_begin_fun)
            {
                return type(range_type(fusion::begin(seq), fusion::end(seq)), context);
            }
        };
    };

    template <typename Sequence, typename Stack, bool IsSegmented = traits::is_segmented<Sequence>::type::value>
    struct segmented_begin_impl_aux
    {
        typedef
            segmented_end_impl<Sequence, Stack>
        end_impl;

        typedef
            segmented_fold_until_impl<
                Sequence
              , typename end_impl::type
              , Stack
              , segmented_begin_fun
            >
        fold_impl;

        typedef typename fold_impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack const& stack)
        {
            return fold_impl::call(seq, end_impl::call(seq, stack), stack, segmented_begin_fun());
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl_aux<Sequence, Stack, false>
    {
        typedef typename result_of::begin<Sequence>::type  begin_type;
        typedef typename result_of::end<Sequence>::type    end_type;
        typedef iterator_range<begin_type, end_type>    pair_type;
        typedef cons<pair_type, Stack>                  type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack stack)
        {
            return type(pair_type(fusion::begin(seq), fusion::end(seq)), stack);
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl
      : segmented_begin_impl_aux<Sequence, Stack>
    {};

}}}

#endif

/* segmented_begin_impl.hpp
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
*/