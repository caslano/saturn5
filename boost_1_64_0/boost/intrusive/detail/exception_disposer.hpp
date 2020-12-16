/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EXCEPTION_DISPOSER_HPP
#define BOOST_INTRUSIVE_DETAIL_EXCEPTION_DISPOSER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class Container, class Disposer>
class exception_disposer
{
   Container *cont_;
   Disposer  &disp_;

   exception_disposer(const exception_disposer&);
   exception_disposer &operator=(const exception_disposer&);

   public:
   exception_disposer(Container &cont, Disposer &disp)
      :  cont_(&cont), disp_(disp)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void release()
   {  cont_ = 0;  }

   ~exception_disposer()
   {
      if(cont_){
         cont_->clear_and_dispose(disp_);
      }
   }
};

template<class Container, class Disposer, class SizeType>
class exception_array_disposer
{
   Container *cont_;
   Disposer  &disp_;
   SizeType  &constructed_;

   exception_array_disposer(const exception_array_disposer&);
   exception_array_disposer &operator=(const exception_array_disposer&);

   public:

   exception_array_disposer
      (Container &cont, Disposer &disp, SizeType &constructed)
      :  cont_(&cont), disp_(disp), constructed_(constructed)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void release()
   {  cont_ = 0;  }

   ~exception_array_disposer()
   {
      SizeType n = constructed_;
      if(cont_){
         while(n--){
            cont_[n].clear_and_dispose(disp_);
         }
      }
   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EXCEPTION_DISPOSER_HPP

/* exception_disposer.hpp
FfR9fe4O+2GkUcN8ff+rFZ46vAsPwnbxq4Ctzcjb1+WB+YYPk75L3CHXzw6eEDgCm+h51vvUlDFMylpbfmmV/T41ebNz4DX9majXxXL9kWDEx2WqhG8K0nPYgdKDXn/2Jv7hLxPP3Shh/npNwqmWe9vMU/VC9XyI5vG6XL87kIGlZpNzBe+S453r3GznLk6maQ4Mgi+sQ+8L387ArfTqnfTwRt6s8gJZzuGBkHMBbSO6BsfvpCyHyFkwL1Kn3ZJuYPAP8GboWVJYEXw/novu8q5/wUWSO84dJ+leJt3Hki47+AvS5bS9/9Y1Ns2t9sqfD99u+B4SvjnBAGUqCmZJPc/Il/fWpkt1DHMQF+UjpjrygaSdFRji5Ad6SJy2JdLl7B/kB6V8WcGfUY6oM4y0/GPlejf/Xf5E0cXhToGc10QcoUqJC5ctdZCnN5XlTeXePTVe2nYYNFPKcl2wkJRnkVON0z2YL9ddub5Vro8NHuO8LLqcTZ2ifJVUj16lzHOF92tB+W7I9/eCkj/Pl2v3Bwc5eUZ9FjiDtZ9XSn0GBjyfpn70dS2nCt3kdudcr+Hax5E26hPRY37S1H4bHCHXbyOHedoGvo6Gz0iijPmSz/uB79CuMd8Gfv8MEp6NgfzAwfAQ5+vXYEnzt0LRJb+f08w2UT+RiJ4tFFnj0Ow0nhkFbuQ58pT0TS///QJ5UojBmu56SbeWLwnsEPCNcF7Ey3UQnoJTfb/tX4iM32ATnK7PXEot6Qr5Cnlb/RkjbZAnbfCGpQ1ezg7rbWSMf5b6eH7WaZn4hGXrd0eo5ZmszB5ZwatHM3Yn9rMmDX6G+h2S3vJKVjAz/ltE+bYSvt3jy152vPIwgkTzvArPF8PfGGeZcsz8snsRlytnPPXJygzF5ddX+cbCtwc+vmvepxJZKKqTKF+eh5rv1VclKv+1vSLlv3pBIjkbCK8Oy/l27DfSuYRzCT/I4Ho4POvAO8C7SXNbdtgf705oLWHiBNcQz9+Qxmm4BYR4doafmUWu9VtoPKzU+QTxY81zXDm7KawfOBDWVjfOj32m8gw0faEG5ut3keHzOUz45Pnjv59wf/r+fMTJWHiGl1bGR+UjjnGJOG9c0jyI4/4ibn6ET/QRHZW0jvoH7hQd5t1oUPS7zbPUX7QZcqEG6CHur9Lwu01t1SJ5tUnq3aY0/t3Gf38s964RPpR/pxv729E/0p9rQQTRH/v3HqP+hOxlGO9Xt5cyFa+P+NWNm1U2YdK0slOnzJg2q4x64v5YU+Pr95tJ+MCZ702vWvJ7n/xK7Pn5++e9274fH+n33dfy3QS+lrvy4ssaQi9KrWX13S2lvG91UF5k+L6W6/p37GtZun7ffS3fsvhakmdCX8tn8816K1Lv2Qnq3dw4P6k6h9O7xjxFfZN1btLg9ce2TvTnW/G+ljoHQX4xfbylT3xdPyB9vb2u6lqanE7Wr++Eb+n6ffctfTcJ31J//8qC+Pqm0bctsfWdeMr0iWUM3ZXhur7WQV1bjLqu7qBvlbftGdkJXX7NUtfVRt+adb3woPi6fkT6Vda6MrR5Min/H6T8FZgTsFgkOnsspg6nJ1GHfK2DJz/PkG/q44y+8WUO0D/rbGX2h5zk+midMeY8l8SYs24/xpzXLGPOc+2MOSX97Hq50V5vhpzk6ryxE3q5cT/GnM7o5aj+8XXNoq6t1rrKkCPlzxjUfl1bOzHetO7HeJMxKPnxpuDg+Lr2oK22r4/y25867oxTx88wxptt/dutK+nNuYf2+3X7fow3lCOuruRn7dfQgPi6ZlLXXba6Gv2a3oEO7+pEv+7aj35NT+I5Et5rt/NrEZane/E3Pjv2qmFv1Tz0s3s=
*/