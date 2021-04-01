#ifndef BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unescape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<class Derived, class Base>
class unescape
    : public boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    > super_t;

    typedef unescape<Derived, Base> this_t;
public:
    typedef typename this_t::value_type value_type;
    typedef typename this_t::reference reference;
private:
    value_type dereference_impl() {
        if(! m_full){
            m_current_value = static_cast<Derived *>(this)->drain();
            m_full = true;
        }
        return m_current_value;
    }

    reference dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }

    value_type m_current_value;
    bool m_full;

    void increment(){
        ++(this->base_reference());
        dereference_impl();
        m_full = false;
    };

public:

    unescape(Base base) :
        super_t(base),
        m_full(false)
    {}

};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

/* unescape.hpp
rxcNZawNKaQzDEEvAfo9YiV/1Qmqvo00MHFe1UMtupE9NeNY4Ghl6Zk+IY9+vBWPT9SKNI7+hHUChW3rek52LFPkMnN4WaOXK1sngnhko2/Rjze/8EifmWyIEK47oVJB19lhJkSYtYeii4ieJ+JFgnPQ1XBqM6Rxt+Ym014fsiRVNsTmhvK49onmhVVM8p9eBsx/ymxywd1DC6oOw4Iv9oSaxAcZX88wJxkBbSA5iQKUxgMv7GGheTMhYFbvFmTwkKoT9U+HumTwuN2IgdNJk6rYqSv/7kBlKV12knVcWZEYq3NnrNmywHIisEG1jwfvtUMIDywy0qVhOQwE7kAgGLBMSkQEL1DLiYV59yEzrGB1i1xlUGCw9n+0LGqcJ0Te4ww/mWWfP/rcn3Avhzjr5HAel8PplFQ8bIsffYK9TGjJ7Iq3wSdThG5a2EjwPd9TEViHvE7nG8HLtujRp40L39MNGsCAeEPbhUky7hNiqiy5QeVwIgIWlDQ2jLt7Vi+ZaLslkn40LOFUDduKcY87gRqVdgckzUF8sO4ESCBfj1XN9ygVzODsiW7MsA==
*/