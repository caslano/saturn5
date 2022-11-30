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
8lTLQrtmO9psacLImzNEEKTHGa0X7GJnwaAotXYsF7tE95P9nuf5k/2I04Elt27n/g8z10n0PniFrtpZrMayC05YNWDOtVGlRkYL2DEG7ARZvf+V/SEGjVn3FLCqDxrBRDBKQMwNF0Pjq2Vfk7OxJilN/l8kzWaKwquvBZMPReYvUaqvvGmXTmpMXqKgVdHGbsPKv8ymAaMl90x2qhW4Nreq3pFsAU3sWLucTRRwiPSQoBspFCMTUQXiPB+7oQcbgXG49N7Qoyzy1U1064gx1n+itjeD0g726mpeZ7SJEjrTlMg7z+z9T8bcO3Se936MnVi6O2JwQ7SDuyOnQIsXau0aXPkzdK4LApdhtnFDgmhOxtn1b5MCOA5N6Xx9LMHcs69TRHro87RAjcxf8Z2w0SxbDl5NLAu+IOom2mFnGjyys0Yqt7XQ5+gFz38IxUFpI6SfXoeHXIdQDvwTfmSyGcLuiydqphhxYzkMrWsthcWtYWHjsOQjuuJktz2LiY5ydPyDtWbRu0mS/1Ys08YcNmPQs91xcWW5khAJ64rA96hzCN40uvvb4XreDT+ingucR7M8Uu8HBcbI8YrsxxeONAY9cHvKda4L/2aGFR8Uh0Cu//U7pcUDdP2daVyLIFoEHidtNrHYqhXItPjEfrY69GYOm8Apa+Fe43zL3y43sGuwmmwbQ0irh751xAWTCqkrZssNltXeZ76BbD0M0EuQ51YGbsgBBZns74lqzrPgKaUKYAjWSg6d/VaPJRvpjM3iXUVzk+oIu/tLgp2XxI+YjRqtHN0AtEXUod3v7MccqRYL9b9ULSbalPWbgmoJ7goxBuHDuU7iX44jOgY6G6i+SSH2HSYumlbd3mxKbWAjWdGXWDNA991xOLD9y7QZs5qb5hAoILMeA04B43rfLLdx3a4M0GUqL209IMB4foN5gY+wYNAabcpqsu3HTo3kMf3M6UlwSHjds96WCblsA9jm8FwJfQOlJPNEtLugavyQFL1JtNzsCrnG3Iz8rnAvF9brECqjjqUo0K2y86ZWCpnFbWxZwPadfY6pGeb0InUorSmGlM4K+8vsZKRSECJF5VJoYPvT3LEoc7PAKssxbgqbVH2SttJEvYtvK55REWHmE+xwyHX7FTX8KDLzyARdKW37TliSWLPwXJL6G1/ycjaQopTd9kK8uU9wV3fYPKUmntZ5QwjjAGCdaYtPSZ321mWysIwG/ahbGwSpHg6hfY9PO+PD82w6+0od9D67LDwsZJ3Jlr2B2K9YuPj27kDf06Ym2TvjuVri2C63WI7ZLSeU0uc60zEOCkl32sFzBaxuZ1LTTqSenUM1O4nk7Og4LNYuOBBRTrVYBxpw1ylK3Ii8lOrcP1Kw83aXzajYIM/3aTQVwyUiVW0qKhXsdbNK1PpB5rpgHg2/nuOtn0wQUl2gCiMrAlllWaDhP8cOPbHIreMeo8r7cHJ7sO3YOZ946uihfvcuSw1M2+GDJslflTBrGk6kik8v9xP024TCnHR7FBExDMxuOQKYHXCgcxXB4YZUtCtK6ygncIPk/YNxnpaLmshrYCzcepXxcMcMlXmxPr23rVXKneFJl+LJogX2rcKAf3Wo6lANQ417d0CGsCjInsLshy4BuowT9UY4L4MJj3J/2H/heDok1lW9F7QA9nY05SlK295n1KKjz2vYTZxipjfyWg+Le8eBDvVpD4/jN4fxwhTtlp6mfqF4nyfLf38BNFZ1/8CLeiGlMzzROyRWvSW1GrZ0pxRhaWoUlNuIG3Os8HUQQPO69TJF60LZNXyTcqpH6FboAOwQGfdWt2V3dzcxXPdgvS1fjCOgFEqPTChJTAzBtqH5lEZ7NTOxxPild+QuGw7Bjdye9aq/NUB7zmPceO9k5q3UdYOem5ecqB4A1lZMotmlqJPiFMKR0OnHe9SpqqHxxiXrsd3JqMU4vVA+TdpGOVcL16cblr4UPb9VmCdx0yHx1nGDgXZevCtsBpzmAt0E1bzeRrc012e0Q415jBnSP1hwBKXB0QQbMPw3hf4iQnNsVJjmFf0vBRhcWf0qiv0scslppF3bwnXHvVqNNCTdrEJNmTU3Qj0zQAb8jaCzoDHFiV2azJOfdZyX8QKQkVEteiKldJdBI0N6umLmQT1pkmMmso4rizlKaTi9dmS2FjOywquhyWsUgvg+Jk0lvU6Uvkof2Q6oS2vSNfJ5Km9GHaga4Dk2+NOwigJl3o+54PjdLGggD5DWH47Fo9/gRNiKVAx/UbAWhP2qIQ3y5Q/ajQtHVbd8r0Bn/JytQSo5kkjHImU1xXatc1H5HPpv0QXuNHVJie/2gu3Gn/WmX6s0LI26Q0HPeW4lMFlL7OvX2HPd7RNDr3dLOarXoKmqzCvye8MeAZ5Yjwni5c4SQ5P1RmoLwNkHuMM/avA2vdbJYIU2YH9Uzw0GapRhhkHTynit1gX9beXD5TpEXWqnxK3gxfKwC9fnePDC3detUYXynMutsz1u54TM4RiEBjUOecyjQyx+q/oEb+zDZ5TQe7TI1LSzr7ddjmVoEsGR/zWo9/PQl7GUDp5V2CruJ59f7VLAQ1gc657+FrjJKxQovoQhoTASUJWIDrcOycK8H9DHESiZUiQ6SOW0THSVTK/+7CSE3MdKNHd3ISpCqyzIYjtV+K0PawGJFm5eTTfmHCuUG4Sm0B/BPoXshOscYrPGef5Ru0SAsa8YXaa/FR08mJevY0z/OUZcFcDOlvMbBkHfK1eEZgrss/cEZys5MEQD0hk4LghIC1wq6JwUaFx6X0Y7FoUsKKE0wcWiVewywCLKNxZosf8mRO9khBJE9dApAfraNfgej/j2volD5ZcHKQGPwbzNdRRAvo3Y5Jiqe3yZARtMsG0ISGr9tsVitdYpky4XVFPD5O12d/rZfjFfM/dTDsVf/4LMfEVoDUs+b66w5uh3clmL2/RShb3YPY2EcwWWZ4cRhVKYatZT9vmNrkEwfaSLBJSgGbP2EQk7C+NITLovPCo/N1bMJl7/LbG44Zy+gegTm0b20wiNGHadzhLIijptFKqeMOTwlE2YZtBj/hXu5svCGQ3mStEVeABn8Rmj6DOlXOJqXyELCUjaXSG9L6yKm/gf5tH3fFGYmL/N2JUlzXVF+vq0oK6kYY7okyIrvVIJYCcsDcHoHbSNEOTx7+Oym5Q8Y1IVC1WPtBayDjI4LhpqKlUipKFA2VEy29Yf2PctqVAv03//G9oHVhtFrNVuDh1muj86MtI/MHZPT2CBAo4qssgcJ2hgIC48M8YeNmKjh6tm1AWFKXG9NSndOtGFfbf6S2uHNcLuyOdKi/WBChgMpAfCEkb0COmINeZItJCvP279za8SG2eepHPDza3pC2t2+eLyslKpTDaHa+VlhcZE+DitLJKvB8LHIVJVI5QMt8orykfeXpgspU/G4V6uCYIGJWDpfJYvycY7jypXkV4iEzifDkElx8jWGWPDgsazbqm6YpZR1sJeWHMHvfFVD2zNsesp4ena120d75L3JJSTKOHTWYQwW0HVF9RT7q859CPRDJOHtksn4TfqM9BpeY2I1SGhXXRwj0dM/zMrz9O2wMuxKmOqndeHbv1oRslaAQULJ2tpWz3Fyml7kvWDtkshZboMLSsoSFYvTnWiziEsD68Z9/LWufVBppHJXAt8BPzklcx2PFwgXacSHpPcQL/Y+bVKzso+TPVP2R8veYkmg+iz3uWBGAtZgm1+d+uWxjxD2c2zsSCcj7tUsJa2zw0TOMjCDkP2WHRpleH2fkFnoqBA0oUqpg095KybcxQYRfenHJWBzUscFb9FujifUNXNWtdmsUEjRm8D97QEjfJyhxs5Mt9u16kQ/BfVudTUUDHhzfXmEU7DY3T/CUChKdRTzMk6R0Y7dfk9lgn9PL3xz0B8arsYwmSoKp4J1qOZZiMfVYyMJX7xOs3C7QNpUwq6ouFnT+wvekYTksMMDAkTVKNGlrGpt7CW0JIvkoFVSrOA5O4WSjENdzYRrWHupOJuewLZRy8ezzOsF5cN3+u1rO1Cylt8P3u5I8Uv45A+FZTq1huAZRG8/9jNHCGl+GTTU215EzOz1pu99cXBqxW/8rPBJnvGAJbiyeKCYMTLB2h6qQle5Xzmp9GjTD4zRKzR/pXDRoC65qvYYz6QPXLpWf9AqK+Wy7qp1w+EPzLTLk2a2WXxZRDFJ9TYO4VMn3ZJ6pH6EmT6dC7zoFj674kD1VdlX0iY9wjlhS3odGranylnc2ldfbp0vDh8UwHL1949oeutnJzFu+7+6bbWd4LLMjv1DmjOtSh3/kG1Tu+OdjUsTyxAyFGKbRRNZc0zioU0ZqR6DKNH94p2lSCTvtsXVpdrSV1aT21Hy0mEJ/+d+kBL8sEv/P1v6GoNbHUnITpW8eA19eFHouTy3ZeaMtwz5HRVQiJvnhPCvJxbYijCCDaUahmopksn11RBLFZqZkkCG47pBfD6wmZmCj2ZfvGmJ7FB/7gsj2ipAFPxQpQsoobshYqXS40lS8GOv5cLz6ZSndHDuHkr3ZJ/mt19yqTB3Z9/R/d6Ib9UFHpDZmKD18NUz6n5praojGN7/DSJ3OxtZjrYxtyjJ9y1ddmvfPr40IvKK2Bty67RYi1uwMslU5EVu0dmk5TYG3kUK4OyrTvoGaqFBPyG9Lad6XYcEaP0hql4Fvsfe/fgJMdkZFu45oe/7HhvarbPTI9R6bSekrTiJlptWWNuTaoMLlNQ/bQ0KUCTqtzi8QeSyc+WrmTjvIVLEXDiv1zudbU2sqmpPgWIOGjfBBctEbmkn9PLB4FhfunhrZ8pbgn8oK5D2i+Zt8JG+cJtLdPiUKfY9VT3BkgXMdH+BqY9lqQZcBuJEFNYE9NBgLOXjIyA+NOZo0xTU8VZrtVGCQcZ5pLzLWviL6tEEY0Ohq00p1w+2/pV993PfLnaGVavXzsFlfdePjHeEWczJa6V2Ln4X6mPUpe6SR4fz3k3LSQUMlCHAUUENzEoJHGownQU9TtxARwJQGF/09JqjRxFgrWpx8yTocCp35e0O7qv9Re3hrrS++YvnzxfazBcYkUChg3yX3lZcaBDDOwtQjfMjOHlWM8Qq4zFDq2Z6c7lwWrCQd50VmdsxipyI1VsNtBk4rG7kVIaF53bJK5M4MK0Rm+WjmEKGaNajcxx7SqW0A6FxaHpmFSwpK/65bAdMvGH6RtKF1NbvYnB7QBFCidkUg/gjqFi0dNRibQMbsXPwA7KxTw2hJCKx0blC5CnTAJcA9tO5/gOpRKf6Zl4V0a30OagjqbimukcahvTW6AL1lO6ZDYGt4Tm1I458ar0L+SJGe22ZxgnNXHojC7JzKrE/lnA/+y8d/gWK0HJo/KfuSQxxhQy48lgjMmeHorwob2i5mahi6aQiRkFLO7EFhiSWoTisEQFWpCwDMls0vGWI6kHo3HDqQODUKGK7DJc/fKWk8U6MCWIxBc2CqQZolgl7BvAWAApbEzJqcHiITAltG7FKTA1JsiZmJ65MV5MyobcsMzPSFP8QhvyxlhCVxq/mJ4xJ3kFMjR/MCZdQ26mFDHBEqahi0jkEkPymWKErNVqEmxLOc25ePPh7c+UQkUQvKPym7ziVEbmOAVfGJn/zvuYm8kL+kzM9QT3jM//CbIzsSTMC4bCETuTCm1YSPObmkMVQGNmSp5bh8oSOGMJLUHKWJF5UO3AmsEzQdzMyWca0YwwO6MVKMDkSJljCKEjeGatfJx7bAyszPJqwTRgr/9jq/FDX5906dmx132hVPOOdg0q/rxW9Ua6AbviGzHDftJgm+bjscxjkv1ifrTIiTe5EWm93bVm11Y00qweNm7BvlTJG0PNo+g6yLxk1niIaMXOVM5DjJTL3rGXerkoeSdZh82WVAAfKSvbyVfzYYmcE+8i1Hzp6JbV2LFjH67gy6Piq3AVCrx0Un/I0Gd/VvZ5peK7cBXSWzlzmzbbUP66D7C81dNDT/bCKiWNuU0uhtNap6ihlxkiC6dpCz+POmOPGwZ794qt/E23Yq7cbKb78qw4AmPnRpAVqpApib2iFapQYMm8bE9hzOnNfB+nF8oc6byBbK4ZFR9rSVXQufQu6HOdOmVow5L06e6+OX/d1mM8Wl2fTDYJ0njDGe5laVwpNsWqdMRruJaFn0ORQ/UWrYOcFTL0DPc/X2xJ3dEeOGMZVkGIH2s0kWIGPWNl4QZlZxUxl/4kyRE94mirz40Tf2G7UNUJomyWkAvtmlP6u+3y2HQzW6lZWsrQMmunwde7e8rea7XJ4uDCNXkot0s8Rd91eug09EsaYFdSsqfDY4HeIAcRm3EKpdyN3HzgczPw0fVWXLgGRK0YswI1UzEIN6mJi3Fdc6c+PjrDikOdpaiGx+iugrri3B03b8dyV6X5EtH9ttZijerch4584xwq2i1qSQqPBxRLio3h951lb6nXlV7dQeBpMXRsLHOViDNWsyFAI/sCgBrBa3uqWd7v+BlFClJbpSnJqSw/kUPXaRHkXvA47bDMtL6rDizw6maTY+/ygqCQavniPeCTZ9mXV1xYcevJZc7WSnq9gvxadyBATHb7opQLnixyuxpsbh4ff2yEvAUYg8T30+UJFttCObVGrqJEjubcUu51d7LkyBQ/5qWKQh3rA1B5puzLu5I+GjN0rbG77VuJkjAsuSnf5wk40wuUR9YjJon4jjhCN4fKKlMlv2etio168dD8A62Z22Ax+1fSY5migEPUrkfuS+fdkytrmPeoncORDZF7moWhrK4xE3JSrkgJ1AWuTGEdwkKwMwh3OZCxpy3dYWhhz6gjH2mR2dboSmTCcLHuP3lqiHUodWHc1yNs1ydg0u8KiJwoYiZDgDeyIkNbSYqFka8mr9jGKuXSbGwW7s7y09FU+ARCnXvLtaAgIuFFJK/oNikWnR4J8zla8fEks9Z8/2XXf8tjs3ih4ZLBoj563ugmM1JnMrSlLVXj2dYvYWPTe65GAYcU3xfi7ZwDCOQSLa1pJ1kaE/uBery8NLD1JmBKmuBBGD6dVNikqn1ShR63SYVKRD80dlyBOL7kBISC/1eYoSg3U1n5VcBSYY4XQWl09TAnclYwqtRw4owAkGbHRSpq3L+VrHPXkzspFj5LXHiVyaBF3wwd7FVHfg/2DqGTSY6B/wSSseaHDuUywF8gmFNFtQzKzxLSuY+vU0D3za1SDp0hmPPyViufZwDlokod8jm91yCo424X0nn+i2o5EEkQ0lmZIihDNSdpiYBzJRzmcSg90LBwFrC7SXCfBXJGN9ChY2+Lmq0FcmY60KFk35t6fT3hlmr7V33CbLzQ1+QCTUlI4ZemYn+jXicjYZ+lNLg9mmzfxkcauBYDD8L0F9+uy73rtWPswSg75crD28U0einFn+m3084DsshLek++sKEEY8V3YZIcyn6MaQo+SfsV1b0I4Lb27OwWrLaoAaWWUKwC5npqYZbGyRb/C2/9cmq9b4/vjswI9e0q3Hm907qwQDDrRQm8zasI1tEVQ+XgF59o6nFBKJx6qI7LZ28QOfpo6LZJwU5CID3BDLpKNayhmz7nWmyHmmZCazPLVznc6ErJ63xT3tRogr0FzEg5YWXYnaujkxo6FavzI7UaIgt1bjwma+yrHHG2rfMw
*/