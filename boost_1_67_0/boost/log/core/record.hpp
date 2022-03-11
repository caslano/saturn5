/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

class core;

/*!
 * \brief Logging record class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The record can be updated before pushing
 * for further processing to the logging core.
 */
class record
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(record)

    friend class core;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    typedef record_view::public_data public_data;

private:
    //! A pointer to the log record implementation
    public_data* m_impl;

private:
    //  A private constructor, accessible from core
    BOOST_CONSTEXPR explicit record(public_data* impl) BOOST_NOEXCEPT : m_impl(impl) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record() BOOST_NOEXCEPT : m_impl(NULL) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record(BOOST_RV_REF(record) that) BOOST_NOEXCEPT : m_impl(that.m_impl)
    {
        that.m_impl = NULL;
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record() BOOST_NOEXCEPT
    {
        reset();
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record& operator= (BOOST_RV_REF(record) that) BOOST_NOEXCEPT
    {
        swap(static_cast< record& >(that));
        return *this;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set& attribute_values() BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set const& attribute_values() const BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * Conversion to an unspecified boolean type
     *
     * \return \c true, if the <tt>*this</tt> identifies a log record, \c false, if the <tt>*this</tt> is not valid
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Inverted conversion to an unspecified boolean type
     *
     * \return \c false, if the <tt>*this</tt> identifies a log record, \c true, if the <tt>*this</tt> is not valid
     */
    bool operator! () const BOOST_NOEXCEPT
    {
        return !m_impl;
    }

    /*!
     * Swaps two handles
     *
     * \param that Another record to swap with
     * <b>Throws:</b> Nothing
     */
    void swap(record& that) BOOST_NOEXCEPT
    {
        public_data* p = m_impl;
        m_impl = that.m_impl;
        that.m_impl = p;
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        if (m_impl)
        {
            public_data::destroy(m_impl);
            m_impl = NULL;
        }
    }

    /*!
     * Attribute value lookup.
     *
     * \param name Attribute name.
     * \return An \c attribute_value, non-empty if it is found, empty otherwise.
     */
    attribute_value_set::mapped_type operator[] (attribute_value_set::key_type name) const
    {
        return m_impl->m_attribute_values[name];
    }

    /*!
     * Attribute value lookup.
     *
     * \param keyword Attribute keyword.
     * \return A \c value_ref with extracted attribute value if it is found, empty \c value_ref otherwise.
     */
    template< typename DescriptorT, template< typename > class ActorT >
    typename result_of::extract< typename expressions::attribute_keyword< DescriptorT, ActorT >::value_type, DescriptorT >::type
    operator[] (expressions::attribute_keyword< DescriptorT, ActorT > const& keyword) const
    {
        return m_impl->m_attribute_values[keyword];
    }

    /*!
     * The function ensures that the log record does not depend on any thread-specific data. Then the record contents
     * are used to construct a \c record_view which is returned from the function. The record is no longer valid after the call.
     *
     * \pre <tt>!!*this</tt>
     * \post <tt>!*this</tt>
     * \returns The record view that contains all attribute values from the original record.
     */
    BOOST_LOG_API record_view lock();
};

/*!
 * A free-standing swap function overload for \c record
 */
inline void swap(record& left, record& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

/* record.hpp
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
*/