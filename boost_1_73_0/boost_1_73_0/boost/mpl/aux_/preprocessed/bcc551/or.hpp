
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
rujMlTShhZYYJ025pyDb6w9qS0aSk/O/v7Xz1Qdja1c7MzuDuUVjY2HQZ7yQqaLXF7Z7pRPjs8U6YNy5nLlzuMJuYIV6h3pkigQZ11iXLbVNX4yrxGfhPHj7C8HTagOeN4W5tKgLmUEgjCl28K4ShIHruT+H3g96hq43PT13xPMNiTtHeGKdlQVKe2SN+8OZ1meprc+jPgMuRYX9EpChtR17JBLIlbFQyE7WSKOplTQIVvVaacg5TAGPVVUJmfSwj45z+7JcrV+Dx1vCC5bh2vEmUxiNksKIqMQR1mZH5Och+jzKI9kb2j1tIRFWgEjJCbA5cZLzkAsDEaKEa5Mre02X19SKVNYYEElCAg00Bkk2aoTCQEz66bqpMS7SIhZl2YJRBCgs7HPq1FrFNEUjShJcjNoKWrdb28C+sDlETZa1QNCqJKcgpiyGvSIqNWVv1Il64P7yxvdjb9znctMJSLWqQMjzlahU8deBn7pZI7SgsIleYodOzkYIXeqZpOIgXMwmk8n93ZjxXW+LT7DuA/yG2Uf4Nt+SvdvP+Wv4vKWAtotl+P60Zhy1VroT6jP3gcz9dua0sFWxKn32sZqHJE3JtlKNuWIU6Qoovj/4T1R1iWOKh6qfz31rc0VAl2HunPRw5/JT/AdQSwME
*/