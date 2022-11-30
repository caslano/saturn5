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
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
*/