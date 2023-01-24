
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
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
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
        >::template result_< T2,T3,T4,T5 >

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
hTPIvjuUfNreYrldJ24QntoiZIdiyesEuDB3jssCuoPA1NzCj8G42LPzKX80RW/3DHWZYwZ/iJ1XnSsriBC8n78n6ZHyKUg07f8FYehB7oFwBGGJhpiUbedvF7LOXs0R37/OLJLPkc/qguJBqieqINaTupM60BWO4Fbp1XwQ2AesCmb1Tw9mc2Xau+nyRb15rVIadi3d443fZy3ng0ZH5/QVWoxnMdRCIqL3DbWFRAr23KSG9k3wtvM03DY03SDaeFd9+Xtv6VrdMLTke7/qF/Wo/R+xAy9u7H3ThwtGooDq6aED/1Ss6btRGrzkhwlWQA+ky7U+bC8wo1V+vdB5nmzR2457zdubmN0OT8UsFIrvBkn2hGv/KFieky/gHANxQmArXapAaklv1qnBoF1gvuj0zrZx6IbNG3Q9jnf33C26zKvaCwjV+kqAS71106FCmwJIddn4H33pR679oU3+BuBgx2IhX9bnoX4E5O7R7z6awzDZI3f98yeUTQWgUItMLnoPLnRKzbgJtxKVDFWgoOSmjgLqqA3+ZfHylATxFrvdntPB7QZANq9dIyATEOigLOe2MIvNNNyYKykV4OVtxKPAFj4Pe+MP2+iAYPmzFUSoED6bAQSa9zMCtvS4/Fv2m+xaeuXXWAWY4iqMMIld7VYXbAp90lWEQkvQE8z0oe6wiYdvh4EwLrmXbZgR2jY2Zlh8tomAa+7zk60Q
*/