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
fsmymh+4GblDi17OrpMYrdw7OHDmtNXpmUskZ4kwHH11UNUng8YmKRVOE18bbCgwoGPpFtZZYtkhp9zvXhSdbqN/9wTJ7zTdaRXYCt0IZbGlC5eV8dtTNOhJa9AU2pACPMDvlWOBe2vUE6zt2sKrvF6nirMorVvdwoCZynhiRo3IcVyvwXJ8HdKtakSRyBAOYpd1Y9Zt7b7CYdKEfe7o2ORcA9EET3wbY2eHnrTOvPZFXg+d21aT+TxcnB0dTRaLka3U3Kn0irevUBB+WxfPNP+Wr9fj4+nZfOJ82cwiqZT9V2drvEKN/7jjWBZbp18e7nY7WoeH9GOM6gK6187Xr8K/J/OZv6PipvKt5Erdl2B9dP8Hr5IYo/MAq2q54xT20Y5dSNYlvh3XW2VUNjY1jm6PBM0o4HldMcVA9potgHQNMMB9+87jHyvMEXZNQXvDnsWlnjOeAT7HVr/28xMNH0ihnaFHeW6x9pwwyjgrqvJ5s/iwrDA31EgR+GPFCyz8PTKbktPpuMnpFlKK53iZ3FsVdzQab269NAduObXyWwbNtm5P6kIUN/h/xZJs5H3x/gVQSwMECgAAAAgALWdKUnamupv+BQAAfhAAACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xp
*/