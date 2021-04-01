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
cO/hqxuGXUszgg7xv3/XoB53gE8Ro4BeA6B2iE43fNcwQeO/xRK/CQm8z7DLq9FRC0iX+wuAXuDUMCBPv4Zy21nkIdzViO5PHfwb44yo6ohCJuVH5LH/T+tlvuCj3wTR6MYL85wZ5VFzU0oBobX8XK6kENApcpQsAmky6XzkJhoP3z+75aC6LoNCMCTUSDx+0WkFvfdcIabWrmvEYUnCCwhfjRvo2NgSQUQr0CincMbhazMijwPNshFEw0mgQw3l03byBDrXCxMeTZpHVTcTV1z+w1YD/6CC/hVSKC23bpbIoqadH9PyMUT5Xg8/fEh+1Us1LeHUSdk/ssg2Jr4drOx1Qc/+NsNrX67qn5eM2WJLqxFl5J13XmfuKjxwQtKzRLfHx9X91+6jvdhCiuezC9mgThh1S627wTo3xybaHYTls4swxEhLMyb0mvb6TDf37VhtNAygfJ3TCmlqKo/zx4UA8Dv6BPmeXueJNF8CTqy1cGFrdKLKD8vvy/f3FZRen91Cg5TCvmXraAbkDUoMItS7oOL1ujcpQv1hWzQGioE8OOzmVcEBg8jAkg==
*/