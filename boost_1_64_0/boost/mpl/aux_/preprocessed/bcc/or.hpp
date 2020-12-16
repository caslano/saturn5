
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
eShLfdrRg+FMZSGr2cohLpBqo2PyLK9SlPLUpSXd+IzJLGETP3CUi8SbjBEZyUZ+ylGXVnRnOJNYwvfs5TTXuf17Oc6z5KQwZahPJwYyllmsZDOHuUCqzdY6WShIRRrTmaFMYwXbOcRvRFusd16iKJVpSnt6MIZZrOUA57nOvVvFSH4q8w6fMIBxzGc12znGZcJtjsWz5KcCDWhNT4YzkbmsYhfHucrt2+UdL5CfstShJT0ZyVzWsofT3CD9DjlHXqrwDl3oy2hmsJodHOEi4U75QyZepQS1eJ8efMlkFrCGHzjEbwQ/GBsyko08lKYWbejFBOaygX2cJ2WX/cjMK7xFc3owikXs4iypdvtcSVbyUYF6tOUzJjKLFWzhIOe5Rbo9rit4hVLUoBU9+JLpLGUbR/iNP4l+dE3GM+SjArVoTmd6MYxJLGYTh7jATW7bKzfJRG7eoBqNaUNPhjGZJWzjJy5wizv2qXNkpSDlqcW7dKA7w5nOMrawm6Nc5c79xoyXKUE1mvMhgxnHFBawkf38TnTAvPAMgb9EHwVxkAQpQargtiB1cHuQJkgb3BGkC+4M7gruDtIH9wT3Bvf5cvQH3MH7UPCwr956NHgs+F/wuC+feTJwb3zwlK84fybIFDwbZPZFDM8HLwQvBln8ObysQbYge/CyP3SSM3gleDV4zZ91zB3kCfIG+XwhdAF3AxcKCvtapyJB0aBY8IYvSC0RlAxKBaX9mYsyQdmgXFDeH36oEFQMKgWVfQ1VVfcOVw/e9sceawa1gtpBHV9xUi+oHzQIGvri18ZBk6Bp8E7wbtAsaB60cI9xy6BV8H7QOmgTtA3aBe2DDkHHoFPQOeji3uMPg4+Cj4NPgq5Bt6B70CPoGfQKegd9gr5Bv6B/MCAY6N7kwcGQ4NPgs2Bo8HnwRTAsGB58GYwIRgajgtHBmGBsMM69y18FE4KJwdfBpGByMCX4JpgaTAumBzOCmcGsYHYwJ5gbzAvmBwuCb93jvChYHCwJlgbLguXBimBlsCpYHawJ1gbfBeuC9cGGYKN7oL8PNgdbgq3BtmB7sCPYGfwQ7Ap2B3uCH4O9wT73Rx8IDgY/BYeCw8HPwZHgaPBLcCw4HpwITga/BqeC0+6ePhucC34Lzge/BxeCi8Gl4HJwxf3UfwR/Bn8F14Lrwd/BP8GN4N/gZnDL9IdhFMZhEqaEqcLbwtTh7WGaMG14R5guvDO8K7w7TB/eE94b3hfeHz4QPhg+FD4cPhI+Gj4W/i98PHwifDLMEGYMnwqfDp8JM4XPhpnD58LnwxfCF8Ms4Uth1jBbmD18OcwR5gxfCV8NXwtzhbnDPGHeMF+YPywQFgwLhYXD18MiYdGwWPhGWDwsEZYMS4WlwzfDMmHZsFxYPnwrrBBWDCuFlcMqYdWwWlg9fDusEdYMa4W1wzph3bBeWD9sEDYMG4WNwyZh0/Cd8N2wWdg8bBG+F7YMW4Xvh63DNmHbsF3YPuwQdgw7hZ3DLuEH4YfhR+HH4Sdh17Bb2D3sEfYMe4W9wz5h37Bf2D8cEA4MB4WDwyHhp+Fn4dDw8/CLcFg4PPwyHBGODEeFo8Mx4dhwXDg+/CqcEE4Mvw4nhZPDKeE34dRwWjg9nBHODGeFs8M54dxwXjg/XBB+Gy4MF4WLwyXh0nBZuDxcEa4MV4WrwzXh2vC7cF24PtwQbgw3hd+Hm8Mt4dZwW7g93BHuDH8Id4W7wz3hj+HecF+4PzwQHgx/Cg+Fh8OfwyPh0fCX8Fh4PDwRngx/DU+Fp8Mz4dnwXPhbeD78PbwQXgwvhZfDK+HV8I/wz/Cv8Fp4Pfw7/Ce8Ef4b3gxvWfxhFEVxlEQpUarotig=
*/