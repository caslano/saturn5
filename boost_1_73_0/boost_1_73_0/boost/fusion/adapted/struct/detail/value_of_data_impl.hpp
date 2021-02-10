/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<struct_iterator_tag>
      : value_of_impl<struct_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
ZpgOKmKYDoZ8v4WY4nKYLVE5LbxG9lm+ICL7LDuC/xSqq1mI0xVeTuy1EzdxWjmvd+Z8Ks/uKar6wZub7ZmqJHsuAnSiaSpuQz4VlcpZ+pPHligCnhqyHy0xZD8UkbNFroYWPfNTFtnIsns3gzhP2uUO+4Q/bnUSvmK7nQhkUhrRftsgOvM6E13PU/jsBmJjFxGYuIUIpZAaEbzxMghvbOwgxO2ArpeOiK8zNF8YSVQj3Vyp+TfffGP83xyPVBtUVsRpz5nInYBBjHEGflJFFLGEL2ewEydHTFNXc5ZB+LIMH2HPMnwETF1UEb3sXKSkHNQfcQomUqKax+OsWY+QEdniiVgQOpnGZda8Kho/cW4MbmtK2vheEiIp4JRwoSrNcbqgCHWDiDPqiYltBE196YmVyMU8/A3GjsghGctwbN+mIFlOROi89wjVDjTKbuK+1X0mchbQqh5BZ+T8Fx/Ejcrfku4mnN/ysBNznFXx/uhM+JoE+kSgNmAlvLUBN+H3SDbCX9TsESWGuCPUOmUhBsRSXf1BkNvILOtcsfB+X+cl8eKrQ56/9qBPgO0RJU0ESd1xd48oml6EpnkDTovjRPYJ//dVXUToKzg9Itg9bBBwOvCEePs8TcKfYdkIb5HcRihfOIDACy45nczd
*/