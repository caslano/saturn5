// ----------------------------------------------------------------------------
//  format_fwd.hpp :  forward declarations
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_FWD_HPP
#define BOOST_FORMAT_FWD_HPP

#include <string>
#include <iosfwd>

#include <boost/format/detail/compat_workarounds.hpp> 

namespace boost {

    template <class Ch, 
        class Tr = BOOST_IO_STD char_traits<Ch>, class Alloc = std::allocator<Ch> >
    class basic_format;

    typedef basic_format<char >     format;

#if !defined(BOOST_NO_STD_WSTRING)  && !defined(BOOST_NO_STD_WSTREAMBUF)
    typedef basic_format<wchar_t >  wformat;
#endif

    namespace io {
        enum format_error_bits { bad_format_string_bit = 1, 
                                 too_few_args_bit = 2, too_many_args_bit = 4,
                                 out_of_range_bit = 8,
                                 all_error_bits = 255, no_error_bits=0 };
                  
    } // namespace io

} // namespace boost

#endif // BOOST_FORMAT_FWD_HPP

/* format_fwd.hpp
Sbdpw640G1aWGFujymGZ+4YB7/D+XhgG4TKfWSzHFPdTIpd9zygq13jXTGC/caGxi3VaOODn2Ccmg2HbmW0mJoORbR2Ak0YLdGEpKcvtF7oQqZteUqGBVfRrKDykADsYRxyxkIUaJYQdZ5nRRGpsgZQYWe1Taucb4v9Fad0Fwu4zXEqBvQwk111UbYyGQ6sTptOX+8adT2LLZN8aZmEQB1fBJLIMU63J+8O9n008y+G51YmqveEvX0mOcaaHqCCWD41xBH9b0OsGG3idsOw9jI9AkS/srihWHpMVFS3EBo7GxuGlhI1hL11cbBhIrWocvvSJ4ECgTiqq8QCRX/X+j/D7xFpfVMnBfXB+YnpVd5nD4GlJCW/q3dY/lpOzlib3s+tP3I/+xI8Xlptl3f+pc+fdiXPSHgi9eB5O4bM7mXtW2OpSQafK4A5Y1z5dccwcVU1dC4lT1O4Pzad30+BhmgRtdxoHrL+Ns9Hqg8zjJLhJ7r37IFz08ZDiDTYu46rJc5Yy05kFJTWomqS008Ag8jxwJ1GAo+pjeEhY6P0+96IYBsOzEZL/gs049Nx7rIu/27f+BVBLAwQKAAAACAAtZ0pSAAojOwoFAAD4CgAANwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9v
*/