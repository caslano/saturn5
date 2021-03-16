//  Boost string_algo library constants.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONSTANTS_HPP
#define BOOST_STRING_CONSTANTS_HPP

namespace boost {
    namespace algorithm {

    //! Token compression mode 
    /*!
        Specifies token compression mode for the token_finder.
    */
    enum token_compress_mode_type
    {
        token_compress_on,    //!< Compress adjacent tokens
        token_compress_off  //!< Do not compress adjacent tokens
    };
    
    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::token_compress_on;
    using algorithm::token_compress_off;

} // namespace boost

#endif  // BOOST_STRING_CONSTANTS_HPP


/* constants.hpp
B36MdbAMh8LWbG6nAeaVhifEEtvbuRUdZhO2s2ygITCVpMNSPqbiiqgCDN8weQDklwr+QQMWUTFTncOzR8prHgwQv/Icnj28XgMxVbTwnIvFHaAA6IUZ8CKL0YFqJT12XAVOglv+1x8//PCz+4Q+BwFDG2yjSjS9CY066aW1D0CRtDapO5bPTtc+RwNbariQAj0UbJ7s/CXjEKkgcHbdlM8/BMZbrWtQnjFwJZGepm4GlXqcLchLBZA+d0Qu7dU=
*/