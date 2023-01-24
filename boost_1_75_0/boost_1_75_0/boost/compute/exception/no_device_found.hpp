//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP
#define BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

#include <exception>

namespace boost {
namespace compute {

/// \class no_device_found
/// \brief Exception thrown when no OpenCL device is found
///
/// This exception is thrown when no valid OpenCL device can be found.
///
/// \see opencl_error
class no_device_found : public std::exception
{
public:
    /// Creates a new no_device_found exception object.
    no_device_found() throw()
    {
    }

    /// Destroys the no_device_found exception object.
    ~no_device_found() throw()
    {
    }

    /// Returns a string containing a human-readable error message.
    const char* what() const throw()
    {
        return "No OpenCL device found";
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

/* no_device_found.hpp
ZrPy8O0z5Ibofr4ozsnHcIGWY3JD0yHhjV0u/6JLPZjZdDob8loUF82VTIcajML70riGMP+FrPZHfZ1aam/LYvYw5rZBNQuF97PnOkYNysrTOdyOa9+mnJG71uneS8jTif2c6POD/D6wK00o5vWAXWlKsaA3xaThsH9dYV97C+32wgkoxxd29DTF6SLDYH8upyhZBrsY6A5MXgr7OAr27xLYt9GoD+n8cV8rBXzuUlxvyU60x7euAPl8vkryhajIZ6ok39sdledjlOSLVJKvbDvaASzaLmy3ZHPl5eVuo2ggynd9U+X8eyNf+lZhvkgl+Xh5MUrymSrJx/ePw1ZhvpAC+GOAGreRDhh7h2LqefT/Lfg9gHoFVSsnJ19Yjrgf/ii+RT1uwEhgOjALmAd8KMIyYBD4NLxTNf6ykb7kjlAub1dRO7UwlmLqDorWycDdFLVa16J8z6JxjRE1CCYinnigGpXb1xTjgQzQBfnT21AsCIeehNH8ZS0pvSiFxuO3gI542nlajtEFiumwryUJmC9Avwjk9coF9rg72hOJcl2QL2wfjQ/chvJw37e9Jq2vA8VSYJYBxfCOFAshn8OQmwfye+vT+6btKOrvpPRQ3DdC3L05va/bgmKqCM2HMYK4QyuKORsxrtZT9FgHvQb94lohWreh+czaUsyeSetPcaL9GAKM7Uzvuxki/WcU491o/2gb0XgGMKQbRQNj
*/