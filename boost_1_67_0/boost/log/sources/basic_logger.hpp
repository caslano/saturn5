/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_logger.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a base class for loggers. Convenience macros
 * for defining custom loggers are also provided.
 */

#ifndef BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_

#include <exception>
#include <utility>
#include <ostream>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/addressof.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

/*!
 * \brief Basic logger class
 *
 * The \c basic_logger class template serves as a base class for all loggers
 * provided by the library. It can also be used as a base for user-defined
 * loggers. The template parameters are:
 *
 * \li \c CharT - logging character type
 * \li \c FinalT - final type of the logger that eventually derives from
 *     the \c basic_logger. There may be other classes in the hierarchy
 *     between the final class and \c basic_logger.
 * \li \c ThreadingModelT - threading model policy. Must provide methods
 *     of the Boost.Thread locking concept used in \c basic_logger class
 *     and all its derivatives in the hierarchy up to the \c FinalT class.
 *     The \c basic_logger class itself requires methods of the
 *     SharedLockable concept. The threading model policy must also be
 *     default and copy-constructible and support member function \c swap.
 *     There are currently two policies provided: \c single_thread_model
 *     and \c multi_thread_model.
 *
 * The logger implements fundamental facilities of loggers, such as storing
 * source-specific attribute set and formatting log record messages. The basic
 * logger interacts with the logging core in order to apply filtering and
 * pass records to sinks.
 */
template< typename CharT, typename FinalT, typename ThreadingModelT >
class basic_logger :
    public ThreadingModelT
{
    typedef basic_logger this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Character type
    typedef CharT char_type;
    //! Final logger type
    typedef FinalT final_type;
    //! Threading model type
    typedef ThreadingModelT threading_model;

#if !defined(BOOST_LOG_NO_THREADS)
    //! Lock requirement for the swap_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > swap_lock;
    //! Lock requirement for the add_attribute_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > add_attribute_lock;
    //! Lock requirement for the remove_attribute_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > remove_attribute_lock;
    //! Lock requirement for the remove_all_attributes_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > remove_all_attributes_lock;
    //! Lock requirement for the get_attributes method
    typedef boost::log::aux::shared_lock_guard< const threading_model > get_attributes_lock;
    //! Lock requirement for the open_record_unlocked method
    typedef boost::log::aux::shared_lock_guard< threading_model > open_record_lock;
    //! Lock requirement for the set_attributes method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > set_attributes_lock;
#else
    typedef no_lock< threading_model > swap_lock;
    typedef no_lock< threading_model > add_attribute_lock;
    typedef no_lock< threading_model > remove_attribute_lock;
    typedef no_lock< threading_model > remove_all_attributes_lock;
    typedef no_lock< const threading_model > get_attributes_lock;
    typedef no_lock< threading_model > open_record_lock;
    typedef no_lock< threading_model > set_attributes_lock;
#endif

    //! Lock requirement for the push_record_unlocked method
    typedef no_lock< threading_model > push_record_lock;

private:
    //! A pointer to the logging system
    core_ptr m_pCore;

    //! Logger-specific attribute set
    attribute_set m_Attributes;

public:
    /*!
     * Constructor. Initializes internal data structures of the basic logger class,
     * acquires reference to the logging core.
     */
    basic_logger() :
        threading_model(),
        m_pCore(core::get())
    {
    }
    /*!
     * Copy constructor. Copies all attributes from the source logger.
     *
     * \note Not thread-safe. The source logger must be locked in the final class before copying.
     *
     * \param that Source logger
     */
    basic_logger(basic_logger const& that) :
        threading_model(static_cast< threading_model const& >(that)),
        m_pCore(core::get()),
        m_Attributes(that.m_Attributes)
    {
    }
    /*!
     * Move constructor. Moves all attributes from the source logger.
     *
     * \note Not thread-safe. The source logger must be locked in the final class before copying.
     *
     * \param that Source logger
     */
    basic_logger(BOOST_RV_REF(basic_logger) that) :
        threading_model(boost::move(static_cast< threading_model& >(that)))
    {
        m_pCore.swap(that.m_pCore);
        m_Attributes.swap(that.m_Attributes);
    }
    /*!
     * Constructor with named arguments. The constructor ignores all arguments. The result of
     * construction is equivalent to default construction.
     */
    template< typename ArgsT >
    explicit basic_logger(ArgsT const&) :
        threading_model(),
        m_pCore(core::get())
    {
    }

protected:
    /*!
     * An accessor to the logging system pointer
     */
    core_ptr const& core() const { return m_pCore; }
    /*!
     * An accessor to the logger attributes
     */
    attribute_set& attributes() { return m_Attributes; }
    /*!
     * An accessor to the logger attributes
     */
    attribute_set const& attributes() const { return m_Attributes; }
    /*!
     * An accessor to the threading model base
     */
    threading_model& get_threading_model() { return *this; }
    /*!
     * An accessor to the threading model base
     */
    threading_model const& get_threading_model() const { return *this; }
    /*!
     * An accessor to the final logger
     */
    final_type* final_this()
    {
        BOOST_LOG_ASSUME(this != NULL);
        return static_cast< final_type* >(this);
    }
    /*!
     * An accessor to the final logger
     */
    final_type const* final_this() const
    {
        BOOST_LOG_ASSUME(this != NULL);
        return static_cast< final_type const* >(this);
    }

    /*!
     * Unlocked \c swap
     */
    void swap_unlocked(basic_logger& that)
    {
        get_threading_model().swap(that.get_threading_model());
        m_Attributes.swap(that.m_Attributes);
    }

    /*!
     * Unlocked \c add_attribute
     */
    std::pair< attribute_set::iterator, bool > add_attribute_unlocked(attribute_name const& name, attribute const& attr)
    {
        return m_Attributes.insert(name, attr);
    }

    /*!
     * Unlocked \c remove_attribute
     */
    void remove_attribute_unlocked(attribute_set::iterator it)
    {
        m_Attributes.erase(it);
    }

    /*!
     * Unlocked \c remove_all_attributes
     */
    void remove_all_attributes_unlocked()
    {
        m_Attributes.clear();
    }

    /*!
     * Unlocked \c open_record
     */
    record open_record_unlocked()
    {
        return m_pCore->open_record(m_Attributes);
    }
    /*!
     * Unlocked \c open_record
     */
    template< typename ArgsT >
    record open_record_unlocked(ArgsT const&)
    {
        return m_pCore->open_record(m_Attributes);
    }

    /*!
     * Unlocked \c push_record
     */
    void push_record_unlocked(BOOST_RV_REF(record) rec)
    {
        m_pCore->push_record(boost::move(rec));
    }

    /*!
     * Unlocked \c get_attributes
     */
    attribute_set get_attributes_unlocked() const
    {
        return m_Attributes;
    }

    /*!
     * Unlocked \c set_attributes
     */
    void set_attributes_unlocked(attribute_set const& attrs)
    {
        m_Attributes = attrs;
    }

    //! Assignment is closed (should be implemented through copy and swap in the final class)
    BOOST_DELETED_FUNCTION(basic_logger& operator= (basic_logger const&))
};

/*!
 * Free-standing swap for all loggers
 */
template< typename CharT, typename FinalT, typename ThreadingModelT >
inline void swap(
    basic_logger< CharT, FinalT, ThreadingModelT >& left,
    basic_logger< CharT, FinalT, ThreadingModelT >& right)
{
    static_cast< FinalT& >(left).swap(static_cast< FinalT& >(right));
}

/*!
 * \brief A composite logger that inherits a number of features
 *
 * The composite logger is a helper class that simplifies feature composition into the final logger.
 * The user's logger class is expected to derive from the composite logger class, instantiated with
 * the character type, the user's logger class, the threading model and the list of the required features.
 * The former three parameters are passed to the \c basic_logger class template. The feature list
 * must be an MPL type sequence, where each element is a unary MPL metafunction class, that upon
 * applying on its argument results in a logging feature class that derives from the argument.
 * Every logger feature provided by the library can participate in the feature list.
 */
template< typename CharT, typename FinalT, typename ThreadingModelT, typename FeaturesT >
class basic_composite_logger :
    public boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, ThreadingModelT >,
        FeaturesT
    >::type
{
private:
    //! Base type (the hierarchy of features)
    typedef typename boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, ThreadingModelT >,
        FeaturesT
    >::type base_type;

protected:
    //! The composite logger type (for use in the user's logger class)
    typedef basic_composite_logger logger_base;
    BOOST_COPYABLE_AND_MOVABLE_ALT(logger_base)

public:
    //! Threading model being used
    typedef typename base_type::threading_model threading_model;

#if !defined(BOOST_LOG_NO_THREADS)

public:
    /*!
     * Default constructor (default-constructs all features)
     */
    basic_composite_logger() {}
    /*!
     * Copy constructor
     */
    basic_composite_logger(basic_composite_logger const& that) :
        base_type
        ((
            boost::log::aux::shared_lock_guard< const threading_model >(that.get_threading_model()),
            static_cast< base_type const& >(that)
        ))
    {
    }
    /*!
     * Move constructor
     */
    basic_composite_logger(BOOST_RV_REF(logger_base) that) :
        base_type(boost::move(static_cast< base_type& >(that)))
    {
    }
    /*!
     * Constructor with named parameters
     */
    template< typename ArgsT >
    explicit basic_composite_logger(ArgsT const& args) : base_type(args)
    {
    }

    /*!
     * The method adds an attribute to the source-specific attribute set. The attribute will be implicitly added to
     * every log record made with the current logger.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    std::pair< attribute_set::iterator, bool > add_attribute(attribute_name const& name, attribute const& attr)
    {
        typename base_type::add_attribute_lock lock(base_type::get_threading_model());
        return base_type::add_attribute_unlocked(name, attr);
    }
    /*!
     * The method removes an attribute from the source-specific attribute set.
     *
     * \pre The attribute was added with the add_attribute call for this instance of the logger.
     * \post The attribute is no longer registered as a source-specific attribute for this logger. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    void remove_attribute(attribute_set::iterator it)
    {
        typename base_type::remove_attribute_lock lock(base_type::get_threading_model());
        base_type::remove_attribute_unlocked(it);
    }

    /*!
     * The method removes all attributes from the logger. All iterators and references to the removed attributes are invalidated.
     */
    void remove_all_attributes()
    {
        typename base_type::remove_all_attributes_lock lock(base_type::get_threading_model());
        base_type::remove_all_attributes_unlocked();
    }

    /*!
     * The method retrieves a copy of a set with all attributes from the logger.
     *
     * \return The copy of the attribute set. Attributes are shallow-copied.
     */
    attribute_set get_attributes() const
    {
        typename base_type::get_attributes_lock lock(base_type::get_threading_model());
        return base_type::get_attributes_unlocked();
    }

    /*!
     * The method installs the whole attribute set into the logger. All iterators and references to elements of
     * the previous set are invalidated. Iterators to the \a attrs set are not valid to be used with the logger (that is,
     * the logger owns a copy of \a attrs after completion).
     *
     * \param attrs The set of attributes to install into the logger. Attributes are shallow-copied.
     */
    void set_attributes(attribute_set const& attrs)
    {
        typename base_type::set_attributes_lock lock(base_type::get_threading_model());
        base_type::set_attributes_unlocked(attrs);
    }

    /*!
     * The method opens a new log record in the logging core.
     *
     * \return A valid record handle if the logging record is opened successfully, an invalid handle otherwise.
     */
    record open_record()
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
        {
            typename base_type::open_record_lock lock(base_type::get_threading_model());
            return base_type::open_record_unlocked(boost::log::aux::empty_arg_list());
        }
        else
            return record();
    }
    /*!
     * The method opens a new log record in the logging core.
     *
     * \param args A set of additional named arguments. The parameter is ignored.
     * \return A valid record handle if the logging record is opened successfully, an invalid handle otherwise.
     */
    template< typename ArgsT >
    record open_record(ArgsT const& args)
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
        {
            typename base_type::open_record_lock lock(base_type::get_threading_model());
            return base_type::open_record_unlocked(args);
        }
        else
            return record();
    }
    /*!
     * The method pushes the constructed message to the logging core
     *
     * \param rec The log record with the formatted message
     */
    void push_record(BOOST_RV_REF(record) rec)
    {
        typename base_type::push_record_lock lock(base_type::get_threading_model());
        base_type::push_record_unlocked(boost::move(rec));
    }
    /*!
     * Thread-safe implementation of swap
     */
    void swap(basic_composite_logger& that)
    {
        boost::log::aux::multiple_unique_lock2<
            threading_model,
            threading_model
        > lock(base_type::get_threading_model(), that.get_threading_model());
        base_type::swap_unlocked(that);
    }

protected:
    /*!
     * Assignment for the final class. Threadsafe, provides strong exception guarantee.
     */
    FinalT& assign(FinalT const& that)
    {
        BOOST_LOG_ASSUME(this != NULL);
        if (static_cast< FinalT* >(this) != boost::addressof(that))
        {
            // We'll have to explicitly create the copy in order to make sure it's unlocked when we attempt to lock *this
            FinalT tmp(that);
            boost::log::aux::exclusive_lock_guard< threading_model > lock(base_type::get_threading_model());
            base_type::swap_unlocked(tmp);
        }
        return static_cast< FinalT& >(*this);
    }
};

//! An optimized composite logger version with no multithreading support
template< typename CharT, typename FinalT, typename FeaturesT >
class basic_composite_logger< CharT, FinalT, single_thread_model, FeaturesT > :
    public boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, single_thread_model >,
        FeaturesT
    >::type
{
private:
    typedef typename boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, single_thread_model >,
        FeaturesT
    >::type base_type;

protected:
    typedef basic_composite_logger logger_base;
    BOOST_COPYABLE_AND_MOVABLE_ALT(logger_base)

public:
    typedef typename base_type::threading_model threading_model;

#endif // !defined(BOOST_LOG_NO_THREADS)

public:
    basic_composite_logger() {}
    basic_composite_logger(basic_composite_logger const& that) :
        base_type(static_cast< base_type const& >(that))
    {
    }
    basic_composite_logger(BOOST_RV_REF(logger_base) that) :
        base_type(boost::move(static_cast< base_type& >(that)))
    {
    }
    template< typename ArgsT >
    explicit basic_composite_logger(ArgsT const& args) : base_type(args)
    {
    }

    std::pair< attribute_set::iterator, bool > add_attribute(attribute_name const& name, attribute const& attr)
    {
        return base_type::add_attribute_unlocked(name, attr);
    }
    void remove_attribute(attribute_set::iterator it)
    {
        base_type::remove_attribute_unlocked(it);
    }
    void remove_all_attributes()
    {
        base_type::remove_all_attributes_unlocked();
    }
    attribute_set get_attributes() const
    {
        return base_type::get_attributes_unlocked();
    }
    void set_attributes(attribute_set const& attrs)
    {
        base_type::set_attributes_unlocked(attrs);
    }
    record open_record()
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
            return base_type::open_record_unlocked(boost::log::aux::empty_arg_list());
        else
            return record();
    }
    template< typename ArgsT >
    record open_record(ArgsT const& args)
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
            return base_type::open_record_unlocked(args);
        else
            return record();
    }
    void push_record(BOOST_RV_REF(record) rec)
    {
        base_type::push_record_unlocked(boost::move(rec));
    }
    void swap(basic_composite_logger& that)
    {
        base_type::swap_unlocked(that);
    }

protected:
    FinalT& assign(FinalT that)
    {
        base_type::swap_unlocked(that);
        return static_cast< FinalT& >(*this);
    }
};


#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, typename_keyword)\
    public:\
        BOOST_DEFAULTED_FUNCTION(class_type(), {})\
        class_type(class_type const& that) : class_type::logger_base(\
            static_cast< typename_keyword() class_type::logger_base const& >(that)) {}\
        class_type(BOOST_RV_REF(class_type) that) : class_type::logger_base(\
            ::boost::move(static_cast< typename_keyword() class_type::logger_base& >(that))) {}\
        BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_FORWARD(class_type, class_type::logger_base)\

#endif // BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, BOOST_PP_EMPTY)

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_TEMPLATE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, BOOST_PP_IDENTITY(typename))

#define BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT(class_type)\
    public:\
        class_type& operator= (BOOST_COPY_ASSIGN_REF(class_type) that)\
        {\
            return class_type::logger_base::assign(static_cast< class_type const& >(that));\
        }\
        class_type& operator= (BOOST_RV_REF(class_type) that)\
        {\
            BOOST_LOG_EXPR_IF_MT(::boost::log::aux::exclusive_lock_guard< class_type::threading_model > lock(this->get_threading_model());)\
            this->swap_unlocked(that);\
            return *this;\
        }

#define BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT_TEMPLATE(class_type)\
    public:\
        class_type& operator= (BOOST_COPY_ASSIGN_REF(class_type) that)\
        {\
            return class_type::logger_base::assign(static_cast< class_type const& >(that));\
        }\
        class_type& operator= (BOOST_RV_REF(class_type) that)\
        {\
            BOOST_LOG_EXPR_IF_MT(::boost::log::aux::exclusive_lock_guard< typename class_type::threading_model > lock(this->get_threading_model());)\
            this->swap_unlocked(that);\
            return *this;\
        }

#define BOOST_LOG_FORWARD_LOGGER_MEMBERS(class_type)\
    BOOST_COPYABLE_AND_MOVABLE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS(class_type)\
    BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT(class_type)

#define BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(class_type)\
    BOOST_COPYABLE_AND_MOVABLE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_TEMPLATE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT_TEMPLATE(class_type)

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

/*!
 *  \brief The macro declares a logger class that inherits a number of base classes
 *
 *  \param type_name The name of the logger class to declare
 *  \param char_type The character type of the logger. Either char or wchar_t expected.
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 *  \param threading A threading model class
 */
#define BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char_type, base_seq, threading)\
    class type_name :\
        public ::boost::log::sources::basic_composite_logger<\
            char_type,\
            type_name,\
            threading,\
            ::boost::log::sources::features< BOOST_PP_SEQ_ENUM(base_seq) >\
        >\
    {\
        BOOST_LOG_FORWARD_LOGGER_MEMBERS(type_name)\
    }



#ifdef BOOST_LOG_USE_CHAR

/*!
 *  \brief The macro declares a narrow-char logger class that inherits a number of base classes
 *
 *  Equivalent to BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, single_thread_model)
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_LOGGER(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, ::boost::log::sources::single_thread_model)

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 *  \brief The macro declares a narrow-char thread-safe logger class that inherits a number of base classes
 *
 *  Equivalent to <tt>BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, multi_thread_model< shared_mutex >)</tt>
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_LOGGER_MT(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq,\
        ::boost::log::sources::multi_thread_model< ::boost::shared_mutex >)

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

/*!
 *  \brief The macro declares a wide-char logger class that inherits a number of base classes
 *
 *  Equivalent to BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, single_thread_model)
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_WLOGGER(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, ::boost::log::sources::single_thread_model)

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 *  \brief The macro declares a wide-char thread-safe logger class that inherits a number of base classes
 *
 *  Equivalent to <tt>BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, multi_thread_model< shared_mutex >)</tt>
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_WLOGGER_MT(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq,\
        ::boost::log::sources::multi_thread_model< ::boost::shared_mutex >)

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_WCHAR_T

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_

/* basic_logger.hpp
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
*/