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
kcOEYxSbiX0VCDYZ0tYs6SliLIfjsdRiMN1xpbLvZ6iNGlqh2wzvBsBmR5chHsmcNECwJGl6MqexJGivExVKhlLZmdKIxEzpcbZdpqaI64ORcDTsvx/XvO5+PTy9cpEQi3JguWb4hmr3o8kKg3kFg2YF5gEfoGdQ0qQTcK2bnCk9K7jVXoyPyOy9OeCmB5i3w72+apaJPC8PPKSyCUmoB62RH3mQNvufD8HzWXWzQ+B4e/EWBS2n1ZRAOoZh5XJcnM1Ogm0mXxzc8F+ZiGdwuO5QqcqoB7UODK1huGufhtgiFWkb+7ebxMa+Vg37X3eTYSevuclg6pbmc1ChqdvtIZqpm9/Ln+734QLG3hc4lwyt38UVra+f/aYA6zfn/NdPeM5e/KDP+n36AK3fFQ+e7/qtOL/1e/2B/2H9Em70Xb+4Gw3rF3RjW9ZPCjrH+o0eg+t395hzrd99y1pfv9mpAdav7PzXj/sUy/c94LN+h8fT+j30wPmu3zfnt357x/8P6zfuBt/1y7nBsH72G9qyfpuUmNbX741RuH4vjTrX+r35ldf6nTSu35r+/tdv3sLzWD8zrl85d4qU3xzvtX5b5b7jorHoQwTvjkxps7zoT0g5N+88lnKlWEpf8ct3KbfKMeO8xS+fpTTKXvqlfDnFdyk9KYal/E9KW5bSdPYcS/nDCOJ/RviehYL/+aJ1/ud6f3ryu9hRD1KZYjt8
*/