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
9LhZoBsOFDhDACBgj4GO3PBBdnBTPTLouAHRiXOI5L6sAlndfFeXQdNgNKsfGVbANJzVKxRmTduDMZn3QgHx7PXXsa3hMrNBfoRwmCnCZJMJAqlKeZ/tfTkM7Ldo8hV8eo5lbel2hREYmyS3jpDyAJYUKdfrqV47IP4R7ni+EuNKEnZ/RROP+LSymkk77AOsI05uheBBc2UKE03EWEQ5KwgAxDSt4+FM7MNmqcbufsutMjVLEIZadY/tJpkpRtA4WuP6MF+x5qUV4hx7rnSCVmgoeQNYyfRSbT/EnkvwWXgGVs3s1EsUExVM2itAM0U+W7Sjqu2tq4t8NV3fT26aAvu++iyWaUcBffydbYvpKIAsJa3+/y41psggb0SD+u+9fuPXf02z3zFRnMREPFvtFphEtJCDcTbWX8fiARCWROC5xu7kbiEIgl8PmdaF6e9BnBbQnVlsbJC2aaNGmfyZNMCR/DKQu2ari1bku5od4aip9f0EywSKDeLGMb8+fx/J6Hp8iimM3h83lQ6SHvFZxi+xyRCW53ALSbmuty2Z3twZbaqqKJ7Thadtk4sMQ8QIDW+aG4prRexzluSkuZfgzUeCkTYMStSZ8vsV6sOJWXCnoHHX0VLw9XPV8lhTkEnQzew83KId6AjiacJpT5TC4m4uViQAgZCzkPaPq4IAzej21ApzqfOW2wvRsxKffep1FdsDe37rul+2iVG8
*/