/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record_view.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record view class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/detail/atomic_count.hpp>
#endif // BOOST_LOG_NO_THREADS
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS
class core;
class record;
#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Logging record view class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The view is immutable,
 * it is implemented as a wrapper around a reference-counted implementation.
 */
class record_view
{
    BOOST_COPYABLE_AND_MOVABLE(record_view)

    friend class core;
    friend class record;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    struct private_data;
    friend struct private_data;

    //! Publicly available record data
    struct public_data
    {
        //! Reference counter
#ifndef BOOST_LOG_NO_THREADS
        mutable boost::detail::atomic_count m_ref_counter;
#else
        mutable unsigned int m_ref_counter;
#endif // BOOST_LOG_NO_THREADS

        //! Attribute values view
        attribute_value_set m_attribute_values;

        //! Constructor from the attribute value set
        explicit public_data(BOOST_RV_REF(attribute_value_set) values) BOOST_NOEXCEPT :
            m_ref_counter(1),
            m_attribute_values(boost::move(values))
        {
        }

        //! Destructor
        BOOST_LOG_API static void destroy(const public_data* p) BOOST_NOEXCEPT;

    protected:
        ~public_data() {}

        BOOST_DELETED_FUNCTION(public_data(public_data const&))
        BOOST_DELETED_FUNCTION(public_data& operator= (public_data const&))

        friend void intrusive_ptr_add_ref(const public_data* p) BOOST_NOEXCEPT { ++p->m_ref_counter; }
        friend void intrusive_ptr_release(const public_data* p) BOOST_NOEXCEPT { if (--p->m_ref_counter == 0) public_data::destroy(p); }
    };

private:
    //! A pointer to the log record implementation
    intrusive_ptr< public_data > m_impl;

private:
    //  A private constructor, accessible from record
    explicit record_view(public_data* impl) BOOST_NOEXCEPT : m_impl(impl, false) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record view that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record_view() BOOST_NOEXCEPT
#if !defined(BOOST_LOG_NO_CXX11_DEFAULTED_NOEXCEPT_FUNCTIONS) && !defined(BOOST_LOG_NO_CXX11_DEFAULTED_CONSTEXPR_CONSTRUCTORS)
        = default;
#else
    {}
#endif

    /*!
     * Copy constructor
     */
    record_view(record_view const& that) BOOST_NOEXCEPT : m_impl(that.m_impl) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record_view(BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record_view() BOOST_NOEXCEPT {}

    /*!
     * Copy assignment
     */
    record_view& operator= (BOOST_COPY_ASSIGN_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl = that.m_impl;
        return *this;
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record_view& operator= (BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
        return *this;
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
     * Equality comparison
     *
     * \param that Comparand
     * \return \c true if both <tt>*this</tt> and \a that identify the same log record or both do not
     *         identify any record, \c false otherwise.
     */
    bool operator== (record_view const& that) const BOOST_NOEXCEPT
    {
        return m_impl == that.m_impl;
    }

    /*!
     * Inequality comparison
     *
     * \param that Comparand
     * \return <tt>!(*this == that)</tt>
     */
    bool operator!= (record_view const& that) const BOOST_NOEXCEPT
    {
        return !operator== (that);
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
    void swap(record_view& that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        m_impl.reset();
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
};

/*!
 * A free-standing swap function overload for \c record_view
 */
inline void swap(record_view& left, record_view& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

/* record_view.hpp
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
*/