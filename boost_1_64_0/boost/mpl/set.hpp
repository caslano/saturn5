
#ifndef BOOST_MPL_SET_HPP_INCLUDED
#define BOOST_MPL_SET_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE).hpp \
    /**/
#else
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_HEADER)
#   undef AUX778076_SET_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_HPP_INCLUDED

/* set.hpp
6sJt9G6ILwES9/fSy1TzSi/YTM0qUZakJX5wKDJdT39l2rxD+CGzOjeEmih6iPuWgb5gWFQYyeaKW6irGDPQfcZXGAMK3zckBKxhauXlLU8QCNasApqId3GmEI1qRT7hdOxddB+a0SgwwlOLbBCFlAuLZzHa/LBK/HVXX0XbI1GL670CQq2M64Q2PLtEcYRTalYJiCLs70xyXA/Xim4hyxX0hFs0BMmCMAE75H9rEAGbqjL+qQcyNl1Hc/8lgdfl76R5Vy/KFaki6DZ898Po7HLzac5srNBM6PKAQXR01EzQkWx8ZY9QvXgI1jfIvhT/ExyFnZFWQf0aFl/LjTzxXG+K8TOGVRDITPNlyKf5xmotF6Fvy8wzzodopAydp17/X7IVgj+ST9D/nBj/E7FyY8PJm0Jav7ERtPQPtKRucDB79PMlsWqr6DwRE4UyiCtIfTUnCg50u4N3GlDMbAKVEOH6TpUPj7PEiT04kZn4K47AHXoJm28sY+H17ADvAcaDiFtQ4yuz4xUS1RlNA7BNyKOJIva9PQ23gkZRbYXU8fRcjBo1IOgUHi2jRZVZuspxqsqPLuMqcfA6gdRbNh0D0PTGl3mOy8B2XO/lWRVxb7l18HojtAJEfpTCYpXzeCAV1Zb5g7kNU2VGtQvPsjn5jYo8HxBjEXLq5JmTrOReqvZxfF4lQ9QpHcjQSjVmYnxmjcWbUWB1GGxJZp4rOyyPR1y7ZCjCP+va/2zC1/aZV8y20zsk0kx4/CIA69Ng3sK1wxxEqw+vaQU/xPouvEWw8JXj3YMNMpskNcIkqRHD+OwuuSw2Vl+IC0AQ5Akf3ewSRfd/n+ivmsAuJHgXm2Tz9CwlkQ6hj4huCseuSj9L3lvpPNaptnfwx8iILCKkeQC2VB3QAdDyxthZUfYK8TZYVUy9e/6ppYGTtZiYqZrdLDoSlsUDitQc6OgmXWGV9SAEru5C2GgiYaNFpEMQpB3qPrcQ/A7jf43Wf0Dc78i0DA16fKdu0FTdIG0P1IyN8Q5Wnb6cRnN5KEmKHzuK1s0XC+0nBBCWSWs5R/qkVmqajnMfucN4R60kEMAGVEbdsjDA2OTQjIWEfrL/uViZEP7EQpk6hAStKLmMVuKdLRrx87XNR1uLRNwUtqjmkYyWtCqc76WuX582POqKnpCYBB8EkQ92hHR9M2zxPSTZpVe00hYpcjPKpe3PwKT4s84/r2pqx6ztg1Opg+U+ch7aBwUSLv6+VLBEmODdhBR9AbSrqoDjul/GLVNbyVtvlnTJ5Q9HpqXjVSY3Mv3iuKhMzn21jrHtd/56Zez80rzV7EOjZIXZeSrNIokriCR+cBFIAtdl8PTyTdW7mne/b2nbcLSaBeuvN9leELuUk3BIonx5b5yEcusWyo8txgu6vhmo74MLUR80Xv1ZTUKRkN/NFzeV3H066DfSF5A3nC3XFH/QQY1SkxytAxrFkw/0Bkn7+4WvwH5V8XZiMlswu/sFrjDGkDBn3EV/zBkTgC8lOpRmtwfa/yp7KURyzcKrdOdDdp5COXEz+JXaNIlmMnjVYMxh39UoarPc8oiOpQHYKRDIgbdYTcMeqgc3tOtbScTmjHzuNhO3GAEQNj99n9zH/YoZCrbhjWJZMS9lAyjEPMlD8Am0D/afFLr/raskRzEBygyW+2Gghw1em/D5AJSvavU0wGH7CicWIaDnkT6JlYfC3fdnhZbtJQmKWxGAZKuA6KfGCaVOzfYPCU7QJ5zTDsX07IEF9OqLuFM9GHzPZftlWXZgfvb4D2gs1Flx6W4ZDilbGevEx+9Zahn9mjmX2c5PALVMxc9TAXw+rEYWdfjmGInXwFkYPBXCZ+8ZGDzp72A=
*/