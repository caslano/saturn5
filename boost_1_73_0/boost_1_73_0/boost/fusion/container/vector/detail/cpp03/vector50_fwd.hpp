#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector50_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector50_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector41 to vector50
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector50_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (41, 50)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector50_fwd.hpp
thT/UwjsddwL8XLOJ+0bew8DS793iyh1szErvZMHfzRE+/eLzmU7OO2CMgZqHyYGudzjcR0dVnf03NZ+pvpkrKSgdQWRBYNCSzVKN13OgvUdi1Glmzaq9Or0ou4qxqtDilxDttrY4LQFqmTntP3hojdodwdUz/I0TG8jcjf+hF36ZWbeXXXOB51u0PrY6pwjvTsX0lNlOy3S3VkrCppgTG01vvR8Ho56fXF40Dw8FPsigr//6tA0aETjiG105v45y5XGcjQL0WCrqoUCXSwBwWf2/d9JjP8r9Mzj9E9/o7FeeCQZBMNlNMuxdpKeXc2ZV4OnhZV+8xv91y3eNQEfnuOHXb8gThgAU+OLurH0tf7bCbnTj4D9yCBLR9HELU9T0UDFS+mLtNe0YiPMyr7GoDVyXx7/e6A5d+pK1W6czMiG9NwZCt42HYHe34JzqQ/HaOc0aHU/r2LaGhcv2/2rDyCNdgM8b9kEJb6KFai6qjeEFdl/+A8VX+rzr8IlV+5K7EJWqxZOfz95Jp7v6OgnAj2nhFUTGBGi54erUiqJcvlC4TevxUukqwfufHV8UI1KPbUawtZIT/qrvb6DPrruIBraVSisL1bGxAuQCZ5hKERvwSacyRgUIlIzXHn2e0HrAQ0dKXqFBKxkNlYA
*/