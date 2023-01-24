/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_norm_inf.hpp

  [begin_description]
  vector_space_norm_inf specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED

#include <map>
#include <algorithm>

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/reductor.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for vexcl vector
template <typename T>
struct vector_space_norm_inf< vex::vector<T> > {
    typedef T result_type;

    T operator()( const vex::vector<T> &x ) const {
        const auto &max = vex::get_reductor<T, vex::MAX>(x.queue_list());

        return max( fabs(x) );
    }
};

// specialization for vexcl multivector
template <typename T, size_t N>
struct vector_space_norm_inf< vex::multivector<T, N> > {
    typedef T result_type;

    T operator()( const vex::multivector<T, N> &x ) const {
        const auto &max = vex::get_reductor<T, vex::MAX>(x.queue_list());

        // Reducing a multivector results in std::array<T, N>:
        auto m = max( fabs(x) );

        // We will need to reduce it even further:
        return *std::max_element(m.begin(), m.end());
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED

/* vexcl_norm_inf.hpp
UDN48Q0hhqm2YRfrm/NOsAHxlRsC/Zm+8CB/tu/PNwP9Bb7xLsbxEeWrB9Vr6/MrB9U3sjJct0Fty5LQvOZMSsi2pK27twfWawjsdurby8NPNNF+lhbd9jCn+aKbZHOaQood/Pj7zLs0n7nK7GipuuJ4E/gnt9SM9aMBIWca2om1LbuoTeSpzI3mWb7rmHsBuuOZmzZHOzA3zhW+5eGXtOO/BeGXgldd6g0GquiK7yT0F5hg3ueVplQNmlYvlELgcP+QlEEWTbbv2WII3Rtn6Ru2yW/ogsnaWboQdMPv+iZwFPuWKKxbQHjs77oK6sfvmuih7JaegGrffC2anqUzWyRibE1uQbbaJQeB0cmT2Bqf9sZ/06tpeL1W05Zd8Zs+2o3MPQ7dlxdTcznRfZq5p6P7J+YmoeYIc5Ocm3EzGXDVoCxpZW7kKL7fvrikMcbnjlxq3Lwtk+g3/ysk9TO7xqOXAgzOROq0jFTZtLqx+USiL+PNWs3A0SNc0obB9acuaWvuhzFc446pvs5B3DLWZ06rCzKX6Dz8cqA9A94F2k9ootrxLeJbn/ZrYd+zRWvmddqS3CLPHqDqqG58VVuSn2VqEdOv+pK858c09zs+5uvW+dP4ucrNr/Al+ekkdf1quoEvR29apw/48Vr51UnaBsrUidqiOb6ObaA87ye9eFtW3mNbeXltp6nrZI9WzpsppOjMdG/9Bh/8cKaL
*/