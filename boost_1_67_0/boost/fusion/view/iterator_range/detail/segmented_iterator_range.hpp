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