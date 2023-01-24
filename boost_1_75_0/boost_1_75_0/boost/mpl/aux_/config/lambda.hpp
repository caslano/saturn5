
#ifndef BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// agurt, 15/jan/02: full-fledged implementation requires both 
// template template parameters _and_ partial specialization

#if    !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    && (   defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
        || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        )

#   define BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif

#endif // BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

/* lambda.hpp
0B0X56/7YnfPBGOgR9eMS63YdJtDHsh6MR4gKsQKtnknn4pLfnAP1g80OSnYqNgRYXSgPI0VQPc7Tyam02rbJz8tWaCdaqhLC0qQC8ZPzq3+eVEG4l6l/mEctaQ6+YiN7oeadiC+8sCA7ge+h/7ztZw+xjQabhwM3gxn9QbCgwMteuC70iau81fc5bZMvJadproazwzjozJvdq6vDXZ7WBNaVtk+j26spCsFqfhlFK7opj/D1N4/WLKg6gP7R/IOht5XV4IHPrlo4OlVfY1l1a4HOZ96CDS++6cOFI2kPzGjX6HfmRAO3tyhP62K9goiHK5MuqqvcIt0O4iavHDqIW+DstBmqBd2My2whJIVo6zj8tCcCzfK+MBRJbu5ltOXkUwZIp41rhqTItfCSbx6ZaSOj9gKaaxBYdWuQSCS0ebIat50vV05q0aDaj/tuuuYe1jtbiufzU9hMvAqaEVT23UNBq8MpajFOyYBLxX8FmBfVj7Q7S/DnijgE7rqgO9iQNsKfpj1O+K6H6/hwOvuCxijW0EURuRB4YTdpWekYkfiQxR2m/OIaeEj0y/bD5/4DvpE0uZU3g63bUS0gjtF9B4R90tNybIaUXmsMtsLwvBkoEvXJcTHK6LP+PliXZ90uppoVMM9zNMcx1VE5mfWPM/ash4EWZNCHjWTkGSWb3vOqs5qwZCAR0g6I2Uw9Ntk9k3JW6+7SZmVgyva
*/