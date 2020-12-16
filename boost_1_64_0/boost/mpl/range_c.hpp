
#ifndef BOOST_MPL_RANGE_C_HPP_INCLUDED
#define BOOST_MPL_RANGE_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/range_c/front.hpp>
#include <boost/mpl/aux_/range_c/back.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/O1_size.hpp>
#include <boost/mpl/aux_/range_c/empty.hpp>
#include <boost/mpl/aux_/range_c/iterator.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<
      typename T
    , T Start
    , T Finish
    >
struct range_c
{
    typedef aux::half_open_range_tag tag;
    typedef T value_type;
    typedef range_c type;

    typedef integral_c<T,Start> start;
    typedef integral_c<T,Finish> finish;

    typedef r_iter<start> begin;
    typedef r_iter<finish> end;
};

}}

#endif // BOOST_MPL_RANGE_C_HPP_INCLUDED

/* range_c.hpp
UlMw+J/hhxhPsx18/98Z5vjyq5dcyjf8VHsOdnXhah/3QcvVPpykPm1wU/xIX4uqHktp3ZST9Nt2akZwk9kep3/lKPolfQPXwpudlWO5vMIVmJTin5QemJ7i9JNFonjnm9JfVKtKmf5JnsCMTKd/hsdJpXjlo5xHjZlWX0GrL2gZr3781XlcaUa6018zlH7pRJJ1IsnxieAIh3ItBksD/JNcgdkDnP7ZLqf0LzrVVIinOLcLzu3OLdWDKBvj8JDASv7N4xN+CMJVmssvfmzkTE9WzTQnwaQGNVZyd2T90bltNY3LvxlLBtgeOBCoRlmNKJu+ybaaRuYfU2FGe8aBgE5aL2yyr6ax+XuyUFFF4TbHahqdZ4jCKLLO1TQ+j4lDNnk1jdD94pBNWU1j9CdjYpNNXc25/sdzKO3fmGv0S5LeHytHcEmOLQAU+WfbnDqS7LJCnqww1FrBISvkyAq55grXtqcGAAnR8NFM7eWTSKPhwD8s2Wdo5zDr4Qxrdj+tjmtv81e7KGku8tc4ucJozU7tAjVcnLE1UM2ZGU9793ubLXRO0a7S6SRF0enspArHaU+OZjpJOh3OFHSEeI5Jp2fPOd0p0WxWSj7J/PhQ/lFucwrS+5oCAP++nf57OojSn9HstRT/xjClAhu5cb7zxPwZJzq9Td4PA8h2HAigcvYb1O945Eu+8Xme7EEvzaX/ODayfrPvgXLx24/fukU4hCXwy9XqHN0As2tQGRyRMUJweAv08aODtBlfEti2ZA/V1p0GEFmzT9KGcO3mwNP+6vbOCFJDtAXchnTeLvT2sTdsqTBca8mTrdsiWx+vnae3blOtHY9DXAlVnN7VfQI8Xr7bE7hnFP+Y43EabgzKaYGOUWuSx/94KycfR91yj9O7w/uGJEi6wwvux6kd9wqUqnH1QQPyB6Wy08mfner0/i1QzbnepwMgRm/68YzssP/xEXgiEw/+/DOKfYcIs+QZt26f8DJ7XP6VhrspzqoZlJyUpHfdcarrArPTnY/atMdPFN0Su3yy5hmF/olT7tIqThSq1n3qcQRW4GA3S0bTwNl9neTYto0UOt+tdC7AvS2CXqo2jOh5270W96E/O91aN1vbP0TwHrv8NEw9wHvM8nO1J4ZYeE+XvDebeHdomYJ35Fp4j6CXon1viODdjKcYcuTqhp0l2uuImJTumJQCS5qR4tQNsMZkgDX/XkdaMzimI/3wlJiO9BuDhQPc1RnpAJs64UifOIUdIBXDAVJmbEd6nE5nexSdrcKR/gB0tut0tn5hjrTR4kg3x3SknA1H2nhUHaljUExHes2ImI70pYHSFW6IdqTeEYA2imI60rtU64ZoR/rJcNG64QtxpPVWR7qud450fUxHul44UiYGR1of7UifOBAZ5TpUlJstolyUNiZR4Od3p/hnpzhlvCs5onbSiF2OSQMCM1xkxAOcpmIKdDnItUbC8ZuhVLWSIbECjdHO45iUCU5nZzplMRq6OIC1BssOYT+A2FCjg+wsl3OAn54sJ+HSXqhdLOdkKqYwmENgGUjrJSndN0xRDaND7PgNUawaijg1mSdqYkYTPOXjrq5vXPl1sdD9xxGHs9B97O/Y37G/uOuD2mCa1mwp6OSpLi/Xl59QVelOKs/B2kgmnWALdokV6KQKXpWlWykOcg6uUy730hK1eiUm11G0PR8E6QVVTnVjRTa+IPuqeN2lP4SbaD/7NMhZ9P4oUYNW3xv4/peY3w4mpX8ygAnjP21KiDwSAqJ4IEoOi1L3gRIF7yQ+YGrXdHImv49IKh+kXY4Uf6qAG1zUqSStSA4uBe9WcfGh3c/e18Utv1zcTO3mOxuTxEfh+Pr9pPIpYuE=
*/