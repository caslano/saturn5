
#ifndef BOOST_MPL_FIND_HPP_INCLUDED
#define BOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // BOOST_MPL_FIND_HPP_INCLUDED

/* find.hpp
CvzI2IxtErhOD+PgBw5+4OBtEweMR8G2LKIzx+F/j68nV2Ai/weaNsBJv/cNJT+0Q/+EvzKCDbCHG23hifJiX4n51dcib7+RXmCZPP5LNcrTOGKsW2TL30xbRJqcNIgo2Ub9T6K8tnCuO6ofWUgrHLrGxOQX1seMxyjg0W48v9WlSf110Ctv39a+v0/G7bp88vQR17WdXlWbNL2hAuvfXOf50hp9oiQWxvXEzA23+ESp09GPudiltC5aq8IJ4b1gAZEbef5/Uy8vW3COuqrMuECtJ7w8GP2u0o5ewyJ5UnAmCjbehIK8ftBiSWGtjGxU7OeFUy+WKy8XDnRVXckaOiWunUNak0GML70TTa6h6VU3Jq91u9RwXKQ/agjzFXao5DapJHZi7LhIgaTdpdPCKi2T8Ix9hYCVGQ9DtUJzSVam3fOO0Mpk0T9pho3LWIsPjsK9O1L37jcJx2du1L2LA3Uxcqy8ggYavZGve0OUG+iNfKs3xgAULL4BbaZAi32DemO81RtIm6TSLqDQmSE1TkgYqRLOlBlXR8tb1iUbP87q4s0ThgcjfDyMIfL7cBTs0zGLsQvZL9RwaAtEyvlSuymn1Jh7hbYYkZWK42/G03+idYqU7ToJzUtSNr3ytRMPrfw/6tIt7xdXoZwyY9aleoonT/dNSUy3MXJyTwoZU6LJGHTq/P9Y1F5+Gn9qz1WTNItLwv8mFClJs8sYlSuxPsTE1/nuuS1prRqeV/KhoDGiQrU6+XzLnXV8Qry5Z0aoem7/apv4rND5zp3YJj6VI2z4rL+sTXwqgE8cPxhAAraERR9hu9+w1HjvfLwqkxK5ILSizNg7Cp/bnVkm/BdmKvjPn6vha6ULJL4rLkH7VD09dBr8fysoytqlSE6/vst1fZPOtbcHG5wloBSfqqu71MFdB9eJCdhqpBkFwFzfPqiKu0+nV2WnBjq0pgCOMBrwiYj4Xe1Q8vRwa/cUKEDM1zmU5gis+1sqjz5BUIDL2N6hIDKovmQNMbvOEhCsoL58DWVeRQ56F6sORD2niQUEArYbq2TWqqRuDCe/XnZQtZsq6LLJifain8hqysPM1yoZo2faS7+mDwOe+qJV63H1IqGjtUKYcOD+Qxdwr2BsjTM17goHmrrl9sGvQohVadVXHSmXEd7UeoWd8bSDZs6NZDO+ulEPOhJPFJjGoDFojGQ18uXNtiW8dtYRWnjT/DE9LUvCL5YU6tt9Lm+TX0zT+YZOapNfjC6086/SNvnFq0580FsH8h6YnYT/DVV43lDeNv/T+caH2+Z/Q23tube6zfaMT4LPQF1Pt3PbxMcv+UCYbeGzZ4gNH8+MNvEZjfP/b6biHz3s/KOT5h+1QxT/2GDyjw9ddv6xIWQ8AFWNnoMvuXjeM//YWGo83BFzkOZT+UbJPFNnRj0/AqwNxD8MukF6up0DfIuSUMIYZl8aZjiqzjer5rRLqN4K1Dsovl5IadY8HSB3htVxaNw9jpRuPGcNGunR8XP20RlHbs7q8cwerMb98fl4iKeffeeo9A/nt0k/W3W+Z8e2ST+rzrHRT1Ob67nQv4Y7pTApfhN0+scXtS3/6HxHlbYt/9jx81zYJn0vwnyz3hvi3o249+DNzvcxce+Tcf55g3M/uVYMFRtM/08Kc7SezONgs127y0tuw1pV05tbarV6PdvasfFsEYxnG0/yKAi+ml3w6G87P1nuxS6QGkuNgQV2PSamyxtEqA4AWLDXOABgv9rpTHUC2gCRgYz22O21CCaoa7VB6VrLoIHXcahm49D9Kgz68lGnXZQOiJQe4B4pat2uUO9RTxtniVDtI4vmuRh1TphjnEokSsGjKaA0+78D3Doa+ds=
*/