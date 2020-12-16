// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/get_pair_functor.hpp
/// \brief get_pair_functor definition

#ifndef BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_by.hpp>

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/// \brief A Functor that takes a relation as a parameter an return the desired view.
/**

This functor is included to help users of the relation class when using
stl algorithms.

See also member_at, pair_by().
\ingroup relation_group

                                                                                  **/

template< class Tag, class Relation >
struct get_pair_functor
{
    BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    operator()( Relation & r ) const
    {
        return pair_by<Tag>(r);
    }

    BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,const Relation>::type
    operator()( const Relation & r ) const
    {
        return pair_by<Tag>(r);
    }
};


/// \brief A Functor that takes a relation as a parameter an return the above view.
/**

\ingroup relation_group
                                                                                  **/

template< class Relation >
struct get_above_view_functor
{
    BOOST_DEDUCED_TYPENAME Relation::above_view &
    operator()( Relation & r ) const
    {
        return r.get_view();
    }

    const BOOST_DEDUCED_TYPENAME Relation::above_view &
    operator()( const Relation & r ) const
    {
        return r.get_view();
    }
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP


/* get_pair_functor.hpp
FHkM2YnsQh5HumRFtRXsO36ddPvtOE+o3666Wvtx/O2H149DGWSfe+90/nm7z9YX2Z9n56q3dUL2r7b79f43aBMK1d59oLZNpyNdaRMynotqEygONSuIILC97SFhcjx7c3FnSp18W+p4OAZtF6yfXMN9lHp7GLnNLRdpuenJGUbClrWX9mHF5UsWrjG+MtVPwnaIGBewuwk21zHaazs2gHSyT9OpeTVW82qU2uD3Uvv7TsjfiKMoMK9KNNGB7aiG7dTodZaKnyzNs3CYDG8cS+NrSEw+3jVzXvbpeRuUjyr9VNF5Lc2Ves110desFxt1rbZv/Q4Jcyl9z2neM/k41z/F+uEK9dlxt7inmBEmRc51KJRSCRXuT35A/Mwwg41j1904v30or3jOIydWTmLkmdVfjG9lZEv2vYv9gzjynm+YZyW8CC0MKhvqP9lka5+zY1zvJRXLSpbW2Pzx/B13niFZr7jB9eSyzw1E/Ozzxx85dmlnupHNcULl/jDSnUCDQtfEM428qKxYUEJ+lJTPrymX9Nl7yl57XRpmgJ0DeZ64z1G3Y46Ie4SEXyvthkSo1xsOf6Z9l7hU3K+G+uZTwv5L5Emn7xIapq+d17lY3K8FPBfCaRhjMu38wUvLJEZ9nyiGdeJnV6Q+QY+Xw4vl+BveceLwv0dcJMe/r2NGNbycxBszuln8JNpn3xZxF6vby6selPEWHC/hZj6ZG9Ir3eB/NjXhXdF9LhFfxHOpyJZ1rV86dpT7wr7QfcnW5xd5zz6b93acKfnHfs2/qLVV/M8kHUfY1sjm9ue6O86Dnd13/69IWdOBx/KKWrKoYrW8REW/d0pZ0zCnSbswB/dt4s532nDGoHfPKTZclm1zNon7J7gdLXeO2VYfmou7q/99smT+koqyiBc8+275C4njkOdf0hoVwN7rl8X/LyWdF2dq/Hg0Pt1jtaRhQMM0SZtR0M4Lg/puvv+ZskH8ZaibcX3iTvDOJWkjoK+8XiV+eqs7fK4ceXbvpn3Y3UbfwSrdF7rMJr3P5cC/y3XulOd4V40rp62+Hyblpye2TGtNjN1bmqa9I2bBVyTOh9TtpVXOod97XTsas4c4nlZ5Bnm2CesxqZ416t2sMPrdLELXekRb50qkCzIHae+Oa38holwvXigfCIFlWv2fYdvPSeIe4RvXt6yizBvXp/572PXCxop7fOjbQNrLUMmj+UbJW2bXoisQf1O8Me/izgvM8yI5nh91j+Q524R3Ey8/G44hDF1PruY7aWZfZJo9vWWQPq35+szm6t9O1lzlAXrOAP3hv2+uv1dlfN7lzy18+qvXvLhx6MDXd3xt6vvzg/SuzR9vF6C3DNIz+8fbyTdEuUOdM7Qj+nuojrcrN9oXJP1KoWOt4FzfuDKXPeFp6s6Fp/vGmY3QcWYXwb6wTMebXQX7wZvgmar7KzTa1wOn6/lS4Cg9X47OI98Rng47wX467q9QdZJTfOP98mzfiPTlSHzd+Z3l6FhD/OWp7nUYrNVxZVfCiequgqvgang1vEZ1r59U3eutcB28G35SdZyfVt3mjfBteAv8NbwL/g7eA/8M71Wd7RdhOrwfZsEdsCd8SHW3D8PhcCccAx9Xne0T8BL4JLwaPgXr4DPwZrgXPgCfg/XwebgPfgV+C9bbcZH6fQkHar77x0X+Gn+Z8Dea74c133Hb8EUavleM8L/XcZlHYCf4Huym7vdhKVKn4ddq+Ja+OUyPqg79A3gG/BMcAP8Cx8K/wsnwQx0PmOCExi/+Q8sbbh1fqd8AMFnP4x9fmYw/lykwCbbQcFvcsBrO0XLkXs8GDfeiXte3VQf+HTgTvqK6/oOwHL4KK+EhuAn+CN4=
*/