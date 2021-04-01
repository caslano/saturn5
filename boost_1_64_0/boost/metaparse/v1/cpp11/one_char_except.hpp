#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Cs>
      struct one_char_except :
        accept_when<
          one_char,
          impl::is_none_c<Cs::type::value...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except.hpp
HvTR+M96j+EqmrtfN7F9tl+3GMxcKNtuaGIZpNq8vlP0JPJpvhenpbiNmHxEtNopDz3ddG5YYYOwpNTaBs0S91Eq+bJPJZq78PGK8ZTuqYYt19qeDDNUgIavjIuoTOwNWJiI2y1ijBDcxyhOLXCZuY9wkl6GLsDV/ymtqgfkLIuSNLsM5lh2XXauuUzacviQcG3cDN1R8mWr8zgFAayAR3t1O+qjWUY4NtCMgCBQdv00TvFKo5u3lMrmuqcM9IGjcwMq40kmZVQ7g2lWBu20rDZEyCURNSTXbrJXHuWv1hlRBUP4LN99sYdPzz7x7FbFzKbIF6fbX/vdAuxNJ7CHL5nCWXp63qad5zeTjpvM0H4tMuO32IPZKgvt9OGtfQ2wLK1UkiReMjeqcU/F2AwJH+pTajAX53k7JapayflLaffsUnOSUM+Ms7c/CRxY1KDPIZErPZ7Gb0PwwaQlDhHJsxLIfqpKdQJ3d2KayrDpeq84uNftVVO8hHwbJgvjCuqPINwCQpzGkkdSYd+Qfawh4lo52YEy9vE37GdTH3+C3zX0ciM2TzXPfeCduw==
*/