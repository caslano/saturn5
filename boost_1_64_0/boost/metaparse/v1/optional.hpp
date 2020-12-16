#ifndef BOOST_METAPARSE_V1_OPTIONAL_HPP
#define BOOST_METAPARSE_V1_OPTIONAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Default = void>
      struct optional
      {
        typedef optional type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Default, S, Pos>,
            // is_error evaluates it anyway
            typename P::template apply<S, Pos>::type
          >
        {};
      };
    }
  }
}

#endif


/* optional.hpp
ZnhnxZwf/pDX6oIH+q4h5OHy7Fr6DiOPB3D3utacAd9l5rsfI0356pwmVWDbjvtK5h7hzzFXvSViSe9n9jT3EM699EsX6HP0+0SbtkFmkvYDZcyLPTMaGB//BssvwM9dxnb8SsuV4B7/4TLdt1aujwq4K2Phj3Hfgx/Hm27n48b+PM59pWIWHmT66knTV08h/aTpqycK0Ves90gzXJ7PPGH6548sG8YnPp+DLJ80snxe4xPc478gZOVoWFn9WcBdGQv/C9q3nvnld1VDHaB4IfgGh7jSg+20znTBPaL18yoRR2Q2fBxfKsvxYaeChMKrS5GFN02HjYUmv4aZPOwLXjZrnb8b2/oKZPsPs8YjPPppuWwD7mvA5T5mOq/H0Fll7Nqb0Vg1axTCRTxZb7vsevkdlHs3txzw48u9j3L/iuHtiBLN2wfADRL6bJJ5Qxnp75bwZXbIKcM22JbZEWXGJJROcz3GnowF/s45dVjfLq5jV5QZl1sH/IN0HR8B/u7An7fdWFl8Z+XVMu0X+s9w/+giOPn0G5TOl9/SUabI+x6sSfe0hoVd/tuUX5LNDyJc6hJiIcJ0NICbRH7wT6br361lmu9R3iSXJ+hNgf+CpPdvyp+GfElvRoTbn0710p9cxtOeZeBR2VEkywPCet2wZPnkUf6cKD9g3Pmgk8UGnZ0ItpBhWZkvcfdk+4/py4B2xM/SKF/Iehn55MbhrqR8i3s45VG8orRs5y7Ew1HIj/jaLRH6IGQi34t8Sq8N0y4omr/PRuRGFySElznbL+2fa7KHf+/KIac6++CowiQ4V9rB8WbcFCX4zNh+nyjGOJgQUybJtkmVKUGZPRLK3lIZbW/LgJdICFsEvIXGTlYAtzKHj6HHfBXKVEdjfpQcwz1m/La7i9g+8Ju6f+X6QL9/Pi7oXO+yZMyufDH+J1J9RWL8lyZCv+5edEaIU055iRh/mmTguorfvkomwvGbzviQZ6EhSGfS/QOuDOCTgjVDwmsIPoV1MpTRNHFn3fnv7UYCrhU6OUPqU64uOT2K9+n6kLrs+mZP1hH6m/eZk4zufBS6s1cCcUrRt3sDb89YfjrWRix0rGX93wdlhng3JtUqliE+xWU/hrLNHANAvUu9vNil+wfakA7CdEc2PTXh+Yp0Z1rC10np8J1qmsPH7JsY2TvVPwhYn/FOtdDngTayWGEm63LuW+VdJeHZpuuYEG9yGDeNQql19mTHwfRQn10HMv0STz9H39w6MWFixEVySoo30XcmndtP6Fwt645WGpY96QT7En/c2IyZCffTNmN/6Mgs4D4MeZEuuT5Tbc7jNts1K9I+vmW6n7LEeM0PevvS/d5Zj30G/diK0iU83sT8HbaNZmq+55vJ4/nbP0fP9dTK/FZ/8Te66zFbyHHSiNfDflzReFJr1wMgs0+Z8feu8X04COVILkhzX5xflBsreJ6x/SuwBnxX+05QWvdrQyJ3zXxwQsQMPhn+LOBxRgHPBbnflsYEixM8d8wsYHw7dyxJ6HcUVhdgLWx8O5oSet8VwA9jaYJxSB4KZ1XkBy5wGgydd0FnWYLpypi108w69jBTnuA+5kGC01weZzKm7z8LuS43bTzC0F4O3o5McNrT5n4LYvxZ2oSOhDIwOpIycFs+zXDiPRe+RpcnHA3vFPB3Y/g7WsCXx8C7Df3lhv9eA7e+eesg36nQW+Ai7ozGzQB3MGH3lwzbANj0Yd75XFIf2QCRhj09Jpo7iY+xOe/M8bqqj36fV7IcG2wCD8cm9P6TaODNuPj3KY5HuRPEvD9LxOv7gqHXne9osn/aFxOa3kmgdzLKfXOY2Dzrw3k1XCeRQ25PegPs60bKHxvl+5A=
*/