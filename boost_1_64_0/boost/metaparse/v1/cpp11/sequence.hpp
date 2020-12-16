#ifndef BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/push_front_result.hpp>

#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct sequence;

      template <>
      struct sequence<> : return_<boost::mpl::vector<>> {};

      template <class P, class... Ps>
      struct sequence<P, Ps...>
      {
      private:
        template <class Res>
        struct apply_unchecked :
          transform<
            sequence<Ps...>,
            impl::push_front_result<Res>
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef sequence type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos>>
          >
        {};
      };
    }
  }
}

#endif

/* sequence.hpp
j8RjieER+tw5FB8l/pm4Kh0Xj43stfd7lludZ/I+r8XPYSpXKJo1iMRMPm08CKV9F57nbS8T2UX9pcGhYdfQ0Ll7hhO9uwZig6Meyme4KTs24jWKss9H2Zlc7uLSTMJcwEKZLtCUFT0WGv2XDm4EIMD+Vi8Erz7onCVLphN22s7z6moDg+rms7sEMyrWUiXXBQhuHOXlxnMZsbZba+CGAvb1b+VhjYGP0xJTlt9wG7TjJfCRx0XWdiIYmRz2LhvsyseJMaBu3vpWUX257ySUrf+J2uj75UnI1Rjwb3R4VSgaz8jMJ9hRPM6JNRS73GNFxdRUxq1AnP9uNudXG+Zn7SXwwfDMjmuT5s5fkM8TLM/88a4IX2HjlmeGBYlwUacFfJuQfLPjIMqSgyBAC8/PF05reDip9MV+NZZNCR10kYo7gDClwZlT975Sd607FvwZ72hnle4z+PuV7psR5T4BcTHosDzjIoz5LHTSP9b4v30OXrVXauEyY9BX8hz9LOTqIqnrxHvaFyCN+R1ucfemLlFlDcjzqihPy/FTkOYJol54w5J4wnMCIcuZHO0kS9u9xrO+z8ReM5Z2gSP2m7l/yz0erAHaK5DGjoX9fxnLIuZHal1NrK3JveeseDu44ZF2nMBflz/PaBG+jdBmmj/P4vYCjisjz6H4SLt7Pnoh989DG2sa9LrCC+x4KceM+FDvuYmBwf6hRHdf30gsHvc6aHyowvjwIowPRg0nbDeXQ4SGEznUTqvQ5jRWY3ww49Qyk+eylxh7ReVYshaLgpn5ZNV8ejA5Pk6L+3PHjDHaTDbKjHFXADcFeCA3tdCJlkI5Xghd6bwZg3wsmXLMKKMr66SuxLx4kzdOd5lSCT8n2vS2pbMsd82Jd99c79PxlkqKR/47EW96mp8112tCxtlsOW5KxtkseW084+vfqSTNehqxRv1S0Z9mTDwoYhEFBNo5cv2kgnRGtl+mdPqVSm+/HOErWW+znsZdFZPPqyL09JVKT1/V4uq5nRF67rWqH9+h7pW9HnnO4G34G2tdfP3G9JtMv5drMhX2D1Ont0SsJ76YYG9tcWl+G8aC6+tcXr5d8fIahL92lhv+ogrfqsK3qPAXVPhmGQYvMFey8USH78dMxBsY0eG0zwdV/BdV/LUq/lYVf52Kv0XFX6/iv6DiP6bib1bxN4DPXz2Lfel/oY6/f77GfuMub/T+QbHa9cvxaeTpbeR8vnki50M8hJxhL47HLu3TkcJctpGLW1o0jjy/iL1HlP951EmepdxZ5d5d30LhjY79msljPIfezsyacGPwRq+z5pM13b8o3BpIQPl12ArS2Td3xbwNeo/+yRnjgemz4YQ1MHhMsTBjmBwZDN7cFXSvsHqMDjGlCI02B3HWg9bfoNPKxBJl0b6N/4P8TD2/hXpe5bRDWtVL1xVzCIvnyT1Y1J1htT6MDDNhgyk+rqOwTrfewJDuHMwRvjNnjjCZiK51dFzZNzGOMi+7Hwr+7V0S2EkDw8MjQ6NmYj88NDwaD+b2IXygd/ewZ2FLGLYjgC0NYTt2DCNtNeMN793u4y0LYaO9Ad6KEDa8J4CtDGF7+gLYCZxfCDtNltHol/GoEDYytGd0YHAHcE8P4f0j3Tt20/KBj98QwmPxIN+zQ1j3Tu8eH9YieWFKA7w1hA8ODcb8PNtCWF98VPBzN+P2BekHRb67+vf17Abu/VyP7vMA86oC2O7ufUEbEQx4Mbv80WcSoK3mxBGj4rHeoOylZeKH+vt3DXX3ebYd5+KcN7jXz/+YOXGWsCObyb4+Gfb1D0jWgOUb1QiQKPLdA7WWZcLLSap+BL18u7IBSnr9Cvh3AP8nwJd53bHVj7s=
*/