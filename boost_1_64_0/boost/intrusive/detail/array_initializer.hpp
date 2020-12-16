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
85d7V1X9lpg7WL69R1KQlXWNTUylBlvqwvePHKuvfxp5zgx5LXF7o/bzy5d8m6GuXeS9GMn53nRje0beLqsOJa80VHHkW3mvrl/mXUVqAW+aec8ueAz3S7tPGKOunwNvGnul+Gy7LlV2+Ux7Qul2ST9Tb9efC9W1s7wp5P4c+qmp3hFx7r9LVVkeUPwH9D4r/H6d6LdTXX+B+jXaM507ym20jm7ijfgKHrnPFkr9X6H4p3lT4J+GVL53JOlH6npL2HipmydIv9BzefZ22l4nE3QvMzGWWpY1LT3FN5rys++PjYSneFZl5wjv8/D+iYzwZc2yeV7yh3ki8eVRyf5o8WSGHvJ53+zLSPHYfWqvHxL+fOFfNEriTAl92TciPW68daNEz9BzoqhTT2lvyo/5vPgzr+Tqx30+Dnz2z++4T47InqXqgad2C2VWqNqc7M/laA/09zF7Rvo471Dnqt6qMH+ML8Teb6ocVJiUT2zfuE86goAKp45Bo2m7XU/Htt2tQVagbuJybJsxtk/k9fYlfSGy0kZ/rq7P0eu5ff/pVtdK7bbNXcz2Kf9sXSNFq77My6IuoP/GPKsupNhldTJHylV4ynyR+jLW5z1FVRdjfYnEWeeT+jKy2FFXIueluc77dobZj9XLKarfXCR73+8WoQ9CV5zC3O8P9bynx7Tf8Nxce4O+956WL9OUjM9YFsRn9ylzCiy5zaY+Eb7EPs4SdX218gzO5Ujd88G7VPgk5rRTkQ2nQZlZfYetX6ni4T6myyBhtdF28rtndLjtZXnS03xZGY52l8+5ZcsPKeuQX8jFeuWY/fLstoSOnG9W5TFbyiMke/Qfh1Khl6E3TkY3vTxkrFAb44f+RvH8zvMO4ttJbnZDhrKQuLxaHBvt/vUVde2IZxv/t0CHTc9ktTj0fl1/xnr6M1ynJ+CJql1Gl6uwd/Nc4jq77r/qV2T2P815qPufcr4x6j3p0pyw4LPQGbLnz3uLqVs/svOQ16K31Fgbb9Y3N2+tbdpQxVlzbVN9VUNU39K8mVP7nr5KyX/UM5IU3wYZ6zk8ki/iu22puq7WPNaF134Ge57iFRUkH3PAixXPQnQYY7z/6+lJP4V58Eh5tqrrb6KtFEoYJaDClngyCdX6Pvt5/E3qeqNnpWeCuj43H32Vb7NMlW0RdKHoNY5QS6+A3Gt3jCX/s6Wv8672Zfh83sV0d6a+LsK/C/5ZGJQaTE9JzabtjU2z68fbrQQhTU+7PX9U6ZBrt+cOdT4y3I9K3O3ZkX70Gkc/atW5Tpf+aFQ/KvVC5gPER1XlbO91ep4VppUn9VXlEXnp+GZRTZ703SiXB6aDd1rvX/zYUV/xWzdeW1vdEltH7bJbomR+QwvbZKqfxGmunznic65T15/zPEWJG+os8sb6Zvt7ler6Yb287Lq4zLpGj/Zb1Stwn6OCV+ZKXUkb7csc6fOGuuLfG88Umedyw3UidUlWSdbM9IzUDMG0rOXp6b43IucY36p+yjBWvNXSiXZwOtblSz36jAp7N17oek+Q+qXqk6R9nLQPWPqmXhAVXpAn9WxUqbGepcX3w1zXragxtnybQEDVmzXWg9ufRK3PKN0Q3LqRO7bxfr1D8Y421ROJx6vdAxPe51aY7nO6n9E+Lto/GQm9y/rmWoy+0guv2nrdxtom3c8wzx2JvHeA9+CqqPa3PN+p29xx6BytW+ReYRVGv3q1D0KvSBmfyHeWcSv9QmeMXlLE4qtGl/HBBGXcGVPG1+e692WqDWW8e7wzH99LWE+0vjFFLHonyMueAeZlteSlrltpgbmMe2N0k/41XMgu6l9v/7qtiFfOSyP9/wTZuxVKh2aLz+c5bOvm9FM=
*/