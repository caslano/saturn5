
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/new.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/new_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

#define BOOST_PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                            \
    <boost/phoenix/object/detail/cpp03/new.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::new_<detail::target<T>, BOOST_PHOENIX_A>::type const
    new_(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                new_<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* new.hpp
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
*/