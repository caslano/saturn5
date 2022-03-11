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
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
*/