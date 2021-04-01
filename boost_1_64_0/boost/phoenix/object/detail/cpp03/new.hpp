
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
2rwpcJx+Bdfz6Rimfs6KXlltSkU5iThivYAkF0/FO6nghP2m+rJ/KuIwUDc7plu+0Ztj2JYAS6dja2MalUVXs/KlbX/88NCOVtlyc4rRlZM1z2mxZTXKL6rfO1PXow467I5V6CWttmAinQMphCMdSlEI3MRzA2nNyhS1AwctHCGBKnqAIgKfj8LAudJEXYNNpjDSw/TAuROa6XfSCoLuYj8zGy/barzXPAi/nQNGDvxgkB30QtpxWfDd7d4CsCsRPTm1pyaWPPPqlz+59dpTtOddk1+evg+cjcA/zw7zAPFlOAj88xHl9XTYVjQq1TuuOSAz9vON/j+26OE9v8H9w3nNkttfrn+fMUliwqgs+puxv68sKPmsq29ssse51LjeFvqXruVqNfI/DqtRnCoDp2G0c4Hih696TEdch0pNmgxmRCuWEV/53geCtrdsIRpAwjY8PucbG/ubI3OHtzuDxSH/YaV8yxTjVzob6+CcnIQrZIHGgGk4t09Qn7lk6ydrvwwOHr7Z9A0IC+pPCW/uzuNs8A5Qnw1746EfH2e9zE8R5+IdZk6oRsW4Hw==
*/