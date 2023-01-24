#ifndef BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP
#define BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int From, int To, int N>
        struct index_out_of_range
        {
          typedef index_out_of_range type;

          static std::string get_value()
          {
            std::ostringstream s;
            s
              << "index (" << N << ") out of range ["
              << From << "-" << To << "]";
            return s.str();
          }
        };
      }
    }
  }
}

#endif


/* index_out_of_range.hpp
uwPO9q73jiR43viHF5G1muBwPx3qKWU5yhqRWes7USD7zWvnRKmxb3peNzmoRiRlVWc1Cm/YpBp71l6btNm6rO0B94z7rMuO5c14wGOTdmL6Xat/nN4e3yC8YV12/O4HZjh80Wn2+E3QTrTUiWLMNyUtwZMvehPr34apY0jbGEUYXR2j17nTRxfFROncg0bPxp8LjR91/gF2Ter8NHGNXqcnmSQKb9bMTbZJRicIM6u3QW/zGa1wGIiFa9lwQEm+bH7xdG7boksRVvi6TULLIVr9tlB1sMfcOHt8Dbxr/B2lYNbbTOLZfImZcChU/ZIseJ9iF/rDBSon4huYzO71n/sw/B0wdy40r28Saw6kivFNvLgFqJqX1P6l1jNVMv78VpTO22CqN34DBzg+fMav4cjaXpvqzvY2pNYb/w2nRrpRBUeVOp2hyTa42Zbb7EmhlijLbqI38SW4a/ENfOotNt7T0SB1UwcnkTzMqs4xroaboELWqpaLMuRxELfKEBv9HU9/Rfrbm/5G0992lHVDTHT8LR1/R8fb6G8qzrxDLqG/79PfS+lvOv19g55J63L9cvo7jP5eSX8z6W8VPf/vxVwGZV1FMihajotiMiirOkx/JX5HzbTT5h+b7jA0yJORQb0zsdCd8f7BHYp3ZiEcTkr3zryVauP58pIw2Wge8vjIZcjjean1sUU4p+Wl6HrCwL93aCeqptco5iPz
*/