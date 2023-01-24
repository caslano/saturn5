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
3wT1C6rAna7O/Muc5KRqbrrG0KMqrhXdENgKvVSSIZrzcGK+5L1UDyRVTAU6rbiRuN3EnWRyEXg7eTJ8AHZSBm7BaGYukttGqOCtjLSoIqcQFgMPOXHkHL9nOWCUyL+3ieVxaSTysawWNvGDk1jCm2VYb6CEN76WGF+BeeVTbbDIdGUBS3hefPX+Al3Cm3+XpV/f3ETnuJCiwnyxf+j5uXDxEfPx/sR0C4Lu3+8kHbsAUpNAfpJUTs1DM7NUbac+NyHnrhAvZnyEIWATo8X0j7sq6DybO3mHAnLzeySQMwnIlMReA/NyJxnKvcvJc+Uscgr8DbSOxrxm5AtuANIzndpoeoZmkQRAn7cNoNXmbga0PxTQf22VgN71bwHou4PuhNsY0F9vhVdb3qYDOuVOC9BtnPUA3eeqUEA/Iz5idrlKAXrmHQzoswF5VbQdyKPES5ibFZhNIDLKMNKEsO2qGEeQ/mG7gvSLkySkB1qQztEhfWc0QTpHQtpV8aSgz5RIoWEop0c3COX2FpTf2wKgeuuuxtB5zhYJ5bvnEDqvuFXWv8JXX79Vh/LW2y0ob4qqB+Vd/UKh3Et8xPyon4Jy4u3/EJ3vibJDuq4Az0EkIULPj0BAX6wA/VKtAnSfuxsAdK4O6POjCNC5FqC7nT47oH+PPBegh2wGaGXd2Rigu2+WgI6cTYAePoEBHYuvDpigA3pCgQXoByPrAfrO
*/