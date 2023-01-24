
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
BswbQsEpqqDVncb9+pGoMuNmYZwsF/0p86AM46XszZDGgrmKy5h0Z8sNDv3LqaN6raxX1+Em4yXntj8yAXzQ+xgftDdCWl5V4XW+Rb5CtV47yyXnKo79Vhq9CX6KZb5BexWbmjaSEAU2dQBXxLaxVl5Teh1TS3LpVOkMQnkh/xqCDaL7D4Q8ibykPHiVkD1OscM8tJn+PMBPHHbi387TmzM6bQVR5rAK2Jz4z2w25sbNivEr+vOHL6jLPFDglrDOebfLNGlgxNE4nSMOOwBw725/eRl0UpQMaA80tlJWF7TURLZIRtuzdHzFrSqdbIwly+86KNHiFxUGJMbNoQJSc6iCFaJmeVGfin4oo8l+lj2Uvz2kS4CN6PXSW5vsdGS6u+HbL0qD+E1PxYD4xyg5pWztP9aaGiMv5/WZ73m96SN8f/OE0AMobuWOhXAw4wX2hw2eXohKn8iV58e6sV4UCB0UWNiUsgCC4mac+b9aWkdI0cnJvijXhXHPCC2IxqtReR+znRY58Csoz3O4hSFbp0vRi5FyE+MrpcjDflea/SwdiWWUw0gxvtSMPXG0s/rwZP4r3/NEL4/hXPv5ww1mgdZ6DLFtX/ZuE7XhfmqnBz/HwzdDZSsRdanQUTHqg6KLuS3WmbRj6hf2T4DQrSL6XyUVGp1QGyGJeAUH/nTmhA4OF/Xeso0YnMO2k433HvGrWVtUG+p8ZbaWQ3yH
*/