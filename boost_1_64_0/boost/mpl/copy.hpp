
#ifndef BOOST_MPL_COPY_HPP_INCLUDED
#define BOOST_MPL_COPY_HPP_INCLUDED

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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Inserter
    >
struct copy_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

template<
      typename Sequence
    , typename Inserter
    >
struct reverse_copy_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(2, copy)

}}

#endif // BOOST_MPL_COPY_HPP_INCLUDED

/* copy.hpp
SgI22y2xM6eCtMG4BTtWiAyfagEZCgk23k9AYceFvCpLNWKfnD97cJXGJX3xK6rHiqh19ZkbsYL0ixFUqWRLKQHF7M/eA0SeBfo2CD7vbVUP0ErVhr+JiXSWnB2an6dN2sudtBCbVS07Txe71kkarIoNdR85muakdYg+bTSGEyD84I03FLAu3ws0rbOcTitCpy06pL7DPmTVqc8+ezxoFDjMRtnD+HP0585pUfrzu20b1J/VmL3F44xZ62VWqK4/qIdt5CQZJXemxI1Z2bYJkfulsjOMl0X44x9/5znrtGdCy6j2tGm8PT91tWeb3v/9W1x7tvp0e+5tvD1/+uiwtIftfy3E/if89kkXv51DyPocZE/X9R/lMyGrLmgE1xMYVzD+W9741nib/Z/UWHxfceFbRPhO/DoW30u8Bt+pjeBb+qHBd9/u745v59RYeVbjwvc6wvfBrwTfMzUOz3pcxnS/kVCfGwmFkhaXjNnH3FL5LbA2+r86XMOCaJoRRNZLPHC/qBNcc1zqrFfU2ffBqYJN0A9Z34NHQllQ4o35y0J+eU4rC6XJc6AsFHDHJJPnjLJQhjxnlYWy5Dm7LJQtzzlloRx5zi0L5cpz37JQX3nOKwvlyfOgstAgeR5SFhoizyPKQiPkOb8slO+OQSvPBWWhgiZTvPH+4PNvPkc/iBr24eEyhuZSv/zgS5HrfdS5I8UTZSF1MtjQUN4JZJlu/+DHcv4z8WGkOiPlX4BVIzs8hqu7FNX95QupDidTRy7HIcTTSkcq5qVyj9fDFLm3OLlvZd26DEwbqvVUeHbkTGgXtEvZVBo5VcAElrVVD6XXXuAhCXq2G+RsgAQDVRwTwMpGX6AayQy0ULmCy/ROo+lNr2tUCpT8C1StTRilh+9n1r/Ei6L6h4/0PgMRZcRZ5ING5w/De1HxCh4Rs2REXEsUKvhciK7CD6BG99J6+IS0ojZQ3S5QutjH2kJVzCBmAkQrARG5Cgr2BbxipCKak4bY334qfccX9aqGzfgLuB3DJ2OLEt/aqg/oHNfnqWXoYW013fs61gWHpV+IPnHRgqaRKRyx0dQxlwoojFkNrH9Wvx0WJ7rxEArQOavAafdREgM90XaSfqOG8qrCdrxWrt7nJKh9F7vs1wfqQ2jnQu9nkrJSpez9lFIArKClk7JIpTxGyhNj8IlgUHSZfcJbAukz5+tke1i1QDlQJ19PtvIEnWc+kI+9rc30EeWnvywfM63gRPqoig+uxMd/7BakM34PkciwT6KnWH+OD9KMP8dZr7I/xyVbxZ8j+fpXwZtLiyr3mrcbIPaU4xPFrLsf2tl0zxSj/xH8cuxHKhhhjzO6SuEzoxRAzacb3OQQ+2E7nPX/AfuHRE4kp+fU4oD9ZzJAwaUp0pW+TKcvm3x8cMQXaes47jWnd9R6fVxLwr9UBRb6AcGXkonweUzjk0u15yt8UgWftnDHa7x2o/+T6s57jsPUyqU+cz6v1Mj1AEp9wBrRNptDrvdgu4C743LZFIrl1HVqQIDAfGv2l83ZSnLGR7nSZkduUgImfcmN6ssiao6wxp4A/YffM+i2GxXX9JevA+tSL8pLBw92H29sqbWNl1qt/uzwL1FJkOipChGvtj1510mWprQo2fhXRBy5GwKZ5rI/Fsuzv9ZY7mIstwHLXRpLPKzexVhuc7Dc7cZyG7I0E0sj/4DfWqb/3UqrTCV3g1R7KPhTQJC9iA9Q2r8WZlRUGE7DrJ0OkxZzt1Vns8MaTnYKd7uAPqJs3m7D3bKochS/ertwtyNR8gCvZYyxbY3CbfXaZrYvQXsBgy7W1BWkos2YLw3a/+sUfVa56BMEfTrsT0if9R/E0mdUuwQ=
*/