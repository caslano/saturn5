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
y+Oy3gYvTzEw7r5/CxFMZdgGmAFmKsOsWgDD8pr6Qce0dzQCToAT4AQ4AU6Ak0RfCWFD0Av0Ar1ALyyBVS7St6+7HYJlYBlYBpaBZbVj2fY7MREmBJwAJ8CpdnBCmLBCYcLId5zC0QLLwDKwDCyDo1U9Ryv03mx4WyAUCAVC1ZZQ8Laq521tEmp9aND/DFwBV8AVcAVcAVdq4goRQgANQAPQADRECGsRIQz7X6Ab6Aa6gW6gG+hWJbqt399Sj1RDvJAlmCu3X8iCN7DgDSwiqVVBaOH9ybkosTc+D6ACqAAqgIqKnlBdXI+aJN8BFUAFUAFUwP8Qg4q6ZMGBG+AGuAFugBuCXAwEr0AWkAVkAVkQvCrRIwFmgBlgBpgBZoAZPlvt+J9od0ejTycVDnkhkxiZxMgkRiYxfvhZux9+RqNqb3whkA1kA9lANvxGpr6/kamNG4bAHQJ3CNypwLAKIgyZBwWYsTf+EBADxAAxQIyKXlI13ZLh4P0q4Ob9Xf0f7tc2Ztb7ejW8GV2/ux70qKUQQkMITRobxvbTzA3gkCGcRv8R7cn/xnGM9YdqISTWS9k8m/5n0fbSbu5euJpuEZpTx82KY+DeuFVAJpAJZAKZQr2uNGQGFwKZirqN68hkPRxHBBfjgoscMYpY
*/