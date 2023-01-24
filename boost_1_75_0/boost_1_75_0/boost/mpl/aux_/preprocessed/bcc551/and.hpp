
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
dHLP5X57LX6OUAvJ/nWki00LphvJB/YiqSPXfV6Fyf5i8U/vyj2K1c0zOmiK0VlHBC7PqMnelvBvsMdOrb0aL9nT1NOF2dERci9EXh9YuJs4r4ZVqLr70V0V7EuKNkulaqmLMdi8MH214tM/xOG0G/Um3m53x+LQ8c9+K7muPMIXGLeHnFBiL3Cu9cViX9zo7wnD7GM5iK6ZMZOOIki+ukAYJbJei935RTXsQDlg+hr64vTTaK8VeMyJ1Q1xXvrF4CA/GGsU7DNseGiC67vCF+yPKL7EhxWKWd0LiGhklKIDZ5A91YGyGKphLdjaCH+etj9UDFnDH7vEFud/gwOY1LYMp+ZNSLqE3Jh9PwnzHUvFwhJ6OyNEQVC7V76psBTDqSdwg7HkL8y8IXHjcUVMgNREhDstOJDE0wTbEKcrt2iqFqvmTzWY5H2MplxOVJdYm7F9pJve283KTWqxzTgXU33am6Sb2qYUdVSHOvZRHIYFMVekZtAwa8I67CVcvGfBfQnHA1mL1VxIdIDywxTRSZ4Xt+WZa8FYOknDVDqXr5PdwivB+l054W8MYYY+C405nhevxYJVhL+77v84idGv4fOACJ03FW5cRVgQ0iC8RcDN8YwiLM4zgns3eiVpbtX9q+tleytXWz+o+Nbr/8SVOnhIV6iyFuUT3H3u5PKCbLbsaxef/miYHYT8mhJod1m9uPSneSECUmFIpLw2
*/