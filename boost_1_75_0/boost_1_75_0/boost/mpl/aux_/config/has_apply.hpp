
#ifndef BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY) \
    && (   defined(BOOST_MPL_CFG_NO_HAS_XXX) \
        || BOOST_WORKAROUND(__EDG_VERSION__, < 300) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_APPLY

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
Wcn8KHFR6AYxUXgw1J3CLFW+SWgQqh/OHQGIN39EvAdWGPJv4JIf1j+xTJz5a/n8+e351uIzobnwYLQ7KJD07KX4xxHxBs49FshyVmg2IIFuFLkZohnjDskG04YdFJ+vI14XmhZiDA9GvIMDzeTziiuI/xPIBN0F/YIMqsvvCd2GBZPckYLI8h/FyUI6xcnC0sK1Q1bzU/O18pfIyWZl84PDAsTtxYLIg2dH8lXEIPPFVDFsWEAaswKzfrNws9b5sfkz4tliJiE84a18pxfodeRteMjkO+Sj0cUZAqL5TiRdO2MZa0E7RtM+sIE+u5Z0oo9NxYFDlqQLY++Px+UGBUfLElXLYioJjfiSLNoSsVA57OKzQcHW/nXD5r/k90ZuNU8Ua6+pFkDgdPxIH+GOq7FndL+g/RKD+qA+8+jSdbesSyPZZ4uc9oD7A+lsE332y7HnGWPzdtaLwlL+11v9cbo9cNzcjYnf3MVzJ35wn2d68NR5cGbhCKvGu8Ip3pNf4B186Eryyhz8o/irnEnSBP/SzV9sMT6K9B/SW2GytXVv9k6iBQdOOs/efiLCzhdMK8YcUySqItdWvxc0WPJ8tjys8jygj4EGGXzpH8lHfeeK3Tq3wTfVPWR3jvfBNwEvjB90I0fsl3v3nu8q067PH/OIxx8rPlv+qILOYmWAJjgHr9ih9bUqQD3zJ+26peJjkgZDkCnhHQ9wbHVg
*/