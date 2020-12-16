
#ifndef BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/tuple.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION)
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_MPL_PP_SUB_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_SUB_DELAY(i,j) \
    BOOST_PP_CAT(BOOST_MPL_PP_TUPLE_11_ELEM_##i,BOOST_MPL_PP_SUB_##j) \
    /**/
#else
#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_MPL_PP_SUB_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_SUB_DELAY(i,j) \
    BOOST_MPL_PP_TUPLE_11_ELEM_##i BOOST_MPL_PP_SUB_##j \
    /**/
#endif

#   define BOOST_MPL_PP_SUB_0 (0,1,2,3,4,5,6,7,8,9,10)
#   define BOOST_MPL_PP_SUB_1 (0,0,1,2,3,4,5,6,7,8,9)
#   define BOOST_MPL_PP_SUB_2 (0,0,0,1,2,3,4,5,6,7,8)
#   define BOOST_MPL_PP_SUB_3 (0,0,0,0,1,2,3,4,5,6,7)
#   define BOOST_MPL_PP_SUB_4 (0,0,0,0,0,1,2,3,4,5,6)
#   define BOOST_MPL_PP_SUB_5 (0,0,0,0,0,0,1,2,3,4,5)
#   define BOOST_MPL_PP_SUB_6 (0,0,0,0,0,0,0,1,2,3,4)
#   define BOOST_MPL_PP_SUB_7 (0,0,0,0,0,0,0,0,1,2,3)
#   define BOOST_MPL_PP_SUB_8 (0,0,0,0,0,0,0,0,0,1,2)
#   define BOOST_MPL_PP_SUB_9 (0,0,0,0,0,0,0,0,0,0,1)
#   define BOOST_MPL_PP_SUB_10 (0,0,0,0,0,0,0,0,0,0,0)

#else

#   include <boost/preprocessor/arithmetic/sub.hpp>

#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_PP_SUB(i,j) \
    /**/
    
#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED

/* sub.hpp
xTjImBzGkWwhjjSLcZCxOYyjjH32cegGWIiDgsnpeiRZiMPJYhwUrJVxmNo8eMt76YXycF8B/yDOlXWpN6Y4jIvniYJS2MZlh2sWavk7GZa/5xeE6ucsgyLCIrkmzPabfsnSF0ZcoPFZ9TrNM5TFMq6X55Cb5fdB8vsNpvnD4uX5PuOqvuKryLbipd5WtLs0ies48xb2lv4q5PlOZE3SSlzqdikhQXE8VzU+w5lob/w+QT4KMTIw8zncPlO65H33Q9LvfVBIiGH8IOMzSxJXrLHM1OVmepm+IMt1xSd5jOUWG5ql3NiAjOWmVx+D/oJym8PynMirBPn7dk05LteU40xNOa7TlONqVTmayqytusy0hxJJ6waz8lbltaocUxgv6p1ZjpuzKcfG5PWTfFzfK/duw1RtQDTluE9TjsmaclTafRUeIv1UeJtvj1flGb5y2u2KE5FypeJkKVd2WsZyHfMXl+tUlucs5Woqh36actAclqU8zct/gab8J2rKf7mm/BdrtuPV2nKVvC+hKtcLjE8un1muG7IpV2cy5Qz57o7+UZnlullTrrs05bo9m3KtMjz7cj1Y0Fgo/yDDXfE2KuXqm6gtVw4Usr0u/4vLNZzluai214ma8tJryitUU15jNOU1UlNeSdrykjIupSqv44y7qrbDqeryUtW3WHV9057KSbneoEw3k++9C/Cse1Rmuc7UlOsCTbnOyaZcP52UfblWk2fqbeR7Uz5IuXKDLku5cnA2lmvsX3z81O53d2nKcc5zjp/rstnvTrRwXqne7y7QlrfsC0t7E5fp2Cy/GR4UmbmNK2mJijXL5wWSz/PlXGguoQzLGTgzSz4PSogOee45kLptYyyq+4+pVdj4w2bK7+S96HLE5TbLEJchopBYOs7SZW0jbG8hHiX/QuP1GWWo1K/4uBDtd5bM20Bp0nVG0hUi6RpAcCNdSdp0Bbr/S9LlLOO0QcoundI2w1KbipfXhiH7NgY5b1OR0zYJOe3LxUJbFAttJyy1YbDUZiPn36rOvk1Lztt+WGrTUnWyMv3I2lnv13PycVlXKWhrgn7vLzlvM2N8Bi7XnVggm+8vpMoz8MvogFfU3214xnzXZL5fZb7rqvnSnjHfLZnvtsyXpppPN8DyfPdkvvsy3wPVfE4W52Nc5nsk8z2W+arllmszuWZjPtp/Gp9/6eQZmQs2QzdsgdWwG9ZFf/THHjgMe+FEDMDp2BsXYx9ch31xE/bDmzgAH2Ag5iPugVgYg7AEBmM1DMEaGIruOAg7YiR2wygMwBiMxlicjsPwXYzDPRiPxzABr+BwzM26jsByOBLrYiI2x9HYH8dgIo7FBfgGbsdxeBCT8DSOx9s4AZW2IROxKk7CFjgZ/XEKDsZpOAGn40qcgXtxJn6Js/AHnI2PcQ6WsOd4hZ44D1vgAuyOa7A3rsVx+B5Oxm24FT/Aj3AnHsBdeAp3YyruwVuYjI9xL/6BH5ue2eaWa0K5VlTqS2f+P0bqi/Ls0BW/wgp4Eqvjz+iOl7EHXsE4vIqT8BrOwF9xCV7H9XgD38ebeAtv42+Yhg7EfQeL4F10wXtYHe9jTXyAHqg82++E+bA7OmBvLIAxWBBnoSO+j4VwHxbGr9EJr2NReaZWDKviK+iNztgBS+AgdMEJ6IrvYEncgaXwEJbBFCyLT7AculK+5bEBumEbrIB9sBIOx8o4D1/FrVgFj2NVvIjVMA1roCPlVhOrYi1sgbUxCOtgHNbFSeiB76An7sd6eB698AY2wCfYCe3yUOaYH7ugO/bABtgf++NADMMgHIshOA5DcTIOxvcxAnfjENyHQ/FrjMIfMRqvYww+xGH4BOPk2eU5O7mWlWs=
*/