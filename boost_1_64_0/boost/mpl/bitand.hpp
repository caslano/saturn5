
#ifndef BOOST_MPL_BITAND_HPP_INCLUDED
#define BOOST_MPL_BITAND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitand)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitand' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma push_macro("bitand")
#   undef bitand
#   define bitand(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitand_
#define AUX778076_OP_PREFIX bitand
#define AUX778076_OP_TOKEN  &
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma pop_macro("bitand")
#endif
#endif
#endif

#endif // BOOST_MPL_BITAND_HPP_INCLUDED

/* bitand.hpp
91Xpgnsgee1GzJca0pgg3cKIpeJGPcSNepL58wprZp+Mnj9C1jqyldB3WFWWk4xbUb6cazsrubahprYTWHpahUH85lN6TA0GiS4YzS9JonsP6/RkWO/vEFh1kHKW4eJj+8S1rqBQHfDgT2hDLudrH/NKdmZVnCjnVYr0PBmQOfopv7TFTeoUK1kolyovLLZ//4Rxf7mBaIRllaxVN/CYvxC1bYV8cwgtpKDWVgIAMZ0oszWvZOnsAVwlFMgmHJZDBVL3Zetd6ZJl7fhTdBqM+nt4YX1WxUKIUbXBq3OtcocU45QUb/1OSPGmHNhxrhNAH5Wsd9v0jNikgqZLNwPJzZWFm/MKa2f3lqK2W7Sbp+iNXGZb3VoWeNEG3AYrqH+vDvkgGuGqanGIbiRJg8434wqAnXyFiWj3xSF82k2upoapIUdNbGwE2xDTeFJpXJTzHWvqYiYtDvGHwIH+9JDhQBtpHD7hHk0sug/PcmMEV1NYzUJQNXqrmlUCEYKqWQhqfEyFoJ8qWXHgsPsWTB2+VMHegTwSQH+reS5Y/H8Z6F/50/1CnLVDRAIcUguQr/711rI+2Ji9js//V6sF+8f+jeiu0fmSbyby3aX54te6wEon4XnBNWm4qSO3xe3IfntQMp4fP7wl9wI7JJD36RA19cAdolrbPxz4xz3NEqnHh+XShxGgx+vTN8v6ERUAEeDCkYc9KV8k08losURJ8fu2jPTD62atVFgIilIDrRVRTYlgPJGD+92C2da2/j4zsb+na39fz/d//Fr7e3WC40H0AtPfyLfaybcI+ZwuP9PX5X1a21+2i1eDABT5qVeredq9K3mO3M8u9ZnN1Qfie7Jv+hSR3ddDn57RsYY+1lOyWDz+ijb97kQSnWJIpFlvfuXLzor0N/c9Kyb8eP+zougrz4oW6ZM4fg7X8VNOLb51W6v8orchDvJdvu3LUiZes2/KHHPXP4MyTrzDva8Zf4cI2Sz9O5c08bOeHZtZ0Rgo6+ob1x8dnJLC1th39NaoLvSZcvNNAmJew2WgJjGQNzYHYQ2ewEXNDXrh/4MCxZznuI35x1b+Z9yRzJAaKCz960kMaTaXd+JpftuBEGRvqCYOOYioO2BaiNvnZA9XZogp6VaIjTkopEH2rB3eisHBZsKfKvyPCrPH9M9G/LtXPfQnBGMljQvKGwPUN/MHmofSkyuJBHZACBHKuvlXsP82Zj15y865meHmPrdupf8oz8Ag5ZZcGVk33ye5mvtU2fy5JExthzrmxMA70npb221V8dMLMu2XvaSTgP02jbNDh7dRViyMsaB083jU0VQxnIG97wCr9AA72QHWlTNjqAPgfbsgSgugvRLy4ouyM2TUcWA0PoZDz/mhurdYXTgR+8NCKRvC2K2iLR6ZEpagZrtlz1+FyoLddfdzwUMJcPPcdvRvYF7HdSS/NpurTZqWFIYXTwjx56yFMDVrDRDYG3BET0ogZAD2iuUmkNpXnNt0pAEjBSI8fnohbObGl5VgLPrKJwz1TnrV2KEWY65XjR//jJxli0iqXOpr79otqV315N+UOMDCGSOD2yn1bwgYAobMtK17SFICpWH6N1hq2rE84LY8U4ouUDNxhMIQStIV0H0iqDOsc/ocAZgy34A6lTPBbYziSkmWoYAeQZNyYgbYEWxIPDbgzLAmBMBbD9UxpBVHJJiXwsuOd4TjSbbbwj+kuDhFYgHOmZ9dt9mEfrP3bhexv3FM1sIFKUCjyLYlcdRKglB6BfNa+1WTxApv6TdR9DnNxUkTUPBRk3Q3J52AgneaJFYUyF1irDbIWuIZ7SUv6rpwjLYsTU6UHK64pxl6xkPyXzqoyVwmq2fK3uszwz8=
*/