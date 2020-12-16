#ifndef BOOST_METAPARSE_V1_GET_COL_HPP
#define BOOST_METAPARSE_V1_GET_COL_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_col.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_col_impl;

      template <class T>
      struct get_col : get_col_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_col.hpp
X0p+P3wyMcDFN4H3M+XrbYP9e3l8o+fLwXeQxh9q368Fvp3EqX3fBr4Fcz9zCnwzZnwb2xb+fe79ceDnMvcjfQU+jXk/+dfgNeb95PNuh/ZP+IZLSOdDweebSXDqv7kN/CNk1pN4uyfy9z74yYRXPZG/D8BPJPwJT2j7EPx4wldZXpofdkR8BHn/66Xgy4T9472d0H85+3Fn2L9cfCT4hlx8JPh2XHwk+DZcfCT4Vox9PQbe1uD9VMtH/jPwBcAXl3hpUTE/fwI+B+G3gkfz85fgMxH+B3i0fv4O/JeWqfzAxaT2sRva/6wi/3R8uA18afC1ZL6Y8E/dDr4k4QsvLvxTo+CLE54Hr/tfdsf+C0TJ/GnwevvYF/OjNP9Q/9CW4IuS+efKBSX/OviXZP55Z0Fp/tkP8UkoPzp/rxxKeBP8y7D8FmhQP++Cf0z4reDR+PIh+HuE/wEejS8fgb8jcVo/Bx6A8VN6fzod/6rgu4P/U3xWJZNMfNNgfFowuv8C/P0EHT/F/sgI+NuEj4JH9XsM+JvM+ca5+5KJTZnzjVeBLzEz1qlS/fy5iJgfR/qTiU+l+qf95wLwp8CXFhzx/6J+LgV/jPBrwKP6uQr8AcJ/AI/q52rw+yRO4/+/HYD/nNn/+Q58OrP/01XA/j2z/3MW+O5h/XuN3h8CvgX4AhJ/blnp/SHgmxE+13JC/kfgGB+m8P3Ao9r6GPwnwh8Gj3I7UoT9II1/dP/hAvDLiX9onaTYf7gU/ELCy+DRb5USbz8cAs7ZDwkI21Maf+n4tih4moyfFyws7J+lwNch/NWFhf3jga9O+CqLSPvzQ0nY0lP5yYtI7aeC+AzZv0n9H4dg/30m4b+n7X9b8NvBPcHh/xL2z07gNxFeAo/2X3cGv4Hwh8Gj9r8L+PWEL7+wdD98DfYJs/55HXw/7v2fw7Dvmf2XDPjBEqfxE4eDb8fcX3IE+DbM/SVHgm/F3Q8CPjN3v+i0ZGKNhPRFzw+AryZDen4AvJtJvwl4ikl/Fvj2DfK3UGRfg2/bwD+ZDNOfA7414Q+AR6dqrgBfX+LUP38teFrmtPzA2fjvQ8G5+G9w1n8Izt5vrki/sUL/zgp+IPjSLcz5FfAlJU7H/6PAf08ITu3/o8F/lTi1/18Cv4HwtRaU1ieHJZEX5n4U8EUYnpjOc0/BN1bwAxV8RMGvUvBHFfw9nmOA4bmn4Bsr+IEKPqLgVyn4owr+Hs8xgPLcU/CNFfxABR9R8KsU/FEFf4/n6IzYn2755/uVWsAvlzjdf50J/FKJ0/OT84Cfxby/Zl7wM5j31yxwVDLRzsWngS/FlS/4Xlz8HPjKzP7c3iNYPzHyS+CrkfFpFAd2o/iHK8F/w8+VZsY3ic8Z2Q/HwL8cgQbpPwEfw8/oHYM0/RfHTq4PPfB5GvBjTk0mFmbydwn4Mgx/GFw+P0b5ixH/h/J5B3zzBulnD/lH4F2EH7LyTPXctJ+G+mfyVwWfndE/HTzN8NPAl2fsjwfA1+Tif8HnY3jL6dg/Z/iq4Fz5dYFHz794g+efBr4ik/5qhfw7wNdlyvdn8JsTaFuER/Fp858B/xjhN68q6m838HUJ//z6lnptPw9+SvhsEV8f6edJLDBhl7SdmUwsRPgDK0M+eAu+HwbOtd/LwFfj2i/4+kz6xc6Cf4vhu4MvwvAy+G7S+EL5q+C/kv353Cri+R8/G+ODxOnzz3sOyp+cj4f/vZ7+ePD5JE7T3w3+u3R+maY/4ly0X4nT9N+Cr9Hg+SJ/zY/gK0ic9u+Vzksm5mTKZx3wFRm+L/iVYXxdQuLzhXwA/HTCPwOvry/Av0lM5R1LgUfxVeBfET44V4uIj70AKw0=
*/