#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C),
          char Ch
        >
        struct push_front_c<
          string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,
          Ch
        > :
          string<
            Ch,
            BOOST_PP_ENUM_PARAMS(
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE),
              C
            )
          >
        {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
Wo9VC+8d7yZaMlbnGqvjEXnStcN/y+y9gBWPVrPROEEQ2PWzE/jeqT7m3ksvtXR5jwC+3PfeL9rw83KeQ3WNflUUAsYixJNz4f7OmuT97TYxvwho3h7AX+l0X/VIh7JOS+qcvw68RAmzc1ihE9E2+TDp8/mAD8dUtc+vgUZDnPH60LRtjMCOmA4+NiHH9IMBHI+ZRAkp3Zw3H9bxmrZ7Y/lVAAr3jpqq5z5m58mOvb193Rj8LNrHeEW345xP2MMxpyfw1BA+WY4w+K0iD15KmmAan6U5Zdc+1lLZLD3EsDVoA6OIC8ZaEZKyVwQyd4nF3be/b4AdXEIPftHCTbgO3f2IHDJeXfAT9bdYgDx9nYfFO4IsGPIbp4+iPsYg6QF1NtEXnyY4DNkEh+dAWD8eEBm7dnZjfWZzV2VYbl87ju6T81Sni0+PjmY2Sx51PHNDw2N+lqJDzb7EdHQcQ4X7quLInnbIcf0GcIfKkWiP4VxfPz7PEUfNy7WjpVm+MlKu35p2P5lWZiT9dPqzkitWw/X/DNVu/v5K+c5gfjztGc/42MO2nj1jm1+/53vujOkZ8ymkd9mM6en+3Beosm3nu/5hmFvOm/V/dPVZcHdWI7si/LgV+3NIvyT9bT+bE5c71UEu0WFg18ExMI6xmG94c19xSrsHwS5R5PRKdQ9fGus8vK8xUSobUwbVmddT5zA/0Q2Q8MvfdZWBue+VnmzLguOz1BV3XyXsozy+fk45DxDNo/TvihnPK7yQVwvn6RtUn+Icyzu2JjM0PG7zZJ8ANVkn045bvlZV/KlvUcdt2M5R3qsqw8POtzmreK8j+9i5g7p8tr2Dpai7Fj5TJHq8MJ6bSsrPWEX4UIxSvy5d5awluqOjp7h4LwnWHETkGhFN5lNLZDWqxQtcrcrqzFVWVvw2njsfl68im4Jna3R2XInyOR/CNyvAeQKdJ1dT2R9MWcp5ZiJXwvF9/4znbU49n16n6sOuVRSHicG1Z2aWT3ax9U9ARhx9JuD3Ql34ODw4j+1OwLv2IbAHQV7VEka0F0E0lAAf0jafFyfnwd0q7hEE/dsK5mF8OTYPAH68r2KhwsnE8et7CWYOhbjKxalZnFkJBnqVGgGXxX5Jmg/GArBJnvuD7wLaQxznHNkXt10AcduKDiNfSwzbD5gIcjQkxfsaYZvy279zaQxRWBzHEoOdn4xBP8m1P4q7CgdArtlDAa4u+/OoH6iOjhj3E/NyAcFQCFjUAsdSAyb9D8wJ6itvFtpNjmWfIdnD1URi8OUUwB1/SkdQ371nfxDgnIOYRRTDH+yOEVQVhpLXEtp34GibZZtdJXPRTpbNKIECPuNB3L37jTvPXZrXMY0caAQfV/MQJXj5BO9gT1fvARdNtHUwHsfxOvkTdBj5FBJYD8PYbxvCEp9PkrcIY4vtLwt45Bfy1+0w8b3dit7JtTrqwuoS1glYoWLIhvlTSzwf4+Y4Fgow/mbW3qDjShD1dR0YbZdQcYD7OtCH89utqC9SbMoHKTnPIe3ZrnEn4uC5D7YqddPsO1XABj+C7/uA96QmYwJrpSqeLx+sQQ/Bstfupm9R94oJs356EZXc3bFtk5dv7KgDC/ONTUk4XaSm5JWulX1ef8e8ylx1aM/WRXvB5bLdxx8FnMoN2LeB/+Rm99j8FvOTrWMWhnv2n9Lv2UQP60jp223BfeAl4PnEj9nxvrTpNjLmpzKMoKaQ59tVe/aZZry6MrS+m3vjgNrJ6+20zE8vm4heA1nfYcb0inntvHjH+dPIAbojtRzgJtbG9MT0fCPhffSLkqu69O46X1urD0X8HlHLDps/aP68Df15r7FtT8D34lR2Fcpuuivubu8=
*/