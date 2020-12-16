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
j7OhS7A/D6NAjwcwP+Mdx0s/k2K/jPcM7iL1F/oYm/8qGNHvcexfMM+vixi5T65zS1fuE9wv5T00Lve9sJgRfr0rGJk33p0RvY3ANwHf+8p9z5L+6NsiRvb7JnDGc3aznoA/8vrMtJTPicWM7P8w1hXce5zk10vcx7jrdsGIvV0g9ft2RsH1bexbIGcZ/yc8LOPlAD4L1rP4LODnAtYR6GVCxpPJRYzQ2yj5uy/rCj5vZl4Bn5+X+cOV0CGwd3KUdv5+KPd1TXdG+NYfeQn0Pijt7WjpNy/hPoH9SPvddjj4gvUnQYdAX94FT2DXF3K/gD+PgC+Q6x7WF8x/rIzvE7hfYB9B6S+e4bpAP99l34LrPaReS7n1KGN+wX01Uj/P4n7GQZ9IfZDxoWywYMR+50u9GwO+wI7hV/s6i5lfQOdWqV+jZPy+VOotv534nRCWcfoD9sd4rox3X14h9zdJ2tsurgvo/lza0zGMAr5dxP4ZOb5lhL4/S/ndLe1toYwTI2U8fEPG4d9I+dULRvZ/tmBk3U9lfvMQI+PrHzKPgK71rM/Y9QJpV9OE9Hvy+vPQybj1Phlvekv5Xy71PwxdAj3wS7/yNqOA31HoEsz3Sxnfm7syYj/HMY/ALn4t8yWpny8MkXS/KOVxHaNAjtsFI+tfJvPJUTJe3My6Ajn+szsj/DpC6kWtjOtnMTKuHQ8dAj4cKPk4muuCv9+SeeRkme/8TOYZ5XK9nzO/wJ77c11gbyOLGLHfgGDk83IZPyXfriotZoTepZI/m1lXoB/LZX71qLTvxwQjfEjwWTDKeQbdxzoCu+ws+fms9Nde6Xck3/92i/S/0v6mHcx1AT+/kfY3VtIzRuZRZ7A+4/4fyTh4OfcJ7H6t1IeVMt+9FLiADq/k46HSHw6S9nKj5L+08w19usp1pP1FBSN+8jbwBH/3RW8Eenc8+xTY9xvSrs5iHcHfE7kuWGcc+xfIpR/rCPh9lmDEHq4BT6A/pd0ZoaOiCyPyOg4445jXuF/An1dknlQPngD/Y/YjoGOrzDtPKWLELkdLv36PjLcyv94wX0g/K8eurCOwz/eZV2Af85lPsM7N0t9I/KuGyLxghqxLjgNfoDcyLu5axvqCsUbmE23Qx/jJDVwX8HGPtPd7mUcg38HQJZj/ZfAE8p0l46bc35f3S72U8XDNHun3hxUxMmZkHJF56FqZFxxZK/MA3m/MSJxmHwJ7qZP5yhyZt0o/0u8y6BDY72g+C+gZ1ZURu79Q8v1X4Av28Yr02ytlfDmUz4wjg+xHoO8nc59AvptlfbJV0n+9rAuIl4zQKf1mlPUEfN+fzwJ59xOMxJuuEu95wYh+3Ake47a9jIL7+F+7nLZKfyDjztAbpR97TdrxFqnH5dK+hkm/25dRQM82Ga8OkXH2K1nPDpF8PpD7BPurhn7G1zdIfauSfqtU1sFPgCeQ1zfMJ+B7H2lnFvQyLpH73jxW+rlSmYes4j7BOpJvgZ78H3WcKPpgGYLvDiJPMXPxgsmVi2dXLK1sCEQqI4HmUFN1JCD4GSbxQjl4LYFVwpnDc6kb1soc1aFQZV11pFrwM9aZ4wqNV3bCkrIFs8sqZy44ubIxQriTONECOMArHXjMhFc4t4tKZ430S50UvGJR+YJjKitmzppXVlldV6foTb1cGKe2KVDd0hZS9Hq3FcaDR0Lx7+jOOTj2LOHK+nAgIPhx6E7l4zWHoFvt25cHD4bWKDhno7lwm7saXpUPbzPnT+fBbQo137yzcuHs0ptd5ABnjjx+2NpSF6ivbmuKVDZXty4XLc58/rz5mgItDZFlgJoc3lV1gIMCIVJDJ/Lw0D4hline3J5LVyjc2BI=
*/