/*
  [auto_generated]
  boost/numeric/odeint/algebra/fusion_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/numeric/odeint/algebra/fusion_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>



namespace boost {
namespace numeric {
namespace odeint {

// specialization for fusion sequences
template< class FusionSequence >
struct algebra_dispatcher_sfinae< FusionSequence ,
                           typename boost::enable_if<
                               typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef fusion_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

/* fusion_algebra_dispatcher.hpp
e4fElKFuglslADbDyMQIADRilkZpAEbgNop2XU4XBUu7XQLgmkjbBJg/f+Mi/usA/dn4lA5gEyRV/EZM//WPP0vfw/gRALh8wpdt3NAjkDb06JUaAHAdABiJwHkdTkJ3+HIYNvlxXa6d6M7v9vjvmyE6cfkrRU1bAbQ3gla5CJf97rzDYoRtVGoaGyNsvd5pgse2mHilwlmFJQxW12lhK2FnywWddhthp7vTbjfxurFJwiqt
*/