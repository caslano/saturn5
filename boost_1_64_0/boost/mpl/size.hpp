
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
jjafI9ghGtngoo7LoI6T8n4WlcsQbXa9ZVo1hjw8WB7ZZjASVQPVizR7k4usRDTZY2/ySCuRodqbfJSVGEGivcmHWYkfI9He5AFWYhMSucm1ZaLJ4WloMuZenhxX+dqTRp1eG0Ke93iYX0WT/Yyc/1XRZM66JpuyZlBWyvMpJ/7TSky3Ej/hxJ1W4hgrUYJtsRJHWYkRTvzMSjzaSvyYEz+1Eg+3Eps4kYd5Mla9EvoraTkjus19Um/zQcna3D1Rm8H6k7V5bLI2H5eszcMTtLkYbZ5oRUYcEs3evpc6e+ubjL0dnIy9eZKxt4xk7O2kZOzt+Hj2BhY2GtN5DFgY5u+I6Ol8RKrT+fJNhyabz/2SzWd/svmck2w+ZyabzycnmM8jMJ9HWvN5dDRtH5M6bR+ZjLYHJpvP+cloOzcZbfdIRtvdEtD2END2MPqrBdNaLF9E4KHwDJaK1lhy5XSddo5KU5JhmU6appKU+Mdsg+gnBNYRnJaxRklxIUwvTptopUEICzEZ0hiEQIoQ7JRYhOHi+kZG10dSzRANc5iCyWNIS+8dOUKq0aNKwskifElpYI+l3BnI3fHYDlXpCYZ3kEpPMML9VXqCQe6l0hOMs1elxw51YVgMa2E9hhTPQXrWbDzd3i8YGeqpJYBEjM2FfgFbsfWLnbGdSLlzODcYDNJtvK0wKp37xc7ehkWlM3w7hxsclc79Ymdyh0Slc7/Y+VzvqHTuF0aDSFr0C8iZyZueteTmov6EFKy5fRZBwpcUGP4721S1CVh+kUpPwPVHqvQEjP8olZ6A9x+m0hOw/wEqPXYFKKwvE91Si6mM5yCeJfvPs4hDfulJBIQvKa0J2ZQbnZhgWUhX6QlWhjEqPcHiMEqlJ1gfjlbpCZaIw1V61CoBcpks+iUMNobnIJ7lpMmI65c+XeqXgzrpl+5J+gVb2U76ZWwn/XJcJ/0yPHG/FKNfwMLxHMSzZLJD4tju97rEdvt2wnYP7oTtejphuxmdsN2TOmG7xydmu6PBXrB84TmIZ8lMRsSxlyO6wF4uf/3QTvhLv074i78T/pLTCX/J7IS/nJyYv4wAf8HSjecgnuWsGR03j47p0jw6spN5NLAT/pLfyTzK7WQe9ehkHnVLPI+GYB5BbMFzEM/aL52VCzyZQrUzWCpaYGkHp9uTz1HJSsFXZk+dplKVAo75GRNkSLA1qMQsFVqxPXmiSlaaMqZuHrYQETnkLq3zCmGQdd0jo+vuFkJbNfBhEnjTbZ9Yutar43Wt+B/Wor8RqaGVqL1wTC/SZS0onNjLRVowfMgunJjtsnSv4mNwTM/gxJ5aLRqnaI2G2IMh9nBRYXzoWWgVjoUIiThauZo6OCLwaGjRalL+//V0BTBXAZyWu6BwmgXQUTjN4ZLdRUPLEN3BaW5XrG5Ui+LREDMZYqaLCuODu9BWOBYidJ2yOvE/uKqCmKMgluQsKCyxIPqghbVUrYDoDJY4XbGqUjnOmV0Z58yO+lGrPmU/dutKP3azt5pyCLqsWVscxAOfxQQrfN7av33U3v5jaWz8fJ8un0v8//f/3/9////9//e/9RPnz08i/pcv+r4MH9zLfA+QYUEYYluZmXcYTu+VXYr6POAzkz57wtDB4VzdfPhD8UlER+YFaeDBqS5Ilv23l/1H6hbQm7A1n9RauAkL6Jc7KT4XgdavWCmHrqtp6IYo6B6KOsbmbesQ2/YOxyJ6Sa/wSTs/hC25wy0+StM88SW0xCe+FJX6Zk/QtyY2ImGpSCCfDX4P4p0gNwqnmJWLxUtalVdeDoKwOe5Zr4gY7N5aPwc7pKdsPAmjsj2UHbEn6G5H39qmrGApIu1UHs+XiDSzbXg=
*/