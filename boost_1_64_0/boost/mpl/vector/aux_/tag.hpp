
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

/* tag.hpp
Z79Fjbafm/oU4uBwK+KNUeQn5pvZH05/D+rZH0E+O4jnU8/t7YlcNqLfEon7Y4kv0VtWcdjNSuz/N/hx38M/8L7nk4uJe1qoIxkOf7iUeSiFp7PBj7Kn7uU0+nE+8dsB/Eh79iVPI/6H73bzh+f5gH1dvHev6AHWgTX2Bd7VOAreuoX2tcHPwgM4DeZ9B4/zfkbsY+dA8r7YdRtv/P5W4vm/4bF5/37OL/DWw1iXH8DjRg+A92G9PYY8jSefD99nM0J7vwJ1J/hLTh/BFw7V3m+APPgwD9/hr47H/2V+0++HL/8NXm8U684N/go/5VAOctKk7ddCLr4gbkjkem/yMEGMM+0vMZLX2o990PVjHRPvBJBnQz/XxKDXx8IDfc54PUO9Lp/7fOAF8L+W9aOOkk9b4sGG76nPxy40FhLHDyDfk4UfH4r9PaCH5yIvup11Dj/oncx+hUOsL94TUgUfvC6N+/6JHojFn8rFPj9FvzfAi97Den6VcS6BD1hP/VUIdvdG+kk9x37iy0PEEcvwB/dtYR3cjh4YRz3oGJ6vvad4PftBtPcoPmViHxT7zA9SH4A9cGuhf29hx6YayKdhJ7X937vQ2/Ai6bbw8t8jL+/zPpNE7Mdy9mFtxl8iLqkLxi94B17QDt4evtVmCHa6En38GHXBBfg/1Aec/Aa5/YB+IQfJ4/GnvKk/mkPdgR/8JHFMw4vE98vxc34xUWdPXWQ3PEI59Qcv42e7o6dGkLe+BTvJOvYKwB4U0W7eh1K2En2w2sx7ERm3J/FrVuOH8hmNPvJpw09+H7sLP1RlZJ9TIvEbfk5DJXJzFzyXM7zlXOR3HfpFT72LP/oPvyKB9ynvd0YO2uBHbcmDlBP3ZsLfYFdtqFdI6I8fg151uBP9QR4oh7q6LB94uQr06QTOR2I9+jlhH9up38jCvgYi52bsazN51e+Qh3mMazznYOXAD/PewAL4ucoZ7Ke8jngAvrmxgzzGDOIf6rO6vfDbTuInOTC/yQY178yj/hB+wRHiV/Jh3ZnwBPBLFTuJCytY7xNZjznUc7FOc7R9/APZL7GA9YSeSJuJHXgYOaNOvNuber7vmedvqEuCx22IRz+yH0WP/x85mvrRH4gvK/A/4NdtEuBVdiB31FkFbKKfg9Ab7fC9D9PPp9jnzvlnJ9k/WZxgSZyDvF5PHrobu30a3od5zbkTP/pX4v5Y7L0lfnkc+0bI2yflmpBv7OfHxAklvKfwT/zDeuI++GIH5MTmWuxgFfrCgd/PI66EL/FxQd5PUGe9iDjdCf86AD//RdbfbhPrkDpX9m8G+BG3aOdrwPtWe+Lvbac92Yy7I/v8M/m0xR58qSefCi+wZgDt5X031eQJs9DnEdSjhVLnEEbc0Gykfg0/GP44bgB+N3XWofiPnS3UBfzMemuBx3qSvO0x8lQd7I8fyr6Rv9F/gaq9Lduol/uG8YP3jPPHbywi7z5R28+E/xtKvzej91vxg8z4N0/B+zQQr74xAP4Ivw1+aStxu91mA+OGn835MYeItxsi8V+2sc/jJPX00fBETvizYfhJTsTZw7F7S6l7jyIOQQ59HtHqmLHf+IUlEeQZo6j3LUV+CtDzKfgH6ei9O4mvqS+q+RweKY06uBX4KaOYf+o+CtA3pfDMHqX4fT/BF33Un/pBeHl4mm7eh1q5AZ5/C3zty/QPfd8yDj24nDpAHXpsEvnmTPzuMfjt38FPHccv2wWP9ip2lXi7bruZOmfkYiX+8GHGKQw9H8D9byReaWQ/wxPEpS+xXg6Qj/iE+GId+ek/iHPh0wuo53RBfo/Mop/LqLfBblWdoM6OujQfa+zcEPTNSPikM/hR7+Cf5fA=
*/