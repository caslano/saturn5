
#ifndef BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/transform_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(F)
    >
struct transform_view
{
 private:
    typedef typename lambda<F>::type f_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;
 
 public:
    struct tag;
    typedef transform_view type;
    typedef aux::transform_iter< first_,last_,f_ > begin;
    typedef aux::transform_iter< last_,last_,f_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, transform_view)

}}

#endif // BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

/* transform_view.hpp
90fzyVujNxvkK/x/5xYp5HgssZR3WWMfJ0loXV1w7EJyuhSASzzmsBc7vpy7ifm0LpXlxRWHDm45SsWG1DgBU9z0YSUOQeJQk+T+udfogWFHxh9lULNQYFre9baFxXQ4dL7aifWA14fIaBwY7vjprQG2aN0q2O7FYYAGT38im0gp5AmSEHRtGx/u8saMDemdXRljM0RZeq4gMk+3HH7QcBBxpoaDiV5xf3h4/bpzZihiiifRn+92Hj2vPCQZtO8UNmXpHq5n+JFwm48P+6LzAeuIk7AjlE6g64Lrotcjr8ju8nr4v5vvbcm4nbFAIFTIU3mVoye9bqxFPn0Os38OEuG3BikBbKalodC/ZoDS3LCc4Y5/yNvT2A43s4ieOcrSDSaUY2w+cqrbJU7TKUXRu8p8496nLBQ6EELOfVgacddnOH1z3YdVIqm5EuOMSYMP2y3LDO+IlsAtoMUtkoacWLjDL8w9Pl9R+YcRYrG7kcUujW9Bn+BQFaV+NAJJdJ1STQUFV+0KB51ben3HUR7jpI4dM4L+zwxUXLgp7tog+wT1+zI4k1ggOK4XcA==
*/