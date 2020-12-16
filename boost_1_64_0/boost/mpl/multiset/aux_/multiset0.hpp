
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
sSXGYCuMxdaqco2sWna5VpZydZFyraKaz3Cd+VxlvtoyXx318Xad+erLfN4yXwP18Va17OOmmsxXHW/HGqr5Tl5nPneZr57M52Gdj2d/Zeezo8zXSfIZYJmPdJ35omS+sTLfOPV+uM58bWW+djJfezS3OWWQ+Yp1pduc+l2O72vYCv9Af/wTA1EncaMuOBGrYCpWw7uwOs7HGvgE1sQN6IobsTa+hHVwH9bFt9ANT6M7foueWIReaGpzSp6T4ZN22pwqlHwfQQ/8BDvjpxiMR7Enfo598QuMxy8xB4/h/Xgcl+IJfBy/wnV4Ek1xyPL8CyMkH+o45HOSj+/QE4vQD3/E/ngeB2IxmtvGLJTlLbDTNmaotFnZD2tgGLbE/uiH4dgdB+J4HISTcAjOV8VP5+nkmRRukvW4YpqsJ1HWkyTr0ct6kmU9KbKeVFnPNFlPGqZgOi7GDLwfDfgkzrDEi8uzJ9xu5zo1XOKWR6EvjsaOGI3DcAJOxokYi5NwJsbgvTgFN2KsJU5ZnhFhgqxPHaecI+vLk/XNxm54B0bhnapy2ybL2Win3M5LnO5FbII/Yy+8hKH4K8ZgCSbgbzgXr+DdeBUfwmu4Fv/AfPxT1n9OJ89fcJC0EdfQeLzK+2my/gPogQexOb4j++9dbIeHsAu+L/vxA9nOQpyAH+NsPIIP4Ke4GY9iAX6OL+KX+A4ewzN4HL/Br/EXPIU1yeMZ9MWz6IffYAc8h8H4HfbD77E//mDZXnlWg43sbG9D2d5G6IlNsQM2k+1rjj2wJQ7GVhiJrXEctsHJ6IdTsS2mYjucgf54L3bA+7CTlENnKYdAfA2D8BAG44fYFT/HbngCu+Nv2ANrsA090Qt7oTf2lu1lQ+V5DmUu29tYOX5IDMb3Z+rgY+iJj2MgrsbuuBYj8Qkch+twCq7HJNyA0/BJNOBGfBQ344u4BV/FrbgfC/AzfBZP4nP4K76EDcjbTmyLuzAcX0Y9voL34B68F/ficnwDH8N9uA734/v4Nn6IB1CuD/K8h22zc32IlfuWRAzAJOyKeuyByRiKU3ESpmAsTsPZOB2XYRpexMhK8kxGntUo62vD3wNQGRbJcbYYPXEZNscHMQAfwm64HPvhP7A/rsChuBLH4MOYhY/gXHwUF+IqvA9X40O4Bh/BtbgaN+Iu3ISv4mbcj0/hO/g0fozPyHG3Fb/DAryIz+Lv+DzWVbYVG+CL2Bl3YA98CcNwJw7GXRiJuzEa/4WT8RW8A/fg/fgqPoKv4Sp8HU33JfIMB9vbuS95V+5jD2FbPCz7n69A0/MXiJD90cT0/o08w2B/4BT0xDhsgAnoj4kYiEk4APUYick4HqfiZEzBREzFqTgNDTgdZ2MaLsAZ+CRm4Q7MxkLMwS9wFp7GPDyLs7EI78CfcS5WYxvuQldchJ64GBvjEuyK92N/fAAH4lIpjxCdPKfByVKOVdBfyiNTzods7Ig5OBJzUe4r5HkJebNzXzFCynMkeuNo9MUxsl/GYh8ch9NwPGZjNObiBDxajvdDbtSWZsDoGn/Z+yK0pXndd0aKw6tWyHsj5W1H8+/w7sjfse3Mw7wTUkxq4EobmqQk0hLSFtJB0jmSW21XXQgpmjSftIV0mFRM8qzjqgsiRZFySKtIe0lnSK51efeENIyURlpI2kjaTzpDukrycXO+k+IcnINzcA7O4e873Ir2/5QOlJINFdP/3+X6/H6Wusnd8jvrCKk2qZBUmRvOfB40Svykcd0JqZkO18Ne5gEI81jq99LdrO3Q8SfP9a2x10VlxVrLv5fY1n3L52ny+ZylztVaR2uwxLV1d39D2Q7Jk/K5Np/Mn6k7tJRDnMTc3ynlMIs=
*/