/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FACADE_09252006_1044)
#define FUSION_SEQUENCE_FACADE_09252006_1044

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    template <typename Derived, typename Category, typename IsView = mpl::false_>
    struct sequence_facade : sequence_base<Derived>
    {
        typedef fusion_sequence_tag tag;
        typedef sequence_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;
        typedef IsView is_view;
        typedef mpl::false_ is_segmented;
    };
}}

#endif

/* sequence_facade.hpp
zFEMbPTiCYZaiCm3QaDxdCu5QhSaoaApBXs4Uy64bI/GWIaFk1e4XkLTzAD44LovzixqGfoAqOEjs8kHQs7o/90dDsbd4VWvj/lO3hmRTz0AHXqQa3fh8OCn6OeWwZR6ULmv4pstNjDzrYIq2t9dEIUNc0LVu8vBuxKinEPqgEY84hyfCs5oFIuxX1yM4TvE1y/iezsHfHwEQdjFxxBN8NMvLo70I4UlJGMPvzt4XUzLvLLTZ+LaIkBddAzx8EjhnNKxOH4Fy1JkgpX0rgej8fte9/JipExesxwk/Hkk4xniHiN/ZWKwfpDfNFJxlRQPj1qKw+RqRvqRj71D2tCgQOFpnESf+Ix7wz1Lk+9ybodAfAX3vUg3/9iyrKbjK5Xm39Ukp+Vj8FP5L3jYhrUUK8uyE6Nv6U/m7uOF3Uc8q6OQZ90VKhJagJqtMuvQrFk/M1aAeaMuOjYtqCCLkoXUL1xQ1SP3OMHRIWVtD5C5ZyNb9L0+i9HEq4oXhjgWJwjRPWjPNiLL3ByauY73RKpLOXjrGCWzdimO1I0ddM7XfBUAVYH8GmJxK10ui6fK000GoLmG2GO3Du06H7PLqu/STUGH7ediqioStEpSzjRuaneULpSBB6n68q45NSKIgPAhXdBTlzHFHBDCIZdc
*/