
#ifndef BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/overload_resolution.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 11/jan/03: signals a stub-only 'has_xxx' implementation

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX) \
    && (   defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
        || BOOST_WORKAROUND(__GNUC__, <= 2) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_XXX
#   define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

/* has_xxx.hpp
arsqnv3XtlvOC45zAMvcuP3Xtxs3MaLtqhDmKawOtRWzzBcW1NMH84sRs5Yv72ca/EMMOLekurCsKuD9GxroUjo30VtmNsK2tcqgiLdM6GcfIkrWLoPnLHkINdf5XpFlEKYILbCqzjKhH+TKy6/mkg5bxl1S7TLFeVXFufmYXXW45ZRVHKlMyWxp68O3YWVhRWlefuFhyxQUlqKnHmlfsNhh36u6sqRwXmGgAWVy5VCILBPZPtIA9W27hPO7DJob6DUs0KW/8pgfUL1gblVhAf+7F/YEPT/U5yhCP5zWpaB3l8x+BYEAdtjcvNKAVzbw96VKZWXVFIdJ9F8g1TCyswxjemfDWFyBM2qpYWwdaxh7JmPmB5j/E+a/hfnPYP6VmH855t+J+Q809Dgtk22eVpRf1rdfVkOvN1QdPLWIqnO7/jvttNvldR8jI+QzJJ+B9AjLLc+VJ4vuEt3Pg6hPkxhHrI8htoHXP/xvaVBHfginKqLtZbw3jKjfLRg1aeTY+biylR8Z4N/4BYjLRpeL+nGDWQt6VVblRZXBMliEy5FfYhpl1Pme7nLk/0AoVOWldO3fVeBidXmU9pTJL+hVWoCZ7vv1ypk0PvI9qyrm9CqsrupVNae619zKEiPqvXtVVM2qv/zs8uqS/EJ3m/Q7eNehuiRUvqKyvHzmKTNPqSwpKpltGJ738bxL/fUmFuYXllRUGxH7Iffw7zWysBRn2cqFRsR+OfJ7TSqcjRO04Xmvw7/P8ApkcLL2vA/eo/7yIyoL+chcL3/SxBykJ40cIHWrKivkemMA/JhTJk0OLadiVsmCXjgG9fKLyquq9TbMkdzwudXFaBHtSsTlwameqJeBBbMseoPux+hJLBv6Xy3CbZNflq/KevpM+Wwu19MvKgryVLmRkybpcnn5eSxXUFWl1zO/SpWTrcrs675PfjXLylZxBre5by/9n5P0ysoy+KeX0befEVm2pCyqrGe5KFz3co/p710u9kT0MiPL6WViL7FcWTm2obJsZngZ/E9q9Dy0o6ceP97AebMK86RXyG+/uSt9woTh40f1mzGQq1xHWXdlZpTmzSpk2Yj3rPAuS37LI2L+HJy65OfuULKwMtRe3uUdsTzfPvKY6CXXMYWzq0eUl5by02ERy8irxml8xtzqwtAy6qgv7TOKv+FXMBJ3nZH1q1Es9Ktw0grV5fnlpe581F5Q5mlXXERVGPqv1FS/83CNZRibwG2m+p2Ey8FyvL4Frx9HutZU35e+A+m1SB8Ad5rqe/6/A5fg9e14/QTSdUjvAtch/yC421TfUb8CXIrX6/F6K9INpvo+dTvbMNqC9qADSAMpoA1IBWcY6vuk08BvQQCuI0jid+yestT32Q6Bv4NteP00+Ar5J5H+jPQAeNZS38X6HvwItuP1c+Br5J9B+gvSL8ELyH+H9AfwE9iB1y+Cg8g/j9QApfw+Uhm/Y3QeXDMD7QZuNrEeeP0DKEf+YlM9g1iC+un8nsmVIE22hc9FhoBhoCOfnQzl9wiuBscb6jswcvQtMlWM9AQwB4wGI0B3+HzeP55qIZX1Aeea6nPqnRhv7g32y/5D+hC4CMtfBmLgklG3ubQrcEBr0BI0Ay1AK5CMOlNR1mJsHsqoZMz7CsilcJdIfwLHSBuZWCbS+8Em8FeUOQeuheTxvl+ABD7PSeQznKv5DGk9nxFdy2dUK/m86WY+D7kFnA/usNQzo9v5POlo0BV04/OqPFkmyixAejZYCM5hvLwliDPUM4Z4xu2LGUfPYEy8CvyR8es/MM78ewvrAxJAExAPEkF3xnRv9amY980+FZveIuvJ+PkX/LzyFbxvfcE0Qn+JNpYlyHqa6rtqm8E=
*/