
#ifndef BOOST_MPL_MAP_MAP10_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP10_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/map/map0.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map10.hpp
#   include <boost/mpl/map/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, 10, <boost/mpl/map/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_MAP_MAP10_HPP_INCLUDED

/* map10.hpp
VLgrrIAFcDGcAo+AfngenKpePw/rr5+NRO+N4SiYKXqPgZvCLLgl3MS6fmTuA0scrp+Dpbz5cG1YC7eCC+Du8BD46cruYv2/KE7hQkoJ+vbLSYbvewXJXPsYyf91wx2gfQ1kNr9NhHl7DRv0tZAlyIq2HtLjX2VA1kSW3bS6b+nuKZ7XRmzrIn/7mkjH7ikDvi7Cmojn9ZDkB8PXRN5Brx7S6nuwBkLagVRGmk86idRKepj0DqmXlFrC+8Ck3UjVpGbSFaQO0hsliTWUxJE4EkfiSByJ4/94DM36/0GLBiL+31jPP87h/f8Dxe9ZSbqa/8l7qO+d/OLSqTO8vv9/5bqR7/+fJrJ2F7/1VFK94WO1yXL//n/I33zluon3/RPv+4d8o6VLg/04vuK9s7OzFg5v27zttYseevjvfd+/0ifjCR4otvQwWO5gmw+DmTAFZsFRcBOYA7Ph9nBTOB1uBiuVfc7KfDKW4O4iZzVYZHvPPw2OgSPg5nB9uCvcABbC0XAqTE+8r594Xz/xvr6r9/Xzp6f4KqcnfAGJI3EkjsSROBLH/+UYCvv/wNqDeV/V8AD0z/434/zPCsb5h0o14vxHy+/Lgr9X9f2H7A1w/Po+K/a5XBOXnxqy46cUTyudNd1jbPf7i/Sx1k9p5GWG5BWGBHqLtV6xSL9HwBUSm79A/BQHkfzGtwgeCMo7sN6IqXThn/g7Yyofo4AD68PrlSYx8gXSjrtKzGJXh9RrgOMVTblviNyzpT1Pl3jFPKs9+2IVV/cotz+xiiv63teP2m4l0slZ0m6ZEpcYMNttgGMSTbm/idydRe4kiUnsfFDk/kPiEbcTfV9axaavjJuApW9DTVXT4hpj+Li5N/wd40etT8mqzv3e2hFeH7ffqHTb/4n9Av4fvkpekOb3Mzu/L7ik+ZG1nl6v+tieSzI/GLo4Tp7X2vf/dxSf5CRo5s+Mkn9nyb8rDPk85XkJF0h+1efZJL7IJXALeATcCh4Jt4VHwenwaLg/PAbOg8fBg2Cz9Z62PL9ggcN72uWi1yyYAvcWufvAkXA2zIH7wu3gfnBXOFfKbyblST3OVvYNapTyK6W8KjgCVsPRsAZmwYPhBDgfToYLYCE8BBbDOjgDLoQHwHpYDwPwdHioEt8VkHpmiR5qfNcUqWeh6FMk+vjhRnAazIS7Wb5ieY7AnaU81Vd8lpR3NhwFz4EbwnPheNgCt4PnwUnwfCVuLKCWa4sbO0nKPRmmwFNgOjxVyjlNqW9rlPruIeWUSH2nS31Lpb5lUt89YQsX6hv45pZPT7xzn3jnfvDfuV+9lLgy0mRSOamOdBLpCtI9pK7ShJ/4v3QMhf3P5+EWLR6A9/+Nb/uvi/07cpH1DcCCkmkz9pqJFVyzMPgdQOs7gbvZ8siXAoP+gBOVGIL5On/AvbKubwnxZqPnRtrolsxekVkhNuV+pICxT5xdZkXVwoALW920kcaup3y7Tf4+EKrvti0+LFyXSodv9p+YzfMrQpfqpoCL+lvfLnSIoXjJQdZ2nNRpl+XSlldlWd9ktL3Dv5fIKiM1GH4Qu6zgVxljyzLtn2O3MGxurmXLnhNbPWAYa332+6GT+C1kKIlNJ/1jjAWbrss17//77Lp69EsFolyDuyVHfhuxEZ3L7rPJdOkfUMvukbKvlrKvJB1mtEdE2Q2u2j6sn+v6vj2Zy9/SFX1+E5J0hdXuScmWzRr2Lf/TxOYvJ60l18gS9My/30HPioXVbuN6FF2tsbgPxoZRwvp9Y5HraPE8blsoG95+aatGfl/ySPRqv1/9vqTo5qJvRCe+1en+G5OmLq0OuhxtjCMnXWa612X2dt51yVgt8nuXx6JLaoc=
*/