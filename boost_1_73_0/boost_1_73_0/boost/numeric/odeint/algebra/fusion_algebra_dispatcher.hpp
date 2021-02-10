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
Ps2niLfK9k22VAVfdppN3MuxyRLF0wziFOPP3OLWKa1hY4rPmNCNu0UenaZcpbBBjn70eCF4MFAMGbtS6irb1taFR6PF4paELtDRHLHwc+eXauTSIJM8eb7ip/lQ9x1d34Zof+vUK3QqW5oDzcLx+UQ8dpiYjy+HUQA/+kj/Uxfy8O7w6j2cjJ4o7XkvHM2nw+cLe2h6W0ku9UbeW6is28bdH6gy78t40JTLAlFIrRuPfVBtV1d5h901CMvMaXdrX2r/AlBLAwQKAAAACAAtZ0pSSMbZbXkDAABhBwAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU5NC5jVVQFAAG2SCRgrVRhb9s2EP2uX3FwsM3OVCsp0GFJmmFqWnfGPDtwFBQGAhC0dLK4UaRAUnGMZf+9R0qePaxD9qE0bNLHu3vHd49MTr/eiOAUXhwsfBkNmkPErdG/Y+6+7M3YM3Qfinqg+SWQBA4hz2wEL4c8wzCEsB7lrV8z9hLQg6/N/yQ+8oH5JVkozEfe6GZnxKZyMLwZwfnFxY/wCl6fvT6L4T1XAiXcOVRrNJsY3hbB8nPFn57GFn+KAR1wOe5TZZWwYHXpttwg0FqKHJXFAriFAm1uxJr+CAWuQiiFRLhZ3K6m
*/