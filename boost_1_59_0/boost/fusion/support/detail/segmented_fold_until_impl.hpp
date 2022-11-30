/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/fusion/support/void.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/segments.hpp>

// fun(seq, state, context)
//  seq: a non-segmented range
//  state: the state of the fold so far
//  context: the path to the current range
//
// returns: (state', fcontinue)

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;

    template <typename Context>
    struct segmented_iterator;

    namespace result_of
    {
        template <typename Cur, typename Context>
        struct make_segmented_iterator
        {
            typedef
                iterator_range<
                    Cur
                  , typename result_of::end<
                        typename remove_reference<
                            typename add_const<
                                typename result_of::deref<
                                    typename Context::car_type::begin_type
                                >::type
                            >::type
                        >::type
                    >::type
                >
            range_type;

            typedef
                segmented_iterator<cons<range_type, Context> >
            type;
        };
    }

    template <typename Cur, typename Context>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_segmented_iterator<Cur, Context>::type
    make_segmented_iterator(Cur const& cur, Context const& context)
    {
        typedef result_of::make_segmented_iterator<Cur, Context> impl_type;
        typedef typename impl_type::type type;
        typedef typename impl_type::range_type range_type;
        return type(cons<range_type, Context>(range_type(cur, fusion::end(*context.car.first)), context));
    }

    namespace detail
    {
        template <
            typename Begin
          , typename End
          , typename State
          , typename Context
          , typename Fun
          , bool IsEmpty
        >
        struct segmented_fold_until_iterate_skip_empty;

        template <
            typename Begin
          , typename End
          , typename State
          , typename Context
          , typename Fun
          , bool IsDone = result_of::equal_to<Begin, End>::type::value
        >
        struct segmented_fold_until_iterate;

        template <
            typename Sequence
          , typename State
          , typename Context
          , typename Fun
          , bool IsSegmented = traits::is_segmented<Sequence>::type::value
        >
        struct segmented_fold_until_impl;

        template <typename Segments, typename State, typename Context, typename Fun>
        struct segmented_fold_until_on_segments;

        //auto push_context(cur, end, context)
        //{
        //  return push_back(context, segment_sequence(iterator_range(cur, end)));
        //}

        template <typename Cur, typename End, typename Context>
        struct push_context
        {
            typedef iterator_range<Cur, End>    range_type;
            typedef cons<range_type, Context>   type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Cur const& cur, End const& end, Context const& context)
            {
                return cons<range_type, Context>(range_type(cur, end), context);
            }
        };

        //auto make_segmented_iterator(cur, end, context)
        //{
        //  return segmented_iterator(push_context(cur, end, context));
        //}
        //
        //auto segmented_fold_until_impl(seq, state, context, fun)
        //{
        //  if (is_segmented(seq))
        //  {
        //    segmented_fold_until_on_segments(segments(seq), state, context, fun);
        //  }
        //  else
        //  {
        //    return fun(seq, state, context);
        //  }
        //}

        template <
            typename Sequence
          , typename State
          , typename Context
          , typename Fun
          , bool IsSegmented
        >
        struct segmented_fold_until_impl
        {
            typedef
                segmented_fold_until_on_segments<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::segments<Sequence>::type
                        >::type
                    >::type
                  , State
                  , Context
                  , Fun
                >
            impl;

            typedef typename impl::type type;
            typedef typename impl::continue_type continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const& context, Fun const& fun)
            {
                return impl::call(fusion::segments(seq), state, context, fun);
            }
        };

        template <
            typename Sequence
          , typename State
          , typename Context
          , typename Fun
        >
        struct segmented_fold_until_impl<Sequence, State, Context, Fun, false>
        {
            typedef
                typename Fun::template apply<Sequence, State, Context>
            apply_type;

            typedef typename apply_type::type type;
            typedef typename apply_type::continue_type continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const& context, Fun const& fun)
            {
                return apply_type::call(seq, state, context, fun);
            }
        };

        //auto segmented_fold_until_on_segments(segs, state, context, fun)
        //{
        //  auto cur = begin(segs), end = end(segs);
        //  for (; cur != end; ++cur)
        //  {
        //    if (empty(*cur))
        //      continue;
        //    auto context` = push_context(cur, end, context);
        //    state = segmented_fold_until_impl(*cur, state, context`, fun);
        //    if (!second(state))
        //      return state;
        //  }
        //}

        template <typename Apply>
        struct continue_wrap
        {
            typedef typename Apply::continue_type type;
        };

        template <typename Begin, typename End, typename State, typename Context, typename Fun, bool IsEmpty>
        struct segmented_fold_until_iterate_skip_empty
        {
            // begin != end and !empty(*begin)
            typedef
                push_context<Begin, End, Context>
            push_context_impl;

            typedef
                typename push_context_impl::type
            next_context_type;

            typedef
                segmented_fold_until_impl<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::deref<Begin>::type
                        >::type
                    >::type
                  , State
                  , next_context_type
                  , Fun
                >
            fold_recurse_impl;

            typedef
                typename fold_recurse_impl::type
            next_state_type;

            typedef
                segmented_fold_until_iterate<
                    typename result_of::next<Begin>::type
                  , End
                  , next_state_type
                  , Context
                  , Fun
                >
            next_iteration_impl;

            typedef
                typename mpl::eval_if<
                    typename fold_recurse_impl::continue_type
                  , next_iteration_impl
                  , mpl::identity<next_state_type>
                >::type
            type;

            typedef
                typename mpl::eval_if<
                    typename fold_recurse_impl::continue_type
                  , continue_wrap<next_iteration_impl>
                  , mpl::identity<mpl::false_>
                >::type
            continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return call(beg, end, state, context, fun, typename fold_recurse_impl::continue_type());
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun, mpl::true_) // continue
            {
                return next_iteration_impl::call(
                    fusion::next(beg)
                  , end
                  , fold_recurse_impl::call(
                        *beg
                      , state
                      , push_context_impl::call(beg, end, context)
                      , fun)
                  , context
                  , fun);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun, mpl::false_) // break
            {
                return fold_recurse_impl::call(
                    *beg
                  , state
                  , push_context_impl::call(beg, end, context)
                  , fun);
            }
        };

        template <typename Begin, typename End, typename State, typename Context, typename Fun>
        struct segmented_fold_until_iterate_skip_empty<Begin, End, State, Context, Fun, true>
        {
            typedef
                segmented_fold_until_iterate<
                    typename result_of::next<Begin>::type
                  , End
                  , State
                  , Context
                  , Fun
                >
            impl;
            
            typedef typename impl::type type;
            typedef typename impl::continue_type continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return impl::call(fusion::next(beg), end, state, context, fun);
            }
        };

        template <typename Begin, typename End, typename State, typename Context, typename Fun, bool IsDone>
        struct segmented_fold_until_iterate
        {
            typedef
                typename result_of::empty<
                    typename remove_reference<
                        typename result_of::deref<Begin>::type
                    >::type
                >::type
            empty_type;

            typedef
                segmented_fold_until_iterate_skip_empty<Begin, End, State, Context, Fun, empty_type::value>
            impl;
            
            typedef typename impl::type type;
            typedef typename impl::continue_type continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return impl::call(beg, end, state, context, fun);
            }
        };

        template <typename Begin, typename End, typename State, typename Context, typename Fun>
        struct segmented_fold_until_iterate<Begin, End, State, Context, Fun, true>
        {
            typedef State type;
            typedef mpl::true_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Begin const&, End const&, State const& state
                           , Context const&, Fun const&)
            {
                return state;
            }
        };

        template <typename Segments, typename State, typename Context, typename Fun>
        struct segmented_fold_until_on_segments
        {
            typedef
                segmented_fold_until_iterate<
                    typename result_of::begin<Segments>::type
                  , typename result_of::end<Segments>::type
                  , State
                  , Context
                  , Fun
                >
            impl;

            typedef typename impl::type type;
            typedef typename impl::continue_type continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Segments& segs, State const& state, Context const& context, Fun const& fun)
            {
                return impl::call(fusion::begin(segs), fusion::end(segs), state, context, fun);
            }
        };
    }
}}

#endif

/* segmented_fold_until_impl.hpp
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
*/