#ifndef BOOST_METAPARSE_V1_DIGIT_VAL_HPP
#define BOOST_METAPARSE_V1_DIGIT_VAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/metaparse/v1/util/digit_to_int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef transform<digit, util::digit_to_int<> > digit_val;
    }
  }
}

#endif


/* digit_val.hpp
jNg9C4zr2Ni5RevYbcoZ1vGin5tbR++6/+U6njL91XVs9/OZ1vHHn/6H63jn1DOsY/HdtI4r/Hwd59YDU683HYA+1vUJ9Uf3U50d9rK8HDquANs9P7cCss4MfUtTtJBXqspz3KHKRXk+cDn8iC4HZyiZPbGayUarsd9dxEIG7Xg0wUsnhMPBg77cEW4UDBuUrKQtkGQAGY/sg+5PgEy8jm5pREKELQtbrKwEqGr0a7Z0BOMfMIoN3BVvmshdwdBxtIjDyCH/ErkIsI8RkzAw6GqCvLAU2qn/C+N+Fcf2gyS5TWBj93FWxKWaubOXLeDFbOY81553th7JX4RYN5DfZmlyW1vdbW5pRrJT2QLBrZn1Ixh2lCiF7WE6bgBO7x8ZFjU4lTFJaJPXEpMNNvk8WPGZN9OKF/A+Uyr51TXKnjKdFn3enWZt7ZKg74vqLspjC5d1lt5dxBbukCd4c7VJxMqE6i36NuluXZv0RRC0GH4EmqF7wgugIDy1yXb3OI7koWnERrpTGp3MPqgwWG/2XwL/2OGf2+CfW9g/kSk+aZtagTYN+43PqVCUyNlNz3vLYipZFOtC8YGGxo0graZ4pBENvKIDiauoHr3HvlF3hU5O+NFioobv8IohPIYpi/JUswmb/o6Z/+qDELuT1SS45yCObuipbpiGsaTTZna3Txpdq7vFJ4Vgk1C0gnMThpZB03a4/fHT3A7mVfXG
*/