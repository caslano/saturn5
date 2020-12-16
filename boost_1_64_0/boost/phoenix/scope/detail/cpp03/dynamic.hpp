
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/scope/detail/cpp03/preprocessed/dynamic.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_DYNAMIC_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/dynamic_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER(_, N, __)                            \
        typedef                                                                 \
            typename expression::dynamic_member<                                \
                mpl::int_<N>                                                    \
              , self_type *                                                     \
            >::type const                                                       \
            BOOST_PP_CAT(member, BOOST_PP_INC(N));                              \
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_DYNAMIC_LIMIT,                                        \
    <boost/phoenix/scope/detail/cpp03/dynamic.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER

#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#else

    template <BOOST_PHOENIX_typename_A>
    struct dynamic<BOOST_PHOENIX_A> : noncopyable
    {
        typedef
            BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PHOENIX_A>
            tuple_type;
        typedef
            dynamic<BOOST_PHOENIX_A>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;

        dynamic()
            : frame(0) {}

        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type const
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }

        BOOST_PP_REPEAT(
            BOOST_PHOENIX_ITERATION
          , BOOST_PHOENIX_SCOPE_DYNAMIC_MEMBER
          , _
        )

        mutable dynamic_frame_type* frame;
    };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* dynamic.hpp
vvYMx6NN0H1CrUuIrotww3V3QvdJXkbxp/cQdJ/iuvGn9xR0t3Hd+NMr/y1J+zTXjT+9Y6G7XdSNONNbAN1nhG6c6a2C7g6hG2d6V0D3WaEbZ3pboGvGeMT3ROKcX+2ErkXoxjm/OgTdTNLtQTtiR7DHSLo9aEcZ0LUJ3TjndU7o2km3B22wBLoO0u1BGwxA9xzopvN8ij2mJEfbY4TuuVwX5jh1N0H3PK57+r3r0VF0d0M3XRXnxtjhRtYN6J4v4hyn7knoXiDifBrd0VF05Q8wlu1X7zMkRx0XkqOsy0zQ3QTdxB7olkD34aBucpy6y6H7KHR53x6n7nroboZuYw90d0L3MegyKX7dQ9DdAt3sHuTVKeg+p9pT5eGf4bpbPpqkfUHsT8apa4LuLtLtQbjF0H1R7E/GqVsL3TZ1ehOge4Z7Baug+xuR3jh1N0F3N+n2INy90P2tSG+cuoehuyIsvWfefk9Cd6VIb5y68odJ2lWk24NwddC9TaQ3Tt086I4Pq89n3sfOhm6OSG+cug3QzSXdHoTbDN1JIr1x6m6Gbp1Yd8fZFg5A16/WRaDp0XUj55PQXUy6PWi/6R8laZcI3TjDzYFus9hTVYUrnUFezYHunUJXhBumGzvc5dBdx/dU4w+3Bbp3cd34w90J3fVtwb49znAPQXeD0I0z3FPQvZvmVz3I5/SPk7S/IN0e5HMOdG+CMzGnowaRHNIVD5clJEhhunOge4vQDSIxiq7Edbt97gzdH3+v6LYCXFOKHq5GEx5uC3RXqnTTRV5EhMt1w79HAd2+qv5Kq5pfJQTziu5bzYiSz3uhu07o8shF6Tdi6B6A7gbR18WpexS6d5NuD8I9RXVD9HVx6PY+vU/v0/v0Pr3P/8PzPZ6mziTt1RgTBeiJYj7t48VSbM0wjRZf9JQ3gX8Gcwf4XnDqcI22HJwNvhX2s8HzYa4ALyA98DzwRnANeBtYB3f7wQbwIXAB+Bi4EvbJaRrtWTCng/0w68ABcB54CbgKfB24EfxDuGsidxL8B88B7wSXgg+Al8PdKXAjzNoRGu2NMI8aATP5C76J4g2+GTwHfAvFG/xTuF8Bvh28HvxjyDeDbwXvBi+F/DB4JcwnwLeBtSM12tXkL/g9cCF4DfkHvhruV4F/SvkANlI8wbczpBvcRPl4tkb7EKUT3AT7BrCJ8hv8KuTt4M0UziiN9jGKN/hxBnfgbeBW8A5yB36B3J2j0baBC8B7GdIDfgW8F7yP7M/VaH9H4YF/Dg6A14K3gu+geIFHIPyM85Au8BxwM+Qt4DvBneCpkI9N12jN4AqwS4I9eDH4KPhnYOv5Gu1csBe8jvwH30X5Bt7P4P8FGu1L4Nng9eQ/eAP4IPhOKrcLET9wHvhuhnwE/wK8A9xC8QQvh31ahkZbT+7AxeAAuILCA6dReYFngOWLNNpFlC/gA5Qv4JuoPMBrwZ3gFRTvizVaH/kDzpMQHjgXzC7RaO8jfXAzzGvArTC3gQfDfAr8S5jTR2u0D4BLwNdTPQJvonSBHwYnXqrBZ3QIBzwP9rXgRym+4ExqD+CtVJ/GaPA5EezBT1E9BD9N5Qx+BixfptE+S/UBfBX5A36eITzwZJgPgnfCnDMW9ZjqFXgX1RfwixQf8HTK58s12hxwAfjXkDeBG6idgsvJfpxGe5DCAd9B+QL+DZUDeDdD/oJ/S+V5hUZbQvEA72HQB79P7Vqn0Q6UoA9+meoteCXlO3gV+CR4HThdr9H+geol+K9UL8Ed1G7A75J/4Neo/oGtcD/KoNG+DnMxeAz1B+Bp5C+4kPwF/wBsMmq0b8KdFzyTyg08i/IZ3E7lYNJoh8DcCB4K3gu+i+o=
*/