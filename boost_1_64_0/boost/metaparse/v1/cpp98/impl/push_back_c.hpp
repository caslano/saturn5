#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <class S, char C>
        struct push_back_c :
          update_c<typename S::type, size<typename S::type>::type::value, C>
        {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
8T0Nlb3/AVx2MpV93ZQ125dRs+LrsFvLiq6+Mr3+J3pV+4dC86r0+o5owmYMYz1x2vPvYdsgh1e82r4zVWiyjehu3f5WeL5GHdNjS0Q+FuOpFbA1K9xcswjyju547oPyz4O3DHCKxO8DqGyZKLuAyu4ryrJUthBlzeaOqNeq5oeyqPr9ul7di0dX2HeKDuJo3yeeEXTep01w6CHoYwU1z2UZeA4SJjjUofOtV1XBQcvJfjsGuBFvhCD0wcNQjr4l9ciHx7aRTxdGtNTDE4AfxDsY0NATRbEHHdX4qR/N7uhjXXt/D8f3L14sZchHdf4m0IHj2t07BzwqlC9hie/PJA3PBzt7jrFvsO1h+lkQ9/v2M6H/LhjIdu+Itvtk/3ks9UkEU4Aw03w84NRYdSyXL8J6Suo+kesCznteDC/rMk3G+PfMk+PPvSSciyxNMR+fHMpL4nGcfYgX+NeeCZwJlFbGh7ZtEevi2bYP5M+y3v0SaGBeJHWfuyK2K4dKZSHzm629CWPFJkScFdubUVsTFbSUyPL5KKOYUHX8XmDboHsObvtFxF8XnnPPTnH5Syz+eKUANVTl8pcxHee76leHMnfiki8P4eQJYh5zwJETM7n3CesG8/rlSV0+RSd2lazv+abeLGF+DqJw3J0+vSOEJ32Kx+oqI68UeZ1i3YtTiaJ7f6WeS95rdZodwyM8VlfL8qmLWpSxHZ8cU8cc5o1ajlwGHId5nS0HDS673paZ+py3ncbGXkRnd0SUzPx36ZTLKJd+WtRDeXTD55dNyjwXN8j1U4VyIhvoM2ZPf4ONbxhpdu8bzZmfrR0ZzU67XZX/TaZ/uzs3b9+S7ZXz7su2HLQouFnMu68yzDpbbg3oAWbpxfPt6yi3vNkw5MhVY71nkZ3wPervZuA2m5eN+ot7GK2/d5qn9fdmy18m4/X3x7YctML+/pRhQX9vZpjT35+j3PKm9/cW6q+xgUrp+tuhx7DffZ5m2/we7Zg6ARcp28yqtuhpqoz/aGXSYSXC5bdReSzhuPxWKifpRvP/dpQV3m7twSPN8losFqJf2cpw6BeZq8rnxJXJ3oNKHZntOAEbcs2+ecNtFvNhmwvmaXb0yWizv6enO2nq1hAGg8TAms4jwXzklb6fofb9VO57/p/re34oH7TZprZ5D24TlZw2G+MkwmjON5bwFeZ1mOefnZahrRdeidz5oFmlslVUdjdT1qQsavWc+clOnb25YyRod407D0J7BAexmpPLdu3KBAYTk2319bb8AjQDqcBnFX3THD1lmuiyexocMgjMugVdb49T98KRfIHLNlgahdJRtlM2ooz20lLZXEoVNdsKA1oQcYeCXxt3DUvygurDpC27NcThXokzxhrg4X022XkgNGebyPEJ9di2eWnP6DE9QBRbZ/vM6cF/E/J3L3X+3AfysC/NIrd5vt4hzx8Tc6ys6OIoWWVx3R2oa/y8aJPCdngsuwEzZ/kxOAMnRnn8d64Ueedw+aO0Rx/A04Jt8tvWpO+5Sj3s+w5Vj+y2vNhLhf1dAz0DdNMhcPYCBz6oECflmFTr2l3Bznnae2bn0hytwoo09134JwrYxANiuAkbHxnuYDn3A9fC9u3aifIkH4ulQePiVU/Le03zc+0JZarnM6DpwzwfJt4ASO7IHoKyG66BPxLwY1RWRtmLRnCXaMrS8my+aAh06LkOz0v4u3bWCSbtjD2Hc+z8IuhweEPNRI/vJxP/M3ik61UarXHUDc6weJ+2giOBWl6WPpC3rxTygya03m6u90NbL1fPZ4bkWfkdK+N3iyeGJkXe5+7FTM9mJW+4vpMFt4Hg7/TmYdRPmkr7O3sO2LnE8/bqcN4G2Po=
*/