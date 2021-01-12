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
7Czxczb7jhzfdkeYtp4vkXxndejh3nt8LQ8rFy6YrenVdbBTxM1E8i1oTvO8s9iRJXKUezk0LZqXxA87iV/C8+5Ofbip41mnufJSdw4mcVkZy6+JJbW1fY7kea3enyN2+RJHtSNkN59WE7ZjFjGmxNclFy+U+ahzDrXtlNha0VrsWGWTRV50QgYj45F5yErkeuR+5DlkN3IAiThB097BLWLz3idOUU+csr1lV11VyyW7D76v
*/