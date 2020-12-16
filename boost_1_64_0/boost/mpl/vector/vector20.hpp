
#ifndef BOOST_MPL_VECTOR_VECTOR20_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR20_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/vector/vector10.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector20.hpp
#   include <boost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/typeof.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, <boost/mpl/vector/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_VECTOR_VECTOR20_HPP_INCLUDED

/* vector20.hpp
+YmiUvXLXHGC+1D8svx/8H0G5zUrihtUeT53un7ro/tV5K/lcSvct64DvFfnCvAweaDao+dS5NGNV7RMktcP6ilrlSvtV/Mr2oE1xq93accivmCc+CYW1h86ahxefmC0cjHjMeUaf5V9/Y366iXtJ3LJ/D+SD342+h1U87rQ/8z7hrC+SR6l7oawvku9emWKcqMdakT++Dt2n332vCbrj9UbF4p95j7Ky/Xu6fm/R7vF74Hw/Grq8euDesb/ivpnkOfO368suUI8A97lvRL9wb9r/80XLRjtvFcob+Rl89w94gzaZb65fo/xk+e/RDnDP6T/o+oR+BvGu085L9YP+Njn9du/OijPcQv6JWj/0iBviPJVeT30J+NTfmdcKy+/w/tfjmmnO+j/Pyqf635P+sj4/LvaQfXpGr/7LInLF7whnztNe0H8nfI55VDcmKEdSt8r3u1HyX3K/r1UnDLE3xFYLq8wQj3UYB5bjfGYixPNd5YvNp6aJW9e/m9xDvLK/Mfo54hrDwX5D+2Y5wfi7dNs9zvxcp1+AvaLUrltXyZv94B5nKwz8/+Aeu6F8jn2nfHh/7CuxtfXyLeXEKfmPb9/+zS4l64V6yWPUB19v2y8egn5I7STqh6SB63we5xO+BH0u0n5096VxZWbC9UXz5sXr50v1H8rLdfOqX8yp/rdY7K4Fr+L+fwz/C5xJPFhyv7i6Mnm7WKHaTfROA3ngnEd1x+U/+0d+Pm3xIP3T5fn/Fj5qdReaTc7me9TdYo8n/GwZPtJBx8ynyBvbwL6YrT+8Q3axQflKRP1n38bzrPee7W6fmu+7nt+74Z/yLyi3wO27I+/SPuW/TYql5SM/0Nx+XZKfo9Xe7JFnm+P+jVdPvpW5SLKR2/reRomv19mPMTfWejUTj7V/V13rnhEnrDM/nonyXv9nXp+Z02ehLgg888xD3uicvFq9J298XPHkbvO+20PaHff1C5FuPGgOGST+CSIq7RkHZgnz6mHMvqAx4L3d2un97hODcYPzVc9yDgo8S+oP8vzOE37v0O93zqoZ1x+B5Fv/Km8kPfJPzSv4Kh5XdvUK4yb8TWqz4brT3t/+qEzqSf/TR77gPtyjbxaiXGQz8RZEzzvG5SfzkE94yBvmfeie9rluXLEgzPU87XwI4zjqOeR/Fj22/q8iK/90v0d4/7498oTyqP/L+hsPmCtdvb3YX21424f8HwprCfPM54PtNsRL0k9/V2nfj7P/ZbXqJBPKL3Y9fe5TpPlJ8vVB+A1xnuRevli/SrP3ZoTkb73dz3OkSc+Kp7NCvVDQ4K/U9nguZfnaFKuY/yffcpQj2qXGuyvFjxGfb73ZP1DfijKE5KnLYzsQ7HrP0m++yHtZ778U75yKb9cXRrhdPnwR+Xh4E15zn0biP2kv5XivUXak03yOGnyFeS9MB9/DzJfPJ9ZTUnekvkjTzq+ra5HdP9OofG0Gu34yepl7BLjfUb8ud/9mSkPuUZ9o35vmKyffZ950jdSz718nqtm8c5OccTuKD9fPm6x+rGD9wm877re4H6SN817Pxinvdvzgh/Me0HeQUeeZ77UJ3m/A79XRb8F+i1RvrXjynxCuRgqr9xWfH6Z/Dz+M+MbrR790fzYDNfzbPky9+/gr/k7OESce4f+fyfXraV42nGkaBeWyGOuOV25Ok8c6XqXJeqfrJEH7ao8wfvQT1vz4Gfbnvn/qxZ5/mL6C46jwHlvma183yQPy3cClPAajG+KPFzE++i35rt/I6fYf5n7t1h8ear2o9r1XBHU084G87XEC7nvqr9L5B/lmwZif6mfq98R/T6qv79Q/7Y4nDgX9bPV197HlG6/adX6tTXa9SY=
*/