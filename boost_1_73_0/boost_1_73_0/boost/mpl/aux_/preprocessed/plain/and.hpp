
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
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
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
JhK4yRMwznIDbZlaGFhhhZpWmcCygSJfOvoHmCa5BWGhUVsNqq5A52Yd0HpmlHBOVvr5pN6Lb++m3vMQvIuz74upNxqOj8efDo/Gx54zsdeQC980/Ve0UcdLxRr/nTxuyewdp1SqiwYt6NArRbMko3E3EGfEJ8fRoO5R52kDzqIgUosabIbgaJDR5JZIBuuZTFna4EOLpQQbraySqpgwupfw2kC7qzT02Z994LM7snX/jDZCp24PfO9+eru4ml/77ExK3NDrfb7vbpVbaNhKGZ1Sm5/b0EXuZr0r/MqV/01CxF/mEPHn4fCXL9pvUEsDBAoAAAAIAC1nSlI4aOaqUwEAAF4CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjIwVVQFAAG2SCRgjZJRa8MgEMff/RRHSh+tYw97KC4wtpYWBg1Nuj0WEy+JLIlFTbt++2lCVhhjzBe58/8/f+fJHVpXCIsx4aortd8+8HrRRtqYpOssIeun7ethvyKc3Q44G7VkRmbw3CjsHLVKIuHFEHiFRXNGExNbupPXTyHwTrQ4lgaDzig8iwZ0Ca2yVnUVlKpBKHXT6AtKyK9QaS2HrDez0Q280G0rOhkTSj0WFL1pjuPdxxBTeurzXw4WPg20h/kh
*/