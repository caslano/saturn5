
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
7KdPRDRDPN5gFBWDJPv5hJ+yTkCpk+clLeRVTpfxi9b51wsP3EgzfkrM22LCNPMuSgj5UerkVnPFQkfXVvoTRuABQP9KGqQeLbayhCSaVGm4THT5ok1advxbCnXtLtajMWuZuoZmNAjuJ2b7hRgJAI6ydgffxzsxyKQfwRMx1y1i+NrGkjHPJbw61gP8i1dT+b04C0VC4LplQRU1DWKIufnkZ5LZ1G5XW5G1tAEXj+HkGqk8F4PfUWt9eUH84647w12Fge6q7FXr2uIeLRop7NaK9+xNs6iJZpE8dJnWqKO3By97eCBOLtUFAZuXqOmu3RkHDW0GI3u8rNP4QpQ0H1yAhP+87fS8Cz/FwsmyCA+GVYWHGutIefIc3Onty0c4qK85AZKsR7eijy3dkoVtMUEw9YrtwBRKDyFkqR2yqDvIPs2rMhDIzQH6xPeO42OijfCkzuvsdKgDHOGbpPHghfPWcSbauHpIx4nL5x0hvLeiE/32Sx44xtZajMUkgkfQ/VAsYjcwLa0srWbdc4H+p0porFSoYoiB5xOq9fSfUZb1ar5Zv0WiC/eTOg==
*/