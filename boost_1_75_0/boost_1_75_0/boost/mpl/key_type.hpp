
#ifndef BOOST_MPL_KEY_TYPE_HPP_INCLUDED
#define BOOST_MPL_KEY_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct key_type
    : apply_wrap2< 
          key_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,key_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, key_type)

}}

#endif // BOOST_MPL_KEY_TYPE_HPP_INCLUDED

/* key_type.hpp
vjVZD2PhKWgZRtBLlEm19cEMQGkvM9VAtOxk6kIEqLffknAP6Z7lLKdw2QVu0YYIMmuFhC75GPoULZbWbAaIu45Y7bbQ0vwv8Eoend9QsgOjxO2FGAbxPl/X1vDQM2ML3zMx91on8NjeRIif8ueU2Ko0wCtk/HM+iDrEGeDXD2PZC1HwtdDP1YzsXn9LU7hJl56+Bto6zP0JNzsKTuJOjTBPxh+KLEjaWW0T6wJemP22+N04cUpji9fQhim8gl7SiLHi+eJp4+Li3mnyvSCmHYkpb9J3uYeC4RXChzENV+6eQnHfYf4IOVXwIye069jZ9LIb0RUizkhEdxT2rO7t6eBGgAI+SzDMtR0XxjuOvRJnNxc+Wt66blkV9F67uF9YACM+z6ytryxbfNs9cPIy5b2x5nO1bO4grz1J1XGSdoe2TK/vis9tatmK17VrSIzqewvhEKjs8DEQ8r14jKe0ODGYc7X0utbiUZ4XF9ZVmzD2dXuXNf9NWdEXDHKYfA+B/LYB7P2RA5r9oaycwHI3Frsm+JIczy1yZ9el3odgcDxFl58iQ0tTrejgIkXuzZdjP3zmXcZkI7D95g8e2iSTkONlG2rBPowATCF0jqOHKjFVVXmlBjoxs/gxMJPJhdPX0Gq3kDDCQE6G7cACBfyfn0mSzCyPol2o836OZ9/n75NcxMsk1ywgxLNBcwNj+qU22YQ2ApjjPHy8lnIv
*/