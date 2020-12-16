#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct digit_to_int_c : error::digit_expected {};

        template <> struct digit_to_int_c<'0'> : boost::mpl::int_<0> {};
        template <> struct digit_to_int_c<'1'> : boost::mpl::int_<1> {};
        template <> struct digit_to_int_c<'2'> : boost::mpl::int_<2> {};
        template <> struct digit_to_int_c<'3'> : boost::mpl::int_<3> {};
        template <> struct digit_to_int_c<'4'> : boost::mpl::int_<4> {};
        template <> struct digit_to_int_c<'5'> : boost::mpl::int_<5> {};
        template <> struct digit_to_int_c<'6'> : boost::mpl::int_<6> {};
        template <> struct digit_to_int_c<'7'> : boost::mpl::int_<7> {};
        template <> struct digit_to_int_c<'8'> : boost::mpl::int_<8> {};
        template <> struct digit_to_int_c<'9'> : boost::mpl::int_<9> {};
      }
    }
  }
}

#endif


/* digit_to_int_c.hpp
FrI3mtParidoXruHzjf59U44UO1NkuyNi3pvqzii41Dp24Cyz8Vc9f4PkoDb1L2uoEWQbIZA7XUjvGm3YAvFLyO1/yk08zGfPfp+tmY8Cmj9TgR7KZ1Zkkd78YIhkPS8p/cWuiJ/2St/3WbKvOooHp9hBD+9V9naVOe5Ym3z6lMt31ztBy1ljycgRv4NZG3GeKCvJamVS2DlJ1NyobrzvTbBCxfEz173c2eEHJAf7LM58v99pHPGJug9l+TbMwYSf70je1FP+1+Y7OfcgNF6qOQhj/CEr0gVHax4RR8QuzTbX9fVfJYnpp2l4pcppPrNlb9YsfzZUYrnyUpr5EMb76KpG66rb996VGuja2n/Nzo/Gsu/0VzzORIJpuWCQaHyms8FKfuuk2SP7OK3S+Vvbyv/30z0dVqt9VFG71ViGdXLxmQDf4C1rIFo9eWpXCZE8RmkKpWX/Tz8lz9R/jrZOfllVd3Se9vPWpLlZa/9NkL+cU2kNotI3UlBtP1JkLT1pWxrqux73e4qxZoxHovgkpiLHnrcApI6y8l2XS/7xRGZI9+COF8LpvuO6fzID1jaUvK91HuuG6boG6H3PhMAV5whHvsNUKM6Mg9N0H1VO3qYn/Q9TCo9GhCw3aD4DKkg9csrWRSeKwAuAYBuz2ht2kvxU92BrWjybDI1KuvASH7rCL/p2u+jJJ+qHYohO3y+PfOlgN4fpGh8RbK6jM7LxpRV1/V1jaZ3mtyV3yeB/aQpn6zxrRIDXaPOigc8hu7HAcW3nMBWuEo2Wu1m+lGt4l3dV60YrTM2lpznv7lq/Soe2lv7wUaybwsDwnSgDZOdM34gXJZMIesxhdSgGPnXlA2Rlg9DqLasofYX2UPtrsgevwTnA9LS7Q4kb0vR2i3VaBSBVK1Xa2+SuB7jFN9qQl27fIo3OgIGj6Dvx0TLv3sGxBBhu8+VP0fgcQLgkhpaLHBN3b7yh96fJtGkhRi8PwoDr4k0+VRPMip+BhzR+2IrPahrcB3s8n2y13oiy9UInUe2eg83gSaLyC9lrPfesXp/lb1K54d8PNFXZd/LZqh4HoEGNIJLruZgr0jwVpeZQxvvompDE52/Q/Se9SpljSbL/3KblG1XmA7PhGTObfkT28t/r4txfW1Vd/vBpbP4uZYCLG9E9mZD2c+tpW8HiM8tQaBhsvnrZqLvaD1R/TJF51FeyTcKMPUSQk6U3VlG7EeOUTw+QPNFAa3cqjt0HGU5dGR11fTpIEmd1jOC57U1e0yQvaZdoPQeFNw/3hN+owH2WuI3RDfpEMrkc/eUvQbdJ4W7xinSX7Oj/NlpSLAjDgk2F3Vm/apLcr4BOzMK9RO8yFZUbCJOtln1IXq/UVT7yz44f0+Vv+Sw5PMD/K542efj1DUuqPfouWC/MCdZn3q0UTqBrhshJ/TDkTJ7dAp1ztT5WwTigVu0X5WgrGFbZ/gd0XxWqs89EPHvdT/vAFgYL3+EbOr+k7U+Ssg+jaVswAP56/LIvgqmjbTm9HgzExPOX5m625M0vj4aj1I0uXIKdJsVLOlYnNQcAzVKh6BgNb0lGaz3ovZ69nvjNuDKSrqubDpl0+XdMjtC2ewAlNn0wgX71NhW9jhtjI6CX7bC7g8ykPlOkuKh4bTbdgfZrQv1vriw7Jer8pfIf/Bd/VJZR3k5RZy6dkOCzzmo8e42NW6HOMNvHtgKJQB2iiOe1pPcinqSO8CfGk03IsukLrLvdTBHPYOp21idb4v0frfEX+z7d/aUxapfLOT2clbvzmxC2dfikJg0JRXXVO+vxlJtt0y1rCIgDmifnC/dkuUL6hpM3T6qu7IoTZbyJVVULpV6MWC9hGjiTurhKCs=
*/