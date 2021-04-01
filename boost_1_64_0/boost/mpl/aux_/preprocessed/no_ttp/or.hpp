
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
7OZGLXJ6foHGUR0kuObvSjjO9WTaqu3n/KosFR4aHizxpO8KtcujYQDEk/OoCVcvt4+JvtLuBubjqTAN8vvv6FGk3Ha1/OU9MF4WswfAgDdpUyMJ52VlKUcUwPDwEeEoOAoKFPl1jkTvBqRafrcHWmRbmDtGrGFW0Jec3MREI4bQ82x058/hUQY4L+6cSoUtCEhGCYJqko9N24LOCvbTobjAV/48faqxnzjBX0Z8NL2+1Q37UxZUaZM4WoeffpZg/gzz6h0B00rQ4q2bkKvZl6NxX0bJ+H8E/CkggG1OUc6DcoLuElL60LVfVeADFR5XQZ49kGOHU1GuwMLz/5ThuqraYflaSaRSFlRrK0aNEsbD8UNp38sSDonYkoXzH39HnM96vR8r540nckVKl/Lgkaeq1Q4ACaiIK1p0WPwrnG/Jg5sRWNC43DBOnUSnwy9epnp3HtJeAty3pT1y4t/3Ub0AOQx6btI0dUq+ZGeaKJgKrD8Peb526/YebEuhE6Lb3IuZiyVvprPdGdXMO4U3feyD9q0W5m0mplX+BuEfFRx8o27c4FBjf7ncGQ==
*/