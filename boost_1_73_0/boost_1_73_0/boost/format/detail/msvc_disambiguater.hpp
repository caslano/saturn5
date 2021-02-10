// ----------------------------------------------------------------------------
// msvc_disambiguater.hpp : msvc workarounds. (for put_{head|last} overloads)
//               the trick was described in boost's list  by Aleksey Gurtovoy
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MSVC_DISAMBIGUATER_HPP
#define BOOST_MSVC_DISAMBIGUATER_HPP

#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))

#include <boost/format/group.hpp>
#include <ostream>

namespace boost {
namespace io {
namespace detail {

template< class Ch, class Tr, class T >
struct disambiguater
{
   template< typename U >
   static void put_head(BOOST_IO_STD basic_ostream<Ch, Tr>& os, group1<U> const& x, long)
   {
       os << group_head(x.a1_); 
   }
   static void put_head(BOOST_IO_STD basic_ostream<Ch, Tr>& os, T const& x, int)
   {
   }
   template< typename U >
   static void put_last(BOOST_IO_STD basic_ostream<Ch, Tr>& os, group1<U> const& x, long)
   {
       os << group_last(x.a1_); 
   }
   static void put_last(BOOST_IO_STD basic_ostream<Ch, Tr>& os, T const& x, int)
   {
     os << x;
   }
};

} // namespace detail
} // namespace io
} // namespace boost

#endif // -__DECCXX_VER

#endif // -BOOST_MSVC_DISAMBIGUATER_HPP

/* msvc_disambiguater.hpp
2FKkKlK5oOm/d0jJuW2B5GFl2KTIuZyZOTP2rkaw+8MexzPm4M0ns98MH1y3SnEr/6S5/n+FLHuA/oOKV7i+w9UEnrQesh14l9YDjK1WNvg6Nfsse4e7KwPS/EyM8lVmtnjSaw76U9nct+y60jCe7sDB8fHPsAcf9g+OXDgjglEOiaZiQ9trF04Le/JbRe7uPEU/uUA1EO69MJhWTIGSpb4lLQXcc5ZToWgBREFBVd6yDb4wAbqiUDJOYRrF6yD86sJtxfJqsHMvO1CV7HgBFbmh0NKcspveTENaDbJEC2i/YEqjzU4zKTx0T0HTtlaDGQOCcCWB3BDGyQbdEQ2V1o06mUzyruUYyaSQuZrk21R4la5fRbVGNDW5B9lo0BI6RV0w8i7UsmClWTFFeNh0G85U5T7BQoeimMgWFOV8MIeqjKo+BArJkC3XSEKD6Jk2i5JCGW+3laxfCGJaB0Nl1wp0h2lBuUJi4l3oREFbK28TsfUyZNmm/I2SPWEvQApEBSM/gSAZwYYoply4DNLzaJXCpb9c+mG6hugL+OF6sHcRhGfIDYZeW6B3TUsVomiB1Q1ntHjh/Id2uuOl5zBdLedRnGaJn8yzYAmHMDo4ht87YWj9cQQjzjam7nDkHR55+3hg3jJK1H2mqDYV
*/