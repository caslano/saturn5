#ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED
#define BOOST_MP11_INTEGRAL_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <type_traits>
#include <cstddef>

namespace boost
{
namespace mp11
{

// mp_bool
template<bool B> using mp_bool = std::integral_constant<bool, B>;

using mp_true = mp_bool<true>;
using mp_false = mp_bool<false>;

// mp_to_bool
template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED

/* integral.hpp
6VyEl9PZp6maDjtwlKMKyMc62a3Rex9ajjP7ZI+e13mYDJX2rXybxvrMaGz+5/wLUEsDBAoAAAAIAC1nSlKWkKK5MgQAADAKAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQwN1VUBQABtkgkYKVWbW/bNhD+TiD/4eCsaOLFlrN22JaoBhSbboRotibJybJ1EBSZttlKpEZR6Yxh/31HybHdNukcTB9sSXzuuRfec5StWanTpGR9cggX+D8DKcC8/PH7U2JzMZd9Yn9gq49Szco+8Sf+KzLIWKIgYn/pA+K5YUQ6nYzfpZXKiG1tsbbVmJND5A6ZumeqU/IZI7ZiRbZCQFm/TPNZnwTU927BsMG3kys4fd37AU57vXfqnegi0w7SttbmNe8g40zoNW9aP2yI+6SQxauNdZ+ALZIcU93EC3OpwOTUeJaCQc7KMlkwxFoNGMk0E/d9EoZePKBBFI9cj76paZsFO5V5nohZ4+/Msl5cTsLI9c9eGGp/EkRWnU8ng04FFUZzVrJUMQ3bQDK5sEzZDbCbIvmGE2/XadUJXzPF5yuYJTqBZK6ZAr1k9Y7BMinhjjEBrXIpdYvY9zUWKQoltUxl1icDx3cOyDSkQR3IAfGdMIQmnGY369ofkF+m
*/