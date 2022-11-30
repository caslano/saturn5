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

#if BOOST_WORKAROUND( BOOST_BORLANDC,  < 0x5A0 )
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
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
*/