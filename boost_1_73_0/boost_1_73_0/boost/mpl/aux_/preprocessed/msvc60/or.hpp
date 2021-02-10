
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
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
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
        >::template result_< T2,T3,T4,T5 >

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
lKJLQqntdqtM3pWNhRiMZ8tsMo8HTb35bJGJmztWO4Sx2QO1qK/kqqLGphVURSCHoSRsziCWyuOKyOCpL204BfnRxnIJcs46RmGA26b4N1/unA1W200CTS8sjvudRDC2PsT4gzCCFx7GxeiNsXjm724jBq/pYjmZPUcw0pp2/PpcnEfQLP0oIMWeiM3jb/MFUEsDBAoAAAAIAC1nSlKYQ6dKNAEAAPkBAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzdVVAUAAbZIJGBlUV1rwjAUfQ/0P1wUXwQX3BiDEgoy3BTGFO18z9JbW9YmJbkq/vvdtn4M9pL7kXPOPTdRhIGMDpgIVdrccfjB88n5LCRikabr7oD3eSreZsuPr81cKHlHKNmThmIIW/RH9JNQZiiUx6Y6832mSbewa7z0O8JrVaKlC8F0BUNCJ5OIgqhhwrUEZXWNyc0OnEoqwDoqSrsHj3TwFjPIvauh5zBF9hxQxtW1tlmvGks5Wqy26XIdj1q59WqTyqcXHnaDcXrx0zndoS/zM7RLgM4JPVCB0D4dFDrAN6KFQSgcDYQ6dliWQO+dNy5jA8+PrPinVo135IyrEtGuwsOhNSKnD9NILFygGP45jMQX7zWZ7dlWDObgKzna
*/