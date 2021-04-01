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
N1nv0cr5UeOvTmMDSN4zOVjJklU14yU2nO1Nud4LLKLXhfQHfLGFrg2P/9F5GZFH0fDlSKf/4NYfeSnRNShtbBS6fGmUhYm11PVXFmdH8OBDS7oaJrsVXhxWJqy0+zPAImaV3+f6CxWv2n1MrjQ3ItzHIlAz27b8PxiAI/NhbpjTu6CXiRm3qMX2AQUikfyNf4MhSRQ/J9V0ohxrGZuG0mzaRV0wWTRm3W6RRsQgRinOmRND1sSG96qJFZzCqsOn8EsdQGkg8elG+bllO6TqZKSGpZ3wdjTZPjjRsBDGztE6tH9Yuth7g3DNFHayFuTsvf5nPopJUaO3ELKfC7XmKYbjm0BL2/ZCRA+aTK1X1L5DhD+utkFnIT3c07M/65aUg/eiePGtPQxnD/C1wYwxV/yr0lDN1WwZuAZYkeDO+7dMj/QcGJEguhzYlKBuBztyaSGuDGlaJ1w93iXog+McSoBZ+1eCqypL7ZIQO56IkIsOzmFg8OQYznfpStfZpwusVVGvpfM+X3N4Kw7H79sy2J/nazWn4gMT0swqrgPxyic7We1WpFZWkkuJRg==
*/