#ifndef BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct first_of :
        nth_of_c<
          0,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* first_of.hpp
NoC7mielBx6Z7ThTSfyrPD/kIYJePzjDyoLeVuo3eLlwJ76AX0ui8AyZeQKxajECT4rRcx4/1Hvr/+D5olB4e4Iu6+Heg72HTww/7jyjDnyC1an7u7cZZZlE4qNeG723/oHWhjMGiXvG/uKwxeyzgjNH902WnY+DHyWiwNqJsCmm15bmz8TVz8DrW5osNfzGn5vhxbjR5uR8WI+bcvEC5lQS3yL8VXKzDHlsrTbadqTz9XBrc7OSDeg5vboeB136Sn3/iaPFa2s+egtPdxkHm/Rhkad09l3XkMfnB2HgWP1zz/78qwl7esKkMw/03UC1aV6ULa++0V97XznLUPsfttDGf+FQtTz7lbqlgSYmpAno03awf64ZPiwM9KSHIo+rzXZ4wHuvOBefP8X6X9Pewd+xzC8lWOMMtocZVH5ajcbNTLsPcd1haj55R/2/Ucxh1+XENO1ws1B4/RhHdXKd/PDrrRn3QXX9Kd6P5ntZcOZeWHSiE28cYsYVG2+lFAuao6/eTbaNtuAjquOkOKtg6QRcUhIfFg6YiZkpVMGtvMXLMupMjXWpiA/44APXaBAaqmwJM+5ifBnde/ZPWFSVvtdvW+HQKWtPBktyxKIn3vIvE82BYPeIm7Csujn1bGevPc2aYVSXjOK1Hqb3saaa+ioRbaT/hjShP/VnYVqtq5pNrC5ClqrDG7RhYzWE49/gifm+Hn0qbqpJx/7kXklhRVxrWi8/5u8p95pXDzBDEvt9vcV5HrznHX/FlXWCtb+f1k9j7V3Ur2u1NeeIOZIPNOubeIJ3aW+tt/nfqGpwpTjdNhuPZ95Tlybx70kXurQv3FIL+1fANpwbA/bMrASfPuPNYOmw8Xygc0fPfwTWqONFM5yHmVmM9/rZ4jiK/g414yx4V4xLOwNca37AG7yo4SwrHr41e92yAIfwDt/jmCgT6Ms6ePcZ3JpH+8G+gfb6L54c7pqTecBVOH6xWjhl3cfH0vMraA243PCAenjJa1zAq3pzcXbaWP0fT2WGSPudfo/H37kPHJ1exX2q8b9Dna+ppY9HxI0u6L5Crbnn0skw6gXso8tDfxC7GDjxCiyz/y7ZxG8v7LHv6OqqvXs0ouMHvjUv6IP3EsnVKTxlTlw4GexbzTuVwPsfXC+NOGT3uupiiZdOuN4z6/4EXu1Xvw3awYGvxZQnij9Irt6qt/hwNbrayqHnl8N8ONhULD/QUavuwBm1swHHTlzEq0ehw81eiv5oDXtoED/38fRLmsA1W8OR/CvhxBi1J6+/nHb+OoYOfupMq7P683zGSOefM/Xb9A+u11aProMRmZ0BOStca+70Gn6kcY3zZoUZYMyF5rR/B1qMP3Lu+j/PfcJMprca6RWiVlvIVytrNuMvbs70dyIafDyPcQN3buHb1urb3bCxjPqab16RGYf3VkOrAnAD/sOn821wdcCzhxX0E833p/d+X1deE5o9VObZ8Eu8DJ4RiQsfnMEXE9tr5kDTaKE/8phr6PUdsGRcPbWRi4aR569SmXmYPZ6m0ZLHh1k1edzofHM9/XQRXuu5RbH5ix3297OYtFfbOKlQN2ckemzLO9w61etw/EE+99wlOkKfN8ZvfE9gwUDzCblush7n4YLeuDJdS9iF/78Knm3AgZK9aP6pNNhV3NQJzleD2fr/ic8fN+QPeY06ueEO75PLPnenlU84vjMDHoH1f5Xn1ed4Zj+ucEaDV2J91R4f3KY3YcmlJuLfEf/htsez9UoPzwe3wvtnxbAsPqWlmg8VL2d+n/v/N+dpy5V4qak809yh7fnVHrDrdcDz8wF/30XO+9pDWf+PP9bxg4d/lJtNtIe9z6N9l5rLZc4P+6ypirg=
*/