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