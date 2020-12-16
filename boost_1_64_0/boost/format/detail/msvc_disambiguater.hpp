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
MzlQFdqCUXtQD95nwz8m9raJqkKwGp3YRquRL1678gV8ujBJUAC944FlbeWPBIwvbpJWpxYDGpAoygIcmpmX9f6xEVo5iebbSzveAw1k2ycQZcbXJLVEWnw5pAelPfMhBJc9Xo6ay3fdS6vVresg651wYYq+glTtwGl/qeaQrd9aypa6BjUC6uLhbgFUgAddREF0w/Q/YyF4F053xmlz/qpWAQzQEE4v/sKnPSsqUPauTQamxdi9vFnlGDQVgCYotl0BteKZqin8vRB2YBi/FWKWLOtd2hC6dRG2ZHqx7Ul4gXOd7VH4qxV/wf2/rPcceLXIrk9/Fzo2/Q8QPPgBBIPKcSSGIhRMfe4wNhk7KvOxctCzx2eX1pA6bdeFiw4rzW+hk+hY1vt0A2wAzpoog/8bTDZ7o/CPpaAvsZ39XOerIAeOg1QiRlMXQVke/03XjVkerJzljZ+Yd01VFfTknF2EiImzbIUsARFDAWxAxDaBq4lxjSi4MqiW5kZEcB0PSp9l4rawF9RqsND/pV/l9QaciHxiggkipfsw2W1/gwgDdTbzVUGd+f3dDg3TsHOl+pwsmlYC0F9/ETpg4ZZHIZMZiLizsBEFwbr7zHn1yVxDAEY2NPHXT6Kl1phLDoDB91Qa/bV9C7ks9PQpPGH/gFbs6/FbyJawu8jkLsqxusEOvrsoO7bEylwUGEdrMh5qZIQZI7r1mzC9oJRjXo8ozopNXnL85ukT+seUyUgLR073TpgaUwZfHO4hduXC1o4I4fplX2FNCYTsLvDmBUGeMN17cyXI49wDMhTkWAU5VkKOhUWD3cWH20QraCOkoEZ9Eclwba98HG2ivc6WXC/GhB7NbPXhoRhytjx2tR7fexc4Afdm+99zgZPndfnfZ+J7qv89OzICDGUb8uO7w5g/AvT1i23PJmJ15iLbVnjAtiBDvCnlM8Ufi+9tis81zYd8RYkCLbysLFsTIftJNCs2VaZYZIpZpsDsc0TNH10SFUYvmVX/B8MlcC1xZgGagNaJBETLUmSrgAdjplQgJx10m+EpmoU3HOH5WGwbAU/UkoHwEFzEZMfbzJViHeiAB7A2H/SUfZ7siTmIPBh1qvYsOxrpAYNHBX332o6XR5siqJ7v4Qmd4tm+hgfVLwiRraY22Gt7FVJslPkVypxcZCuFByBWcalAjbMxX9FJKnvUedeL//UffT67A86TSct6v/ZRNJBAtfZaU1hkCA/40RED59Wk4PPlXtvndXhXFilB6SM8S745Bh3OrOQ8O82iGODimcCeEXKT+Y79r5uRhlpO1yLhnNVlV+lBGL4f/owWYDAO5BsjmdOYJHUPgviIn4408hGDWaQzFR+xkKkorqtKPuJGUdtpG+YRta7id2lVqcTMcYtNEucNJsR5L0cB0e6CRxTtQMYAaKuJdzoB6gCTDgVIBruYDHbReuCCtc0tIPOtJiO6eYhfLcRvFWnTnLyBFGIyoNkZpoK6CMCN6yZ37JaHylF/EodgzL97Qrtw8DeLEUjlLsoz8bCSoGrKDaTtOZVlgjHxO2CgcED4IIIqwBiVDPhvNoWBf7CCHlIM2FnPQzVGzTlkIiyRR70Alt90ipKs0ORguaCB1ZchRPOuJD93L5XilpXgkNe+FWOaSGkFnuQg6UXzCpyRkvEVFlUS0B489JVvKtf1xKicSgK9INZuscnPF1mSNi5/2tEC5mzAjWxrQW+OL0xOtq1t4G0j35rhW2P51hzfass3k2sjEjPb4MsNixdrEDDTcKffplBW/Ez/Ibqk85ZP229E6489bNHvRZMDepsZHjynDoIM6ft3o00V79Nkojv5k0bESrEaHloT7x4ea5K+fllyy/E=
*/