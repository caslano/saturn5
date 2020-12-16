
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_C_TAIL(set, i_, T, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)< \
          T BOOST_PP_ENUM_TRAILING_PARAMS(i_, C) \
        > \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)
    : s_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_SET_C_TAIL(set,BOOST_PP_DEC(i_), T, C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c) type;
};

#   undef AUX778076_SET_C_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
GJEQ9VIq5TISUWScKBKmci1llFtJvYqk66goneqMJJJ0np93OcfzP5/O13Nmvmx+71rrue6191577bWQu9r3ddfWpw/zfrmR9lqXc6y9sYz7vS6djeV+4Ot2N5a/w8vtTXsZPp/7GitI8+31R8YAfy7cTYx+8X65Fz9LfzDSWJq8fxuNr+SZ/WFklPY+eJz25PzNQe6rnk3FV829X55GrvTZs7Gtn8/nuZSTmC8wFpF7qcWUG+XteJXc+NmXW4ltiz17g7ryLv8tZCzy5TZi2yvetveImzxjbyVucc8+ho337DN8KntoFeCrWimO7UaG2PsDvo/5WP6Dcvtk/A+d5R7pd8rV9rl2FLmyD1FKA/PfQtn/11hsq7ejnLG4rPd1krGcDVHHqtLeTb5/OQUm52BtY+miy5nI6OFz8jxjmcN8e+nGsmVN/EbGCuQ5+RLkzpTvf41lyDzaFjB5f96aui8lOXaDscflWfImY7nyPU4nY1lVvH7dYD/6mPcyltZcvv+lveK+7l3GCiW+g/CLrHUw1FheBV/3PtqTtV5i1L28tGNjiWV/mf9H3ZiXOwldpsn6f+TL57L+H+119OxZfPqH9/1z+EDWEZ5PbszxflmEzqt83VfIl5W+3ArqrpT1/9BF6q6lnMx924D/npb1/8g1+cY9TizlW/PttCfvEj7FL8ky/w+fnu51/tZYpIKs/0c+d/d1f8ZesWM/uSvf7B3CV7J3w5/Gyq70uZuczrq//twqYSxjhIz/UU6+FaxoLCq5W8VYzosy/89Y7hIvN81Y/A/5/pdyIvdc2lvvY9nAWJawi9Bvs2dN0U+uKVcYK5C4NadugWetjBXKN61tjGV/5s+Zdugiax10NJb5i8z/MxaTsb6elLvZ58tt+EC+j7/TWHqBZ9m096TM/zOWX0rG/7Dth4hjD+AXmZf2EHbI+6Nx+P4K395E4rbUx3IKcmV+7HTs+LKEY7OwY6t8/4sMydMXkCF7Jb9E3ZKevUzdObL/L3E76nPodeoO9/HIJw9kvZb16Czjde/iv2Lejg/wvXw/s41yMgawE11kPYUvKVfSt/cN+q2U8T9yrYIv95OxyETPfqFcGa/LQfxSwcf3CLn2qPdLUkPuS2T/X2OZMsemjLHCWd4vUWPZ98v3v8bSe3hWw1j+cF/3NGMRWeepLkyeNc6ByXW1Pizuc+hCY3l1vQ8uNhYrI+N/6CLPC1fhg9dl/p+xLPmm63pj8cWetTVWkOLZzTDZa6GrsRzxfRbl5JuBPsiYJPv/ot9G30cMpD2xdwgxkv3LhuOD6r7c/ciVe7gHYS/4PH3UWK6M4U3AL+N83J7A9/IO6Cl0GeF1mYltMu49h/aWed8/Tw7lebbQmK6HkocPZG2vZfhK3mG8hm2tZfyPHBffr0OGjCe+QzlZ8+J9Y9HHvb0f4QPJg0/QT75P/gLWtZJjX6OzrKHxHf4TuT8SS9lfch/tta3o2G/4r7ov9wflcr0ukQtMrjyLFzMW7erPrdLGIrIvYwXKHfY5VMlY4T7v0+rG0mKenQrbK9//wg76HD/bWLrsKVDPWE4b7/sLjMUb+7pNjGUN9T69zFi2jOk3M5Zf0vcHLZEr8++vo5zM1c00llfWx7yDsdwuXucu6LfLx6gH+sm811tp7xGfG/3QWZ7tBxgrkHKDYfK9yzBidFbUsVH4+XGZ/wfb4M+ZR9DvYq/fePLgNe/7yegn71KnEaO1vr1n0EXm4OYay8z07c2jnLwLfNFYLCb7/6LLxcUcW4rO1b2MVej3pc+1N6krefW2sYye3n+bqLva67cFXTZ62z4kX7r7cjuoe6G343Nsk+vCLnw/Qub/YUeyzP9DZ5k=
*/