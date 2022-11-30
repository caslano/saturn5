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
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
*/