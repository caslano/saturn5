
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>

// `is_front_macro(tokens)` is 1 if `tokens` start w/ `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT( \
        tokens, is_front_macro, keyword) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_front_macro(tokens)), keyword) tokens

// `is_back_macro(tokens)` is 1 if `tokens` end with `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK( \
        tokens, is_back_macro, keyword) \
    tokens BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_back_macro(tokens)), keyword)

#endif // #include guard


/* add.hpp
4MOQtmrqMw2+DOvD9TAdboWN4CewMfwWNoGpbv9E4wYHwpYwE7aFB8EseDDsBw+D2fBwOA62hrmwDTwHtoVXw/bwT7AjXAw7w/thV/gg7ObmEx6tcYWe8AvY180X7Ae/gwOg+102CKbDE2EHOBQOgqPgEDhW4w7jYC48DRZCytPU20zpCvjff7Uwhar/Hqr/Y1X/x6n+e6rf3Ad2hQPgMXCg+sl9YR/YT2cz9NeZDMer3zlQ7SbbmyunTSl9c06x0t+iMxa2wjrwU5gFP4cd4Yc6o+hjeLKuR9r1Sj0/GZZ2PUnxToYpOpuiMSzU8zRF8WQFNR+pOeE1sC/m0KDeIxpveAQeAh+FLeHgKuH3w+N6LzwB+8An4UC5nwyfwT4MPqtxiefgJPg8nAVfhH+CL8Fb4Vp4O1wH74cvw0d0/Um4Ef4T/hN+Bt+CO+Hb8Fv4DqzKzbwLU+F7sDncBnvB7XAI/BAWwU9gMfwUXix/N8Pd8CH4LXwD9uF+3oJ94QewH9wJ+8Pv4PHwJzgA1nPbLTwEngRbwcGwHdxLfEfBn+Dx0OF6DkyBM2B1uADWgffCBvA12Ah+KX//gs1hWoi6h0fAQ2EveBjsC1vCEbA1PBu2hVfCDvAu2BG+ALvAN2BX+C48Er4Pu8Pd8Bj4o+LnHej0rKLxDW8uhTjUn2uK2az2Nz0Q7kfM0nN0LjwEzoat4J36Dr0AHgvn6vm5CObCi+F0OB+eBy+D18HL4Z/hAng/XAQfgdfCl+H18E34J7gD3gD3wMXQzexNMAiXwHT4Z9gELoMHwTtgS7gCdoJuPh8PmjNP9nveCWebWM80efjCyFkmvnNM9nOGyeZjEj+3ZAt/z4c3YGLPJmkOe2B8Z5HYzyHxnUGyF/rPHNnBtbmwovNF+mFsZ4osgNlwoc4PuQfzos4M2Q1jzw0pxeicEJ0R4p0N4p0JktK74rNAdA6IzgDxn/lBfAmc9cE5NTrvI/75HpsxqTrPw3eWh87xiD6/Yw1mgM7r2ILpcR/lhJmLWYpZg9mBqbeSOsLMw6zCbMak3p/qdMHkYxZgHsZsxqQ+wPkdmFGY+ZiVmM2Yxg+Sd8wczErMlgeT53kkf8lf8vfLf7/P/v/T8krN9v+/fP//ORmOp5/cSwoUbp+sJmwB73b3Cd1g0X8kC52MioR9HYMb4UYTLj2Q6tzs3O9YdR+JO3FdXr/fz+qbdenTJ2o9ZRqcgTvXAkMogTMZNd3l5Nl0cxSPX9+Sw5cVT2PY07hvczqQw6swG7W3ZD0vbKNAJD5ds++rrPgOfjO852lEf62hsVvXxCuu+Lo3pxj3lGCZuzlT3lt3dp5xfy2QTfw3OtWi153pHk4w6dfiHqSrqLWalIK3/mOniedD2sGbnm7OXuUtslbgK5W3m5ejw2s+pxVPcbx1LLON++vsSVCVscfU6HVu0r062eTlJ6eivTpPMPHUCp6MDlCazuQ+L8Os07euTbiLaz/I7fwM2bWmf1ZG5fZI6roxMd0+2/o3t402VBuVXp90AE172+/+ic2rO+a3wR07g+vhCld3bmM8feROPJXx9y7v+U83XE6wCzXRD7PKqcLY7C0Bq87cxsTXlXt+1Q4CageHq46/NO73Bftpn/MbMVUCKYwXdWJso9Doo9WKxMPd9gvM8J4vXfedNe9/7nXmgrmvjGAmo/bdnWmBOwMlXhv8m3H7OHAMOX8WfbSITvNbm9zrF3C1xK6Ht9EqI6zPLH7tuncq931uHijn9U4VXWPFnrnWIxhCq8uyr190+n45oHu+24RP9Z7NB429iv9598r1UHOvCynVFCdKP1lldK5xzwx0d1pw9WBPn/cBc32f04QVmkOZTbA=
*/