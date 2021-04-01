//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_LITERAL_HPP
#define BOOST_COMPUTE_DETAIL_LITERAL_HPP

#include <iomanip>
#include <limits>
#include <sstream>

#include <boost/type_traits/is_same.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
std::string make_literal(T x)
{
    std::stringstream s;
    s << std::setprecision(
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS
            std::numeric_limits<T>::max_digits10
#else
            // We don't have max_digits10, so add 3 other digits (this is what is required for
            // float, and is one more than required for double).
            3 + std::numeric_limits<T>::digits10
#endif
            )
      << std::scientific
      << x;

    if(boost::is_same<T, float>::value || boost::is_same<T, float_>::value){
        s << "f";
    }

    return s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_LITERAL_HPP

/* literal.hpp
EB1Cc3PoVUTZOaLjyC2gtpR/yzxrN02qRImlO/PkU48fAjtcGu2DRZ5cDV/mi5PZak7HUQh7TO0VKm6j+TQyDbQJXSeZWmyGrxnFr5HVhayI6L6Zfx/JH2M5vr+lmsJ649WCLS+NKL+/nSa2VKOcCg9U+UObIJOE30X2kFx5deWB+n0XaG54xRsnU79cC7+QZjCiRmJ1P/6bgXp4Ex0/8uF/+5fDxTXTdr28bMlazrXzinv91eAgfUa16NB+S3ZZvzuUTt0qEVrWUoEe3Pqs1inuPIdvkrfRLNaeHeSQrb3Fs+GWgydiodmLl28QXL5uOlEhVupqan3Y5CwP+3N5OiOlrKNtk4tkf/0FOk2nDoL6zIOj7JwpZD9Apui6NVt0FN6KYtrtVMly+uIcqW3PqCwLdiPuro4l0W+RWttNZNJi0trVxpDJZFb2VpZ1jRrTk6utU4n5QUlqaUiPaE1QtLqMnjKMzM3N1SF6WysgLrSWgkJNbX/LHmQJCg+l5YrNMGAE3UxWM1xyI6LxtIFKHtCB8OMHknlTLfvtxmVymOVo8WJ881e1f/uBuA==
*/