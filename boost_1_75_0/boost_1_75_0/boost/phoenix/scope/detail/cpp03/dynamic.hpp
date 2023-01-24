
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
tb/Bulu6NIFKufOZQgpTX9n505In0y4sd6DBX+lRx+67+2rFPO10xQnJvC1ouXlzMj6IHs6flk6XyapxinAWucy5vl8PrGdPuxykEAShmYR4XKAakoF7rKWy7SoQKEuNO+tuhcjBG3yduS/SuYMiwJMiR/B8Xk7q3hILdYqGHZFoDaeWkHgFwn1gqX4I65NJlIDJkPd95PZyubXYEv9kQrHyZJWaOd+j+q8AYMV3E2yb/kr9/IaMeRik/p3KI8z7PeaAB+6AAO5Ay8yut5GtnkH+C3k+qwPieYhCNNTsVePPSv3eCkfmVf1dCk+HMy62ugFvJKxutcpVEPHc9RkFtrOdn2fbyVp2cGeTo+5Ok6dHu0r9WObo/paVyCW0YLhdIHFYZHlV36pjo8FSl8pj82ZNRXKuE4tPc9BYM8YsYivNLKohx2VlX5PebPmfb7TDboxsWvK7dH47aXVWq9/ko505qnoaLHlmpw0MZpEM6i8VzLi5x9pRcFnzrE/REUPWTbS3WiSoNO9d9URFVJrUctXu9wq6pXPx7kWKn3uI7mXL6ytTqsbHv7ktpxrxVZgkVk0tW541YK8tFd94DByYN3zXa06QP+gkEPP9+SBB/94b/cI7Yn5gVorvNxpmcy/SQ5yyzwkDbN9MmLEztOWqdO+46RPh0bFaCJTU1396Ya8xtp2rNLadsybXL5vJFMOvCysbmNotC1feClPy
*/