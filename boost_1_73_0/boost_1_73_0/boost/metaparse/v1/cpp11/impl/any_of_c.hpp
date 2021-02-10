#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/or_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          template <class Chr>
          struct apply : or_c<(Chr::type::value == Cs)...> {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
fgPHQp7yHIpJ508BNeoE+YQrckKWXEoAV+roNjhNr7o9Rzuk8bAqY6h344SEbEJOgzjnvhIQudw4hGeIz1LkcLDP5zxOPrFBR15nOnTbl123eajvG807kbRYzgDUz2Q8B5I/6jfrJ/UaAr4Fmti+WC4hMM2khmUdIk7d+8YhUuj+zvUslCFmUakHmPIGS9fY7MsAPgbQcbOcAQV3iuwMotNs96PFFgmyg9229gdAbEN7iGPM83i+JlgthM0VEmwbVcQkzCmYTc9lJNRzw15VZytjQglfJBcGcIxoZ7cN4sDogMEG+SKmg1/98vmoY7aw17REt0u/cvX3yxJ/DowRpMekwB0wivFah2PHHXbvbsGg7/MMHr+yXh0YB3+rs1VTv6Z0Qp1zXE6wHb8rt75VseAM6EKjxqtDqY9t+5MrDOFlx038E7fuH4/X49FZz1u8/dlLssWgvHHb76760eNjTZWnb0rn8abjdpLVh/nTgC2vAMx+sTpf/fjE32eRc3c2Pq0/ucEb923A7wbN5rckBtmxRdS2tjC/IN00K1RVgqJQuHxZlWJ9W4o/YL/aF5Nh78p5WlVv9QkPchfGxK0+yau1rZXhw78MP2jdaoOO+rn134zg5A9GcLKPwPP+u9P9S2hubr4rsn+FBgih
*/