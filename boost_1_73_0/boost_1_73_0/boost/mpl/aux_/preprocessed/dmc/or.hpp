
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
0iQ0wPgt2oAFbGPkIegJRjvwyrQtBYxoSRRdP+frcr5KrnumVV6U0e10evdP/gXmEf3GaDzVa6IBh1qivccv0XYN3lAghCWEBPGTTcfjpoYdvqNV9QGk8AJE7dEC4UP/arAVDjaIGiZua/yE8d3gTakrjiGE2VuxyD7W2cvjR1YUecE4WmtsZSQtKY4p6ZfmnTXeVKZJWfa8yKG/acCWD/MFPBX5MuF/0dOAFbNVCWWe8F8XpvLr27zsN3ueyaMTHI/Ov9w3UEsDBAoAAAAIAC1nSlKgWh8cAAIAAEoDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzAwOFVUBQABtkgkYGVTXU/bMBR9t9T/cBXUF4TnpO0YtUIlBB1lA1pBxp5NctNEpHYUO93y73edfk1CspTcj5x7zrlO7NC6VFmcsbjUuaHHB3Z/TJPZGeNLFotTGItdxxk7g1dstthwW2bI4gbrqqN6ppwCbdIC04/roEMbzNgiSVYi+hLBKAxh+ZPdKYcSkhYvIJzCs9lSIQohmsjJVFLL/VPCduASPDdu+0Dk6gPZo6LEk8nKvMRsjxKN4UerPTyhjGQUHlDmiVpLCEZROPrKs/QbH08nl6PJ9CpgN2mKteMvSq/RSnjvaBK7
*/