#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        #ifdef BOOST_METAPARSE_STRING_CASE
        #  error BOOST_METAPARSE_STRING_CASE
        #endif
        #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, int C)> \
          struct \
            size< \
              string< \
                BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
                BOOST_PP_ENUM( \
                  BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_STRING_SIZE, n), \
                  BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
                  ~ \
                ) \
              > \
            > : \
            boost::mpl::int_<n> \
          {};
  
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_STRING_CASE,
          ~
        )
  
        #undef BOOST_METAPARSE_STRING_CASE
      }
    }
  }
}

#endif


/* size.hpp
LmA4GQaeXcDw2DDgOCrQh8ExRFdV/P4NzSOAaEIynydT/wv4EMgvq9X5zLwWZTYKhCaM4Ou8xc6eA0FjhAV8zto4FwpGD7yhsZwzn4L6B536Z/j1wZicG+sT3gxhLm9PylFB+GZWW3mUMriL9Memp+yMTVKnA3BUMAs3kffGhI67PrcKWWEZ/ibMxxgt0Wqz30dCB5mf7FRuUnnTs6rqoLPBA+aujc3x8jmc48MM+zL3k4RHHWE53S+Amcop+4EzV9iPowvSxu3G9PS8VlMzpldVv1m4eIGaK2qtl+u/ezdpGJb3Xotjw2sTTJ4XfYDDp4qqU0ndEEYgsW6+jd/gN35cETGepSlpfx9Yy+sqea7F3G8J/vuJvuKfTtb+IcKJfVKyjfNlG+a6zt7YoxHu32GqzzqWbb8HA+bEqUkstJNpAs8k9CmU8C489KG8R8mGdUwvuWLqebFdsd+eoq6/I1Y3oEpknw1XhV4ad2Asp5OWiLGgNSnflADM70GEFZ93ti0J+xuOKvN4P+DjnkG2x+tcp9VcbB/JC9EFiryeM+N1qeeKeF4o/zB+A74j4aemObvDrMeBCsTIsKM0Z8wban7cyRTBCsUjwTs/2Lt5/2i8dwPu7t0x7Yv9uSrafYSnY+TeBx1AeyMkJO+Y2+id9iKYta9qJnPp0UTPHA9ZRu6af2zc1wqZDKIvjyP5mfrVY/TavnzPn+CGXyDET+6Pl8q8n14CnLEK4Lhhi+k+Pd6D8SBJt/L26DMDOL3z58FtJLwb6/ZsBxZ+4/hcBx4Nj08XY9eQLmA63eczPKabag2Zeabkj1D3ohet5ZgbM5h8hBZv13g4/j3Nyzy4f+f1csCdBgTsFTHMbAYe7IrTAXOI8h5wuT/33awEqeSl5xG5eoH//dfr1to7yVNb4aNMqYdwFFDaeI+qh96IduLbb9/ufYBY19obQe+QdbHEpZ66VsLIHjb9uhXlj7kN8WHAeR/19fdU9iVR9kcqq4myP1PZaaLs71T2CFHWus6WfUKUnUBli0TZiVQ2ZMqalHElX68OHt2cNf+G8/5jqoyvh65DpElWxKK2mPbvSu1njG+YeDqFyu4tymZR2SpRNpfKXiLKFlDZtaYsTX/wK341xO3PZ1Xfz1K0E1WBKaXFZJ+pwHGL4vg79nf1H4he5Ylu29zv4pdTfWs40pczQo+sjeF4esznYWHYxrkUzHC8N6AnapP1CedN6nmEhzlsHystIErUTGrryI352QR+oJOi5voxuHt7TMfMDTbrkIyKE75vvQV4EVKpQB23efST/MaebAp11vXbYth4biI/StVF3P4z5jl1C0g2OIIl7cQ3P9P/bgnZki8s5p3xeV8sFyT5gTTiCNYE/rUzCG4eWyZovP630xw9YHQEzdt7U9lhU5Z63tZrR4N5+0P1DqFLH4PwbVUdz+xEyRzeCRyFUOKr3w24zckRfatWoexUY7hpMd8iO2N+xRlEyzwmye/FchzHOheOiNeE16edEfAR5BZ7wLpkLZy3f09Pt/wuZYn3ji6Ml0P78EDuAH2mEMMXzAvhdRE7cv+4jaFcvZS3/l7/vcv7rhPrvjeqjxlmn9Q/Ds4R6fc6JMZnf18PVrj75v7hAB6us4fIdvb39fd430NkJXzH4YGeIB8MwXd09vd2GSQ3H0zOp29HJZrvecBa/wY9CbzrUs/3ai38Jv42VU+PJLoCAwF9QjmYON/rnHgdGwDrqlcsJd7NK2UVPNhCCbvwj6Njy6AP+3siNzRWzFgjOtGxFcBcGub6284OmhNuW4ZHr50lAU5tzBgj9Uo5QonhD1sXjIURdlN2GctV+87rjgv1WGJnPTr5ko7Jteq9Hf0=
*/