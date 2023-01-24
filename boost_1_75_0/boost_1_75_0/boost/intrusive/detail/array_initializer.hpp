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

#ifndef BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP
#define BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/config.hpp>
#include <boost/core/no_exceptions_support.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This is not standard, but should work with all compilers
union max_align
{
   char        char_;
   short       short_;
   int         int_;
   long        long_;
   #ifdef BOOST_HAS_LONG_LONG
   ::boost::long_long_type  long_long_;
   #endif
   float       float_;
   double      double_;
   long double long_double_;
   void *      void_ptr_;
};

template<class T, std::size_t N>
class array_initializer
{
   public:
   template<class CommonInitializer>
   array_initializer(const CommonInitializer &init)
   {
      char *init_buf = (char*)rawbuf;
      std::size_t i = 0;
      BOOST_TRY{
         for(; i != N; ++i){
            new(init_buf)T(init);
            init_buf += sizeof(T);
         }
      }
      BOOST_CATCH(...){
         while(i--){
            init_buf -= sizeof(T);
            ((T*)init_buf)->~T();
         }
         BOOST_RETHROW;
      }
      BOOST_CATCH_END
   }

   operator T* ()
   {  return (T*)(rawbuf);  }

   operator const T*() const
   {  return (const T*)(rawbuf);  }

   ~array_initializer()
   {
      char *init_buf = (char*)rawbuf + N*sizeof(T);
      for(std::size_t i = 0; i != N; ++i){
         init_buf -= sizeof(T);
         ((T*)init_buf)->~T();
      }
   }

   private:
   detail::max_align rawbuf[(N*sizeof(T)-1)/sizeof(detail::max_align)+1];
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP

/* array_initializer.hpp
p6xPyNjg/k1Rz/k1e6KHMMq4bYSybarUSlKXMk9Pss/yhpF4xp6i00KH5zcIxDOyVJ+dnvv8Axy7dTgyHRSKthw5fQTQHKyuhUC2eKiRWhEsWAGWZ1PLrzwkb3Y/TM+G/P1tiwN834aeuuM2Xqz9sqgVtrNrBL7c1OXiLFnJ8O5GS7Ye6Fz5mbHOn+LOUXswOw5U4JAt1jKtU7t/3lw5Ki9bNXPlX2WwZcg+14xFe/CIGD92cLSya1i4aFpYXFzktRNg4FXIGX2+yhydpWMvrbayDLV0GSJAkwnuTKmj7Ri1qNe2q9NcZvimULwdYAOwOY/ZO15cLJShP6Un6IyaqfgGpckSUhM+O2d9w1cBOtjyzW/Oz27uooWu6VtNglboPbUaNALIxbTycsltmr4UWFSooWYWEgcYlw78bgrkGiovVcpjNkcgxUAo9E+t5K4wseRemChZ9bABlMeFffBtsYynMsni9NbHKkv9aXNetyH8cTy3p067ziLZxGMxRjO30+Ls4+TyuaLS7wY2rgpBX5umolzPW1QPgWDDd7t1yakmXxosZB7DHbkv3IRrwVVjO2jwMQlSzfSUGzYFtklu2MsYasr5Em6RHmGxiwrccyWn9w9llvLRUqqL7Eludw/vQ4OhqkLhwOzYbgG2pZJalo2o2dO5GK3y3E/9wpTS5uKrh1Ytw+y+e3zGrF9SG0frbcHKLtc7/ojyCipK
*/