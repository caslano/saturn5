/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_NEXT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Second>
    struct iterator_range;

    template <typename Context>
    struct segmented_iterator;

    namespace detail
    {
        template <typename Sequence, typename Stack>
        struct segmented_begin_impl;

        //bool is_invalid(stack)
        //{
        //  return empty(car(stack));
        //}

        template <typename Stack>
        struct is_invalid
          : result_of::equal_to<
                typename Stack::car_type::begin_type,
                typename Stack::car_type::end_type
            >
        {};

        ////Advance the first iterator in the seq at the
        ////top of a stack of iterator ranges. Return the
        ////new stack.
        //auto pop_front_car(stack)
        //{
        //  return cons(iterator_range(next(begin(car(stack))), end(car(stack))), cdr(stack));
        //}

        template <typename Stack>
        struct pop_front_car
        {
            typedef 
                iterator_range<
                    typename result_of::next<
                        typename Stack::car_type::begin_type
                    >::type
                  , typename Stack::car_type::end_type
                >
            car_type;
            
            typedef
                cons<car_type, typename Stack::cdr_type>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return type(
                    car_type(fusion::next(stack.car.first), stack.car.last),
                    stack.cdr);
            }
        };

        template <
            typename Stack,
            typename Next   = typename pop_front_car<Stack>::type,
            bool IsInvalid  = is_invalid<Next>::value,
            int StackSize   = Stack::size::value>
        struct segmented_next_impl_recurse;

        // Handle the case where the top of the stack has no usable 
        //auto segmented_next_impl_recurse3(stack)
        //{
        //  if (size(stack) == 1)
        //    return cons(iterator_range(end(car(stack)), end(car(stack))), nil_);
        //  else
        //    return segmented_next_impl_recurse(stack.cdr);
        //}

        template <
            typename Stack,
            int StackSize = Stack::size::value>
        struct segmented_next_impl_recurse3
        {
            typedef segmented_next_impl_recurse<typename Stack::cdr_type> impl;
            typedef typename impl::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }
        };

        template <typename Stack>
        struct segmented_next_impl_recurse3<Stack, 1>
        {
            typedef typename Stack::car_type::end_type end_type;
            typedef iterator_range<end_type, end_type> range_type;
            typedef cons<range_type> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return type(range_type(stack.car.last, stack.car.last));
            }
        };

        //auto segmented_next_impl_recurse2(stack)
        //{
        //  auto res = segmented_begin_impl(front(car(stack)), stack);
        //  if (is_invalid(res))
        //    return segmented_next_impl_recurse3(stack);
        //  else
        //    return res;
        //}

        template <
            typename Stack,
            typename Sequence  =
                typename remove_reference<
                    typename add_const<
                        typename result_of::deref<
                            typename Stack::car_type::begin_type
                        >::type
                    >::type
                >::type,
            typename Result =
                typename segmented_begin_impl<Sequence, Stack>::type,
            bool IsInvalid  =
                is_invalid<Result>::value>
        struct segmented_next_impl_recurse2
        {
            typedef segmented_next_impl_recurse3<Stack> impl;
            typedef typename impl::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return impl::call(stack);
            }
        };

        template <typename Stack, typename Sequence, typename Result>
        struct segmented_next_impl_recurse2<Stack, Sequence, Result, false>
        {
            typedef Result type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return segmented_begin_impl<Sequence, Stack>::call(*stack.car.first, stack);
            }
        };

        //auto segmented_next_impl_recurse(stack)
        //{
        //  auto next = pop_front_car(stack);
        //  if (is_invalid(next))
        //    if (1 == size(stack))
        //      return next;
        //    else
        //      return segmented_next_impl_recurse(cdr(stack));
        //  else
        //    return segmented_next_impl_recurse2(next)
        //}

        template <typename Stack, typename Next, bool IsInvalid, int StackSize>
        struct segmented_next_impl_recurse
        {
            typedef
                typename segmented_next_impl_recurse<typename Stack::cdr_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const& stack)
            {
                return segmented_next_impl_recurse<typename Stack::cdr_type>::call(stack.cdr);
            }
        };

        template <typename Stack, typename Next>
        struct segmented_next_impl_recurse<Stack, Next, true, 1>
        {
            typedef Next type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }
        };

        template <typename Stack, typename Next, int StackSize>
        struct segmented_next_impl_recurse<Stack, Next, false, StackSize>
        {
            typedef segmented_next_impl_recurse2<Next> impl;
            typedef typename impl::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return impl::call(pop_front_car<Stack>::call(stack));
            }
        };

        //auto segmented_next_impl(stack)
        //{
        //  // car(stack) is a seq of values, not a seq of segments
        //  auto next = pop_front_car(stack);
        //  if (is_invalid(next))
        //    return segmented_next_impl_recurse(cdr(next));
        //  else
        //    return next;
        //}

        template <
            typename Stack,
            typename Next   = typename pop_front_car<Stack>::type,
            bool IsInvalid  = is_invalid<Next>::value>
        struct segmented_next_impl_aux
        {
            typedef segmented_next_impl_recurse<typename Stack::cdr_type> impl;
            typedef typename impl::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }
        };

        template <typename Stack, typename Next>
        struct segmented_next_impl_aux<Stack, Next, false>
        {
            typedef Next type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }
        };

        template <typename Stack>
        struct segmented_next_impl
          : segmented_next_impl_aux<Stack>
        {};
    }
}}

#endif

/* segmented_next_impl.hpp
I7JGBSLpIFpOteuNDnzLjTYG0nlHvTprCDrq+4ewJ8gNA3S/57m6v2IkeeXfuA92zbb7O9GHHOjDCOB2U0H8LbLjsekggZ0GMlFj9NJ5XSQKDNTf3vaNWR9KJ7sjqFN+r2obO9MuTwQ7R5KTYu+dge9tir0XKnXD6R9ePlm8HA2w+OpR+GqKXg9cj8e84Zg9OQ0nc/Abs+4QY7gqs7nhid4Y+L35OfW/+BiQllOzNX6LIt30nOrjrk3I65RWN5xZiyKD01yOY0uWhepTRaqa0GftFGuiROXzn+t5aw7V454wBU7lrXCq3ITlfI7a5SBwz81CnvUMHscwT3vuFOja9DToly+8PMsbSZosh6fY4XMBfGaqb7yJto2c/ONwNy2a/CZaRJDvofjz+DnsJhyL9WXT2QUhDo9Ed9G+a7EhRzt5zNf/1aD9+990GvOiTDkXxhwGvC1yy3DH9qU9c2mO1vIRb4mAgvzue5yNFbfLyiy7Dx7y5W73HmwXN1tJbMNDph6Mh3bCSBKIfUXGhK0/y3CQTuTez23hzTouQTEeFQ5n8sxd3i9R53u53952dDk438Q2Q+WUZ9Buz9WN0yNjuvkcZ5elbkIaRn2uyAyzY27OMlvu3BxU6351SdPyj6NZuGJkNAkzjyHSuASDk0VITe+rJxuwXdOzQOQc3JMG0npEDs+1sy74R9xAYjae+1n/H4+/bzAP61+sJjhq
*/