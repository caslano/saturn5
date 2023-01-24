
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
pEsr5ijXiuPYmfeyI+Gf+6RW6B9M707pezlrWadDIG5GAm1Mm/pCtzKNX7u9LwdltH/Mi/roK7stoTQ9y+QLAhX1v5lXyXkDUQJ/1lRsgTdELAk2p3l3x0uMNNd/x9rvVGJNKxOtjtJnzp9vgUbAcmEMS7DDrSuJsdBzr21DyvVQG3eNr1yumh1/ZDiMyr5fifUXTIqdwD5QrUs+FXalccf3Svzy0Yqty5XGuc/o/aMzdn0KwVdMEUmAGZeULuuNKcRZ7kDRG2r0J2ZnFXEMu/mz4tl0mku3tiLwYNqeTB53rnyZpqFpa224IkFApyvMg9ygO3O0KipRbHn3FO83nncMzVcaR26yWXQyM783EDyIchSDiJL5k+pe/8ijHodfNI2lmsXEH54pk4d5GlzAcJNzd6v2PD6TZDWJlxnzfEaaGoA/jlJduw3/EGdww6LOt8kHYzxrHCRVWYre25k7VdGIn0lvKIld+gefvTBpBtxxVclDdedjFrtlqkyrrOSqliCDivs66LnBPx7t+W4aDJpzzqxVTrvEowJq31+tHz4KuV4gYafeu2nO1YUsXijk5tWmHTy9s2Uf3pbL6FP6SJHk1Vqb2EmApBx93GpR2MADWFxztSb/bfAiGd5Dm+zVq1e2I3mfrLyBGZSpgMi1vJZ8EGC+SNk0uzZ5cGK+MKEyXZ25bwry/ZkKaeEwweEUA2a7KuESJsGHnky8
*/