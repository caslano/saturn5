/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains attribute interface definition.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_

#include <new>
#include <boost/move/core.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS

class attribute_value;

namespace aux {

//! Reference proxy object to implement \c operator[]
class attribute_set_reference_proxy;

} // namespace aux

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief A base class for an attribute value factory
 *
 * Every attribute is represented with a factory that is basically an attribute value generator.
 * The sole purpose of an attribute is to return an actual value when requested. A simplest attribute
 * can always return the same value that it stores internally, but more complex ones can
 * perform a considerable amount of work to return a value, and the returned values may differ
 * each time requested.
 *
 * A word about thread safety. An attribute should be prepared to be requested a value from
 * multiple threads concurrently.
 */
class attribute
{
    BOOST_COPYABLE_AND_MOVABLE(attribute)

public:
    /*!
     * \brief A base class for an attribute value factory
     *
     * All attributes must derive their implementation from this class.
     */
    struct BOOST_LOG_NO_VTABLE BOOST_SYMBOL_VISIBLE impl :
        public boost::intrusive_ref_counter< impl >
    {
        /*!
         * \brief Virtual destructor
         */
        virtual ~impl() {}

        /*!
         * \return The actual attribute value. It shall not return empty values (exceptions
         *         shall be used to indicate errors).
         */
        virtual attribute_value get_value() = 0;

        BOOST_LOG_API static void* operator new (std::size_t size);
        BOOST_LOG_API static void operator delete (void* p, std::size_t size) BOOST_NOEXCEPT;
    };

private:
    //! Pointer to the attribute factory implementation
    intrusive_ptr< impl > m_pImpl;

public:
    /*!
     * Default constructor. Creates an empty attribute value factory, which is not usable until
     * \c set_impl is called.
     */
    BOOST_DEFAULTED_FUNCTION(attribute(), {})

    /*!
     * Copy constructor
     */
    attribute(attribute const& that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl) {}

    /*!
     * Move constructor
     */
    attribute(BOOST_RV_REF(attribute) that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

    /*!
     * Initializing constructor
     *
     * \param p Pointer to the implementation. Must not be \c NULL.
     */
    explicit attribute(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    /*!
     * Copy assignment
     */
    attribute& operator= (BOOST_COPY_ASSIGN_REF(attribute) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        return *this;
    }

    /*!
     * Move assignment
     */
    attribute& operator= (BOOST_RV_REF(attribute) that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
        return *this;
    }

#ifndef BOOST_LOG_DOXYGEN_PASS
    attribute& operator= (aux::attribute_set_reference_proxy const& that) BOOST_NOEXCEPT;
#endif

    /*!
     * Verifies that the factory is not in empty state
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Verifies that the factory is in empty state
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_pImpl; }

    /*!
     * \return The actual attribute value. It shall not return empty values (exceptions
     *         shall be used to indicate errors).
     */
    attribute_value get_value() const;

    /*!
     * The method swaps two factories (i.e. their implementations).
     */
    void swap(attribute& that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

protected:
    /*!
     * \returns The pointer to the implementation
     */
    impl* get_impl() const BOOST_NOEXCEPT { return m_pImpl.get(); }
    /*!
     * Sets the pointer to the factory implementation.
     *
     * \param p Pointer to the implementation. Must not be \c NULL.
     */
    void set_impl(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    template< typename T >
    friend T attribute_cast(attribute const&);
};

/*!
 * The function swaps two attribute value factories
 */
inline void swap(attribute& left, attribute& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_ATTRIBUTES_ATTRIBUTE_VALUE_HPP_INCLUDED_)
#include <boost/log/detail/attribute_get_value_impl.hpp>
#endif

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_

/* attribute.hpp
DbIa+TI+WFrZ5VDO402Vs/Mon7p/55yNGGdYGzgsT68NNJVXfd5kpONs3lh9HTyeayW69neRcQcr31lOOUhxeQHdRvfYjHzXU7p1dHpiN2j/N7nnOS7TRJk11v2YBo1O3Y851diLs67a2Uba9TBG5WE0tL+tpvvjKJvoyUmReui60ruArqsylL2Tvld84ebvCPlVl/nJyvy475AvwvIq07OUzifuMq3f9TKV+Re+l31h2FHtCj91zCXX/ue69myVL75M0tWO92IpY5Rdym3FmdDn1PezlHuLpbzKteI3Qnc5jThFOa0/R5dT43uJc71qXjvZE13ZxS8ph4fmGPIoaBjM8K1H0vlTZfcPpjzCXXMexUvafSZ2kyhFl1kRui76Ut1/yDPfPlDmL+CX1DXO9lXKz1Gl8zQ6krfONkXy96+i48pbXWe3mqvOISd0Ha3u5G8dqZMY+1bnHD6MkK8qn0tlXHO3ysPQ6piL55rrGMm7oHPbk9sHn0/cQvKufG5VeWfuF0ge6rrlhHKjkSkPcT/4/ae02u+DOi66rljQwa98nvRrVsl3xsQCQ1z058ZK4TeFFzdC/76YWBD6dwLR1We+3yxzHm6v5nnk3+VbozPtPuoo5wbJWqn58q2l1JR2+pOLdz37hLI325rl1a8uMH530WXnQ2XewNyfrkb6BnQr9vDEn1z0HXX6n5XOcNIiQs+haE39+nW8Va1z97/Ldxtne76nk9/RgVJ+B6hnEfHv+brUsbMsT6LpuZP+uNLvY+6Lzwt+7m5v8N3KmN1/vmRe5TXq2z3XqHuvVTavha7+GvURaq37N3O/HX1tfPcv7/jZwYydXY8leq3BPn1rvM1r173XqG8Kt+/vmPJkRN1Lvr677Z5X2ibdOGZQ9deuV3dNvnntvfdaffPae+814eY1555r7M1r0T3Pez595zR/rts7/3jlatgU4bu4+jspTM4MDsy9BBhhJuuQXWd1nA/j4TrYAl4AW8K1MEGuA+uQU8S9OeKecx0yBusVYGMYCdvA2nAQjIWDYQwcDsNgHgyHs2GsPhtM5iRKf2y1a31lmIQ7HNaFEYHw+WQ+n8w3XA07I9n2DVmnGgYnwuYwCyba5rATnAy7wSkwHU6FI+A0iFgzYB7MhQthHlwOZ8N1cA78KZwLr4Tz4C3wXHgHXAjvhYvgI3AxfBouhW/CFfBdWAw/hCvh3+Eq+CVcA8/wkU+wG9wI0+Am2A9eDAfDS+BweCmcAX8O8+Ev4Ep4BVwLr4QXwS3wl/AaeA3cCrfCDLgbToJ75L6UA5nXx7NqKAfXSzpvgw3hjbAJ3AE7wJtgd3gzTIW3wl7wFthHrgNngGSIPzeIP84zQLqjJ+cAqnLQC7aDZ8IusD9Mg2fBfnAQPBueDafCIXAWHAYL4XC4DI6Aa+BIuAGOknwdA7fBsTodZC4bnGlIh73oBda/14MPSDo8CFvB/XAgfAgOgvdLOdsHZ8j9wPOwXfyJcj4PhrNTa8Nbnc9RFfbuEXv3ir09zjNEq7D3pNh7SuwdcJ4hWoW9t8Vemdj7s7bHvSrsvSz2XhF7rzrslVdh76TY+1LsfQV1vShzMFIM9WKU1C/RUi/GwGQYC7vBOrCHXEs4ZF4MuoZwNJFy0BTWgc0c68EzxN5YsedcD97ScVZpXZgA68NExxmlHSF/q/C0k+epq5T7jnAk7ALHyP3AGTK7xd9C8dd5hkycnK1TH8bBhpIOjWBb2Bh2hvGSLu1gd9gEjpfrCTAR5sA2MB+2hQtsc30mlMxPgIMlHO4zBG2Oheo7mLRPE+CZcBzsCzNhPzgJ6v1BxN3G4q5zv4a/S7k4DmPgZzAWnoD67CGxf8BQ7xQ=
*/