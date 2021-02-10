
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
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
IdEo0uWfBAQ/uSBz606j8Sdzanpk/9xkrPHDuZTC3touY51+TZdLiscnCCN7nGYUTfsPrRD2LsxlGtUKvswKpKn/jwbDxMUjGQhl+55Ak4cV55+xs8Awb+XhMHfIB+lbni5vIQJv7h/KalOsbshP8bCtznkyfOak66lVGsEOR90cIWwCZONxnEYevgO00sErooEr11p/xcT7hCWCYbTeqtD/Y5lvqR1rjr3duyT8kzJ4+Y4H2Q8dzkmVok93CVs/3UGwk7C8KHcJq56LHDYJi1tc3iYsbj3cfj9uqoSMXoQEP6vzy2f9C1BLAwQKAAAACAAtZ0pSJNNDXewBAACuAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDUzNVVUBQABtkgkYJ2TbWvbMBDH3wv8HY6EUijLZCdOtxhh6Lq0KXRNyMzeq/K51upIwboky7efbOdhbKOMgbF1uvuffnc+CUJHSjpMmdCmsP7zivudrXOXslmWLdoX3E8zttpUpJngZ7/gnYSJGtfV3m/kkmSn49H7COIwhk8yN+hcwD5LwgSyDb6DcAJPdgvDMAohipN4koQh3H/JAjbN5EsCvWEUDseDXH0YjCbx9TCefOwF7NYaQkODRzQvVCZwfd7K9mufm/AH
*/