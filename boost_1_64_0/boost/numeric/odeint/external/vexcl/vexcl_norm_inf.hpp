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
8bzn+IdaX9bxqRTuKAxkUSG17K1Lfec0/tuk3mjlNWa0S4BDv5/Ha87RahZRWgCncb/1T9b3hYMxDhHwj+aRTWIc3ay1hk57Llcqt/0nY9ttvDevLqFwhfdKZ/0ej4AydZM2XIicMtx58KIy4PHYDxYhjNLJWfTcvoAa89gD89sxPEpc/G8DuVf1eYh29hKQIlGlxMradOM5KPj6aE5neEOaYVYktXh9IZ6qyOIIJPB+nOHUTsoUwN6O9dAav6eHB5536so51PQ7Iy3E8wj4e2q1atSpfGvs4oQKcOaXPlwgDJPPxdiU5gDXTxjxLVfdwaarog/XhU3jfWLnXbCE9BdQaU1QmIdaOBuS8BCxxt7qE+FcPKSUDiXhXflWXtOhsbpCQMV1kkfvAT/Cu5wRA208i3NeivRJMA8HT8s+mpARxi2XKKQ/gP6snBymskK8ACjTkiyrAy8e5mY34W65mBwBBPEvVaPha+cJovYYoHp6IEtE6vL5EqvKDcUON7VsoQuOMvm9aVyixsUqd5J3pKu+JXbYXyG10oVtkf/0gxcst9DHlmiASZ1svQ==
*/