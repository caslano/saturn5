/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_value.hpp
 * \author Andrey Semashev
 * \date   21.05.2010
 *
 * The header contains \c attribute_value class definition.
 */

#ifndef BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/move/core.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/value_extraction_fwd.hpp>
#include <boost/log/attributes/value_visitation_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief An attribute value class
 *
 * An attribute value is an object that contains a piece of data that represents an attribute state
 * at the point of the value acquisition. All major operations with log records, such as filtering and
 * formatting, involve attribute values contained in a single view. Most likely an attribute value is
 * implemented as a simple holder of some typed value. This holder implements the
 * \c attribute_value::implementation interface and acts as a pimpl for the \c attribute_value
 * object. The \c attribute_value class provides type dispatching support in order to allow
 * to extract the value from the holder.
 *
 * Normally, attributes and their values shall be designed in order to exclude as much interference as
 * reasonable. Such approach allows to have more than one attribute value simultaneously, which improves
 * scalability and allows to implement generating attributes.
 *
 * However, there are cases when this approach does not help to achieve the required level of independency
 * of attribute values and attribute itself from each other at a reasonable performance tradeoff.
 * For example, an attribute or its values may use thread-specific data, which is global and shared
 * between all the instances of the attribute/value. Passing such an attribute value to another thread
 * would be a disaster. To solve this the library defines an additional method for attribute values,
 * namely \c detach_from_thread. The \c attribute_value class forwards the call to its pimpl,
 * which is supposed to ensure that it no longer refers to any thread-specific data after the call.
 * The pimpl can create a new holder as a result of this method and return it to the \c attribute_value
 * wrapper, which will keep the returned reference for any further calls.
 * This method is called for all attribute values that are passed to another thread.
 */
class attribute_value
{
    BOOST_COPYABLE_AND_MOVABLE(attribute_value)

public:
    /*!
     * \brief A base class for an attribute value implementation
     *
     * All attribute value holders should derive from this interface.
     */
    struct BOOST_LOG_NO_VTABLE impl :
        public attribute::impl
    {
    public:
        /*!
         * The method dispatches the value to the given object.
         *
         * \param dispatcher The object that attempts to dispatch the stored value.
         * \return true if \a dispatcher was capable to consume the real attribute value type and false otherwise.
         */
        virtual bool dispatch(type_dispatcher& dispatcher) = 0;

        /*!
         * The method is called when the attribute value is passed to another thread (e.g.
         * in case of asynchronous logging). The value should ensure it properly owns all thread-specific data.
         *
         * \return An actual pointer to the attribute value. It may either point to this object or another.
         *         In the latter case the returned pointer replaces the pointer used by caller to invoke this
         *         method and is considered to be a functional equivalent to the previous pointer.
         */
        virtual intrusive_ptr< impl > detach_from_thread()
        {
            return this;
        }

        /*!
         * \return The attribute value that refers to self implementation.
         */
        attribute_value get_value() BOOST_OVERRIDE { return attribute_value(this); }

        /*!
         * \return The attribute value type
         */
        virtual typeindex::type_index get_type() const { return typeindex::type_index(); }
    };

private:
    //! Pointer to the value implementation
    intrusive_ptr< impl > m_pImpl;

public:
    /*!
     * Default constructor. Creates an empty (absent) attribute value.
     */
    BOOST_DEFAULTED_FUNCTION(attribute_value(), BOOST_NOEXCEPT {})

    /*!
     * Copy constructor
     */
    attribute_value(attribute_value const& that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl) {}

    /*!
     * Move constructor
     */
    attribute_value(BOOST_RV_REF(attribute_value) that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

    /*!
     * Initializing constructor. Creates an attribute value that refers to the specified holder.
     *
     * \param p A pointer to the attribute value holder.
     */
    explicit attribute_value(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    /*!
     * Copy assignment
     */
    attribute_value& operator= (BOOST_COPY_ASSIGN_REF(attribute_value) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        return *this;
    }

    /*!
     * Move assignment
     */
    attribute_value& operator= (BOOST_RV_REF(attribute_value) that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
        return *this;
    }

    /*!
     * The operator checks if the attribute value is empty
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    /*!
     * The operator checks if the attribute value is empty
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_pImpl; }

    /*!
     * The method returns the type information of the stored value of the attribute.
     * The returned type info wrapper may be empty if the attribute value is empty or
     * the information cannot be provided. If the returned value is not empty, the type
     * can be used for value extraction.
     */
    typeindex::type_index get_type() const
    {
        if (m_pImpl.get())
            return m_pImpl->get_type();
        else
            return typeindex::type_index();
    }

    /*!
     * The method is called when the attribute value is passed to another thread (e.g.
     * in case of asynchronous logging). The value should ensure it properly owns all thread-specific data.
     *
     * \post The attribute value no longer refers to any thread-specific resources.
     */
    void detach_from_thread()
    {
        if (m_pImpl.get())
            m_pImpl->detach_from_thread().swap(m_pImpl);
    }

    /*!
     * The method dispatches the value to the given object. This method is a low level interface for
     * attribute value visitation and extraction. For typical usage these interfaces may be more convenient.
     *
     * \param dispatcher The object that attempts to dispatch the stored value.
     * \return \c true if the value is not empty and the \a dispatcher was capable to consume
     *         the real attribute value type and \c false otherwise.
     */
    bool dispatch(type_dispatcher& dispatcher) const
    {
        if (m_pImpl.get())
            return m_pImpl->dispatch(dispatcher);
        else
            return false;
    }

#if !defined(BOOST_LOG_DOXYGEN_PASS)
#if !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define BOOST_LOG_AUX_VOID_DEFAULT = void
#else
#define BOOST_LOG_AUX_VOID_DEFAULT
#endif
#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns an empty value. See description of the \c result_of::extract
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract< T, TagT >::type extract() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise an exception is thrown. See description of the \c result_of::extract_or_throw
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract_or_throw< T, TagT >::type extract_or_throw() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract_or_default< T, T, TagT >::type extract_or_default(T const& def_value) const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
    typename result_of::extract_or_default< T, DefaultT, TagT >::type extract_or_default(DefaultT const& def_value) const;

#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns an empty value. See description of the \c result_of::extract
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract< T >::type extract() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise an exception is thrown. See description of the \c result_of::extract_or_throw
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract_or_throw< T >::type extract_or_throw() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract_or_default< T, T >::type extract_or_default(T const& def_value) const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename DefaultT >
    typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(DefaultT const& def_value) const;
#endif // defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

#undef BOOST_LOG_AUX_VOID_DEFAULT

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type,
     * and pass it to the \a visitor function object.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_visitation.hpp</tt> prior to using this method.
     *
     * \param visitor A function object that will be invoked on the extracted attribute value.
     *                The visitor should be capable to be called with a single argument of
     *                any type of the specified types in \c T.
     *
     * \return The result of visitation.
     */
    template< typename T, typename VisitorT >
    visitation_result visit(VisitorT visitor) const;

    /*!
     * The method swaps two attribute values
     */
    void swap(attribute_value& that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
    }
};

/*!
 * The function swaps two attribute values
 */
inline void swap(attribute_value& left, attribute_value& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_)
#include <boost/log/detail/attribute_get_value_impl.hpp>
#endif

#endif // BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_

/* attribute_value.hpp
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
*/