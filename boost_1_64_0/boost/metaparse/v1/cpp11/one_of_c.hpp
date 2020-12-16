#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp11/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
iL30NtRnNesg9DkXL3783re5Hy7bA7i1nMwiGODD+zts+5VXuH14Tp30h8t1fH+FujeOMm/gMlseTlH7MyZMME5934G8lOb4TjiyjnGh/Rzc5Qq3CacVL6PAXa5wRxi30+8uVe1bjfynTnNpE6xzV6yuDv7nlJ14dJ2LX/fJd0LWflnjzj3PhG43v2Prwt+3P45xo51d3EvqpI9wt53/ibutzruIAT6kL1a8WC5k4Rxhu+k52wqBx4zNZ6o2WanoaPt7FadD5lybao1I7zxipK3RJMr5WLnfNo9V4q6zsLNbHNnOD9ca0AO+0xW9dlVenb4+pA+F+U3cUOfOQauOcPHWqfSTpN4DX5YVOteWTKWzmRWDA328GOLG8xrhqdCx6+UaIdYEsXzCi9xYh0rU2TMoAp/n39UjuS3NxbfbfYjgHN9pdXodG+VpTW4bovVEp6Q6xfgqd9bF6GXL5sEVqcFMtj2F8wCg7wX016QII5+x66wb21phvn3Urjp3jbBb1Ke0SL4P51vjwxplibtGyftZhdsF63q8F9QWnKzAmdrF2PPvEWUvk2UPKfbo+7vFtaN9g69O3ItU4xy1If3wNlmdPzadXpcLQ7ezTUBxjl3RBz1LOJgG4EivWt+FA3Xm5/obTde5dhvw8t13TrdpWr9nQTeFuklcwwrX9ro8d3LH2Bb2rb46d1zajrUU7Tfx3cJOGOaxi/lJMO+pc+87Xjzefdfhw8KnTEmBtcn3BeMQxo3ENB7bzLj67HR3HDpHjjMF5jgfqIMfGLa99D1aI/u276x0bLADvA+B90OQj/8RdyWAcRZV+E8b2iBV0gsKVk1LqaVypKHG3PemDbRJzKalHLpukk2zZbMb92haVMT7VkS88L4Q7wsRFRFPEPG+L0TxxqugIl74Zv7v/9+bl3+TTUUFlvzz5s3Mmzdv3ry53vzqBMgO6iJt0Oc3cdy5yl59obClXn8W+zCPWtN7sZKl76lx73LOC3Od8nOrKxTuytryuFeirlQe5lSgg+dlTvwrm9x521DEvOfVTe68bHuZedlrIEM53JO/hpq7n+8j4i4pLcSrPdBiunh4D+BCz5VmZujoDeAtGENeP2cMiU8lyQNseN7KBdm+kgcNZO8a6aGNeumb7mLj2xxh+w5Ugwz3ecWxjMfhCS+TJD02Zl4rk2f3n+llRcTd4T31Nwp6n0v0dveaR5q4YyNc/p76fGmgS9+s5khvUfrwrb5MEx7Pq66WOgpp3q501DUIr1mPfBAmXD1npvTRuufdLLuE48tsCfOkraH+xHpiQDfS7n048ldpZf4fYJpBI7/F/eNNBKIU9lzgibbtva2wBa4lvC5vfCpJ/5nXH6whwEErN4TL7bEArl0XUDz9iNG1J7trLtezXrC8Gj3Ljf8Y2ip1FrfVDciX305gnfcJ8L1Y7b6dcCP3a+ATruLvTaJfF4FH9BKu6yv005wX8Oa282c5L6e8+2vdvD7Pc+iIeiDslL/cu2WeNKg7yuE0tzbNyy/gM79ug+66Dz5Z6kl3SR8rqx8GfwHY37tljTte1hD+IOSuZNNMiLfuijm8xYw7xhPTyUOeeOMum9ov4mvhs+pMnLP5epM8ZzNGFl0ptC4RsrpgI8pfudnK61him19G05kIN/Ad2m9WaAs3BHUK7FSPfXJUe8l8QPe3KL8aKsO+EwFd/e2QbrxZSE/xERWgXISpHH4Hi99h1G8qfrfJ9RGcVO/dHrNSvgNiZNndMywhnx/Ktsa7NzJ8kwpfViXCtmgVXuqGqym9fJtKz9V/Bjvxpk1CX4BmrS9+2VSmTqqP/noOHnBV3e/ivizyc/XC7xiH81F69w9NfOfra3YSM+g=
*/