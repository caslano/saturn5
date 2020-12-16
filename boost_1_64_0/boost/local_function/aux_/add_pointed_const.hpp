
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunction to add const to pointed type `T` (i.e. converts
// `T* [const]` to `T const* [const]`). `boost::add_const<>` cannot be used 
// instead because only adds outer const.

template<typename T> struct add_pointed_const { typedef T type; };

template<typename T> struct add_pointed_const<T*> { typedef T const* type; };

template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };

template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };

template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };

} } } // namespace

#endif //#include guard


/* add_pointed_const.hpp
L2TXrNj+S+SVOe/cFfFuk2+fXoFnxesM98bVB7r+/l1Y1I93Hmoyr9PIp1k/oWzmt6+ddfrOfkMuCRs/pPzkI1m7GFtQ7nsfPLSlQ9awv0377vaBr9V9voyTTXsnm/xONvaDt3Vvb3vfaU8BJxv7TnsNBL93gP0eAc57AZy2tGlj/kcCdHGtJ2FtTWy4qftN+am/q0j4knCx2W+INZyPzf78SG2qwbmwjJx79KcFoN8Ilx5guIwAw+UEGG5qAOFSkPxSrv9oWff1fwPLyLknXkEp8WaVc8ebCcvIuSdfywLMV2Ep+n+RetGi3Pp16IlXVEq8RoQz2FjiXQI9+SouJV8zI86FKykl3AlL/rUjzvl4SPL/ICwj56Ife1jn16/ad4DhUgIMlxZguPQAwqm9MEq5/m+lXR2TdsW5GS+nlHhzpF3NhmXk3GzvAeYrvxT9FaR9VJT2UQma7b2UeK0kXmuJ1waa7b2UfJ20tvdS9M+T9vKwtBfOTf1FAehX7TvAcCUBhtO+DixcTADhUoywXztff4m0l+PSXjiXeEgp8e6X9pIHy8i52d4DzFd6KfprSL0nSb3XhGb7LyXe1RLvGol3raW95JSSr1nSD+V7bMHAlyRcJWS6hMsl/y44DsbCCdAIMxF2hFPgNfBu2BXeA7vBO+CNcDKcLOGmSLj7JNwMcV8i7kvF/SRM08VmiNhvSYANkBa6vHTRbo3zG2Br2A1eD/8MjfTnwFthdzgY9oCTxX0O7AXnwZvg87AvXA5vhivhLfAwvA0eh7PgKYkfRh4GwgSYCevBLNgIGv6t4VDYFg6DHcS9OxwBb4PZcBYcDR+Gf4EL4Rj4AZwAv5B438PbYT3K4S54BZwC+8NpcACcDkfAe+FEOEfu65W62IgQOx5qLj6yVMoxj3ZQHt4Pk+ADsBXMh1fBx+C98AicAZ+AD8En4QJYAD+Di+FR+Aw8AZ+DZUnjeZgIX4Qp8CVDL3wZ9oKvwluhob8/fAMOhivhJLgKThH/aXANzIdvwfmwED4F18NnJNxzcCNcCd+F78NNcIf474Kb4V64Ff4Et8Ewymc7LA+NcLHQcK8m7rXEvQ4sgq3gTngj3A0z4F44WcLdBQ/AGfAgnAc/hgtgMVwMP4MvSPiX4RfwNTn33J8xch+8YnN/HiOcC34LK8LjsB6sSv03hvHwEngC92awHOcdYTTMhBXhKEMnnAhj5T6Jg0/AynCJ6FN2HKRdFXrWrcNEaVdVkeWSr0TjfoA15P68CHaHdeAAWBdOgg3gwzAZFsBGcAe8FJbA5jCcRFJhe9gS3gxbw2HwGjgR/gkuhe3gVtgefg7T4DcS7kfY0dDn4lyuY5ln/bOs/U6AlZHFch1r6Y+i4VswHhbCxnA9bAU3wKHwHTgO7pf+7kPp77bAB+FW+BR8DxbB9+FB+A94BO6Ax+BO+CPcBZuRnw9gW2jo7QQ/lP4x3RDJd7a0iwikk+R7meT7Vcn367ABXC798go4CK6Ew+Eqi97C7c56nxa9i0XvM6L3WdH7guh9UfQuFb0Z5tpBworeKKSX6P2YcOXhJ6K3WPR+BpvBQ/BW+JWU51Epz2Py/PhW0unjWZ8GR0k6kUgXSWcG4SrAmbAanA1rwTyYAufKcy0fDoYPwWz4sKd8dFmnJGu9DP0Xi70AtRKurPt+HA5jYTasAUdCI53DsDYcDRvBHJgm7lfBMfB6mAtvguNgBhwPx8EJcAKcCO+Es+EDcBJ8SM6XwAfgs7AAroJ/h2vharhR0nsHLoFbxP+A+H8Mt8Fj8H14Au6A30u803AXNJ6Du2EFuA9eCvfD5tAIlwoPwq7wY3gTLIaD4KdwsIST9iFrl5jraNM=
*/