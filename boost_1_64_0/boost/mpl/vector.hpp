
#ifndef BOOST_MPL_VECTOR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_VECTOR_HEADER)
#   undef AUX778076_VECTOR_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME vector
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_VECTOR_HPP_INCLUDED

/* vector.hpp
Lp0eJvRxCG+jDzON0ZC0NwgNhpSplqCSeLAm3AQ+PmoCTcC/VritkOGy+VoTtOFB3p1tFft6+nGBplTdUj5pE1FtJqCwZWe1UR7cwE7kdwdTjIj4Okm52pgAOb3TJqeXdU7Rfjum5jA1bp+jtulqjqp//+N/lu2Qpf/h1PgOWHWRCdRpmeAMbthmUeaYx7kxbzCs75w0feB7KFdWps9tKTV7mdH6+ntYMumh7NcodqZVtwU0ep5lxSKwibXrfsZXKOo5LM23xuN3NJa3Q+MZGJM19/wEiUsJhbKqsIsICJXXN02NDiM79wCAZr50u7YKb54JhqTHHEctqZAefmV1iPa5XGsMEm/9WziRdhkKmg9Vo+XqiwixHTHZi/u0kf9WxCVomjzezL3p8ePfvN0kef2SBPXLU6jfOkH901Oo37lp4vilL7njt/9ZevL2Q+7E7e+vPxC3/Rv/cCBh/NYlH8bNNy/1RMcP6hcfXuT3TGE8X6cnHs/JYTWe+PGOdruVR77o+vlpZvz5cCeHLz1+/YbW4z/r7EMD8fRfaTGYj05oHl7pEaiYHPy1wQCk3Hl0g9KiUHfCJHgFbEajgxPsiWBsOWyMLRzQFPxZT4xSAkO9OPiqiliwmJmTXmiwx/+/EFNx+VsRiQWY+wVvRCT2Y3unHRGJHVF97baIxGbgJs/5yM4cfG03Fhv52dqOvhvBreuFoFVy0BGl+FdUFOAIKxRZaZDHHjEyeJKWtU9QPlnOh4a+L6LR+5SX1WxCn/qKyqb5hkRROuGb/w+lroSQeVwf0XguwNjX/Emq/NhyhnForx+ic06wkTMzQIjpYQ/AsJNHnzv6Hyv+9bcH7P5CyGCOf1FkRaHg0MUGvN1irt4uT9TmoGsla8C8GPPgUWLYTIQctBvGkX14ppLLYk6fJndUFqm1VBYjq+tmEcVmq2Ign27RtnqP7pA9/5mRo1b2Qs+ibCG67RhoEYFX+ke01x1WYR0DGRFlfFzmX6oHKfy9TzGyfYGCCFDO+xT6rdR3HPulbo5QtnlxFliCFFAEenuUJgDP1Q7Pu40x52U1shWB0/sU9kuhUPkeUoNI8McZGy7P9plTmAH9qEjkLO7w+vA5eFhk1iDqfXefPQI9oREipR8WWUS/qKw6UHIdGGnbCmxlcHFiW9cgoP0FvqNp7WL37+pke0rw0XwJ4/l9s40g6jzcj+AlfjmJSeI3dcI+LuU5C0wzVt4lgzd1A1bRV1yc+2br3w8IejOdEZlwRtX86nxPQfpO8qoWbkMN9Sis13N0LqYtlQD/Vnz+xPGXuuC3/f6z4JFrH/TLRZvaAmNMy69PjuHixUfyx48/JbbycGGvnNA/0NJamlUb7+URlwqMVFnka15MGp/QZiDNH0SkUYaOtUIbVla5jqqgjDNalUIwZfe6omPBAtlkQ4GHrpr2bD0kb56Q1xZoKJtLcqgiXRLnFmEyAKqwty7K4ZIcOKhBlQT/KLcB4TaYMVYxKtfWe5eGiN67NFi9d6kY3gUlhVUyY//QcegQjKAiT+WZRF6IhiEI/AEoxY+5cUtLYcSLku0N9zcf4ecytv67kdGc7h/4qSPa78b4fBKeO1IqiHDsej5gcHe9bT56OkKXGn0MhNGADeHNzOqGbBTBkFR8ozwUM3z0B531HGN+kgG1KsDXUzaHPu9GPR3nqA/3r4IWnWKb5QEUuRITN5j5iAN4CDvBLFRcgHwb/MNQX8M/jOpjiUZyBONh0sKF6x8lRPYf8hHnbzT0v74EfUE+5xV6OKWqcI3GUP6MiEuhNaEJfWEs5rxwq0C6IdBbVcmaMeZndQ2phMC14t/W8PkPNpchqgrr9SEFq6iOHTkR44k=
*/