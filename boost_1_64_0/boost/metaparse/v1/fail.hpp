#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
DJdFojss10QFc5XPq1X1XazMGLBogKuJtZJ3Z7tHkwDQp7dqtoQ/Z2zX3ss1tQEUGgS7RNJs7bSIO+UI3m2rxmp5CbckPI86yG0LPjGfJ0sSn22z2W+7t5nH+hMmuc+dVnSiNp822zDltbJXNUsWuNcv64Exy3T2+SlgyUIwY+8YJ1YELvVLqPMv/xmq9BJ8gjUFzer6QYBdih2r+S1eKhh3JLFgZqFVNE8pWzYd6aU9R5YJ1lX2lArpAJDfJVJMNnZm/rx5nTmiMv8/D2KmCDGz7we2zYO7010xZy4m0frJ5Ezhl5RbEPccMygfegw+GiyxOkIjfQAmLuqJcmfczH5sHg74pS5Hf90sg1H7tC57kAECUccLdIFt6bKAy2kRwaV0NZGOx1uuWd8vxBp5VbIr+g/BelsYmk/CKSFq2V2MTU2NjfwP7YhDeuDdo/mJRZ8E2pA0CfvNAxUagG0Dzo6mj+CioEG8mHaGGV4xGu2h4xANltrLmj8vqukT+E4h9fFUnxxTbE5TQTXxwSNb9tzgXsveK1nFySMrO3fZbKIjmSFDKS2i8ighSg==
*/