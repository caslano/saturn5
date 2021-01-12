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
FL3sx+dHw+uK4jEfi68XTAu7hVqV8+PxwiqmLOA3O7XKmYD3eUL/RBz9DO30IGGGlMC4XASdphoHn6T1QOX5KQqTH7zCPm36fuoWAYsTuk0+42UFSyau0LK+lW8EiBSVLvSz8eF2t+7ztA2Rd66pbT4cHmP9/Qz7upa1j4/VHFYNJy2TRFmzytFeWGykk8A+SBH0N+6rFyydraFcbPKxP9mPRtupyFihfVWx35Uu/4TRZWP7
*/