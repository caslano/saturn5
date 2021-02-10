
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
1lRJOti/x2lXhtAkDlFi5/Hrj0QG9KFUHlMmdVtb2j7w/Gld5VOWr7K4oO+MVRWT4nolxUizGZtBju6EjntdIZMOO3OOwOUwECujsQ0XohwMQvwQlzJfdsRPFshWHTH9nRmkGH0gS3s8qrZKGedUDZS9M7tRcBdtzrt+f+NiQW7gPcxf8+ftEngBxh5ErQ0+3N0vwlcAKmIpxHy9yYuXbDnP83W22RZx32XvTyLiYzULiqA8uvVISagf8VOTjIIQS31M/ugnKSto1FCpoFhtHXjfXNqD+AYkE+k4uGk+w+Te0On6PISBqgM6CA0OEdAoD3vEFhLf2JAweRpYkhh1/884cfKkzMHp2EKlvdqb2NXVR+dJWVz/yzdQSwMECgAAAAgALWdKUnBhEu8gAQAAzQEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MDRVVAUAAbZIJGBtUcFOwzAMvecrrE07hhxBU1QJwaZNQlrVbnCc0sZlEW0yJWlhf4+zMsqBXJxnvzw/OzJiiLUKmDFpbOMofODl03kdMlau9zlbP25fDsWKSTEVpBi5bM7m8NQatJEHo5HJ+gqIEdAP6DMWmngm/g2CtKrDURo8Rm9wUC24Bqyz+GVCpOfQmBaJKkYuyNp1
*/