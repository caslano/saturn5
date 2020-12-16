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
dG2oHfzHGfgXdjzuNzdkxlwkAjrvv5A52Nmc3NZM7Rgn8nIm/TDknipYfaXE7MZeMWdE0DrjLb0xiw/7Nd4H/TPVCb/gvopzH0JZmc5xv897ePfkJUSPoUnBNuXK8kydkxxzeU4HRcm5n5bAYl4ao3HdH/QSqucSbHDmZUxraBJeAj25kCujoadbZx9nadnyMo6zwCtt2cgcCGPyv4TaJRUW+jn50DI1vu9Yp5cSv8HE84o84JpLF7SC5hZ72cWekj7nObQtc8dZjvuMLvZcrPQbQ4prnRX7O6/c2X31DoaFIv5DJ8z5YbWWctfLl2coDd7a0Qs55H3srKbjvXqYqDpvchkaLHVr3kWcZ4Pco5aG8XY2d12fvhc242MEYLqTQ5+puufSj+w4PpxVxBdcRzhvKFMcxpGo5bToZnMC6WdnG/R6nwD9Kdv0/SG524n0qfFp39ukm8udJhPELMw3MdXg1jSMZX4ApnkXqXMEcVPj3L60RTcCkP6go1PoJyf0L7ToeuvOie15l2l0GuP9E4ipdkW0Lulj6r5eZbm+5guI09/l8TQ0xlpGbOWuufYKE9YB6U+9G9IrWncEN08n4+JBd0c6bBZVESXwHhWhoWxc877/Hpqu94imVgjXjCfuqXHtvaqPmnT0q8LOR9+9eyFd5490vBN+b6RPjVmE67IXuOufsszTtAgis9RovT36x1UXq1TKhR9Va1CLxXXt/AXX3qd5EnoqL/UalNrQ4waHMossCoo8NkuqlsyTRKaK0yAKAVsKTv2UJc07EKl5ghsm2jTvLbpODoPE83Olp7A4s0aZYyJT+nmS89DXS95G7AUXl7NUcE+KOK7WxnQ9PYfvw5O1cVyGPFZCMF9ohsYZzy0yp819GYc8k4Clwhm+F0vaN/BDFci8mnHj+Yut49dJHUuZl37gR3o907gzS9fBKhWpSFJerU+NstG2+yWRGxSRUjwN9Dy8sW9x0e2PPIgLFYW4DqFlOEnWd2XOdSSQdLIqbN6rfS6JO5nksQpiEev1IO0/5eLMckbFuZez1VCGjWXgHL6xQnlKkcmy9ECR+jt9uJzuNgn2+fAi6XO/TD2VJDo/7HP09bpO2oUDNo2SwC6baVt/gtRTT7Qznvo6bibFfZbgsiyOskx6sE+iaDt/wcWdDYrMFxEvNU6KQKy2dYjIVVlUJiGohshVY+1M5CqwDWEaRxpH5aIvMmmDTIRCSsH1sHrhstfQo18SrPRCn8u41G3Qxv6ZYEtP5FlWFICdIrfzQhebJrxQvp/D2HOwuK/nYs8kKg5iFbOoXM4b9s/FPZOrOJQyTQzQW23cPznRmE+lUR6X3BOHnU/h3hcpY+rHUShTj417lYsJneu62KUgKKRIIv1CViBEc6xtuNjTIgxELsKY6ak7tb+kPZO8kDzyjC2TYqURD3ZM8i88GSalChnE19lz40/1cd1HZIsyDssSINW3cMLRt2V+Oykzhwzi2Pf0C2xtP71H2DkFDG8TZwlmIpvu2xczbcy105N5xT8ndCjPovbYxPnAzVmgOfMBPN+Z0+m9IfSujs42dPed5+cNzUw11lz/zKOYbg5ROpqGZ2RI02WAPnfeC16gNJisYV4n76ZpEHoLKJAb8szfXaeT6iLPE++pabqatHwL99Lp1ZIECnAFegb36O9xb6CROxt4koOYYRuDxwoYM+5YGwNHCkh/q6Ef7Pv4T6S3fB9x/Xj7uXT9mMec69fLWc8eB5JHDOdxX4vw+SxLi8T3pM+a170qRuTrPI/ml4CJDXiUIx99C24e7/a7fDDOvDAVmRRsolV03+aJJB/B/CwVaZkmbFqoIVAJu2+Db4s/j4xvsGtFDLWrFZU=
*/