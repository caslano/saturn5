//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/utility for most recent version including documentation.

// call_traits: defines typedefs for function usage
// (see libs/utility/call_traits.htm)

/* Release notes:
   23rd July 2000:
      Fixed array specialization. (JM)
      Added Borland specific fixes for reference types
      (issue raised by Steve Cleary).
*/

#ifndef BOOST_DETAIL_CALL_TRAITS_HPP
#define BOOST_DETAIL_CALL_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif
#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/detail/workaround.hpp>

namespace boost{

namespace detail{

template <typename T, bool small_>
struct ct_imp2
{
   typedef const T& param_type;
};

template <typename T>
struct ct_imp2<T, true>
{
   typedef const T param_type;
};

template <typename T, bool isp, bool b1, bool b2>
struct ct_imp
{
   typedef const T& param_type;
};

template <typename T, bool isp, bool b2>
struct ct_imp<T, isp, true, b2>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};

template <typename T, bool isp, bool b1>
struct ct_imp<T, isp, b1, true>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};

template <typename T, bool b1, bool b2>
struct ct_imp<T, true, b1, b2>
{
   typedef const T param_type;
};

}

template <typename T>
struct call_traits
{
public:
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   //
   // C++ Builder workaround: we should be able to define a compile time
   // constant and pass that as a single template parameter to ct_imp<T,bool>,
   // however compiler bugs prevent this - instead pass three bool's to
   // ct_imp<T,bool,bool,bool> and add an extra partial specialisation
   // of ct_imp to handle the logic. (JM)
   typedef typename boost::detail::ct_imp<
      T,
      ::boost::is_pointer<T>::value,
      ::boost::is_arithmetic<T>::value,
      ::boost::is_enum<T>::value
   >::param_type param_type;
};

template <typename T>
struct call_traits<T&>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};

#if BOOST_WORKAROUND( __BORLANDC__,  < 0x5A0 )
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T>
struct call_traits<T&const>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&const volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};

template <typename T>
struct call_traits< T * >
{
   typedef T * value_type;
   typedef T * & reference;
   typedef T * const & const_reference;
   typedef T * const param_type;  // hh removed const
};
#endif
#if !defined(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
template <typename T, std::size_t N>
struct call_traits<T [N]>
{
private:
   typedef T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};

template <typename T, std::size_t N>
struct call_traits<const T [N]>
{
private:
   typedef const T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};
#endif

}

#endif // BOOST_DETAIL_CALL_TRAITS_HPP

/* call_traits.hpp
ybCjsYJQ7SawlZCm6Au/JFXlMg/DTDzccbuGh5GChyYzD4MED1OSePh+N553eBIPr+/J85rbSVnw2pg8He6GNEVPDJF6wiJPQ01cfHGbhovGHXilrWYuttqZZ0SSuKgQXExL4sLLuBCOVAQW05lITatgyYr+KJV0wyJVg028rKLj5fztWdW4ymNmp3UnnjdTpeq7C0swm2fLTE1gloB96YAhmY31oJzRcpUsX9FTJTobtrKJt01v1fDWuR2n4OIk3i7fkeedr+Jt+i48+3IVb/sw48DOX2ZIZmM9KH+0nBvy1T3n01u1lUzc7XeLhrt36jgNNydx91g9z7texd1Vk3n27SruTmFGgx2DS5GwV0BQKGm5CshX91yx3tp5TdzNuFnD3e/bcho6k7hbsgPPu1/F3YKdefYjKu6uZYrITiNlSGZDPVwuH6Fy2aXpuyKdFRxk4u2mmzS8lQneupN48wjenlLx9plQyedVvD3DVJKd2ciQzIZ6mFxiOTfkq3uuQG8dC03cLbpRw91m23Aa3kribqSwNq+puMsT3L2n4i4qlHIJJDEks6EeJpdYrgLy1T1n6O1lvom72A0a7qZszWmIJnEXFvbmUxV3o4TJ+UrFXYHg7jtIYkhmQz1MLrFcJeSr+y5XZy/zTLx5dbzNCnMKlibxdriwNqVOBW/bCYPzu4q3McLgOKA0QzIb6mFyieXckK/uOY/eXuaYuBt3vYa7W7fiNBhOK3dnC430qLibKpSyyKngrl4YHB9kMySzoR4ml1iuAvLVPefS20u3ibudr9Nw9/yWnAZ/End3C42sUnE3VyjlqirujhZKWQbZDMlsqIfJJZarhHx13zl09tJp4u24azW8fbcFpyCQxNtrQh/LVbw9IFRytIq3C4VKBiGbIZkN9TC5xHJuli/3nHVSBqIpH4gspQdIOnljMuzMvjGZvbLXCnFZ4zOHHTbg8RmV+QvozV/rFRrz931IE4p5qzZlKGZeWB+KuaJuWUIxLjEIpxmmbr9cw8vaIU0opqhWH4r5bit9KOa1bZNCMSyIUVepCcV4xGCbxpX4/DINF/tuqgnFbLm5PhSz7lb6UEzxtkmhGDb736tCE4qRnb1yvbM3QsfDZZtoQjGnbaYPxRy0pT4Us802GYdiDNETadzxvS7VcPH6JE0o5pEafSjm6i30oZiZW6tCMUykplXqQzEFQjfSTJzmXKLhJX+SPhTzdShlKObF2pShmLvC+lAMyhktV6EPxRTJNkw/5b3/Yg1v603Uh2JWCqUMxfywecpQzKtb9TcUUyx6Lk2w4o2LNNztsLE+FFO5acpQTOnmKUMxP26pD8WgUNJylfpQjE/oWJpA09ILNdwdNUEfitllk5ShmA03SxmKGbqlLhTD5RLLVehDMSWyFdSHCFfV8XbBeH0o5vhJKUMxe9SkDMVsvEV/QzGloufSBHc3uUDD3UPV+lDMZRNThmKmhVKGYvau1YViuFxiuUp9KGaI0Lo0YfjG8zXcvb2RPhTz6MYpQzFXbpoyFHPy5rpQDJdLLFdhDsUo1+Qi0pqcXzai+tWTqedpGI5uqI/PPD8hZXzmjk1SxmfO3qy/8ZnhojvTrG/NPVfDXcGG+vjMN+NTxmdempQyPnN3jS4+w4UVy1Xq4zOrClVMswZ531wNd6M30MdnfONTxme+n5gyPvNKSBef4cKK5Sr08ZnVZSOqXyt+c46Gt/oqfXymqjplfGbwxJTxmZ82zcZnslf2+v9dyvcTW/H8n93Z+8A5d++9liNc+RTbdMucb3Y8Cc5kIMywkEQCYCiWP0CAr+0G5L3+kBbvkvPkLf4pYIy0MGkBKBHBFEQEsbwexkgLowWQtxY=
*/