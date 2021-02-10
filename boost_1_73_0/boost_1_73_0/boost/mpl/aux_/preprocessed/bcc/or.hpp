
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
7qLIUVM3RdwEPKVrZvNFRnRm+C0EpaMT+u80vMkK1I3UzZ3rY02bT8j2CPCUp1Okk7boTMp6f2OLJ0M4xtfodC5wzJjxw/TrbFR32KzDnTxHlElOTSaTB/C8tkdXYbRcb3dPmx59A7Q7Be8Kw9HfGnyITYJvcA8aJd5+62GjS8dLpRgxd+Q1t/5Qss8wrhOHRdujzdOqURailNCy0qw2DwRZ5OAPooYhr4K4/qXBcgGuSSY2hS/umn1EAbjZYCCWxtHsY6cG4pmX5s2PTHkGcWkLOdoH4fZpvRqITeO9RasCu30GPxDP3rzIL42ZlOy5skOew5/BIQwW+0MQhutQKLTW2FpRXzx+YfS7WDlK+M78n3l5t41Z2GjdaSXvssn+nv8DUEsDBAoAAAAIAC1nSlJYb5aVvQEAACoDAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjE4VVQFAAG2SCRgfVPRbpswFH23xD9cUeWlEjP0YZqQh1RVkVJtWqKG9t0xl8ACNrJN1/z9rqEklartxXC5x+eec4yFR+eVdFgw0era0OOE5z/GVq5gm7LcTQvsnkummlGfsILSSu1qtMlaK1O1+sgEv+4RfKa5YTewR/tKONdWyITFoTtTv5JeztQ8+5LC
*/