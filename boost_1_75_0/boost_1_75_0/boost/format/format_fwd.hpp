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
sYyzvoLsVTrW7zIh63PhbRk/IslYcfkkHeslnIAhY0mxxk9UwZrZG5iowXdecFPSsjg4UeNmogNBFnkTPH87gfOw3F6+XYtp/tTtnJX5nJXTbheszNWOOOoPpmJ481OXZahhzbW9/j0LiIfbFwi7dZLuvLb/B5VTpeQvQc4SmjqXcLseFkaC85wj8aBYDhQE3o3QBkV5G8Dhfm6Rz27GdXinH1nGLEN0nFIxPHDp5Sxn3cebUMAeTo+1eztiessEMopjmQsqdO6vAdKvkfxyWH2TLzMcxKXz0F9odRS2+TJ0tos/fUAVSiXoOM5hRhTr7gl4LgfcNv1lmqU4G1y9nb6UuJYsMIpeehCNooO+yeJG0ZHjyG0zX7E+MEG1Wk5xsKeeW7tKJrUJ196mBxmVTHm7oZubaHbMJ20IlV/0nlzYtSSG+hAepivBIVc3rhPM8DU7THjIwHYtfDXtBp9krofhIh3d72hcpwAMlMW2jrWy/5eeGWjpYwVmA3f4NsxWzK0P5uZOxuVbL0YdIpxu8e+5JMPUks6Fy/n0HOAboZLzjmORg31DRJEHRFmzeFlaJeQteJQOC9s2VldYUzkHnNninwqFdZd4fVvaMSm6oANI0RfLiSBfyt14/7D4hjfn5HIxN+aHnhuBvdBBWnrwA/NxaLeFfqDabUU/IR9fPhq+3aeOBtbsx9hoYOvX8bqDkhtGU/cAOZXdQt3j
*/