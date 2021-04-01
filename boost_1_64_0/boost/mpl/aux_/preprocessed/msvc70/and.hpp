
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
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };

    template<> struct result_< true_,true_,true_,true_ >
        : true_
    {
    };
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
        >::template result_< T2,T3,T4,T5 >

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
4iZvxAelOvpeijPQ/7CU9nK37JZIcwAHIMIizzJ1FYcoluiOtf5NPXvK7a9cW0QGZBRT4iF7LDMKZiigv7EJjVQiGV6lbbwXLzI7E0w5f7GXv80XskZp8tvbb27EqtFa9jUAmtYdkpSpO8ykah+J12CkQtKVocMT+k4s9Q+am/38Gn8EjT4FbBBYHLhQqA0C5clLY6/Xp1lRnLVbHDau2irDBNI4nxqKIEYe63cEr0H+LHJ+gIqED7RXDiWEO7uYdBd5TIn4jSQoVVXL6QtQ2qdAUK6LwgPM6cwWImmx1BejH9rj7pcvT3ao6OGis+TIak0jsS0lvy28EnXSQ4+iUj9knaNIOi8Oxz6RlbAXH2GP6qeHISGIKaBRIJ/wGNcxgOvdknvp1r3tsEAimJghUKjNcdqNP9eMV1CsHoMLzeIMuMp7twXuWxOrybUqlEgsAQLtz8LcNql6Ku90NJE8R9w5ptg76OuQ8e5x+0GKn/GP2tuHXYoQFOgmhxd01vdEBn5371hITE8Aw2o0o0kqgG4Tj7XYT2oRRx8S0hyQ42T2DeIFS7elsqe1gQ==
*/