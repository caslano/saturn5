//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ALGO_MOVE_HPP
#define BOOST_MOVE_ALGO_MOVE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/core/no_exceptions_support.hpp>

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                               move
//
//////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

   //! <b>Effects</b>: Moves elements in the range [first,last) into the range [result,result + (last -
   //!   first)) starting from first and proceeding to last. For each non-negative integer n < (last-first),
   //!   performs *(result + n) = ::boost::move (*(first + n)).
   //!
   //! <b>Effects</b>: result + (last - first).
   //!
   //! <b>Requires</b>: result shall not be in the range [first,last).
   //!
   //! <b>Complexity</b>: Exactly last - first move assignments.
   template <typename I, // I models InputIterator
            typename O> // O models OutputIterator
   O move(I f, I l, O result)
   {
      while (f != l) {
         *result = ::boost::move(*f);
         ++f; ++result;
      }
      return result;
   }

   //////////////////////////////////////////////////////////////////////////////
   //
   //                               move_backward
   //
   //////////////////////////////////////////////////////////////////////////////

   //! <b>Effects</b>: Moves elements in the range [first,last) into the range
   //!   [result - (last-first),result) starting from last - 1 and proceeding to
   //!   first. For each positive integer n <= (last - first),
   //!   performs *(result - n) = ::boost::move(*(last - n)).
   //!
   //! <b>Requires</b>: result shall not be in the range [first,last).
   //!
   //! <b>Returns</b>: result - (last - first).
   //!
   //! <b>Complexity</b>: Exactly last - first assignments.
   template <typename I, // I models BidirectionalIterator
   typename O> // O models BidirectionalIterator
   O move_backward(I f, I l, O result)
   {
      while (f != l) {
         --l; --result;
         *result = ::boost::move(*l);
      }
      return result;
   }

#else

   using ::std::move_backward;

#endif   //!defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_move
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      new (static_cast<void*>(&*result))
//!         typename iterator_traits<ForwardIterator>::value_type(boost::move(*first));
//!   \endcode
//!
//! <b>Returns</b>: result
template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
F uninitialized_move(I f, I l, F r
   /// @cond
//   ,typename ::boost::move_detail::enable_if<has_move_emulation_enabled<typename boost::movelib::iterator_traits<I>::value_type> >::type* = 0
   /// @endcond
   )
{
   typedef typename boost::movelib::iterator_traits<I>::value_type input_value_type;

   F back = r;
   BOOST_TRY{
      while (f != l) {
         void * const addr = static_cast<void*>(::boost::move_detail::addressof(*r));
         ::new(addr) input_value_type(::boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         boost::movelib::iterator_to_raw_pointer(back)->~input_value_type();
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

/// @cond
/*
template
   <typename I,   // I models InputIterator
    typename F>   // F models ForwardIterator
F uninitialized_move(I f, I l, F r,
   typename ::boost::move_detail::disable_if<has_move_emulation_enabled<typename boost::movelib::iterator_traits<I>::value_type> >::type* = 0)
{
   return std::uninitialized_copy(f, l, r);
}
*/

/// @endcond

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ALGO_MOVE_HPP

/* move.hpp
6VaTbFD548XqF1xfy0nftJMCsVskTf2eeovsxqDu6ywPEtjXJ0XXRQtTg4c4yudwVL7z5n/HsD7kj75v+tEN8r6CFrIKqbx9exM98L3D0pxVDjHmUU2ZWwhvaTuk/aerlBrIPi+F5qO34ax4f9h5ARnIm9j1yYlG/kfSf+SZgxjEuE0jfsOB+C9Rhfg+IB7FiJtYad3TRbr2Cy540UNxkxGHCy7n5clM61n4y7vLm+1MwYDeHigy/aHO9DeOTG/SmR5DmWJ9TyiQJ5Pk7n7c+UkcBXyinrcKfHwE1o2v3TwzgAlX1eSJnWgs0dm86cimu8jGWBl2CS9Gy5CG5W2rPdg8sL2N1xGI2piwW2VOyXM0COq0XOPe7sC9+soWuCdr3Od7nC10YY8OW+hhkdRYqXPa4chpypWKWG4gjjhaaEaubKFY3IiJ1mG192IdPt14UiN9y4H0U0PfN4Yq/JLXWAFnXTkPT5vsQVUy1BJUvyhf1TIGvLoKfxLhkKMxFc/t4rilisq+oIux1VGMa40WVNzfX+EPu+WAOTrq4nYaJLLAAZ6bHSJ/co3gFCjXDZzOZ3WzUT0tUMGv8BZkucxBuGE5ikCXGBschAvq8G8aW3WJtzlKvP6Ktgg3f2oLwr2t6mGdbQ+KjSKQ5k3pPTeQRqSBxls6y9cdWZ55hewAX3NPwV+PD5/HhGD/4Xvp62nI28EtsXpo+hjTKp5guWFPGst9S5B9x2Vq3BW61YBOIkmpWR3khqO5nPHgCeuDtXhhTjjWOEzj/JUD5zyBU3QJKgVmuJVHqC7PLNL1OvIBJu6RFVmqR55t9PPoHunAOULgrOHCODvlx6WOTlmLzMrMU1Rm1pVphRiKcKxaQrxq+VitWr51nFy1NHBN8cQCiX9GNGCA5D9j5QJJAlWwSQvHtD3g+v/MtI3+MJnvP3433R/Thqm0KpFnM7ScHYIFG87MX55B4VYWvcymFzpXIg1Tv4jafqeM2i6EMOGq3ROC80eyOC9EC7QhmFXy2T2kr1wJNrA6PVMIBKXEpGQLVkr0rNiSXzG2pnxLcP3knjur6oLVRe+QA/J3qj7LqaDFV/k7VS+Nqi5/x8oJri96p2rDSRRNaReWv1M9tctOa420QZ2RKFpbVbF2ACtejiZFaxJXkeLlThcOTYwlm6Uo5VShDGesQgCm2WMQAJb9cpmxU0EdJqGaFNS2YyVUvljnf+GTPGx7KfCjroZviwT+HXPkMCLgqckYrCJe4oiQThFREQ+riMFySxEgtCGR1UCvOuMBCf1EW+SaLN8pkM9QOC6TuaIi1yIQiSMcGEAKYzEC0ZsLZSCSr1DJh4pAY4eC6skBfkBx8n0qYt93EEH4B9PhpMO+x2eslRxGgrQS9n1VZvFLTpjHDZY6lSe2vN6QXW0dRSBWKf3sFR9dWdEXnZHDJyM8H1Q3a/oQPO4OzkbENERk0YuBl950qNjdS2m6UsgsCqFuvQi5Ivslqg0nf6dFDY+nAF3DDcQwkAQRfVQNX44Yj6rSZ4jkLBrsCS9cxhZEgcofXq2pTBLlMmOXiniDI0Kqmxj1KmKNihjc2pPskw1MR6mv2UfQ8DVZirkiKwdH+fU1/xmO8vX6aH2Qiijv12uKQ6wQ0gRCCRYVywF/gzJ1rJ82dYvt2BPjbZqmMPexdmQ2VA1uCmFmnKIXJK9hxnlbzDgvXKRmxns4D1KhMuWpjNQ0ShaZfNSbpLEcxeafStX8hpA3o20vF21fLzbXw0Ux4GseAockrY+iXfgyZKh5u0iUpTWO6gtL/DESMtfTlY65StMfqMw/zuSfrItXb711KMKPTny0PZgutC7nWuuz9HQatNbw4Mqu7SUtJTQ=
*/