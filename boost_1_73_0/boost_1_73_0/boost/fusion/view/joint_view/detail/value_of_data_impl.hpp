/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
SXb1h/UPZ3O2dUl1HyTjeiHbnjTxWMCtFY08HrvsXJLOiS2aVcVypQ5xxIqENpMD4Ztk3duPGifEL5y4ki6WV25dCiJnjC7VPmk+rQlA35NwbvwqivdTnaUVWeFXMtVsGTeuvmMKQ92XlFElFoN5RpBJ1qMakXv/O/qGa/svXsAUj4z48jZwNVGLJhIV0EHW8eSGYCwopD0hNt0osGdzzw9NF6ImBFALPAjfLg/m5oiapaS4kY6ysIVafQAmzOSeoDYvYCUpe6Fkv6wwgEZWilT3fPGlmAjkArS0gkhZAL6WWdjVaJiUD6xPk7k6Bdc2JJppjyw4NDJhLLJv49Eo3Y16/y1ssIVbHzGDKYDMnv1eRJweTrC43Eps58tSU4OlRwX2JF3B3Dq1FpJmYR5G4Kz2uMG+EppkuC9eyE3upM8pBdFQg3yUCBA5dxIv5gkhHq7DkGJeYReMBXKMpAPxJrjbCFMkz7+N7Y69krYueSPOapgp2O7C0o3mEiz2r/0iyXCuycIp5FkkvS++VnxS53p9Xz+uZGVGGjEqN4Mq6TdVLhrc4Z9ZxrGVMHc0m1eeUrUiT2tJYDXyOjljk7hOXSI40Hl23QSc3Ov9VHtQBMj0LHJtgQRcMgYvSsC0ppLY2TxgbgYBTevAEeGU
*/