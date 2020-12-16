#ifndef BOOST_METAPARSE_V1_RANGE_HPP
#define BOOST_METAPARSE_V1_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class From, class To>
      struct range :
        accept_when<
          one_char,
          util::in_range_c<char, From::type::value, To::type::value>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range.hpp
uNn8cdl8t1bza7fjKD8/m98xvRN0TqT8omx+5/QO5J9C+SVRPuLwNiAOw6kJG4chfHOmubG1YXljfQt3ngVgDSVt6ldho05P8LlfiXpL0Pv9n5HwZ7eTzLf6MyHLs+TcijLWBp8N3HOA+zm1FuG18JdCmTsfaqyHkTfW5QlZf9nJOszzvufRnHiuk3WYz/vQefhOeZ6QXZH3iyZEs/Y02XyWJN+a8zFeed3vee7MdKbaurAOd+sBxL44EGdYFyRyvunSx+N0jwurG1Wvc4dbO8PnvqOzvzVN7vPZdZDN5/cphqXhbimnB5iIAcg1+EViLF4k1uCXmDXApRh7F2MuuQw68FWhb18xZa4wc8yVKHOV0Zs+BzZ3CfKCfhe3Q3zX7nO7LrEP63MPUIu1WF+qq21AfeMvCtZ29FMpGTfrGtlvw9vJ7cXB8MirlrJjh87Oyvjrka0dRu++EY4VxCpBPJVrBa9jvY7z4pp13GSzbThvPMfZcnxcBz5i9cfTh67YYWQhPI9cD5rtygb48c59yf4IN4Tj31NR8eORx3cl/L2e/CB7sSGYjbF/oxn7zF0uw3G2srUAPtFmvjmygOeawpw3/ncMbob+fkeeQ6Bc5QRvU/PNnePvosz3ZF2mzP4oJ+v6Psr9ILYcn9fYcreh3O3x5aht8eXuRLkfodyzQ9yF/3aopzR/trpY7j6vLbSPsOfAGQcdQNr149rBTEfvBozhWyivSJxN3OrmyfAso52s3KAaGz905yWA4RpP6wDNCJF9vsOdR0Xw1RRBP92vYvvfFZ6jAE5Wpm2A/F2wf/qx3D/9V2NgFNk9tps/NTbwZ7CBV8Bu/hxyvht4k0fBBuZpOY93Yx53tzKd/H7+YODfVVhrYsQXqbiD/k2F/r7egTTvI0mG4c2sgM+b/K0q3meGfk7KL2q3CU4ukYsT1kaUNyVY2zuQYZ+naWEaPKA9M8I9M9qEvFlBurutsytb7gCfjmx7uG+bE3T2yfbOp7RDcH2WT312r+izhX7uXUGPXzXQK61zm+dm34HPAcAWjOj92qZ5ixfUL2PLbgBZ234/+nEkNJc0NR2yfCnTNIAszQdB86JR+g1X0oZQbg+4MejmD/THQ86mkn77u29QT3GvcZy419jkbGrMHcaimDuMJUPcYUwMcYcxOcwdxtqYO4yTYu4wTom5wzhtiDuMM4a4wzhriDuMB5gz1/7xpGvmfl7G6Zs9K8OeYiHOsNy5KRUd/Quhh0tGdO/Z24SLzbroV7AJDxvbcd54jfco8H4NPG9v+FzsN2bt/niCfmYf/FvQeELQmLYH03jS0HgqQT9D42nQeEbQuETw8QdD49kE/QyNP4LGc8Dl+0B0D66A09bPYBLeIbLfBbckdDymG2LiGmxFnURD8fdiIveNgb8m9BsCb9n40QRn32AfvwL1Ez0TuxNnPq+g/tPMfe9XDf5pwN8meHB59kzinwQ/cni707Jsbv0hrU0N3s6EIXMXNC5rXhXq53axsMZ7w/TnmzHnL28lths3zi2MRSylmHzMp++I+fRdMybeM2eJ77OMCMZ9/ulCxHQBPvGs4tS+IeoYVa7rGF2u69ihXLf9MTV+6a6GgZ9nZLMTw4k280h4IXznck5bfyiXd5rRvXHl0B3AKR84rDsfkW1A7NxSrOm8LPw87eXURn03xu05xhSUj+T7Q2jZXBqP/8yePX0Ov6tcAB9feQ9xfDnX78fDxtj6iz9s/eEhjK//v26DoJGNV2N8d0ogzwITN/gVfmuX08ZmTeb7IcDBHZJyHceHcTiOT6XQnVdibECVgLsyFl5Trn2bzoJv07+Ktc7vWa7buxfSlK/O6N825SabcnuX874=
*/