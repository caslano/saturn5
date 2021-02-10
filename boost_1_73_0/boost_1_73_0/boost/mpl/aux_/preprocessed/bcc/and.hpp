
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
1wSURRjkzSvq33gBi1ekKWQJRMFeO4mlpfbdwLgg8AAKX3HBwkEjqMC/C88VKnum7CyK9hhkvbsS+hCJ2pTdUtVlGbH+sI8k68MB41wE9JqEf0bJWEhojXjQ6YxX3NomO/NHMxL+Xqt7KKXfwtYnury8RppX69ml53x9c7uN+vE4QZKefOHnKbeI9AsYmR+JLwnCcwfGh9txiLkgO0ACQltoFwbpQyuLBiqjnRa69N0CTSkVdswRbLgI2hy3HsljaWORa+tm5BWwXvCbp3O5Rywz0lJz+eXD7WZ187kXLIWACq/fRm//snVetgKvqvI0GqKvtGkammtzoGgSlNAZZL72/xk2PzCw6/9ojT5NDJ8LX23zsE0LDofvnCG1kfOwdd7q2EorizLDnZiK6YRP+jlLRuOdADHdxcBGLBHj3QSgn0wmg3zKBqNJNhonw3iXiQEuyVTwcZK/mE7PuunHuWXsh8h9VopYYI8F4ovtqWqi8x/8G1BLAwQKAAAACAAtZ0pSxbxdTUcDAAA0CAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNjlVVAUAAbZIJGDlVttu4zYQfRfgf2AVBAssqkjU1XZtA8a2QIxeYqzdzTNFjiw1siiQVLTu13coOXGy
*/