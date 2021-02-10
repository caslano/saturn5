#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

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

        template <char... Cs, char C>
        struct push_back_c<string<Cs...>, C> : string<Cs..., C> {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
o9t9hX8MBIpgzEd2+3jMVDHSh0HAy910Nv0STnqseLtLg36LfoP+O05W2yRdxxzcbX/97qPot9hyoaGl3JAb7D8h8u9J46D+mYwsO+y7g1npyFzsZdctvhBPyo2ttLsB8TrkMgTX63Su6wgW83juwVOy3A18HsTzJMGR1RseAfaFevDjaZ32NlyvikE1Q4xPA//WiOdZ92ClrQv/kcLcTOvP96woxLw1dTB5Xu6S9XbDtfQE/mIcfKlViF+JGn9ey9fToziVIIKLtOD6sj8AUEsDBAoAAAAIAC1nSlL8Wb5AkwIAAIEFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMyVVQFAAG2SCRgnVRhT9swEP1uqf/hVIS0SQtpUgq0C9HQ6DSmAR0tsH008YVEdePIcRr673d22sIQY2iWldru3btn372LDFYm4RXGLMqLVNHPHFeN0qKK2ZfZhI0n0xv2/Ww6YwUanbDIf/w/8luXHbYDU9RL1F6VC2SRxlKu6BxuMyxAqLy4B4vxARqEezRgMgSBKa+lAZlXBlRtytpAxrXwEiVQQF44K8uPgIgKVC4EiwQ3PMkwmcOCLI+7Bh9MN2ZGGS4h7DGhmwft2QkARzA8gnZsF3YMghAuEwNhCEF/
*/