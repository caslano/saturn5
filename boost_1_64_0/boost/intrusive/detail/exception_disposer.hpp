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
mC/w1moKrPhHhMDY4HQUsC3ICFrf40ZqoxJUztapQX+iY2+9kvU9H8RKw1oWy0zavJoMPpFkQodCpePVUQyuFOyFsus7ZNN2d0kBPs/0uF1jmacm7j+xBXA+jFGLFXm83uth9bhf6Ozv+RGX3uJVypvs0IXbWL/mEVjXN6i3QN4Yw53fie+hpk1Ska6SZq78g6qShxO2uyO9LTY2zStjSOMkQKVRVwPqflTUtr9TvYD+SmXt22jaAWkhHGWqVk42MdIbqDxg7EyPv97QxkzgDuOiOLg2h8eE0h5p125QIyKghlL6tFgmxWupBBN0LExqoHIe3Wx5kPj6v66sw0lw5ySp2RqhnnEmPddeh8SNqaoN0/EOliTLW7AbzOQbJqfOtF1NBPdOFqdFzN5z3fUDZHjjC6CyZwER58Kl2EKGFF1EpFzmws9gYBCbDxxWI5aMz94EgjY8rD3UsDWLx8vwx5jaBCjMIH8gZdZcIozgQnEcXi5PFV+KdNapmko7nwxY/j7p8kx+dFUe9K54hqff4ImdKQ731C00FjhiZpNpVGaB19+Zikh7TxI+qA==
*/