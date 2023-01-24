#ifndef BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_ucase_letter : in_range_c<char, 'A', 'Z'>::apply<C> {};

        template <>
        struct is_ucase_letter<boost::mpl::na>
        {
          typedef is_ucase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_ucase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_ucase_letter.hpp
P8yS/7/mbLtf33wf9pMn6yR+H2DWE7cuL2QY6mFjSYtzvdO6w5xGB1d9xZiWzuwQpT+GHbHe0NeNzVZdr1FQQZsVPl4/uEu7sXDd3FPgS89hLl47YrcnQcUyThp19Fh/8oHPD14lsa//lCo3xvNzOuobng6Vh7gL6gyViwo0hJm6kX03/2BE80VTlsTvgjQ0OPceXpkBG6qADVUGjn/+7/ABO+hlCCCvNVDlH6RBcqCKLop6a4uFEhMRFljc+bVgvLZgvvbO4diIzHQCrOpHHu9Wj0W/hGvZB87veR/Kir5upkjQDz1xMhrVSHZXQw09ubf1TXJQZpIbWaWAtQkNFhoDzq6C/8jMciPNJgEly/3O39w5hgX1hb7zpV5IfZaofTDGP1fF6842vGEjdCo2W6BUxXv5dWPQi3WgLsKUg3pa3caII1YzSLLV3SV3mfl5QFEebOOFm42spEFcSWW0/KMXnADkqwGZCW7kq+RABj8M78v2r7wY7pdKmgn69GG27NCkUH2B1hvjp8SHyTfGOij9tS0oCab4dFOBbFPhSxo4+h+QjZ+xzqIDL0o/1H1MR19MKKFYzIMalSw9xw+UM9Pv54oU+Ycnhe3FpN+lVqR/Yda0IKLAaq/Vv1ClbVJ3KMPNaFRWAesRQmBNvvbQWYfkNzLH0J1gO998dqtVzE9e9OhinRijxmsZmN0D/LmHt0ioCnryxVLtw2F7
*/