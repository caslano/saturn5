#ifndef BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
# include <type_traits>
#endif

namespace boost
{
namespace endian
{
namespace detail
{

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

using std::is_trivially_copyable;

#else

template<class T> struct is_trivially_copyable: boost::integral_constant<bool,
    boost::has_trivial_copy<T>::value && boost::has_trivial_assign<T>::value> {};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

/* is_trivially_copyable.hpp
4yT6kHhpeuNmLlyCeXEF//cNzvbF3yaYnBW6+XBlX17Z52jQbzklcp9LqnSb8caJkgia3kLofvKMZ5FXr6DspcIOtYI1WHGcTinHhuiyt524GwpQEs4LUn4f8NJlGMWpnxp/sabkfUXhWgsYB7J+ZwxcpUD7sa4T/Quc1TgqHCfmOU0WbAWr4GwSdPrvQHnjpbPEjzM/Co0YJQKB1dqffFbrGNXiZuwY51BQHCIl+lIPVrGHQ7GG8Ryzwy0c97eTyiDdXb+hjTps9S854+xraFVrymPJ80U406pOLk9Rhj2JnbuLIDP0Old0TXquYEt4T3+uPf4HkA3V9caXcBEEYyCCZtEsClLD1duGFu+r+ykOPON456eknNI5yF33TTns/hDnfnb9wH3vB362RLAd2cvBnnjZIgnhsxssPCOhCjdQDm3w8ujj4GGmngdukEY4O++TX1p0yBdMzNgC86fD17mX+OE8OnYwfgBQSwMECgAAAAgALWdKUgiPmWw4BgAAbg4AADgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BST0dSRVNTRlVOQ1RJT04uM1VUBQABtkgkYK1WUW/bNhB+5684eA9LCtVO1wFdt6KY4iitV9c2bKdpgAAC
*/