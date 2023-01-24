
#ifndef BOOST_MPL_ITER_FOLD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_HPP_INCLUDED

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
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct iter_fold
{
    typedef typename aux::iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,iter_fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_HPP_INCLUDED

/* iter_fold.hpp
thR1fUKCdGEhjLqwYKHKTmnzoJeIR6FK/77T0j2w/InkNUWl2KCW8jr7Bz/Iuslu9Xx8AfwWmCTWrXHqIZRPp6pRih+4bnFjRr143W0BFM+LZo77mkcdUxGXJJKvrHEzn1yEoOIp9r0FxLIG9bhBBgPWeYjUciK6hFg9WCV7GsUZAE26x5A6F3S9BV9VM+sjvwWw82shm4473+7VzY5syAY0qrzsDLlYeqa1grhJt5ba9Dg7NEmAB4zVbwaOXUc0zD9gtY53Ix8yBm75Sg+H2lvJRSeQCs6kjZsO7tmX7/pV/O80fwrZuXlBqeXc56h6nEaMVo0IhPNaJuIcbVOYFDlErBKGtC3UMxeSsgTMH19nCaRixUCProRar+CnXudKgNP2Z7nqKaAjHCH3PENxTqjUJCVP1KviNrtbqqmZQJ2hDc3nCEyEaqyP1GToV+zeG4UD0NgMBA0wEgrsxHSQJWcFhQcdHN053bkaNvDl345+QsIre1g3IRgapHohZ2GalQy0DVo2gFTe/sTNT1nfft3WJ32dcQ+/uuL35L0c2ItZt4VxjoMYlXqVxI54nwgCSa9P+y63TF8oumMhwkei0FKyhY6Q5vxBrkLvYNql6o2fkjzxZtszzEecTXeFEmMeK4ZEVb/O7XuljOi7SF8sLVhdLgnZHxGhvTzZcMS26cPttEPb+fGNrefWpdvS4lJtOjtY/avg171ewJPt
*/