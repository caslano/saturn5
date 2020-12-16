#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>
#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete :
        foldr_start_with_parser<
          P,
          first_of<return_<State>, fail_at_first_char_expected<P> >,
          BackwardOp
        >
      {};
    }
  }
}

#endif


/* foldr_reject_incomplete.hpp
9aQvetKXPemrnvSxxfHgfrX+Dn6vWD+4L36l2N9jCH6O2N+jiqv8xwo6/0n8h002/1jNm/HtHLfxm/3xON6ofjMA74Q3qt/si3dw3X6fl+j6bdHjZY9XPR5bGg+uFfEHcfxqEX/QFZ8t1j/ohl8h4g8y+H7Gmw91xt9xWX/3eHC39oTHU3eb+FC7vi1+Df92Cd3M/0vjc4xPP8w52z2MP4j1TZvwCWL/k63wkx23/Vtd8SOM33No9NdOeMp428Oc+CT8Iad8tPm7Cv+FKP/n4veJ8v8p/HDjY/GW/eHwQ4w/g4d/ZZYxP1CM743HHxbrM0/AHxL17zPwB0X9+zx8map/32fKF9v/iof9Z6G76/c9i/8z+L6/4Dw/r+BPG9/R+X7+Hl9lfBYe5q96v6d/9xee/l2PJ3C5Pjcu6+ee46c9nvF4Fpf1c0/6vMcLHi96zl/ypC97vIIfLTz1y3iwVsU3478V+1+ejS8S+1+ej9/uuolfmYTf6riNX0k9YPqnzPzr0fhJ/HuK45sPicqfMfgJxpNO/iq4rB/isv6x3FP/wNX3N43L+fG4en9yuJxfiMvn0+NFj5c85y970ldwef09HjyoPYbL/ldc9r960mc95895jl/A14n+t/vx20V8a+FXjG+o8gOX8dF4s+rffciMz9rfh8vfh++r6qf4YcLTReJHRXz8SPwAx+36GKPwZhEfX8BlfDUu46txuX/FCu0Jj6c8nsFlfKPHCx4vebyCjxftww34OPH8VvHh4v5kVhJfqdbHwi8V82+uxEe5btdfethTfuA316lf/qjmu+MX4mc6Pn1wVL/cA59s/Ak8rF/uiZ9vvP1BUf1yAH6G8Sl4y/oQj+r67+H4Zbhpn0T7Q+MzjPc7OLo+w/GLjM/Aw79G4FONv4G3fL8f9/SP4LJ8xWX/iCd90ZO+jMv2s8djT9D/r/qfcbk+jsezuPz+4/L7j8vvv8eLHi958lf25K/iOX5VO4Nd9M+o8hXvLjyNH6/Kf/xOUb6txtX3OfdU3KxPbOav4BPF/JDYKsa3VP8jfnUg9t/BZwR2/2CnfwKfavw1p/+giifU+nq/jrO/GONsDfYfLuE7O/EpNj5rNZ4I3WmfbxvGz+Ddje9K/trX8vcyHnPc9i8ln/H03+IbRf/GEPyDOvGV4fU7At9gfNOBzvxO/AnjgwZF+bscv8/4Qjz8K/ssz7dqf3q8iPdU7x8u3z9c9g+UdPqYxxMeT3o8havyJ43L9X08x8/iMn7Zkz6PTxfjOwvwc/FG4/8L8Yl4o/H/u/Cz8Ebj/4vwM/BG4//Z39D/J+a/TsEPFvNfS7iMP/J4BZfzE5/zzE/Etxbzx/bAv3b6v2z8WxL/yHEb/9aMb3Tcxr/1xz8Q63dnf0v/nZM/e/9n4mV8F8fn7R7d/8vwF4yX8TB/s/Dnjc/8cZS/y/E1xtfjLeNnaz3jQ7gcH3qe+q9b/trxVXwC3iZ0O76Kj3Hdjq/ip7pux1fxk12346vr9PjVBvxe8f1u9QL996J9UsKPE+3TNfjRYn3UtfiRjtv+++SL9eNzflg7/n74fXWOHwv378GXGF+Fh9/PQfjiOvE529Su7+H4zSI+J/YS7TM1fx2/WPz+rvgFjtv1d9L4AMft+jsj8WaRvyL+RdB4/G8F/lnQePxvJb5JxDc9jH8o4psewd8X+av+juurvt8vs/5O0Hj84FF8uRifewxfVif/YfzEKnyxiL9/C59svJ1TfuRfoXxy3NbvbsGfq5O/duH8cPzpOs9/6/D7hj8pxg/zv/esn4fL9o0nfcmTvozL9U08x6/q43MC7TH8Hvf7bMdv8aWO2+ejM75AxNd0w28R8TUVfHk=
*/