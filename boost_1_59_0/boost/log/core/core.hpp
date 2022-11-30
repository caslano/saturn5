/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   core/core.hpp
 * \author Andrey Semashev
 * \date   19.04.2007
 *
 * This header contains logging core class definition.
 */

#ifndef BOOST_LOG_CORE_CORE_HPP_INCLUDED_
#define BOOST_LOG_CORE_CORE_HPP_INCLUDED_

#include <utility>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace sinks {

class sink;

} // namespace sinks

#endif // BOOST_LOG_DOXYGEN_PASS

class core;

typedef shared_ptr< core > core_ptr;

/*!
 * \brief Logging library core class
 *
 * The logging core is used to interconnect log sources and sinks. It also provides
 * a number of basic features, like global filtering and global and thread-specific attribute storage.
 *
 * The logging core is a singleton. Users can acquire the core instance by calling the static method <tt>get</tt>.
 */
class core
{
public:
    //! Exception handler function type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

private:
    //! Implementation type
    struct implementation;
    friend struct implementation;

private:
    //! A pointer to the implementation
    implementation* m_impl;

private:
    //! \cond
    core();
    //! \endcond

public:
    /*!
     * Destructor. Destroys the core, releases any sinks and attributes that were registered.
     */
    ~core();

    /*!
     * \return The method returns a pointer to the logging core singleton instance.
     */
    BOOST_LOG_API static core_ptr get();

    /*!
     * The method enables or disables logging.
     *
     * Setting this status to \c false allows you to completely wipe out any logging activity, including
     * filtering and generation of attribute values. It is useful if you want to completely disable logging
     * in a running application. The state of logging does not alter any other properties of the logging
     * library, such as filters or sinks, so you can enable logging with the very same settings that you had
     * when the logging was disabled.
     * This feature may also be useful if you want to perform major changes to logging configuration and
     * don't want your application to block on opening or pushing a log record.
     *
     * By default logging is enabled.
     *
     * \param enabled The actual flag of logging activity.
     * \return The previous value of enabled/disabled logging flag
     */
    BOOST_LOG_API bool set_logging_enabled(bool enabled = true);
    /*!
     * The method allows to detect if logging is enabled. See the comment for \c set_logging_enabled.
     */
    BOOST_LOG_API bool get_logging_enabled() const;

    /*!
     * The method sets the global logging filter. The filter is applied to every log record that is processed.
     *
     * \param filter The filter function object to be installed.
     */
    BOOST_LOG_API void set_filter(filter const& filter);
    /*!
     * The method removes the global logging filter. All log records are passed to sinks without global filtering applied.
     */
    BOOST_LOG_API void reset_filter();

    /*!
     * The method adds a new sink. The sink is included into logging process immediately after being added and until being removed.
     * No sink can be added more than once at the same time. If the sink is already registered, the call is ignored.
     *
     * \param s The sink to be registered.
     */
    BOOST_LOG_API void add_sink(shared_ptr< sinks::sink > const& s);
    /*!
     * The method removes the sink from the output. The sink will not receive any log records after removal.
     * The call has no effect if the sink is not registered.
     *
     * \param s The sink to be unregistered.
     */
    BOOST_LOG_API void remove_sink(shared_ptr< sinks::sink > const& s);
    /*!
     * The method removes all registered sinks from the output. The sinks will not receive any log records after removal.
     */
    BOOST_LOG_API void remove_all_sinks();

    /*!
     * The method performs flush on all registered sinks.
     *
     * \note This method may take long time to complete as it may block until all sinks manage to process all buffered log records.
     *       The call will also block all logging attempts until the operation completes.
     */
    BOOST_LOG_API void flush();

    /*!
     * The method adds an attribute to the global attribute set. The attribute will be implicitly added to every log record.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    BOOST_LOG_API std::pair< attribute_set::iterator, bool > add_global_attribute(attribute_name const& name, attribute const& attr);
    /*!
     * The method removes an attribute from the global attribute set.
     *
     * \pre The attribute was added with the \c add_global_attribute call.
     * \post The attribute is no longer registered as a global attribute. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    BOOST_LOG_API void remove_global_attribute(attribute_set::iterator it);

    /*!
     * The method returns a copy of the complete set of currently registered global attributes.
     */
    BOOST_LOG_API attribute_set get_global_attributes() const;
    /*!
     * The method replaces the complete set of currently registered global attributes with the provided set.
     *
     * \note The method invalidates all iterators and references that may have been returned
     *       from the \c add_global_attribute method.
     *
     * \param attrs The set of attributes to be installed.
     */
    BOOST_LOG_API void set_global_attributes(attribute_set const& attrs);

    /*!
     * The method adds an attribute to the thread-specific attribute set. The attribute will be implicitly added to
     * every log record made in the current thread.
     *
     * \note In single-threaded build the effect is the same as adding the attribute globally. This, however, does
     *       not imply that iterators to thread-specific and global attributes are interchangeable.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    BOOST_LOG_API std::pair< attribute_set::iterator, bool > add_thread_attribute(attribute_name const& name, attribute const& attr);
    /*!
     * The method removes an attribute from the thread-specific attribute set.
     *
     * \pre The attribute was added with the \c add_thread_attribute call.
     * \post The attribute is no longer registered as a thread-specific attribute. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    BOOST_LOG_API void remove_thread_attribute(attribute_set::iterator it);

    /*!
     * The method returns a copy of the complete set of currently registered thread-specific attributes.
     */
    BOOST_LOG_API attribute_set get_thread_attributes() const;
    /*!
     * The method replaces the complete set of currently registered thread-specific attributes with the provided set.
     *
     * \note The method invalidates all iterators and references that may have been returned
     *       from the \c add_thread_attribute method.
     *
     * \param attrs The set of attributes to be installed.
     */
    BOOST_LOG_API void set_thread_attributes(attribute_set const& attrs);

    /*!
     * The method sets exception handler function. The function will be called with no arguments
     * in case if an exception occurs during either \c open_record or \c push_record method
     * execution. Since exception handler is called from a \c catch statement, the exception
     * can be rethrown in order to determine its type.
     *
     * By default no handler is installed, thus any exception is propagated as usual.
     *
     * \sa See also: <tt>utility/exception_handler.hpp</tt>
     * \param handler Exception handling function
     *
     * \note The exception handler can be invoked in several threads concurrently.
     *       Thread interruptions are not affected by exception handlers.
     */
    BOOST_LOG_API void set_exception_handler(exception_handler_type const& handler);

    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attributes to be attached to the record to be opened.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_LOG_API record open_record(attribute_set const& source_attributes);
    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attribute values to be attached to the record to be opened.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_LOG_API record open_record(attribute_value_set const& source_attributes);
    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attribute values to be attached to the record to be opened. The contents
     *                          of this container are unspecified after this call.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_FORCEINLINE record open_record(BOOST_RV_REF(attribute_value_set) source_attributes)
    {
        return open_record_move(static_cast< attribute_value_set& >(source_attributes));
    }

    /*!
     * The method pushes the record to sinks. The record is moved from in the process.
     *
     * \pre <tt>!!rec == true</tt>
     * \post <tt>!rec == true</tt>
     * \param rec A previously successfully opened log record.
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws.
     */
    BOOST_FORCEINLINE void push_record(BOOST_RV_REF(record) rec)
    {
        push_record_move(static_cast< record& >(rec));
    }

    BOOST_DELETED_FUNCTION(core(core const&))
    BOOST_DELETED_FUNCTION(core& operator= (core const&))

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Opens log record. This function is mostly needed to maintain ABI stable between C++03 and C++11.
    BOOST_LOG_API record open_record_move(attribute_value_set& source_attributes);
    //! The method pushes the record to sinks.
    BOOST_LOG_API void push_record_move(record& rec);
#endif // BOOST_LOG_DOXYGEN_PASS
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_CORE_HPP_INCLUDED_

/* core.hpp
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
*/