
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
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
Ke7uCZQWKMWlOMEpxd0JVtzd4UeDS4IFQsbWyMXMmjWX5+asfbfX8+73e75iNa/9AInzoS9a8cSeIlL+n3hw05MzMOmyMWMcqI1zPWoflNBg6zZ0lCo228AchxmMkvrfFd/WPx8zVMS5dE84dDNObXl8vpAs3/JzhVT9yDVnZbaNjPpaFeU/GaU02NnbCCt+iZezEH/YkDlu+x2/XTc7zqBnkvMToNjY8LXuwPhiQplF/VKwUOz4J9hSusbo8irP3YzY9WH+N3A1ID7nGqNTCaTAbbnpXHga5QwKi4KnRanysVMwrxr1N0AKICXxPZSZYbUmjZh5szKMISlPEU/6a5qFEBrxtq9dJe5GULpQSKHbTLOFJOo9KqrrAQqG2sCBWf5qSDsEF5IgJN4sH1QM6lMiQIozvwMHAHJtp8s/N5MGxnYR01Id+iCIEZptcmmHOF0i99jbtgTMB+/GTHHEmDAXNadALPyBBKQt2LeTU269Z6yuh30Id4s37lzuXOD5ieNlCUfvFsE06SIyyajIjshm5OLKH8H6+qcS5zseiRH+HYQIFk+uKCVa8nrobDDroPP4AhFs6ftyq5GGpva+RzNJrFOk3Amyd26nM2rPzuh3YFU8knp8f3Ib8bmXMZpoz0vM/HA5mIice3c+KFw2oMeJ4y68oa6yNZjISUE/LyeR5pltLuFzhXpYXQFIJFmvXJJuXMpTyEtoEkZZ
*/