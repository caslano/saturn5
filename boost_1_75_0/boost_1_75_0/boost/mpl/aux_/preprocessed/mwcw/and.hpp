
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
5PyxUCo3NWIlDqdJqmCKMfz6h1tobE/QZ9uVpHu/7cIovgwBm2FWcYl27y+yI55SvhcIy5GAEQGanTaauBhVDcHz4+HJMgKe/aILPBXwxhsBwajXF6K8FpfAtd8INsyoZdVhCGfW1uHoENTMDOGHrOG3OuGuYHr49JB3D/oH7RxLEuls8A5JX+43pr4XE44fiBwmHyXsuRGFUCzef+EehXmxdKytc9sPdbpVqU+UTo4t/yo2AyQGiIysoCHADmbrw8bCxugXpt6xKAiFPch9cEbcyRbXKWEonRpoXjOtRuucRxSpbuEEAar6MmbrpRcUgmybjzXrWvIq97NWiEqMhFF/XLQ1JJkMbxPydH1eocd5+sQde1yXLdcMNvvDN6EhpbB9VSuOnuPE442JUuObjFPljcrpLdvZSbczQ0rQaXeQbSrRsZH+1KnLxeZN+fCsEoFHIenFH917kfsprXojQeiO6Wx+3Hvf9eR49uz04vjse9k4nYZrg7c1T4yqivVmxMm70GK5v5E1M3dUN2HkDFbvuJK5z3p0ZHv0nmunPrFm7DQ+i+BkND65oOq6XjgHbglUM7imBaS89o2EKkjXJ7qJ8UfHzeZdSwOsI+wWt9cZo8AmUaJC4VIz4qyb6JV16hdYQ0EUdDvvskVk372SEKzliJ2un3JuxsPOROZDHWFyYhVi8kuFoKyt9qdOZ+6Te6o3xDfq4pNUqyyK
*/