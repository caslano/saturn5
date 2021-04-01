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
hZAXaineVgK72BCXK8i6/X+GAboMINL0o5rvWCuLOntUSIEOWkPW9ZsiRrZC+wBpcE0cxNTuOeRFCOfSallAxsKgJ/BPqnih2lkwKo/c2EmQBEO7h+UDxDXeNJkZ/Cv/dvrYAxcYlyl60LI1btmmTL+T4okdO+Xvg/NpVvnhjEe0ix5P2ckmOfw2nwR3eGEpKo2YmfZWm2p602X0syyfJfVCUjDgB/15D5l/FrEpvjaKLxFf0UKS1Wm/VXxZkG2CxwapQnl0eJUTzGnjn98D+Vov+zm8aqGmnEUX2XSnc+6BW4Q5iPaujiQk5NlERiS/Q9bDRLeCpEpOh4cwVNPkvcWdy+IU762B9Yzta+3y3HBcEgOMqS4zenkgpIngiZ3KBMjGN3pnpsDJxyG2Tf1+gjk7iE2X5JU62dL3LZk+LE0qqiofnKG9VFZOfTomgXA6DuPJyiT+SK9S5o/1DFLLwM1OIGqc+HtKVxx6IbUwEmGegrf9Vkv6DB8duDlvEmrwGTccj6jVtjyxbIzR+qq7MlPgc2czhFFtw5eah8VOpReW23FgqiMq3/n/ew==
*/