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