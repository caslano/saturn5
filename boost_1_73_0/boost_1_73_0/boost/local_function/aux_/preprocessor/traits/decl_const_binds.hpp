
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, \
            decl_traits)

// Expand: pp-list of const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM( \
          BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES \
        , decl_traits \
    )

#endif // #include guard


/* decl_const_binds.hpp
8hgg2oBrojNWKfgN5Xbsef3LZ+QvImdInFRfNpMc/dtp8HNsOp5egTCVU4K8ZQGqEXtvko8rwSlkLXcoikLmaTsqjm9vJ5g5w3jHKwubKDVqLwSKAawcaQhTZScf4NRCUIjoQRq68lytwAjwNQgEPEK2oyMPWBEtylfnPnuMaRGOK32OivGCEYKNhQeZEfceq4msuGbMmAKcqg7hBPPeLqLONZ/rdNcTfarzLykrpZoEUSIicJaoYjrPdq2lIqCmeTe7RUTmlbHZpkZlQufomliO2yQ4VXmM3DcIPN5mmcOJQ82DibdXYU8HmZlTeUkZDsSolAIuapqfgD1Hu/x7Zc8vHssJ8bMF2rAWDPNhmVBQyQ0M0OgKIhb6jadYgZWAN09jYUtnEnRqoxaksU+PUAWefmnAUZg+uy40uhVK6zBnMhYdaxrMYYhSDFIi+DRkG48zgN9B5C0GRAO/YdEZ9gYwD9/HAqP0Z7AIBcxeNmU2Yp/BJq5QQjzSKywYo7xbFVAEe6l2PP3gkAeeffUIRW8wkaaP2oLhEx+KUgMDkCMP8etAE1EI7+TbWG1oYrJ2jhPQemAFLjUtyvm93HWRh8cGELvjgxvuwxFCxtsLxYMjnXWgqQJsnX4TFWQ5ZBZxgebEkluxkd3CDeGJ
*/