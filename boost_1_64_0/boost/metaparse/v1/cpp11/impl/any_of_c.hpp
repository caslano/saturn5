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
gh6Th5bTp4j42Yj4p4Lex22Zu3bdyO8GQV5c/f900EppHVqfybQib9xdEbQYmKblOWI8ufY0tx2fBzoNXPvy//BpXB7jkG+noDzkp8t7sbXhZB/OhXs3tB5m3zoap25nYCPYN768zTlrnCqSGU835Qkxf9jeDpmhBIH5Ui4a9lvHPG/KNVodkszsz0ndQfOKg3SDJWGI4n3XK+SYzjRFUiLLH4nqd/9hnYw8XKn65MtVn3wFwgRHW5bZA11EXUy5r1blXqXKfQ3CBJd9k+hQ67wsv6AT67yQ96sU/psU/lXAfzPshiuFnfpWm5bl8m0U1nJ5NdK9WqS7RqV7R0S6d4K+wXWwudR4OUMBPV6+x9gaUg7h44rHsdx4UZy1f5+UfzsfNbvriRwORQvAPHuXFaSzNoiqs1mvaF7l2ssfcuwC2InYa5P1/DDh4Ywl2R7wk4t6mrGpmtcIKB/btydSk64vrxU8h7Xl1Hpj5PN0IpmHP5q6an+PO29Osd/Db4p9RPBsnZ9vshRO4Tlc/k2x+dPYt/HF/Oc6KZ/gy8fbzM+19W6AvJyK9bUbcacPc7L4aPdozPx/BOe4qyR8eCSWIKcl5+OM9BIZtzPWTZa2Z88/z4X7yXA+ulrG93WPdttYnH12yqP78CJumZOOjoXb8wDL1y7HmehPtvlShjuORmkW/cPRGurfN+zHPcGb2sQ9QbRpNe6G8l0OCtttSIatMLAZjB+A1bKfUMdP7sxhA2TYOp/ScXqQzkm/3oeT9wUrX7b96ow/ucn0IYsH2CbA/J0Khm/xCqVJhXu6gUlc1LHe+JQjcmX52w1M0d9kYFxP28/aDAx+93pwt+9TQua77F002149e/rtW3i+GM8F275/pumnoNczedujGFwHGpd9+v2II/3QTZ+RuonLjO1zFxUiIljnfDyi73yujX6q73xe6R2CA8/VO7dE4HFfZLxbKRy5v75I3pk63BaxDvQllHkTftKO+zLT6OIqGr/K9pTF0e9kfV3NvTaqc9vf5PUmnGnGmWX8JE3fJtwGeY4U92m1T4JqwA9ar2Q8Tn1XykIFe0gLnG3YTd6J/ImHTR0Bhx7+Pnjf6NBuqRY0+9Sa8A8IHz4XqE/xu5k/lDZdhXt2jo88Z6zH/o1Ze6ygnlDfXFE3IpSzO4K6zp8nSSryYkCYx0/VGP+TNis72E/E2xywh+4Q9tAvVLpfQh5lul+1ufkS3JHH36j4z7W6tsVvUe5PRbm/VzbmH9Q+xB+DPBFHcOce5t0i/k76nql1y/yTmAPdqezXvyBsaMXdTORl6sZ8+xLqfx/Gd8pH6zSL+3el0/6h1mDILuI1HMrvX23qTLh6P+w6Nbeuapc6yP9RXljHc/v70nbQx3Whn0vfMYSD8my/+ZJqz+Uq/quqPY9td+Xj9rXM69uA+wPwdkW73/bfF23/kHZX5o6ncNFzeV7bznl+q9Vtr1Uo/0691oC2nlZn3da2u3r5LswxtA1/Yrtcm9drjNHrhSe1+225FevjT6a2VPsGZd+dW9/urq0vwxpoXbDPtIrr9TfQIutVJ+r1W9jrJqD3rTe2u/notfJNFJ917qfSQwLWXJL7TASDacX2m4Xlsv6NzdSEtONs3EwSMEtTrYX5Nluw9ra5Xa69UZkJWzb8WuyRgPLzoArSGT5vMe1r7455R57t3sednlNfC9P1LdkCuI6Tufx0shjeGbPn0YkZyOc0Km+NX+d0QfhOfmuVgdl3HrzAJ8pWwYdrqkC+NQZtdThMtbFjIsrzTHk0LIIG3r9w7GxTN36f9HRR1goTZ62BYEAUYSpL2iE/OEmuOS7xzgzkD/EfCvYUqiVetVdPeNHzsfnraX0=
*/