#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/digit_to_int_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class D = boost::mpl::na>
        struct digit_to_int : digit_to_int_c<D::type::value> {};

        template <>
        struct digit_to_int<boost::mpl::na>
        {
          typedef digit_to_int type;
          
          template <class D = boost::mpl::na>
          struct apply : digit_to_int<D> {};
        };
      }
    }
  }
}

#endif


/* digit_to_int.hpp
f8jFOnEJ2IsawVB3F/jdkT2upyoHXjigbxEkyD8ckjBN1gWaUscqgY3VLnDKxhF9r8kfodEfMY0mU+brfKsM56RQ3bdeG+CXA2y/ndRw09FRZzoMbASGyUcR/0P+7Fm/9hfF81bRB6/2M1BTQ7T/RdN47d9130q1gd9esmlVaaiGApGP5VWrI0/vQT0u6CAGxrNQMG+cJevjtPz3J8HaaZ5mvtX9o4nkq0qqeBcEn1SU1MACgOlvIE49iLiOzoj7IgsGfeSqOzaekdlcl7L1l1llFbIV7xlOx1bzMoPfMJ2/mgxn3kByRfP5aFP4RUnVwroz5U+k8YO1wBaR0vd7AW47yX8/EjBIzxtqaUbsf679+TvVvFXNSsC0IsRpspBzx4KY3BrO5d4DSralS2K6yn+lvd1PE73jVTQ6/hK6V80gGdEecQfrSG3pDOcbh+HSa6reD1W34jxvRN2rGss6mnVdZUpW6Q/TngOo9luy4mU6Jh4YI/1MDePp92j+UM6BMoVJhVY0ov/609DyPVTbKN9De02ae+vg96I5iA7F5B8XCKgMGH4O8F4Rnf4l3OVvUrx7suy1Tdr/3rjLXiPbfQvZZjJx9hynIX9dLko+JNWhJA2Vfy77oKMH+h6ktQq2KHhHE+npKwTfddz0z+MxUmfZpJN0zlgFjKYHgn3cj2rJYXTsuX6AvTJ10z/ayd+k+6/2oZ29oAsU0ybayIITabeMjM+kRQh0JZKGZultxc1YiNvrXUZ+c7Il1eN7dYOsm6T5XBN+69URx03kH28EyEylxmA1udVP+spWcdXkytpugb6vaGhtEdhf0pmyeDvYYebU2BEP8W9i0DdT/kQdHYfb/7LXIEkxR9LXn0GEdgWYTkBmI1nczVRtvgbP8RHZsPl6H3bSWvY9NWLfyl8iT0cbWeGlm0AyVc+2PkxBZu8n0DX1pmyNpncrvWaZHg2/3jqtVnSj3XNHyX7+JH4TdR6NJFt0JqkHv1M2U0yfurGEVi8EcfcbA9B5kvY/+TazHkNSI5wBMJuh901u8NvUHXBygOKNW3VfVaqqZtOgOED/2R6y7yHO0HK5mI30i/zIDplANt9mZL7ZjsbnV0KFe3JmNv8Kwr0xCq5UKuAMk+Z6CmCCBir6JKmnfnoP5+aEfIq7WFUAPNKzCqO9lvDTHrZ2tux73XFqrqKGeR1I4mUK3bag7MsHxKiggbK76aj7IFqalCFruE7qWzvZB99cmM8twZZQXG3ADCR1PKj74AcaKrISVuVbKx5V2lb9R+/OmQIIrEL26SXaaBuUA33HOqDvccbt42qYpi2n2oGf5tpfwG4f6sz805B1sKZa61AYxHYFNL6p+1G27tPeui/IJPkwzUr+IYgX7fSAnyyPsWKQOBniq8PJ5jiv9dFH9osmUmQsNQ7pXJ0ymGqr7kJ8R4dc5jlT2acItLUsoOngHOjbS/HQ/or/rtN62wC4p4lk00L7/XAz+AWDDb+k9zk6Z3y+usBPgeEmSfBzqQy4G6B4vPa6jw0BrTrLvm+jeMobwPZZ1JhxnV7r4wJorZuNreyShblJObvRTbW0S42oqPX7RO8dNbOLa7408CT1RrMpKq/slzDdt2JILd4E3V7Z9wXUJS8VAG2ss2LOGLCBkehhOZXUw+d6T2gMcfEnes+wQfHzviCeb0ajtXroeqm74r/laWjdV/r0XZrig9rWG8uGG6Tzza6Sq/hBklKDunH+gGmLIWlnpPiM4pclXBDtsXazHtsBm6bL3pDS93XwbVb4O7sfdA+KwCowg2ymjLaM2VS7NY02nq10gl85+Dm0AiTGm7N+c1H3bSEQNrqgmueQvmv13nGqnc5f6ZsMl8M=
*/