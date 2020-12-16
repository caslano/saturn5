//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file
//! This header includes core utilities from <tt><boost/move/utility_core.hpp></tt> and defines
//! some more advanced utilities such as:

#ifndef BOOST_MOVE_MOVE_UTILITY_HPP
#define BOOST_MOVE_MOVE_UTILITY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/utility_core.hpp>
#include <boost/move/traits.hpp>

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   namespace boost {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            move_if_noexcept()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && !has_move_emulation_enabled<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, rv<T>&>::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return *static_cast<rv<T>* >(::boost::move_detail::addressof(x));
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , rv<T>&
      >::type
         move_if_noexcept(rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   }  //namespace boost

#else    //#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)
      #include <utility>

      namespace boost{

      using ::std::move_if_noexcept;

      }  //namespace boost

   #else //!BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE

      namespace boost {

      //////////////////////////////////////////////////////////////////////////////
      //
      //                            move_if_noexcept()
      //
      //////////////////////////////////////////////////////////////////////////////
      #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides a way to convert a reference into a rvalue reference
         //! in compilers with rvalue references. For other compilers converts T & into
         //! <i>::boost::rv<T> &</i> so that move emulation is activated. Reference
         //! would be converted to rvalue reference only if input type is nothrow move
         //! constructible or if it has no copy constructor. In all other cases const
         //! reference would be returned
         template <class T>
         rvalue_reference_or_const_lvalue_reference move_if_noexcept(input_reference) noexcept;

      #else //BOOST_MOVE_DOXYGEN_INVOKED

         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
            < ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, T&&>::type
               move_if_noexcept(T& x) BOOST_NOEXCEPT
         {  return ::boost::move(x);   }

         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
            < !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, const T&>::type
               move_if_noexcept(T& x) BOOST_NOEXCEPT
         {  return x;  }

      #endif //BOOST_MOVE_DOXYGEN_INVOKED

      }  //namespace boost {

   #endif   //#if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_MOVE_UTILITY_HPP

/* utility.hpp
23aCnpuRDedgTHiGBo87OpuzevnHati05v9UPnaK2Rwr4BlqiIFjYC6K8TR46ipRlt/dzzikFS4I/p6/nwDDlOA9neBxR4JHdIL5QqB21fc5ASVNTnWHhbHtmmqEkQwRK/CFeFeFEatyUoN3y7dJPjIHzAuzZvpg7TPJhzcLKuVUZzmXhHgu2ceMyo8YMKpDV/w8QPsOBv2OeAL0w4Yi3b4m5nhxy/o8mkb1FhIa91Z37btZm9SkzWVhSaBiJMWwqsC4+EDlF6OJNqcFPEUUvERbcgouAJqA5bGe0zq0IzIly4ECQ3N8rJGj24SN4T8p2qTXfdwm6MaGQZFRj/k+7+4DKOkTQl0EhjHcdN7X0iX4pBDvu48X5sPEtcKhRk+d0TpHRo/9nDPi+hNW6gRlQA4Vk3qSUVWm3JSFcCudFbztWM64nmyILf25GyOAegChzteon3WgLrNR7ycAPkryYbkqlL+w3L0mzENL3XN/h8BS2+iRLK+jlfcuAtoj5FRF6YCPE4zaLEJwsIvRmr/exwabFVQ10M0BqDvKX6m4vSId7BKAfcsJJq4/VqaDjQPYKAYDEP3zcqbnp4P1AFi2woZ/Yrt6fDpYvTJ8z0011CjSJFzmIGFwuSbhLxCSYVxLICCd875pUDgycQPl7QDzGbPWExjNlk6wAN+rC7BNoauiXmMWoQJx02FwCy/gBczp0SxjdhvZBUR2PsAMMkrbLPi5y1TBHbvxq5e5Q5vo+yPqO99e7g4tpG9P+o6n75PL/3d0VNqUB1Y8oucfLQ5scEj/zbIeLpe2VJY60a082YPsWFrHhaaUsi5qXl1FTaA4DWK9biCrV+p19czZ6tnE7GmEGxZqiuorpspbghQrLwrWC0N8kxiGln7ExTJz5JQINTTghnBYD9ad3aVwiCJ+gNx+SEy2W7wnllA87H/xkCyaafVIljeKdd1L96tAmLys8FjnmvnX2vcyPNZpPKk/U6lto4Pb1SUmwdAw4odK+VA3IVQQKm3q3Ux0k4Q0XlM9lmV6434odqjfP90V4sLt7calR515hzJErHo6K2D4ij/2/L+C1z+QV2AeCZwq5RWBzRkraME6jwa8kj3m2af5PRFX9VIgwS9EyGOvP2k5XmkeLiz2xYdrKx9dOLRbGjfIYVBqcSvDWlm15VAUxrV9y3sfcvTvOjeCJl5jN+9A40yPaBbIiZ8WXCS0VK1MPvOJmRqyFj+0iZURsSZ2z49RcUTwtgUExbbCvt+00h0in9o76Q+SxY6mviMmwkHGuSojdo6j8rr/HiGTriQcqQs5u4CboKdr6PUO6Bsk9Dk+h6PB7fQUamY75WSXLN9eZn7zBaXXP8iYqbGtcmAbLrH9zYsDHq/O+2oN/bwDeq/YW7EKlbyLMOIuZeGQMuaO78MpAmX4PY3iGQeK5ySKSmT4XTvDWRr6RQd0QkJfToBy8X1uVDEXzrCBM2xAhrM1iuccKE6TKELIcL9HZzhfQ290QOdJ6E8o1rxzLnpJPS9y6kkzVRxpGNWtu8sHPxHJVlJUlBae2qKE+eIc21n7otYJV8iE13mUqXLe8PvEe8T88wrmOdyCd+gSr3GU+HKJYRTFpvrJ+rFSBtz+QvYR8PBPV4hnzQc0licdWPIlli/Ax8HDh91qeySINoPysmOZH/xCHhrOzTdWtq7R20sEpmVu3Dilh1kyB2Q0mWmazDRNkPGZ1mnvlmlvFFOMNz4ziQUW9icnXi+bHXwfrf2CrsdTjnpMkxhwi1Yx4D0OZrzL5tG4r5aqdUmC9daV5AuI/gpxd2wWRfriZTTLeeNTZJsa8x7jjdMILlhNQpKDyrRJl2mto0wv3yXK9AP7UoqVb2w=
*/