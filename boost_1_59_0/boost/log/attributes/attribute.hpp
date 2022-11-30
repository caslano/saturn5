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
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
*/