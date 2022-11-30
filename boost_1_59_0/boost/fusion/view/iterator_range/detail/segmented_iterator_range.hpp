/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_RANGE_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_RANGE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/segments.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/container/list/detail/reverse_cons.hpp>
#include <boost/fusion/iterator/detail/segment_sequence.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

//  Invariants:
//  - Each segmented iterator has a stack
//  - Each value in the stack is an iterator range
//  - The range at the top of the stack points to values
//  - All other ranges point to ranges
//  - The front of each range in the stack (besides the
//    topmost) is the range above it

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;

    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_back;

        template <typename Sequence, typename T>
        struct push_front;
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_back<Sequence const, T>
        >::type
    push_back(Sequence const& seq, T const& x);

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_front<Sequence const, T>
        >::type
    push_front(Sequence const& seq, T const& x);
}}

namespace boost { namespace fusion { namespace detail
{
    //auto make_segment_sequence_front(stack_begin)
    //{
    //  switch (size(stack_begin))
    //  {
    //  case 1:
    //    return nil_;
    //  case 2:
    //    // car(cdr(stack_begin)) is a range over values.
    //    assert(end(front(car(stack_begin))) == end(car(cdr(stack_begin))));
    //    return iterator_range(begin(car(cdr(stack_begin))), end(front(car(stack_begin))));
    //  default:
    //    // car(cdr(stack_begin)) is a range over segments. We replace the
    //    // front with a view that is restricted.
    //    assert(end(segments(front(car(stack_begin)))) == end(car(cdr(stack_begin))));
    //    return segment_sequence(
    //      push_front(
    //        // The following could be a segment_sequence. It then gets wrapped
    //        // in a single_view, and push_front puts it in a join_view with the
    //        // following iterator_range.
    //        iterator_range(next(begin(car(cdr(stack_begin)))), end(segments(front(car(stack_begin))))),
    //        make_segment_sequence_front(cdr(stack_begin))));
    //  }
    //}

    template <typename Stack, std::size_t Size = Stack::size::value>
    struct make_segment_sequence_front
    {
        // assert(end(segments(front(car(stack_begin)))) == end(car(cdr(stack_begin))));
        BOOST_MPL_ASSERT((
            result_of::equal_to<
                typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::segments<
                                typename remove_reference<
                                    typename add_const<
                                        typename result_of::deref<
                                            typename Stack::car_type::begin_type
                                        >::type
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::end_type
            >));

        typedef
            iterator_range<
                typename result_of::next<
                    typename Stack::cdr_type::car_type::begin_type
                >::type
              , typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::segments<
                                typename remove_reference<
                                    typename add_const<
                                        typename result_of::deref<
                                            typename Stack::car_type::begin_type
                                        >::type
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
            >
        rest_type;

        typedef
            make_segment_sequence_front<typename Stack::cdr_type>
        recurse;

        typedef
            segment_sequence<
                typename result_of::push_front<
                    rest_type const
                  , typename recurse::type
                >::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const& stack)
        {
            //return segment_sequence(
            //  push_front(
            //    iterator_range(next(begin(car(cdr(stack_begin)))), end(segments(front(car(stack_begin))))),
            //    make_segment_sequence_front(cdr(stack_begin))));
            return type(
                fusion::push_front(
                    rest_type(fusion::next(stack.cdr.car.first), fusion::end(fusion::segments(*stack.car.first)))
                  , recurse::call(stack.cdr)));
        }
    };

    template <typename Stack>
    struct make_segment_sequence_front<Stack, 2>
    {
        // assert(end(front(car(stack_begin))) == end(car(cdr(stack_begin))));
        BOOST_MPL_ASSERT((
            result_of::equal_to<
                typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::deref<
                                typename Stack::car_type::begin_type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::end_type
            >));

        typedef
            iterator_range<
                typename Stack::cdr_type::car_type::begin_type
              , typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::deref<
                                typename Stack::car_type::begin_type
                            >::type
                        >::type
                    >::type
                >::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const& stack)
        {
            // return iterator_range(begin(car(cdr(stack_begin))), end(front(car(stack_begin))));
            return type(stack.cdr.car.first, fusion::end(*stack.car.first));
        }
    };

    template <typename Stack>
    struct make_segment_sequence_front<Stack, 1>
    {
        typedef typename Stack::cdr_type type; // nil_

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const &stack)
        {
            return stack.cdr;
        }
    };

    //auto make_segment_sequence_back(stack_end)
    //{
    //  switch (size(stack_end))
    //  {
    //  case 1:
    //    return nil_;
    //  case 2:
    //    // car(cdr(stack_back)) is a range over values.
    //    assert(end(front(car(stack_end))) == end(car(cdr(stack_end))));
    //    return iterator_range(begin(front(car(stack_end))), begin(car(cdr(stack_end))));
    //  default:
    //    // car(cdr(stack_begin)) is a range over segments. We replace the
    //    // back with a view that is restricted.
    //    assert(end(segments(front(car(stack_end)))) == end(car(cdr(stack_end))));
    //    return segment_sequence(
    //      push_back(
    //        iterator_range(begin(segments(front(car(stack_end)))), begin(car(cdr(stack_end)))),
    //        make_segment_sequence_back(cdr(stack_end))));
    //  }
    //}

    template <typename Stack, std::size_t Size = Stack::size::value>
    struct make_segment_sequence_back
    {
        // assert(end(segments(front(car(stack_begin)))) == end(car(cdr(stack_begin))));
        BOOST_MPL_ASSERT((
            result_of::equal_to<
                typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::segments<
                                typename remove_reference<
                                    typename add_const<
                                        typename result_of::deref<
                                            typename Stack::car_type::begin_type
                                        >::type
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::end_type
            >));

        typedef
            iterator_range<
                typename result_of::begin<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::segments<
                                typename remove_reference<
                                    typename add_const<
                                        typename result_of::deref<
                                            typename Stack::car_type::begin_type
                                        >::type
                                    >::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::begin_type
            >
        rest_type;

        typedef
            make_segment_sequence_back<typename Stack::cdr_type>
        recurse;

        typedef
            segment_sequence<
                typename result_of::push_back<
                    rest_type const
                  , typename recurse::type
                >::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const& stack)
        {
            //  return segment_sequence(
            //    push_back(
            //      iterator_range(begin(segments(front(car(stack_end)))), begin(car(cdr(stack_end)))),
            //      make_segment_sequence_back(cdr(stack_end))));
            return type(
                fusion::push_back(
                    rest_type(fusion::begin(fusion::segments(*stack.car.first)), stack.cdr.car.first)
                  , recurse::call(stack.cdr)));
        }
    };

    template <typename Stack>
    struct make_segment_sequence_back<Stack, 2>
    {
        // assert(end(front(car(stack_end))) == end(car(cdr(stack_end))));
        BOOST_MPL_ASSERT((
            result_of::equal_to<
                typename result_of::end<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::deref<
                                typename Stack::car_type::begin_type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::end_type
            >));

        typedef
            iterator_range<
                typename result_of::begin<
                    typename remove_reference<
                        typename add_const<
                            typename result_of::deref<
                                typename Stack::car_type::begin_type
                            >::type
                        >::type
                    >::type
                >::type
              , typename Stack::cdr_type::car_type::begin_type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const& stack)
        {
            // return iterator_range(begin(front(car(stack_end))), begin(car(cdr(stack_end))));
            return type(fusion::begin(*stack.car.first), stack.cdr.car.first);
        }
    };

    template <typename Stack>
    struct make_segment_sequence_back<Stack, 1>
    {
        typedef typename Stack::cdr_type type; // nil_

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Stack const& stack)
        {
            return stack.cdr;
        }
    };

    //auto make_segmented_range_reduce(stack_begin, stack_end)
    //{
    //  if (size(stack_begin) == 1 && size(stack_end) == 1)
    //  {
    //    return segment_sequence(
    //      single_view(
    //        iterator_range(begin(car(stack_begin)), begin(car(stack_end)))));
    //  }
    //  else
    //  {
    //    // We are in the case where both begin_stack and/or end_stack have
    //    // more than one element. Throw away any part of the tree where
    //    // begin and end refer to the same segment.
    //    if (begin(car(stack_begin)) == begin(car(stack_end)))
    //    {
    //      return make_segmented_range_reduce(cdr(stack_begin), cdr(stack_end));
    //    }
    //    else
    //    {
    //      // We are in the case where begin_stack and end_stack (a) have
    //      // more than one element each, and (b) they point to different
    //      // segments. We must construct a segmented sequence.
    //      return segment_sequence(
    //          push_back(
    //            push_front(
    //                iterator_range(
    //                    fusion::next(begin(car(stack_begin))),
    //                    begin(car(stack_end))),                 // a range of (possibly segmented) ranges.
    //              make_segment_sequence_front(stack_begin)),    // should be a (possibly segmented) range.
    //            make_segment_sequence_back(stack_end)));        // should be a (possibly segmented) range.
    //    }
    //  }
    //}

    template <
        typename StackBegin
      , typename StackEnd
      , int StackBeginSize = StackBegin::size::value
      , int StackEndSize   = StackEnd::size::value>
    struct make_segmented_range_reduce;

    template <
        typename StackBegin
      , typename StackEnd
      , bool SameSegment
#if !(BOOST_WORKAROUND(BOOST_GCC, >= 40000) && BOOST_WORKAROUND(BOOST_GCC, < 40200))
          = result_of::equal_to<
                typename StackBegin::car_type::begin_type
              , typename StackEnd::car_type::begin_type
            >::type::value
#endif
    >
    struct make_segmented_range_reduce2
    {
        typedef
            iterator_range<
                typename result_of::next<
                    typename StackBegin::car_type::begin_type
                >::type
              , typename StackEnd::car_type::begin_type
            >
        rest_type;

        typedef
            segment_sequence<
                typename result_of::push_back<
                    typename result_of::push_front<
                        rest_type const
                      , typename make_segment_sequence_front<StackBegin>::type
                    >::type const
                  , typename make_segment_sequence_back<StackEnd>::type
                >::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(StackBegin stack_begin, StackEnd stack_end)
        {
            //return segment_sequence(
            //    push_back(
            //      push_front(
            //        iterator_range(
            //            fusion::next(begin(car(stack_begin))),
            //            begin(car(stack_end))),                 // a range of (possibly segmented) ranges.
            //        make_segment_sequence_front(stack_begin)),  // should be a (possibly segmented) range.
            //      make_segment_sequence_back(stack_end)));      // should be a (possibly segmented) range.
            return type(
                fusion::push_back(
                    fusion::push_front(
                        rest_type(fusion::next(stack_begin.car.first), stack_end.car.first)
                      , make_segment_sequence_front<StackBegin>::call(stack_begin))
                  , make_segment_sequence_back<StackEnd>::call(stack_end)));
        }
    };

    template <typename StackBegin, typename StackEnd>
    struct make_segmented_range_reduce2<StackBegin, StackEnd, true>
    {
        typedef
            make_segmented_range_reduce<
                typename StackBegin::cdr_type
              , typename StackEnd::cdr_type
            >
        impl;

        typedef
            typename impl::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(StackBegin stack_begin, StackEnd stack_end)
        {
            return impl::call(stack_begin.cdr, stack_end.cdr);
        }
    };

    template <typename StackBegin, typename StackEnd, int StackBeginSize, int StackEndSize>
    struct make_segmented_range_reduce
      : make_segmented_range_reduce2<StackBegin, StackEnd
#if BOOST_WORKAROUND(BOOST_GCC, >= 40000) && BOOST_WORKAROUND(BOOST_GCC, < 40200)
          , result_of::equal_to<
                typename StackBegin::car_type::begin_type
              , typename StackEnd::car_type::begin_type
            >::type::value
#endif
        >
    {};

    template <typename StackBegin, typename StackEnd>
    struct make_segmented_range_reduce<StackBegin, StackEnd, 1, 1>
    {
        typedef
            iterator_range<
                typename StackBegin::car_type::begin_type
              , typename StackEnd::car_type::begin_type
            >
        range_type;

        typedef
            single_view<range_type>
        segment_type;

        typedef
            segment_sequence<segment_type>
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(StackBegin stack_begin, StackEnd stack_end)
        {
            //return segment_sequence(
            //  single_view(
            //    iterator_range(begin(car(stack_begin)), begin(car(stack_end)))));
            return type(segment_type(range_type(stack_begin.car.first, stack_end.car.first)));
        }
    };

    //auto make_segmented_range(begin, end)
    //{
    //  return make_segmented_range_reduce(reverse(begin.context), reverse(end.context));
    //}

    template <typename Begin, typename End>
    struct make_segmented_range
    {
        typedef reverse_cons<typename Begin::context_type>   reverse_begin_cons;
        typedef reverse_cons<typename End::context_type>     reverse_end_cons;

        typedef
            make_segmented_range_reduce<
                typename reverse_begin_cons::type
              , typename reverse_end_cons::type
            >
        impl;

        typedef typename impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Begin const& begin, End const& end)
        {
            return impl::call(
                reverse_begin_cons::call(begin.context)
              , reverse_end_cons::call(end.context));
        }
    };

}}}

#endif

/* segmented_iterator_range.hpp
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
*/