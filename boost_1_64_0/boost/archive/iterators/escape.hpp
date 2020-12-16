#ifndef BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// escape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert escapes into text

template<class Derived, class Base>
class escape :
    public boost::iterator_adaptor<
        Derived,
        Base,
        typename boost::iterator_value<Base>::type,
        single_pass_traversal_tag,
        typename boost::iterator_value<Base>::type
    >
{
    typedef typename boost::iterator_value<Base>::type base_value_type;
    typedef typename boost::iterator_reference<Base>::type reference_type;
    friend class boost::iterator_core_access;

    typedef typename boost::iterator_adaptor<
        Derived,
        Base,
        base_value_type,
        single_pass_traversal_tag,
        base_value_type
    > super_t;

    typedef escape<Derived, Base> this_t;

    void dereference_impl() {
        m_current_value = static_cast<Derived *>(this)->fill(m_bnext, m_bend);
        m_full = true;
    }

    //Access the value referred to
    reference_type dereference() const {
        if(!m_full)
            const_cast<this_t *>(this)->dereference_impl();
        return m_current_value;
    }

    bool equal(const this_t & rhs) const {
        if(m_full){
            if(! rhs.m_full)
                const_cast<this_t *>(& rhs)->dereference_impl();
        }
        else{
            if(rhs.m_full)
                const_cast<this_t *>(this)->dereference_impl();
        }
        if(m_bnext != rhs.m_bnext)
            return false;
        if(this->base_reference() != rhs.base_reference())
            return false;
        return true;
    }

   void increment(){
        if(++m_bnext < m_bend){
            m_current_value = *m_bnext;
            return;
        }
        ++(this->base_reference());
        m_bnext = NULL;
        m_bend = NULL;
        m_full = false;
    }

    // buffer to handle pending characters
    const base_value_type *m_bnext;
    const base_value_type *m_bend;
    bool m_full;
    base_value_type m_current_value;
public:
    escape(Base base) :
        super_t(base),
        m_bnext(NULL),
        m_bend(NULL),
        m_full(false),
        m_current_value(0)
    {
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP

/* escape.hpp
D6IZ0YRNmOj++QiMTAgTkJxo4pOM5GJZnI/AyIqwFWGJEc2IJmxFehLZERhZESYgOdHEJxnJlfbX+0QUXxRh0RDGyrxA2JgwyYkmIExyooWY9IUK6VcjmoCwMWGSk1CeKowJk5xoAsIkJ1oZcAiLDid6hOhlogOQ3EpULWFjwiQnmoAwyYmW5LmVsDFhip9oAsLGhElO+gSEjQmTnGgCwiQnWr8Oywu+Qfb/8L8X2rh+8et7dHT2rG4ntXE1+LEs76b17W2JbfieouCr1A1DJQVygv0p5RxUBcNgE4EPDZFxVLyMzRJk7DFMoRNl7Kjwl45Q7BSclUMnydhXoR3jFf4gJZ6RMs5Q+DkhI8Hkb3oOMzefAH3wVsoV/G9avqi/sZz/qPBHz6UCg+nPx0/Xk776Igb1MA/5K7j1xAE8ar74Pq9gy3TOd9O18ntLkpWl7kvoMbUL68qvRBKqSXAA/XlBCinLwzV02V8ToYnWHesj2OL8I/EanxQZHagRTAN+kF9AjrZWownM0QigL+7GqAyiNfSELVwcZFYvJy/yS00OkpxNbeE/+p5D3Qtyv7Konvf5tdYquXpcL5dz/ynyEVLu82TPn819PvDS8zI91eC+NQzNL6jOl84jv66q/KjT8z33x+fXel8wSO9vLL9hfoL/Sv2E/Y5cUnCUIk+aZZK7/s798e+hJQm73w9TZ/3r78sogv4Ecv+T+y3k7rd63RD6Zl9gcJw490FL9ECCAQQKx0Avvqm9LaFvu9+VU5++fg4dG6PxoRtTuc/lhHzopqEkgqIUPYpAPGoOifChW1adGb08gKxUX+JT88UrQlEaTTQl8xVffpDrI47OUI03PrrxSfeiq5oW70ypafFOk/L2tsInFR9llhTpiMwavFYm+DQs6NmGfE3EV3wawhR1Pf1FLTCS2kGuNKL045q+YqMIkwZFQLEr8ar5hMhE9VzfL1DSj406OiLPIw6Ir2Ko3uM0PPkkNDDoy2EiKhNS0KpfYBTvO8dq5Zfe/aL7a/TPy7+YaxVlha8Mr7lfgVelRVUkvrSQK5+6zkC5++rEF7kzSLrOIIu+eT6j2vrG925kfaoR0jdcZ9G81kn0nW+PR5PwXenSGwrfpZ/HNK1a61nvkcczaa+MN+/JPb4dOpybnnr0Xz/+qYPjMSW/+2Q89SBhsb777yrPPyv89f4S9XWHUY2DdJf4iLWXD81GueXRQQENbWzsv9ZXjUN5xkdrM3WUhnLxRul35D9afR+38XTKdX8SnecWqDVBzH/h/tr5v7Rcbf9LyzXwv7RcMQrkhOA/K78XpuBD55Tx74KMl16VcdQpGTteknFSqiLP4V+Rsa+CkxS89FdlXD2l0Ar/vIKz/qzYK/Ko0zLOuKronVGwIvc4/c8dl//dwh+Os1o/HeTpATDc/Ks3/cp4XC/Xxl/Z6zvIe3wHSWfjIL8w3UXB7RQcrWCtwH8c+vxSVu4PVfPeX5rdKaeSq36/8+Yf73fLCbvfD+evfVs/+T09Y/H/r/+ez1/bXwf/jrzcH+6/Vb97fCdvuZWCm/xO/Zndyv37d4eU+gz+ct//S8qj5Idu6Nz+kkdf5efva8+v6+tf017638fNyP17RlMzvq98/y5B+2W95uPZvp1CiTFBfRSWGCt0jO8ap/LwXFA6akeFmp+nA4PiyXFg6BemqujylNvmTs8nUHV+rqBV5+YSrXZYCFrtsCA6T4cF8dUOC3V+8nRckL6qZIqeoSNDzddEGPLVjgxDvoG6SE8U2pDWlUOUNHe76/0zkWGBPnnlTfg7SCDOylLTigNE7f8YqLgU1H4N5dxBsaVQ86NUc5L6/AJD/kDh7BDbFcjxIev2LVI=
*/