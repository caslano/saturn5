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
6u4y9dvP3VHktQw9H3B7DvW39kFcfZNs6gr0/Jd2rTH670UfM5ui6zkS9mG92C+dLZbtXcOhaehdv7Gwo5FrJyoV9VdUR7cP80pcXtQDBcUHv36p5ouZ4u5r05X+5ELqkrX+9Qn+x6/xsXMjvvlR7cfLsPzylLWbVzvfV02npS5H77f/P278+8naN5oj9z9n9UZI1my/ivKRVVm50Hyxf45IyMUMXeqrMkcnq2j31redrXF4
*/