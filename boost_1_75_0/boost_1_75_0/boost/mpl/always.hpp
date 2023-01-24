
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
x0c+OXq8db2w4FU4PrSVbVNhHSXEXtPANa/C/f1bPx1Ds5yeat5YtmF5Y5SxcHuLdquv4qi2caed6/nOwu+1DqNW37EwVdfz3JaWr4eB/FP3bpWxPjTpuXWkv3/tyImw8q+un+tlNIIS0q3H20+zFP8kzEyrS71Nv8yWFSMdmqj+ZVpcNsu+aZs5pX2aoX2adqPr1XOT1zSSWWZb7tGZVre8L+x6k3cGmjRSbwYl50gj25+TebFtMGkxCIdaXMyeo8tR2/06mRe1LgcezVcKTXiqny8soAvJDv9Wc/lZRQwFm9ebI1aUajZ03KLgIsGvszgHK2hO8yGFZR7sdplWvvsyZGpDoN+oYAE7CKbsV8/0JndKk/DDmCdIMClfbm7lzp2ktwT5Hzy/L9brkYbp8mvhf0EczF1LiBB8GZLi2BLBjHqMpqaXzkfw/vZ69JzklSsn2Y0PWjDZoBtO3a6ZXHTxKrtlahiueFl1RgSed6wTByU7WZNxXb/DvZbvuOTLGgRmltbGzj3vGV3kJR0y6C66xSd8gs5TbW4AyL4w8t7wvnTGqA+7mQlPu3nkUZ3a2UJ++/sfMg1BNag2Iv9yKSbrT8T8Rsmm5y+M/TkzHJjP3aNhXdI3BGP8TCHRY6/aQtYGRadx+8aZGLYO5sxkAauqOKU3ri7cyfQL5cSMw6TGhUHG1mapI+XGKQubGPsB/spA05TEzCX/cYn9
*/