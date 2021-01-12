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
SNt+IMNliOaYlupgi7M5Hsk1nkSPtFQrtcYu2CPYT+yxAj0S8eA3L9yiRugUOUtG8oxPH+C4NTGQKvrmx2fkGZ80AwTpuCY/xfM3FSAhWToN/xtplAdlKy0+I18mQV9UiCSwsajK4Wk2SlEOEp/Z6WeKDeWgWplMpiN1tK2CBv3u14jpDI6U3PXu9Rk84ng6kssuHAyg/bbJfVj3Fk3oXkclt/jyQMVdQj1rHSl0sYi34i5p
*/