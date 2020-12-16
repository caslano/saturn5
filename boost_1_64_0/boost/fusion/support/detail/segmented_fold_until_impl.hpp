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
pwEC74F/Rn2rlRQ+WAG0tZnVGhL37TP/jHUUuVGsOEUgltmdneUee2dnoqNdhBVEC8FzTLwlXDrjXsHCDNjS8UopgzLRkSVg2KgfznvUYb0yLmlK0aCynNc7jml8RoQ1RIWomKGkit/ZOb+opMvxuHOJzTZgPL6n4zY2FCkMG7nr0UfM3wijoo3pibCWsChCstaSy/V7+eF8iD+ByNF9Z6dvyQQ1ivv29XXP0rvVnbn+wdhHEZaR6HK0LEeEFcd1jI1rI9usb3/B9uxJG16scghLT4ez6uxMPliARVezDz+nLSOTLJTwziZUhONsEj9ot8UV4qnwMnpc7ZceQ+6WBfi3oDorIj1nhnuNgLEaFQ5b2cXh5DtmgfCUOJO1qSUgfDp/4/3Lzueyxe1aE7INhRMxuP5wEVUfI+NdSL6UkAPNgtQomUNOsdPXbuTBJ71vl7WC+RiHgCmZyjI6pO/Lu51/x2da7E5w2qZsKbF3X3Jnby17ATEekKz0QZjCMzm+ul9PaWtZeNfpdJWK48Um4rJNd+uI3M/1D5A0Y7LDCcFdpIKS150P6c/3ji+rC3DLWMcTjMm/4u+9wpjMjBZyvExKPlsf2/daU7rLLnbo9b4MHZm0JhCLytjJW8oA+6+/9vOqRKGNIqeX+6d1ITuogyucQ6YyiP+5QDhHmAlBcdu6tQL+ZMRTiOHT4neCD1QHHSvrS0paK2sfcl+1slyQkp1xUemWrJp2vbHO/aG5pVqZ1zCaw79p1uZE/mxbTiLepUhlytgvtIu79jWMSSmwlFLGfqEd5mcYo2jU0kSN/Bt7nr9iDJc+uBw18m/seZ74N4SJ3gfpVUF+ej3PUzEmVA4nVOvfOOV5DsYYy3IozmC97WLMblc3I7R2BqttDQGMwRjLqCzRFqS3nuflGFOUdlzZgvXWYY4whgXtCmPIX3PC8wBjdKGSW6ax3na7tbTF7ErtVA5GDWsp9Ayya38XkveBsSKjHtZS6BUk/wEk74wyiooI5e/28p9C8sYnIYstUD7IQ3zKVj4TE1VtsRYrAinkTdSMawXW0w5nmElBuhXR/HB+E5qDcT/DOJ+c94n7jm93gvtrh9NJaUppxzfiIJfA35GtoKLKy8FaYrCZXa/YB3A2/Xt3NnU0MS7WwsgMnICfQosJJHFhHI+KLJam46NXKsQxRPXhlBYtNhE5Fyfd/ML1CdkmY5giy9gsy0c98NCBGOGmxbClYbrSTGRSBlD1FW1N6CYRRRp7D1SOICZxLxSNUNO92Vn1ojq7dx/snGZgr/Z3PPckU1IHToaLs50ThLkH31CIj5PCpbNWjXTHZ0f18HZFT04m+TQfabGRKBVooZwRu4LU60EAjf4ziI+SJFgsOiRyVo3Ep0FaCOQ0RjhLYnDDtjaGP6lwHOUFv439tdOri8kYy0vb0MP5oprlg8cihfH5D9TOGKI3LnBiRwS8s24wz2wxgXDLbQnWrgIK7RsKCZNaO7d/4DbmEBNTg43G0azKbw8r1HAWzOm98TqJCJw3d2/BGRrutTvOoAt3OsiBs8r/X863Yc6knfc5O+CEhFcN5zs6Tq58McqpgbPK/1/ORzAnK4rZYsuo2xvTdn664zRZpKDYsp1V/qGcm/XjWy3+tvHWR2MI6sgXb2R/hGSzsaEktySayv4KyVpVvPBRkLa3QPaPWDZyz51OQ8FT2X8i2eKYr7+aQI+0so//J5Kl0Wcf7FDuVPZJSFbQxJI1lIDWW9mnYFlHWQwpD+WOsmB73MoyO6wLKkdLyfHmGvQQH9hXeBgTpMUnonNhTlmxMl0+OD9dJnNfYd6y8TctLeamzMZpyg1502zR+VG2ci/wjjnvjV7K7b0=
*/