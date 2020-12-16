/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP
#define BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

enum algo_types
{
   CircularListAlgorithms,
   CircularSListAlgorithms,
   LinearSListAlgorithms,
   CommonSListAlgorithms,
   BsTreeAlgorithms,
   RbTreeAlgorithms,
   AvlTreeAlgorithms,
   SgTreeAlgorithms,
   SplayTreeAlgorithms,
   TreapAlgorithms,
   UnorderedAlgorithms,
   UnorderedCircularSlistAlgorithms,
   AnyAlgorithm
};

template<algo_types AlgoType, class NodeTraits>
struct get_algo;

template<algo_types AlgoType, class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker;

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP

/* algo_type.hpp
kn5kpK4dynX6kY3WPh7GfNN9yf7rWu+R5H1JsSt6D9pxTl/yzZPQvdusq/iT/erp73bfj/i73fuT/m73/qS/O3l/stCF3+LGn7T3v813+pNvtfa60vLZ5EdWZyeY0xhAHge63fuRgW73fmSg270fGehO3o+s/ifOO86VMuod7/Qjmy0fSSsj8R/7LZvybvf+Y3m3e/+xvDt5/7E6iTnHyHxcV4HTr2ohb0J9eaP5jf3X3VC3e58q1J2831idYL5RL/t9E5z2tY2HNPt0f7E2gW1tA7CtrTt5f7E2251PfLjQeR+/j79OzbYYP7FfGzsH0Pd0dg/s3t3ZnbyfWJudnJ8Yyau0ImdebbP2WzXnFf5h/3nV0+3eP+wZYF71dCfvH9ZmJ+cf2t+cnWSsVyhl55XJL+w3vzw97v1CT8/A8svTk7xfWJudnF9ot8NJTr+wlfwqduaX+IP9163inuT9QbEnqp+fP9npD34sn3u3QUf8wH71C/S47ycCPe79wECPez8w0JO8H1jrwu9w4wceBzuGcJ+wge4HNlT7fh0mDfR/9K/nb9/nvWvMh4491X5y7obhfb/+3ft+mfd7G7r9wGS9mLw7QL8EderrxWSdhIXng/Z6I+GfLPz6uqELhT8g63+W2HLyjBnMM8idJXKlYC44R5MLJJA7U+RmilyJJlcpcgUGuUKRmwiOB4s0uVACuWKRmyJyp2pybQnkThM5bX8pkYNX5PwGuXEily/rsMZrcj0iV2SQmydy54ATwXNBKW/m/uOX90dF7j693OCPV94fFP7dUt4f0uSYG45bbu8TuTul3Fo1uWACudtF7j0id4cmx1xk3Py/QeRulPy/SZNrTyD3DpELidwtmlxXArkdIneryN2mtx/k4pV3i8htlfLepsn5u+OX9x6Ru1vK+x6tvAPd8ct7i8g16uXWHb+8q4W/Rsq7Vm833fHL7S0it0HKrVJvNwnk1onc1SL3Jr3ddMfP/0tFboXk/2V6u0kgt0rkVotceZ8cgvHlrhS5tSJ3ld5+euKXd5nIXSTlfbHe7/XEL+86kauX8r4WXD7CM6A1UpUdjnVS+hqpIV8fJWujTOui/uPWRMWuhZJ1UP/xa6AGuv5psOueYtY89bveKWat05Cvc3K7xklb32Ra2zToNU3/7PVMMWuZ/mPWMcWuYZL1S6a1S67WLe2FIuuVKllbswO6HzoEvQj581n/A9VAu6B26DB0Epo2Ps2zHGqB2qAu6CQ0rYC1TFAlFIL2Qp3Q85BvQpqndMLwGp7h3//H71/3/n9T01C8/3+Kx5d9PbLTL7X8ITV11dzStMH6sIb1SV11fTvXD62Iut6Ebo1bYLDWD0zU1g80eGW/oci+F9D9efik4ffSL1qzho/tVtVsiMSEMrJ3/NXZqWAmsdzit6j/+afInFGdN/4cinkOKP5ciS9khf+qZ9X7913W9Ns/fLMu5YaHx74Wf27IPEcTf87FPHcTb45j6OYmhmquRPYskfKknOVc37PkVvGld4I5MsacJGPMEvC94BwZsxZgR+ks1oBCMX6z7jPbfnKR+MXiE9v+cAeEH2z7wCXQcqgX3iDYCmm+rMNnFX8VP7XPR+2CeiHL/9wV429uh3ZDun+5CMKHxH/s8xtrIPzAuD5gCSS+nu3nHYaUPyd+G/6a7qeJj6b7ZcgoPwyETkKxvteDkO5riY+l+1f4VdE+Ff6U7UsVQPMgs4+EbMQvqiBvIfF/8H2cfk8FeAh8HsJ/wV+xfRXbRwnOGvYZhn/Dv+Hf8G/4N/wb/g3/hn//+b9/2fi/pnbTUIz/rfH7pHEe+73sIhm/p4s9I6AbiDvwXPS7LSRftbWBd3Bqm1o=
*/