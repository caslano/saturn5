
#ifndef BOOST_MPL_MAP_MAP40_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP40_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/map/map30.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map40.hpp
#   include <boost/mpl/map/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(31, 40, <boost/mpl/map/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_MAP_MAP40_HPP_INCLUDED

/* map40.hpp
8mivN0aZI4zc0Ln9WiNkum87s29u2jByD5xLKLvzBmsPHK51dR0rdvlm+908wv0+OKY+O2zkrE+PTR9rPchFG/dHn+c0+mTeqOqjrnEMjj7mfWnuxs76lIXrY/fVD6pOPRqdmp11GpJ+a8501qndphM+40HVx/LzjXHWp9umj/hfB1WXpQ66XIYuqTepuoR8mm6ep6IL75W418W8dnKznNslX9HF7iPzopOX9tnJvMdrdAqoOqk+kUHSx2yjsk2c9WnV6RNqpkHV6VMHna5Epy5FJ7tfx0u/Xe7hWrLW+bMddaKC4TqJ/2VQdAldQxybOvdZnk0X/BVDcv85y0Gfqw0by64P9r+XfnpoA/e6WOvcmzm3TYuqi2o7D+L1bLbPMo1OnXadygsH7XlqXjuTN9fMgey6YM8N5pzM8vNr9Mm8JVwfsYcG9Xo226gyRzMP6tPJsisGs42sfU41+jSr+ljz9MHRxWybui0i93O8Bl3abzH3c4x/Tr+1fk9HS/5yjfxuS378c3g38uu2dJafeqspP/45u1a+Oh/WyM+35Pdvju5Gh8axzjoELB36Nyd30w+9Gh1aLR3in4Nv7WJf00Cus/wuS358c243spc7yL4O2b5lpuz45tiNybH7PrCVc73zLNn9m1O76fsejQ6Vlg7xz6FdXf/jnOW3WPL7N2d2o8MKBx2uR4dOS4f+zZEnbBz7Omzc2lmHHkuH+ObEEzaOfQ30bu3cB5m3mbLjnwO7GYOBvEj5NyK/zJIf35w330Xf9+Y5173Zkt2/Oa6r+m+jmQdYOsQ3p3U1/jWyuy3Z8c9h3Yy9xvGaOcDtpvz+zVndtEGvRod8S4f456iu+n+CZg5gyY9vTrp1jH29V19Jtw+Xbl8t7/tzOe+TpduvSr/PVPqlxu+vnDbvkOcfOb2m9fgPslf/8LqddPuLed+XKrRfsLxrA9cg3URS9wvOU/YVrpR86zrk21jJ12yWFyNfi+RbJ0a+9ihyt1DydZlyY+TrVuXq89Fh+vIKlXyp1+j120jJl2eWFyNfvuRbJ0a+yijl+ZV8gSj6bab2h1lejHytpn4x8nVGkZut9ocpN0a+HlWuPh/x5Xq5m6j9IfnWiJEvX/KtEyNfZRS5G6rjw5QbI1+LKTdGvnbJt4FDvlx1fESRO1btD8k3PEZ5vuv05Y1T+yNKvmIrH+k6fftlqP1hlhcjX5nkWydGvkAUuWPU/jDlxsjXqsrV5yNWU99vO6n9EUXujur4kHzDY5SX2qYvb7raH1HyTVDHUZR8e6r91qZv5yx1HJnlxcgXkHzrxMjXEqW8IrXf2vT98Rd79wIXRbUHcBwFSwUNExUVFQ2vpJSI+EZFxWc+SFFRMUBAQRFWQCPTREXzLZqv8kWlpWVJ5SvTwvKWlRqllaYWlhWV17iFpml1f7P7393Z2R1cTLsv9uP5fNlxZs7MmTOzM+ecOaeN+rjJfDWvM19hKfvrrz6PNsv2XWc+T5nvjtLno/2VfrxN1eeHJl69+WI08erNl1VKvL7qdNbEqzdfniZevfkKSom3mfr8UMerPx/taCTeUucjPKOfX0LV+f4Z/Xi7qo+HzFfzOuszlBJvZ3W+LyXeEPXx0MSrt758ma/Rde7XilXz6d9fEZ7Vn6+hOl008+ndb2SVMp+fOl9p5tP7PS9Uz6f/+0vdtP58Aep8oJlP9/eolPk6qo9bKfM1Vp8fpcw3RJ3vt+rPF6G+vmjm072Oa+bTu07mlDKfvzr/aebTuw4Vq+bTv24QnpP5rnOeh2vm0zsvszTz6Z1HeTJf/eucR4Xq+fTPI+oOZL7rPVdo5tM7jwya+fTOo1zNfHrnUYF6Pv3ziPJnme8=
*/