
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
9FpBl4Qt0Aahp4SN9vCCaCH0G0dMsRuwTDDG8Z8O949V0zpyuati8ZAu1hyus13ttj4QyXWaAhv/ge+6bio8Zu3cfboJxP1Ndg/sNhCLJH0MRPacLGAZiDRbrcf+74dlFvCcA72SX8rl4a/8C1BLAwQKAAAACAAtZ0pS25qpnu8BAAAyAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI0OVVUBQABtkgkYGVTXW+jMBB8t8R/WFHlpSpnSHLtYaFIVRs1ObVNlHB9d2EJqMRG2Eku9+tvDfmQ7ngA1l7PzsyuE4vGZtLghCWVKjR9vvB40G1uJmyWpsvuBS/TlCX8upPwPvmG3cAa2z22galyZEmLTX2k/Vxa2QPw6FsEo3AM79rCm86rosIczMFktTbInqVFAekO7yCMKWcPwzAKIRqLcSzCEF7eUtZXEOC4BqYLeCG/kL1KWjhjnlCiEfzcKYhihzIUUXhGmaZyI8AfRuHwe5BnD8EoHt8Px/EPnz1mGTY2WEm1QSPg80iV2JNWFpUNXlFtbCng/sE9bllhZiutBPQSzonpsUFH8rflpd3WjFzqbUj4yZbOr6e6ctm9X1kXUEova8JKaxs6cA4hUXKLvZOdiy2aRiuDcKhsCX5V17iR
*/