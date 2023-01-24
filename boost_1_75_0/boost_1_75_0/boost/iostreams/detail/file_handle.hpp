/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/file_handle.hpp
 * Date:        Sun Jun 22 14:23:12 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the type boost::iostreams::detail::file_handle, representing an
 * operating system file handle.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

#include <boost/iostreams/detail/config/windows_posix.hpp>

namespace boost { namespace iostreams { namespace detail {

#ifdef BOOST_IOSTREAMS_WINDOWS
    typedef void*  file_handle;  // A.k.a. HANDLE
#else
    typedef int    file_handle;
#endif

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

/* file_handle.hpp
bAqGGWj43hmxvCAOSG1FBZvCf+nGdHU56RPKHgwZfos7Fq6jEzHRXPtOo+lLWRmqYMMcI4Bd+bC8b2zLVlWEZIdndU6ytb33ZF+6OgGalqYxh3j7DVM0kOeu/h3TNh0JY1KdV5G4lnRS/ZFTWKOJrNTfIKRNeMYeqQX2ebCERDfqT49S8/6mFChG90FO8y7oWSI6pyIspECnhgZKHS9LZvXvTwiVGxic2NhY2KzQvSUEAoLpRmTfiBwlPYPiGAzFV9BssUIBfMMD2C2YwcwYdm9kP1rqmWzCzz5iqbNJxOPptJJzVl0J+bavzfaaNxza6p+4r5A6uEpyvcrDOHNmIpYuFBwqDP6MxOl3RDvDXDbPbg/8/WZBj7KxDy9OrTKOXTiIE6KDJDnxA6vPK8ntTcbhR0a4q3DKLmlbdoIIgHqeaMTBKGa5pFMyvnoT0Ivh5PKOPePT2PkHPtYgX+rS4J+jXNvbHOLDtVzxiy13mC+M4AuaOMOEk+cPCK3rqPNQ22DIiP6UO0/nORQ3IdoUyE5bV2YcioI8K5TJgATNBRxbHbf5E4NwHcVaRnQzYw0AMfMc1u/bQSfyn593geG+5Nvk+R0zblV3GhIyX7LYzh1runYHYdg40td09gl3J30SXBu2+CTjC8rGofNGzfoZDm6aH2i8k8i7Agso40ABymp5yUS1H+LDo5qzDxcXU0yEdtsXLutZOgIDu3qQ
*/