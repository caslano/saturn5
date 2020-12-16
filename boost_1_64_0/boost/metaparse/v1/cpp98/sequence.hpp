#ifndef BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

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
      struct sequence;

      #ifdef BOOST_METAPARSE_SEQUENCE_N
      #  error BOOST_METAPARSE_SEQUENCE_N already defined
      #endif
      #define BOOST_METAPARSE_SEQUENCE_N(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct sequence< \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : impl::BOOST_PP_CAT(sequence, n)<BOOST_PP_ENUM_PARAMS(n, P)> \
        {};
      
      BOOST_PP_REPEAT_FROM_TO(
        1,
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_SEQUENCE_N,
        ~
      )
      
      #undef BOOST_METAPARSE_SEQUENCE_N
    }
  }
}

#endif


/* sequence.hpp
UEleDi2m/R17fC46QP3mN/DrJOJqoQ/vY6e+3Aifjv3fA149M5F1kBv+GT4t/pza3svUgN5Dv4i9JnC2eSQx9cXE+fUHoatpfCT+fH9krufPxOjt+NMtqN9hOx+Ejj+Mkauy9j8gd5+tIjappSYykvoFsc8Vl/fBDlOHehn7MgO92pEci7XcfT6x8aq+2HVqId3o/5vETAv6cSeI/Jx8Z5v9yJXQo/l3I/fwcmkbY15GnRbd+8Vh2Ez8ycjx8PpFYihsXPt+9OPMoZq8oC9+d+LX5LNbUBf9iDXjzx4cR27zUR90GptxCXEddyY+n0V8Q4y48npi3zy2lHzr6Z/is6gtHLqaOu0F5Der8V/QrM8qfDY+6OHXyMkeJt5DZ999Bx7Dw/OY+3p81K3QYMin+ODNiE3SnPH1x4adhZx0Y6uOoHaNLf/oLPJNas8Xifcg4HO/sztrnUOdJY4e9cWGUlfbdBg++0Ro+yYyyR4v3AG9H8X5xgpyzOOpk31CDIYP/m4SmjLH3fCrBb9QtjU59Zv4FvjZfwfy5Tr0ekf4gD94Fxm5A1rMPwf7CS3Ovw3f+iv0EZw+57PWX5MnLWVeahMfJ9CbjbHzKfZPTjua/Q3gjOsE/j9/HvYROlfhK/rujM/Bd6ymfZ83sVGMdTt162OvJ47Dzr/CnAdSH+7BN9zDufFp8OazRuQceo7o4q7AfeRlL7MXYpaGG9FF9tlxHb4G3cusJdbBHr4/jn1iG5a+jT3bEhv2Auf3q+EBe4h1EVefBx2HQxfot/9EbCwxxQcXcE5JPPnSTdjWs4mH0bWFPcQf5Iv3bIyNnB/DfwLDdnavhD/Upm/Ezr1fiayOIv/ZDpt6MLEysrElOjNxEn74AuwP9xPKsDMiLpqJ3hdWYecPIS9Cn1P45JfPoy5DPnz1kTFqJ9DldPKt/Vk/sfnmQ8iR98A2U+/bhjlevAEbypnBaweQH+/B+q5AJ64jXr4JW/chvupiaM0Z/l38f3/4efpw8hb0vvXbxI3EKLPYy/JzyROOx+dWo7Np/l5ArELumryS/ZCLJu9Dppdx13kr6ALf90UfvkU9ec5U8tN/4O8uIK55HHu7An16GhuxDHospF4N7FsHo2fw9nPkZyqyuOgY9G8b8jP2+tPv4vfQjQ/3o2aAbZr7CnndccR8u0DjKfgwZHvGz4grz8Jeb0utqJP8nfyxjZrCeGzH+EfYK/cKH1pCDaCWHKWKeKkOm3sZMRVn7nseSCz5d/aN/b8sQSxEn2Pw898hvrkJGX8WPao8jVwQH3obOc5m+OHDf0L9/lwRP5CD9Gfvt2MT8bc/7MDnzQAnR77LfdCf41O/3AqfvSf13VPo/xg++3voDLLWOBu/S85XfgcxL36z6cm+2Gb8xFRosR3xD3Zjl78Rv0H/tR9ge/G7H6Jb9z+Abb+Z9WzDuQXn/ivLyF3g+dyZ1N5eQp6+JA7jXCh2O35mf3wJseboHVgvMrmEHGkv1jDoOPwMufV7R0KzBcBTxOnnoZfI5r7PEMM8i1/mDkrFHfiO8dCaPh8R2/yNOsUr9djFZeTrSWrL79H2JvinkicREz2KrzuMOAR1j72wlpzoXupsf0UuzkY3pxH74R/fwgdv9DH+ZgzrG0ZOha79lvUP3gR/sj01cXz8/fjeE3fC/2GzBP2GvoOukq/sRHxy4KWMgdzf91N0bxJ+hzt3Z8Kv57uwq//ApjcTF/wLe34mPgcdu7fQB1nHBqxGz5egY+/hE2LECuQzHUPAuYh4/mvOs36OvBHD3gkvXycvqIMvp82i3lSFff0rPmkfYiHitjG/gleMvf+X1Fc4r70fO7/bmcjSlcgxOvojYqZdqDs=
*/