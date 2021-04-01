
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
7xAn22pZcpSpa7oWILUSGK1jcVh/KZb96a4hf2YbuezQ3S8QWYm0WFy5qvlPmT1bhMOkSSSKGweyGaRUiVQA3nUqEPgJHZewqzUku+jpQKmfAT2KyO0dQgscOxZYKtSRRmyyI46PxZE7kFRo2AGVvmrDq1EQvHzUsR78o3+LZmOBRNhfg+bg7wLYEx7+8YzwnfIrE+sFOpk/QvBDQd5rQv1qHuF71McOvmbnFu+RUNc5T9ql+/kmj46vELCot9fS1+cRhh4tienIag4N5r9EehwIJa9dnmFOFuRwChbvoq31eRFFLiHzz2HbcjLGSy1R2bnAvjELClFdPWoWdiPQbRrT5nHj3lMu9ngjQNuzUO0eh8BIxbigX6CiXRcHb+PhbWjQ4/pHWnSJCStcUS9eT/Pr/cD0MeCULRXr3C1E9awh4xgQD0AIV2erntdaWU8JnKanyI+AZf2EeJS9D/38uBSQHcRZHaTYKGUiqy6F59UppvBkw2piZ3BNi6HnbEnVchqETXM06DoAx0C+KeAAesMLG5VjjwiJvhrEaJooX24Qwb0/RWor1e9fmA==
*/