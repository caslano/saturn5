
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
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
*/