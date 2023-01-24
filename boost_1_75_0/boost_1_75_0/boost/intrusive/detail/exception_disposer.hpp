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
KYryx2s1GUU6CyoQzYHcqAn98WphSSHGSpwDFbIl8UnWtOpWaJU8Yu6Wv335lCsvv6CpYCZrFHeXKi+d7U5SHZ7w30vqbFLd8LzgSSmArovtla/XbKjjN0q3ktNxHoBq6ti4pGZaZEb72PYOdMdyh2EFICAw2oZ8yNWaZWgAok8vHROO8DAbFjrOds90zwGmAabvKuDWpYRH/oRnrYLLjTvPO96CrQhMyi87NRHbe7F3OP6fIVpdJeA7g4NvBwdj488xHlKgfZifBpbcsYrk+gkqLWGnxUuHBsKFou199tnaVlG3Kd2chebvI5IBK9HCI0IZdRxz2XvrYZsrFodg58MOzRGLSQ12T38Xjy4jr67k1ivT0nnw0Hpkc8YbtYHInpqKVMmNbg5XZzIoeG+hg6caQM9ifh7qV6tVwpEFErf8oXleMNZz5F3mwp5oPTHyYMC/Z+1Ll+j9pP6invtIPM0kcn/1zUd+xXb1b3fKq5o9h5H470bACf014n+/Uz7webLFRpu/1bIk4R637i7sy5LC8Xx1oPvE7ZEGI5h7NKM4DWvsy/63jvpi0OrCmNw5hX8tQWpoB8GEHndBR6B9EtOEQe9Uju7fefJlV8XRl+TZDHPVt+iHUfrXry9/JnMklmWHKrnOyifE2VfbpYNussZGg6FiAiuU/nJT36XV6Wv2V7JtBv4BlG8ScDHoGwaVmln8Fggm8bZC9+2V
*/