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
O+FsSWc6ERbzJA+Dgh3c4BV0ndaaHOBgv5yYnMQfgpOLz8X7XJKx5Zs8g6RTiwiPLSsg86N8ZMNlFM2l4r1/9kDm3T9xERU9iEIzxxGnDoP/uaory6onPqOLygxmrQeekkGIWGXoK/ATKGV0MPJ6j0DAauWMNegm2YfSa4RR3JRijSBlW8NtmyMMhzw+f9qnxair0L0fQUYa65g7C/hQHEPMaOwD9q3Med1pkGKqz81pPDflPcGK3+XOAPOiiDJxQ2jNyF/VZaXhuAc22OmNVSMpjt34N1lZx8I5twJYh7S7bjavjmaolKCMGtXTcnt1clX9RNGpiEkt24O3L+5iL6yNR7wgDqW8ndkP55PDBWgJGSiT1xH5m9w31p/Krzk4DaYfUlTQZqRs+WtutIMImk+hx5WBWE5Nxfi3NSEcRG4rughqWmrKQK5EZuzoR7Wblch4xOSvlLzwvqq/N7E1g3Bt5r05Sg8bJsKdo5r0yqZLIl4QCJrgKJBZV8ShPDSPhbqA7pMzZWb9gk14qyMP5d0OUg6j9Ij460IkEGYm3oo/muWgfla/tVQzbQ==
*/