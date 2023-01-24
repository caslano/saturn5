
//          Copyright Oliver Kowalke 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_EXCHANGE_H
#define BOOST_FIBER_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T, typename U = T >
T exchange( T & t, U && nv) {
    T ov = std::move( t);
    t = std::forward< U >( nv);
    return ov;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_EXCHANGE_H

/* exchange.hpp
V0peUWUTS8xqJstiJ5kgD2e0tVyPaWIgvU6y7vCc2J4fnqPbA/LMmccWEQ9QiCLCDtDePGx21sNcCzMSFYeAAkQutuGADXYq22oS0TLWhMA6xgZ6GOE8+E6+QEHlXL6kP16pEMdEBy8jTHSonUnTWrAjpLceXa28jAQNS/iyDlVwWaFDmijJSelKSqFT8UJzUU63fuuFuk6ceJt+qd7g9QqtOB7OVhBnoSW9vi3oYV/WQ/aTEi99iOLp0HGvdApdNwng4PskTdJrvI3j707j/6WtJvVGCsPNHmTR5yzlk9rSRxtM6rhImGjderCTUMLzMkBmsgulFuIm6oAwxkOCzKybLOV3I+bboxw6RVTF7TwrZi2XlMBVmfU1URfj2lJazSoTXdO4uDENhZbp3YnSyGmrs5nGIoBfUrp31BQJQHHY2gLFwQ3SryRBE4bnAfUSOjgs4fKXWm2gVbxbKGJQaRHRg3dtNH8/tKG0nVCaQTd24Rvw+K/Ttyhok2JWawPSJvfByI9oXztC07rnHyk87huByxG+Ymm64nCuJ6vRAcSn+PvZQU6yBDnJcgHECHltTKSUlE06CV0aV7hkGub2x25EwPR5OUV9qtyZSwGWLjaD4Zr3p3XYyyFkTXWM/juTu3XUTzlMNUqkVRJnSUwTJI46oUDmfCgqI/Y1eA8RGA6HSA/xXCJXyDVCJLBE4Q64H3FBO8DJ6/DzoI90
*/