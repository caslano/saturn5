#ifndef BOOST_METAPARSE_V1_GET_POSITION_HPP
#define BOOST_METAPARSE_V1_GET_POSITION_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_position.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_position_impl;

      template <class T>
      struct get_position : get_position_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_position.hpp
qgCZ52gtOGk26GC9fIGiNpi7pk/UzyAE+pF9cs78Bx7ktm3wNtfbAcm3BZVb8vSsMeejWbrKnhfxqE96kS4zHk2+T0508JWqB/SHCsceDTl70+cxGorsFU1ddtBnCbJ0FIWrcDgcqKSFd0QFV7bS7oqJ/aAlA7J2OtdNwp4eM/BMp7sQsJm2Lob/oAK2pujD+w2NjiHfmYaPXh+Xq+d0HrB7CrGl5Wt+HbCAEC8jBD/P5Zf7/QlQSwMECgAAAAgALWdKUiOllbTmAQAATwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjUzVVQFAAG2SCRghZPBbptAEIbvK/EOo1S+RMFrp+4haGvJSqM4SmKQjaP2VG1gMCiwi3bXjnn7DmDsHir1ApqZf2e/+QeEQ+sSaXHORKEyTa8PbD61Se2cLeM46h5QG31s2Cr8Ha3Dn7+Y0n1C8ItY8P48+wIbNAc0vi1SZMJgXTZUTqWTfUs+HU/hdjKB8Jn9kA4DiPd4A5M7WOkDFaYTmM6C2V1AksfXmPXtAmhRfdsFPJMfyO61cqic/4Jq5/IAZudM3NTYHjg6nruqZCzTmgh7BsFPTIR6XxatvkdNuoAE/SVzljtXk3wIhZIVGbVVKRpItEoLV2gF
*/