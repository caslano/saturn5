
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED

/* remove.hpp
OUjQNa1FECp6z4HzHEAIi8NYuAORE7TsUrbztHxJBg6cUut7Xo+Sz4BqL5UE3LGIXIH1UmJ/a89rzuN2909weKG9vYr10sxVukxqdqlcDULkl1BqvfWKpPfKyPsWexkorWXCr0QtSgiQIiOkckqejfKCnIpKXRg2AlKYESVGU6FcfLk9UEA0h54F0qIzrHGOAPecTuHhhvcFDkhUOkgzEfn09iT0osEJ/Vctl/QQVvJFNee4v5DMG5t3h5hzvF7M6Kf+d4Xu4bKftb3/XMyDADSl7xfQV4C9GS0Hmp0F4O9OUjCFYSRMzW+ub5NWzsdVPv+vzJOaGuy+qTySe/PCaqnu/nqilx4SIpjOkRUm+IKEqKUPreB8nG1/ai/pA52OOi59KzQ2WxWUeNqsrZ5d//ayhknuw95OSXr7Z0DBUs6dDrHyvv3vcWV+4V02P9FHc5uxWZqN/d10MIsmGbq6uqfTt81qvNl5U+E9f27ey66vU/jHgiUVpA468Ddb1gXFmL5beZZ4wMjCDNgl31au5QpcVbTI/fPywigDCrjTIVTjhxWcjg1VYEkidg==
*/