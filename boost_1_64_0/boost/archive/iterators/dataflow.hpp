#ifndef BOOST_ARCHIVE_ITERATORS_DATAFLOW_HPP
#define BOOST_ARCHIVE_ITERATORS_DATAFLOW_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// dataflow.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

// poor man's tri-state
struct tri_state {
    enum state_enum {
        is_false = false,
        is_true = true,
        is_indeterminant
    } m_state;
    // convert to bool
    operator bool (){
        BOOST_ASSERT(is_indeterminant != m_state);
        return is_true == m_state ? true : false;
    }
    // assign from bool
    tri_state & operator=(bool rhs) {
        m_state = rhs ? is_true : is_false;
        return *this;
    }
    tri_state(bool rhs) :
        m_state(rhs ? is_true : is_false)
    {}
    tri_state(state_enum state) :
        m_state(state)
    {}
    bool operator==(const tri_state & rhs) const {
        return m_state == rhs.m_state;
    }
    bool operator!=(const tri_state & rhs) const {
        return m_state != rhs.m_state;
    }
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implement functions common to dataflow iterators
template<class Derived>
class dataflow {
    bool m_eoi;
protected:
    // test for iterator equality
    tri_state equal(const Derived & rhs) const {
        if(m_eoi && rhs.m_eoi)
            return true;
        if(m_eoi || rhs.m_eoi)
            return false;
        return tri_state(tri_state::is_indeterminant);
    }
    void eoi(bool tf){
        m_eoi = tf;
    }
    bool eoi() const {
        return m_eoi;
    }
public:
    dataflow(bool tf) :
        m_eoi(tf)
    {}
    dataflow() : // used for iterator end
        m_eoi(true)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_DATAFLOW_HPP

/* dataflow.hpp
62BJi3FleqLxNUYTrfc+O0g0nXzHvimG/nz8G9mr+rS/n1bTyN7QXa5/rkQDHY35gV8/GCK+PEArir/HF+7+vOyUCYVS1gZEhwjP7B/p5RUPsQyTB22Abnqihxc05tNOUBvjFy7GU5VcbaOm83ruIeQ0AKuMVHxRN+qnp4IveiT1fj2t9h2Tz0M3iajmnWiqenKJDtaoMiBF5OUvpwkwOsHA4fx7cTt7uXVul7N+UNM0JESG+8jNnuu5KpVGLxfDpIovnmLIozP5F5VoVfF6enXu6qJMXyGq2TkPeyJVYrW9OlqyU/LoI3fNL/o+Hp3d2jv39HHp7kTDo5e3MFPbxdlQIjoHjSiKgeM0xDbSx9PZy5D2cWvv6aWmDftCpG2I2k7Qajui87QjXk4m1bTa96Xnk46azrO1iC/eVFGKKHgqvg2NxjEasU7R5uL/nr4qw2q+UBf9TeVXVMv1Zj5KVzWQK33xO8YlSlE1LqmGBVU/advezUWWt3GQI4uMjQ7Q6OMNpDtVibxenNbW2qaxXhTfyL6eVrxwXS9aE6ahGs3RIGkDOX2x1BJT7O8GjVhPim6s/bZyRQbEqMpVl33veB0VSU9NEww9ZJbWtt460NP1bey19S2t7QJ7CVo9BqnXt+p2UfOpPAotemZIzlSqHvbElYEdDbAxsVpVvupoPeWH8s6qR6leOUOxQ45eYVLsLudFkiQHySA/OrGcpo1kZR1vXVtt50bjrhx0E2Bufvs2Ml+tr0/dgO+iv1Vy8/Vv/BvoS6rw7e2n1bX/d7Q36esG2e/x6wm7uCB1J9mZL+/+G+oI8rkOaQUFfi/BN31fUVL0DcMuJZ0qLb4tnkOpSjxpBb9JPyfs+SvlyfgHlefvDX+9neIbWjeNsxNNZfC9IZo5aUkXECZVk6p1d65H7odG9k4G/gk5RkmybSh18kuQdAMYqIN/bEhYjBQZ4UD7kaho2qwEhNB4JenYgXWlQLoZdcuRKE2Aco/nhChyTAdFRodTj1evu9u07+ogVfvHDrbV8qo3F/d27d1dPP/h6dHOsA+tXckLo61n42OTV9r68dIvjlzfOd4FExMj+gf0z8hIXAtMtJ6Xo0PXxBBsAUJHtlWQzi5HVxEpMgKhQH9yHOJaCcJG5unzo7dXbIiv5EefASUdE5GukqaSf5E3tQdflpEuKajyYQJmSWaOQi1JnILiSP8dzZJ0NDgKXhJxBV/wCOt4ZKPwhFTmOwpdEQ/ZCokiE/HIcQuZ4AvdL/Epejk8RZeCkh/iKGlQUHRFHvU8YUMg4vhSHjN9enIaQoeC0JEdxMyYAIAxMKY/khFmgk9MwvRHQDIiSZdkxBYiEsgqqjgIdHxBko3gk42IQ8SpBOKp7GSWbJ+Tnnyh6IhoVPnT50ekk8MjREzD/Auk5DsnXRBpmCjVI3oQVVdOlZsIntzMJNPxiUc6AivNCEJHqWKSKdVKeqIpBE+JMScuOS2KU+kO4lrpMiIdVX6UfCjNpcRBQUlTL6G49HkS14Ir+DnpfilTjo2+W5OKUoOSMTORgJnQtYkk166Q0VCpA+Iz0gFFh0AXhJ6OJ2Sgt1VshK3MEzogx6/oyvEoceaRHkFOukp6StwiDiVNca3I9HkT8Ss98EuZSEcfB+lQPI50VzgSV45Akq/pz5HmV7ogTNfEJ5k8AkikL0YF0iWeokM80qEgbL/ElSRshYx0vsjIRqQjePp4BU9S5QeEnRyniEeH9fmhuFR5I9ogb6r8EE18OS9KPpQ46UIZUOW7sTWBjtcalEC0kQAyUO5e0qFrwSOga8I6ID5J9XGRHvFFnMJGNLnCE2mK9JR4lfiU/FDI4entKQiZPNron28peTA=
*/