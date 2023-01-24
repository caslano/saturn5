// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_IS_XXX_DWA20051011_HPP
# define BOOST_DETAIL_IS_XXX_DWA20051011_HPP

# include <boost/config.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/preprocessor/enum_params.hpp>


#  define BOOST_DETAIL_IS_XXX_DEF(name, qualified_name, nargs)  \
template <class T>                                              \
struct is_##name : boost::false_type                            \
{                                                               \
};                                                              \
                                                                \
template < BOOST_PP_ENUM_PARAMS_Z(1, nargs, class T) >          \
struct is_##name<                                               \
   qualified_name< BOOST_PP_ENUM_PARAMS_Z(1, nargs, T) >        \
>                                                               \
   : boost::true_type                                           \
{                                                               \
};


#endif // BOOST_DETAIL_IS_XXX_DWA20051011_HPP

/* is_xxx.hpp
LHEhfh8yjc0dsh74NjMFT6fYRTSyQDWUp6yYomEAZuo2s772mts2AD4FlLrf66NJXLhjoEIPOOqq8vUfkkA9EinxhOfZpSeozZ0+ajn5Yw3HNdjfjrkzGtdT4DJSfxx79v5seiPSj0mzoNFX8xmkTukSEV4tE+lFO+TF9bl5mNkhn6+k8QGw9EC0ZANTQ7jpLTFnNCJVQYU3ZC754WpZIDNKPt2+7k4Ct1xq/dINUtbazY9xD4fedLdsm6cWefp9DH6GG2YNAOQHgBWOD+F2KoVJxiBvI6CNE2TSL0bjs1OUZMzrJs8LRWkpwG6YAD+GLkv+wb5T8nvrfSsez0MG8bfjivRGJTXEGWOqTUjPFF+A4CblK76iDb50EBUvVIYcqtxPaGOSGZ6QBsKkdGkNH3tpYjycX7IhHaCygWUMGiOHNgAbCInOSkS+ZTbnM2qvbEy48zwMBUnWyrSOmbEfgIO1Mp9U4kxvHCONe0HXeLVvtwqaAJocv6dHaPt7N8fSQH6ULuXhY2wmaNuemFlsbui8UFa806s/bN2csprEh8+y8M3355tYbEv/EYqeKCjT6BYjggetbSFtU+/rfiBpvU/s/rXnqrw8slDlXCBvQ7zTWKj/M/jtDKThZ0F5+gmzCc+2KoWJ7FZtPSBEFyCqlU90XCy+q7bc+t7L/0SD5yFbSrI2o1GQ9WkT23qJabxtbE0WJJaopgcYJb0t
*/