
#ifndef BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED
#define BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/aux_/reverse_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_fold
{
    typedef typename aux::reverse_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , BackwardOp
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,reverse_fold,(Sequence,State,BackwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_fold)

}}

#endif // BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

/* reverse_fold.hpp
LktCTyevsMSy2QYnZYKT0GiOYdHTXTuNns4Fos94C3IEvx7R62DH7ziCva7818YXlH/2DbWbFD+2EYpXjhalMMwWoafQQDH4enB5oVYqNrdJNyv8SM/PP/eFmOPD6T6XGQW/+Yt1fEApmPmqzsw4jA5PtEQFCKRK8DezNdpbwrrueuEwPJ/h/5+PM76NMPP/9lMR/I+Q/P/cIfgvAP+da038o550cQMdkaNby2smgRJUe8/yPLQ9jjy5ZnmyI+XJlfI8Yxd8jhfXCnpobH/ROkuRIuQWa99/Os4APbxXk89u/JfNt87sv4bZ4vsjDNlVfw/2eN7h27uC3Z53+GRn7HKcf0mA/r/YuxbwqIornN1swiZs2EU3ECBIKqAoKGhA0YCGl9KaYIKkolXrA/W64gsSRCUIhmiWZRWqqdZXfbXiq/VVRQsUqIJarYhoqaU1QFpv3KihoEYJpmf+MzP37m52swG07dcu3xfuvTNz5szMmTNnzpxzJr0T+PUdwze3kxiHjzH5n3s3ObzPVjQl9s+4742m9igdad5KO1+oLDOWUwdjIk2+QAkuB3EQ2TwKqfAsYEeOMJ5U2b6nslX6BX2AasamgWr2Xfki7Fuu4u2t4OnGnSz03Aw69YumGq9QomhvIN08Telhk8K7jOHVCXh3MbzjOoa35/EU4On7zpadXzOQlgPjbiV1H2KIL3QQ+Lv30FtGXi1en+bXVG4H0/qXT15rUvGHzSMesWIQwnzmGVuQYPO05wEd2+WPN9j5TmU1reNbvu7HUuzvl1EaXGNFzBxlmwANjwh9UsoxS49kuevHKphXG9PWzfbCzapwMwpXNJM3QKDAWFQiKeOSZ5AZm9YJbI2cmvVD5z9Nz29tkPYETM25L3KPtxIOaO2tqFdYP4mIHRVtARdQOwud5WJBYdA2fgGEkrsw9l0kW9g/YP0jfCx/S7bRQiTScHiesGI2N90H+OF68TrVeF4h+nfeIqNe9lwc9UZTyp6L1vq/XvWHWY+aXLYISa3F7/XzRbwY2kl3KXWMoCCjgfDACJ+7IZXDax1/uZTqM1aoRhSgsBv0uOBeWUGLNuyiiqHmaxNWXZNavOH3ubHMNMb/CoUlRuZlGCIpifPoDn9Mri+wlb5fhaV+6Jc28Ry+lrtfI4xgcpP5CJE9haoyNtMXAJnHW+aAy+YuPuVuteMfbogSxlaVewrnRj2RFaiHi5j1wIVWpBmP9uO8l92KvNDpdJF+uvrT9kpvvQJ/NNgLQ4EGYbX9Edkju9F2T6lszQLel1MeobnCJ3MVz5j8UjmG57xqjeEnm2Lkl2EK0nGcK+LTrGHtAwxojMpysAREuvG5HlG44G8DmMa+eoULH4wbXuWy9f5LcR2aFwa6gODDwLaK1QmyBdYf4izGZFXfw69YjfNz404NAea3PBhq/YVRb9R7MSSDKPun38vzFbJiVLZl3wf57745qq/7BEYbBjUtMC4wh1aqJS+q44x+MkzGF2ibMgt3dq2N0f6jUJned38n9vHA/9x1UfJDzToSxa9/XC4Kqbs52+zbygnCiFolssTZGx5ihPuk6aADjekq4Kf070eRZPFv16K/iX665IQdg9+jjyn8EvQfye+Vj8j+S6W/KX/vLub/+abk+VUXue/sQCRFOgR48FqV99XajgUdTb8QrTumZ7x7Yt7d0e+CT96s0Ok4/sMa8C8enPbowXEL36vJKS3Flv037SzROpdtgp2GCVbydswEG6gm2LU0wYY+ryZYf3U++bMn7DNsvCsVROL8nxQ+njh85sZO+JkKn7mEzz3PReND3PjOFVH4ePYFn/tWS3zccfjcuDYGnzMVPtcRPt1j8HGTTPdOFD4=
*/