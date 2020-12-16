
#ifndef BOOST_MPL_OR_HPP_INCLUDED
#define BOOST_MPL_OR_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(or)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'or' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma push_macro("or")
#   undef or
#   define or(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER or.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma pop_macro("or")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME or_
#   define AUX778076_OP_VALUE1 true
#   define AUX778076_OP_VALUE2 false
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_OR_HPP_INCLUDED

/* or.hpp
nGFvkqUzHJpkndkkOWiSihn2JpmosvUiQpfpKVmJXYgSpyPcZVRP7GjPBMTnKV5EBADxAkLb7+dTMYBgEzydS5tD7ALgZwDV2N3z5s6+z27n+Ozz2eezz2efzz6ffT77fPb57PPZ55Px4fOb1/L5zVW7Ipb7OekAKt6D9rfTQ/D1xStLjS/9IsJvwc9owsv+p8iDzd7xSCvs4DQfP4jOh2SNWX/F2f7QRKQWPYZfdHZV7uub/Hpk32cEfB45A8decUOCPBA9y5tBkxc/SDjgu/rjf22P+A0+1P+1SB+fbqdTz5UNqOqY+XSxVOX4ehwq9pUazYEMHabJN88a98o56QMPRgGyLDbeuOAtEEC4JfgAvvOb2mi58yKHo3EPDl67/hA/creui5iPxDLCEZxccSBfEMz1AMbkJjRwJOs/PuzL9fXi/r+uSJ95Z0odXonB4ywuOXJNL3o9LVc/9I1YvPqGfD9Yzq+nCuFlcaq/seZ+5snfs4oQkeyXlsovNX6ABvT23KmShiKH38+tlNmzgMCRfEpwVQ7mahoHDUFC5LbIpUIJVP7mE+h1ChdEVgwS6CWRz1Pe7W6ugJy5HkO5tmesdqvfxzW8zw/bHs2PrlccQnxnhQYYO59Dd+AUtfHLdaiCbtS8wzMen5Tvf5n+TqBKf5/+/m2S/F9If8fd8NG/W0X9QWyz1PX9LCl1FcOD36R6BFcOLvQH+en14CI+kp5p3PMSI+XXtPZFRtAtmGhu7g/Kf9LnIIMzmqYObHBz/T2EtVdB0ef5V70a6YOyrF8LPkiW66mNQhnBAZQe6gsNQJTieDRZgGSVXxr/CTo44arMRpE9a+T3gLwZdyUfRJAzoHnoNrkRXzThlpqqQEZFMQIiLz5uFhqrqYqRAECNwo8ASKjjONQb8ge5bYzBraoLAxRvA7fAV+lvbpd0CJFxr3QxJWSQ+rj/Q/VJr09X/SHSZ1a4HmYB5scIiyqYb/9Dwb/MdoFrbYrkWSa/uBvgnl+Z7VsxUKR4WOhoiAEixcc9CztQ1LTPdUjef9Op+WNrFsrg3q3HDTfG7h9DqkzbfjHzV09BMUrZCnZ8qtsKQkVgJpQZrBOBzN2JrJTtIPTBAMjQuVTYh7uagPhFQCq/rszPZtf8Zkx53LSRlYUqPd9MRztfodIruApiJ/elXG6fTMj/7yN95rjBFS9+tV/FL1AVXygVz29zqvgFv/+AFUd9cdsGqtH3J1QDGVPl673faXtNZljL1wuSweRzWkHoG8LnucHZwuf3f634vEhdQgG5yyDJa2mxSN5f1/OPAmrhgtC3+hH5vCLygUcgzf8Y4l8JXm8ZDxXUynfErIKXzwzWq1syrnm/j5sSRe2DvNC2r9dRG6A7y5MxYYeJ4pT/6ZVp8yP99GbndLGfV73C/YNXTpJqVjOFhvIDqK9Q+qu/NI1cb/AOpJuju6cRQkOtkNWzziVPsFScym/d3EoG8nhulWAb9QeQX37FRJ6W1XMLIZNMRCmNrqVK0H+RY1kYg748wmZ53GDBvlCwR+YB+2RGKfGTMOCuIn/yepLaJnQK2BnmEj4JS/lTcWH6GgvWW+a7MXnTX4XX4Ke+lVukyoLnUDkg+0VLhq0ZKWQLxgcvUxxnW9CWMlqSx8LS4MQ8sxn+9LRCc0dutpQ4oiz4fVXi0xacSyzFjRwfvF0Vt8KCM8pS1rGlwTmqrFssOAOpj11y6fe+K8F+/Gj79YeXickqL3ntxk9fiPSxtnvZrdjwkOi48ef15pc74JHqofiw4HKXcjXuz+BvovNFkFbWyQ9SUf1+TAnxQw+KkQdG/3WJWnTKf1H8J7qCTlj7unI54CazZ3GuO4MMRTfbqgw=
*/