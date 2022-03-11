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