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
zAUlBkRvZ57J0mRG+vbmhhJ9QncwFrLUOSZ2Wh5Zvc15grT4S46Pid/ReQ5psWD5Tvq6qPf8lSWOSd7ZOMjTInQXsbHF6q9PBEVll+CuxscudY5J3s36JU+bKam7O8fZi54M8so+kTNywB51xqTv4T5yHFzjZNBSnnrseYKJcvme6lPhjP0Xxsr0vZyjTJ8FaxvySo0xsXt73nFIlznp+3iukL+52G8mL6vqXlRfF9M3XWIxOaDMhJWLa5cWoUvII4f0iV9SH+RoMGc5LjaOOCZxKWPjiGPil9YGGaqMWbqMnLwuFOwq6yxYTcg7FUakLuv5QoPgcl5z/T13Srl3D/+9T9kguLw8kKVD8bvn9f0CbVNgQOwKxkeJAfEryis5WixYupLnB9GS59YtTvjvquf1PQ1zl7IuydIiuLI42WHjyGuqsnTLE0H+jd57cJy8in5vdSLYUG6tO6/sEr2qHHBAl2hann9w3uCMskCH9G1O2MtUbBxxTPrqYqdAj9A19M8OVaYsL5lbKoyIX1NsHNEndi1jYJ8qxySurV2KDEkum0OK9AlfRw45pEv0uuadAn0i15N3sjSYs7KiD2pMWL6+OKkyYeUG1gCxqGsXEt/rT9gHV/1ziy+w/uzDtW4PsqXaeYLNh4R899HP0LGfOSz/3D4jFOkTdW3jZ/ZI+ZFrP3ZM/3v2S7GX1YCq72Cd8Z5Slg6Nb9inhcQ37XfEAR2i3/KYQ3qEB/bDIseExLf1S4kx6e/Yi4VDWsxJf9c58nSYszQ8X3CWI/pExLbG8VfF+zXXKH9erKS/IH4OmH3sZNBUTkl90XkO6XmPK/MZP4eZsvxZcVFiSPRzckeWJqnvnDeYK1c69juz51XwKX3SJPJp95H+hPoXDwWrH7D3E3VmrH3Q3nbUmZH+kJ/1lBkRb4iLIyrlUDBURj5sPxhytAk+oh32qDJh6aPqcUibKamm3JGnzZSljxkbJQbEPn6+4Ax5znmv6zc/GRSVHWLvk7f3iLPq8dusFVYr6nNEj+Dt3iuU1yXlFjVmLL1DTqgyY/Wd8kCTVXtm7ZTc83p9/9T7i0fn83e+NhmTeK2cUGfzVeIo2gOQwuPD/h0s6/TWJ4NNZYkmA9Iv1h9FRtcSkzJ4iTniLAW6hPPOsUX74ieC/o78Pd9YHmv/hBeYZybO7ytLdFl9odhy7iH8HPewT50pqefKPXnaLFh+nj4o0iU40C/bHDF5hHqP1Kbj0tyeJaT+br34HWiP/CO18Vd7nyzsD5LT/rPl9pnq0Xm6eX6qdv1uMSb8ZNcp0CZ4inxR3HevXJ3edO+uuqzLzT5rj7V+KNFlwdLj5JtDKpf0N9aO86QfpX3CD9UuGRrMSD9MHfK0CbaNkx1KDIg+XL/sU2FI1PhPk6XB6T/aK8aYO0Ov24F5cbz+EM/vBzp3P+vQGEIvs4fBffRFh9B9rZ97m5872nuOEn2id1KXfcr0idzZmNmlypDIXdxHhipDond1jgxVjonezbjZpcKI+N09X8jQYErqjDxRpE/sHuqRoU3onsbJIS3C99IXeYakNrR9e+W6c7fWN5HbaIM2MzZva/3Qo3Iza/Cm+l/1PPDcKFxTv8yomuPGK+yf88qwzwLp+7LmlzNkqDMidjkxsMcRQyKX1ye7zEgn1SP3Hf/9XVllSPQKxkOOFjNSV/SYdMr61+/Zf4SDKnPWA+NiSPpc+qRF5NzyRpkpa+cx3/RJhqwlGoRO6I8iI5ZPGgsdYufVF1XmrIf1xZD0+fRFi8j59UWJCasXEC99UhFjpkn4gsZMiQmrFzIe8jQZE7uwPLFDkTZTElFrgz1KdKl9xZ4+JHr2TSJPh+Cr4eAU+zQ=
*/