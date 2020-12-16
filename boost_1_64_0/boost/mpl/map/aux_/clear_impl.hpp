
#ifndef BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef map0<> type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
aVP6snVaoCl9aHtqmdbO+L2f5XuwU2kq+yntL01tMwyyHZ9o2qjtkASMcGW/xRPME5it2e+EiWMS4q1jvfo4se+Jj1r3nTICu3aOLefYt52tZp1mme9gtmVakDmNFlqmdTDO426Ka2LCxIS0tCDTcu1M02i6ap3WWz1N1l9fvayT+Vbd/seYNGVsP2ugMSurdthW9rKDtrIlqrayyvF8ybj/1E9I29duc2zbvhZovl/SfL8813Hb2HnShn+ZnAeL5TyImeegbazpZLjuueBseprazEl7TmnLtMeNfWablAM/TdkGVTpL+1FL+6R18xzncU9p//5VBfZJVPK473wH+6QaU9vLiTx+eYFte99zC6x5/i7+lnxrabPraZ1mabN7db5lmqXN7pfzVXm+DGmolyfVbWuLpd0rySxtwOzTfRFpfv42Uz14D9O2SLtG+3RPmi/pLnlxmXw/qTkOm+Q4BMnvSyDhM+bJWmjXVk+y1vXbOpaWLurz5cmFjtum5UvG/ULy+yklsE35jrZJyRpO5Y1KNdaY2r7Ep6YkOLmNpuOguYZr2kBLWz9Zh7ndoOV4y7HbQjpvI8IefO9i2g45v6St3wRWoGrXd0yVNuq2lX5VXOzeiTut/B4vctCOjrSh7V5yshNt98xt5dZUKHubL522Zjpt08o+ZsvNaiun0wZNp63ZzRv7RaetmW5bsN3GtmP+nkO2Htp1x6DLw+/r8cCCiK/Mbbjk3k/uCbMq6PfzUQvN/Xz0IRTKcq1ludswRNWXr7GtLnphQ/THRngP+mJLVR+9OS5yH4YFsr47MFvWt1nWtwWb4/PYGrdhd3wBh+N2jME8HIOv4ATcgVm4C3NwNy7HvfgUvoabMB9fwLfMbYsqyn2S3DexXcZzzk/uJVvIdgXIft6LDTAIA7A1tpO2aV2wE47CLhgvbc/SMRQXYDdcij2kDU8vXI+9cQf2wVexLx7DfngC78MzOBAv4iD8FcPxDxyCldj2CKyHQ9EXh2FTHI4tcBS2wQewE0bjYIzBCIzFVBwjbX7icBom4BIci8/hONyOibgDk3EvTsQPMAU/xlRpC2TAQszA7/FBLMZMvJ20fgir4FT0w4cxAKdhK5yBvTGLf/1xJkbhLFyIs3EDZksboDm4A+fiLnwUP8J5eByX4ClcJm2DHkNXjv9qvB2fwDq4TtoC5WIrfEryDeuR+ynWIfm5OrK9xk9PqVvujT7YR+ro++K92A97YH/sjwNwIA7CaAzHRBwsddtDpE45ArOlTcNiHC51tIYKci8k90ZZhBb8HY/Kx1W2pzLWxCpYD93xLvTAAKyGQVgdO+Edsl2eGIk1pO3PnRiHNfFhrINz0VvquOvhGqwvbXwa4IfYEE9hY2kj0QSLsSlewb8h20pdOduHzdEXW2AzDMBWeA92xHuxO7bEMAySNj6tcTAG4xhsgxOwLU7Gdvggtse52AGXYCfciCH4InbFXRiK+7Gb1KF3N7cxcDHf+xC35INKGCz5oESur5fQE3/B+ngFA/FXyU8nCPmyni9kPd54WNbztlyH3kFvPCRtCd/HZsp8ct09ItfND7AzFuAA/FCunx9jPH6CE/FTzMDP8REsxLl4Fhfhl/gsfoUv4jnMw29wD36Lb2CRtDn8Qa5XxXgK/6nus1zuY6pKGxBt2wDaj2jr+S11/NTra+r0pR5fpx9xqZvX7U+cOnXq0q116C6mOnPn+hZnGW3/4uo6ZqlftvQzHsHf1Bkb64p9jPXBf77v8XzWRT2s1MGyDiytH/I8qTe9TAiR+lG9fsn3UId4glBC8Eqjr21CFCGLsIlwMK28jrH8U/4p/5R/yj/ln/JP+af8U/4p//xvfP4=
*/