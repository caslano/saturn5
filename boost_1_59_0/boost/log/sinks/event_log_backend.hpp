/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   event_log_backend.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains a logging sink backend that uses Windows NT event log API
 * for signaling application events.
 */

#ifndef BOOST_LOG_SINKS_EVENT_LOG_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_EVENT_LOG_BACKEND_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_EVENT_LOG

#include <map>
#include <vector>
#include <string>
#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/keywords/message_file.hpp>
#include <boost/log/keywords/log_name.hpp>
#include <boost/log/keywords/log_source.hpp>
#include <boost/log/keywords/registration.hpp>
#include <boost/log/keywords/target.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/sinks/attribute_mapping.hpp>
#include <boost/log/sinks/event_log_constants.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/expressions/formatter.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace event_log {

    //! Event log source registration modes
    enum registration_mode
    {
        never,      //!< Never register event source, even if it's not registered
        on_demand,  //!< Register if the source is not registered yet
        forced      //!< Register always, event if the source is already registered
    };

    /*!
     * \brief Straightforward event type mapping
     *
     * This type of mapping assumes that attribute with a particular name always
     * provides values that map directly onto the native event types. The mapping
     * simply returns the extracted attribute value converted to the native event type.
     */
    template< typename AttributeValueT = int >
    class direct_event_type_mapping :
        public basic_direct_mapping< event_type, AttributeValueT >
    {
        //! Base type
        typedef basic_direct_mapping< event_type, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit direct_event_type_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }
    };

    /*!
     * \brief Customizable event type mapping
     *
     * The class allows to setup a custom mapping between an attribute and native event types.
     * The mapping should be initialized similarly to the standard \c map container, by using
     * indexing operator and assignment.
     */
    template< typename AttributeValueT = int >
    class custom_event_type_mapping :
        public basic_custom_mapping< event_type, AttributeValueT >
    {
        //! Base type
        typedef basic_custom_mapping< event_type, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit custom_event_type_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }
    };

    /*!
     * \brief Straightforward event ID mapping
     *
     * This type of mapping assumes that attribute with a particular name always
     * provides values that map directly onto the event identifiers. The mapping
     * simply returns the extracted attribute value converted to the event ID.
     */
    template< typename AttributeValueT = int >
    class direct_event_id_mapping :
        public basic_direct_mapping< event_id, AttributeValueT >
    {
        //! Base type
        typedef basic_direct_mapping< event_id, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit direct_event_id_mapping(attribute_name const& name) :
            base_type(name, make_event_id(0))
        {
        }
    };

    /*!
     * \brief Customizable event ID mapping
     *
     * The class allows to setup a custom mapping between an attribute and event identifiers.
     * The mapping should be initialized similarly to the standard \c map container, by using
     * indexing operator and assignment.
     */
    template< typename AttributeValueT = int >
    class custom_event_id_mapping :
        public basic_custom_mapping< event_id, AttributeValueT >
    {
        //! Base type
        typedef basic_custom_mapping< event_id, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit custom_event_id_mapping(attribute_name const& name) :
            base_type(name, make_event_id(0))
        {
        }
    };

    /*!
     * \brief Straightforward event category mapping
     *
     * This type of mapping assumes that attribute with a particular name always
     * provides values that map directly onto the event categories. The mapping
     * simply returns the extracted attribute value converted to the event category.
     */
    template< typename AttributeValueT = int >
    class direct_event_category_mapping :
        public basic_direct_mapping< event_category, AttributeValueT >
    {
        //! Base type
        typedef basic_direct_mapping< event_category, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit direct_event_category_mapping(attribute_name const& name) :
            base_type(name, make_event_category(0))
        {
        }
    };

    /*!
     * \brief Customizable event category mapping
     *
     * The class allows to setup a custom mapping between an attribute and event categories.
     * The mapping should be initialized similarly to the standard \c map container, by using
     * indexing operator and assignment.
     */
    template< typename AttributeValueT = int >
    class custom_event_category_mapping :
        public basic_custom_mapping< event_category, AttributeValueT >
    {
        //! Base type
        typedef basic_custom_mapping< event_category, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit custom_event_category_mapping(attribute_name const& name) :
            base_type(name, make_event_category(0))
        {
        }
    };

    /*!
     * \brief An event composer
     *
     * This class is a function object that extracts event identifier from the attribute values set
     * and formats insertion strings for the particular event. Each insertion string is formatted with
     * a distinct formatter, which can be created just like regular sinks formatters.
     *
     * Before using, the composer must be initialized with the following information:
     * \li Event identifier extraction logic. One can use \c basic_direct_event_id_mapping or
     *     \c basic_custom_event_id_mapping classes in order to create such extractor and pass it
     *     to the composer constructor.
     * \li Event identifiers and insertion string formatters. The composer provides the following
     *     syntax to provide this information:
     *
     *     \code
     *     event_composer comp;
     *     comp[MY_EVENT_ID1] % formatter1 % ... % formatterN;
     *     comp[MY_EVENT_ID2] % formatter1 % ... % formatterN;
     *     ...
     *     \endcode
     *
     *     The event identifiers in square brackets are provided by the message compiler generated
     *     header (the actual names are specified in the .mc file). The formatters represent
     *     the insertion strings that will be used to replace placeholders in event messages,
     *     thus the number and the order of the formatters must correspond to the message definition.
     */
    template< typename CharT >
    class BOOST_LOG_API basic_event_composer
    {
    public:
        //! Character type
        typedef CharT char_type;
        //! String type to be used as a message text holder
        typedef std::basic_string< char_type > string_type;

        //! Event identifier mapper type
        typedef boost::log::aux::light_function< event_id (record_view const&) > event_id_mapper_type;

        //! Type of an insertion composer (a formatter)
        typedef basic_formatter< char_type > formatter_type;
        //! Type of the composed insertions list
        typedef std::vector< string_type > insertion_list;

    private:
        //! \cond

        //! The class that implements formatting of insertion strings
        class insertion_composer;

        //! Type of the events map
        typedef std::map< event_id, insertion_composer > event_map;

        //! A smart reference that puts formatters into the composer
        class event_map_reference;
        friend class event_map_reference;
        class event_map_reference
        {
        private:
            //! Event identifier
            event_id m_ID;
            //! A reference to the object that created the reference
            basic_event_composer< char_type >& m_Owner;
            //! A hint for the owner to optimize insertion
            insertion_composer* m_Composer;

        public:
            //! Initializing constructor
            explicit event_map_reference(event_id id, basic_event_composer< char_type >& owner) :
                m_ID(id),
                m_Owner(owner),
                m_Composer(0)
            {
            }
            //! The operator puts the formatter into the composer
            template< typename FormatterT >
            event_map_reference& operator% (FormatterT const& fmt)
            {
                m_Composer = m_Owner.add_formatter(m_ID, m_Composer, formatter_type(fmt));
                return *this;
            }
        };

        //! \endcond

    private:
        //! The mapper that will extract the event identifier
        event_id_mapper_type m_EventIDMapper;
        //! The map of event identifiers and their insertion composers
        event_map m_EventMap;

    public:
        /*!
         * Default constructor. Creates an empty map of events.
         *
         * \param id_mapper An event identifier mapping function that will be used to extract event ID from attribute values
         */
        explicit basic_event_composer(event_id_mapper_type const& id_mapper);
        /*!
         * Copy constructor. Performs a deep copy of the object.
         */
        basic_event_composer(basic_event_composer const& that);
        /*!
         * Destructor
         */
        ~basic_event_composer();

        /*!
         * Assignment. Provides strong exception guarantee.
         */
        basic_event_composer& operator= (basic_event_composer that);
        /*!
         * Swaps \c *this and \c that objects.
         */
        void swap(basic_event_composer& that);
        /*!
         * Initiates creation of a new event description. The result of the operator can be used to
         * add formatters for insertion strings construction. The returned reference type is implementation detail.
         *
         * \param id Event identifier.
         */
        event_map_reference operator[] (event_id id);
        /*!
         * Initiates creation of a new event description. The result of the operator can be used to
         * add formatters for insertion strings construction. The returned reference type is implementation detail.
         *
         * \param id Event identifier.
         */
        event_map_reference operator[] (int id);
        /*!
         * Event composition operator. Extracts an event identifier from the attribute values by calling event ID mapper.
         * Then runs all formatters that were registered for the event with the extracted ID. The results of formatting
         * are returned in the \a insertions parameter.
         *
         * \param rec Log record view
         * \param insertions A sequence of formatted insertion strings
         * \return An event identifier that was extracted from \c attributes
         */
        event_id operator() (record_view const& rec, insertion_list& insertions) const;

    private:
#ifndef BOOST_LOG_DOXYGEN_PASS
        //! Adds a formatter to the insertion composers list
        insertion_composer* add_formatter(event_id id, insertion_composer* composer, formatter_type const& fmt);
#endif // BOOST_LOG_DOXYGEN_PASS
    };

#ifdef BOOST_LOG_USE_CHAR
    typedef basic_event_composer< char > event_composer;          //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
    typedef basic_event_composer< wchar_t > wevent_composer;      //!< Convenience typedef for wide-character logging
#endif

} // namespace event_log

/*!
 * \brief An implementation of a simple logging sink backend that emits events into Windows NT event log
 *
 * The sink uses Windows NT 5 (Windows 2000) and later event log API to emit events
 * to an event log. The sink acts as an event source in terms of the API, it implements all needed resources
 * and source registration in the Windows registry that is needed for the event delivery.
 *
 * The backend performs message text formatting. The composed text is then passed as the first
 * and only string parameter of the event. The resource embedded into the backend describes the event
 * so that the parameter is inserted into the event description text, thus making it visible
 * in the event log.
 *
 * The backend allows to customize mapping of application severity levels to the native Windows event types.
 * This allows to write portable code even if OS-specific sinks, such as this one, are used.
 *
 * \note Since the backend registers itself into Windows registry as the resource file that contains
 *       event description, it is important to keep the library binary in a stable place of the filesystem.
 *       Otherwise Windows might not be able to load event resources from the library and display
 *       events correctly.
 *
 * \note It is known that Windows is not able to find event resources in the application executable,
 *       which is linked against the static build of the library. Users are advised to use dynamic
 *       builds of the library to solve this problem.
 */
template< typename CharT >
class basic_simple_event_log_backend :
    public basic_formatted_sink_backend< CharT, concurrent_feeding >
{
    //! Base type
    typedef basic_formatted_sink_backend< CharT, concurrent_feeding > base_type;
    //! Implementation type
    struct implementation;

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef typename base_type::string_type string_type;

    //! Mapper type for the event type
    typedef boost::log::aux::light_function< event_log::event_type (record_view const&) > event_type_mapper_type;

private:
    //! Pointer to the backend implementation that hides various types from windows.h
    implementation* m_pImpl;

public:
    /*!
     * Default constructor. Registers event source with name based on the application
     * executable file name in the Application log. If such a registration is already
     * present, it is not overridden.
     */
    BOOST_LOG_API basic_simple_event_log_backend();
    /*!
     * Constructor. Registers event log source with the specified parameters.
     * The following named parameters are supported:
     *
     * \li \c target - Specifies an UNC path to the remote server which log records should be sent to.
     *     The local machine will be used to process log records, if not specified.
     * \li \c log_name - Specifies the log in which the source should be registered.
     *     The result of \c get_default_log_name is used, if the parameter is not specified.
     * \li \c log_source - Specifies the source name. The result of \c get_default_source_name
     *     is used, if the parameter is not specified.
     * \li \c registration - Specifies the event source registration mode in the Windows registry.
     *     Can have values of the \c registration_mode enum. Default value: \c on_demand.
     *
     * \param args A set of named parameters.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(basic_simple_event_log_backend, construct)
#else
    template< typename... ArgsT >
    explicit basic_simple_event_log_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor. Unregisters event source. The log source description is not removed from the Windows registry.
     */
    BOOST_LOG_API ~basic_simple_event_log_backend();

    /*!
     * The method installs the function object that maps application severity levels to WinAPI event types
     */
    BOOST_LOG_API void set_event_type_mapper(event_type_mapper_type const& mapper);

    /*!
     * \returns Default log name: Application
     */
    BOOST_LOG_API static string_type get_default_log_name();
    /*!
     * \returns Default log source name that is based on the application executable file name and the sink name
     */
    BOOST_LOG_API static string_type get_default_source_name();

    /*!
     * The method puts the formatted message to the event log
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructs backend implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            args[keywords::target | string_type()],
            args[keywords::log_name || &basic_simple_event_log_backend::get_default_log_name],
            args[keywords::log_source || &basic_simple_event_log_backend::get_default_source_name],
            args[keywords::registration | event_log::on_demand]);
    }
    BOOST_LOG_API void construct(
        string_type const& target,
        string_type const& log_name,
        string_type const& source_name,
        event_log::registration_mode reg_mode);
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * \brief An implementation of a logging sink backend that emits events into Windows NT event log
 *
 * The sink uses Windows NT 5 (Windows 2000) and later event log API to emit events
 * to an event log. The sink acts as an event source. Unlike \c basic_simple_event_log_backend,
 * this sink backend allows users to specify the custom event message file and supports
 * mapping attribute values onto several insertion strings. Although it requires considerably
 * more scaffolding than the simple backend, this allows to support localizable event descriptions.
 *
 * Besides the file name of the module with event resources, the backend provides the following
 * customizations:
 * \li Remote server UNC address, log name and source name. These parameters have similar meaning
 *     to \c basic_simple_event_log_backend.
 * \li Event type and category mappings. These are function object that allow to map attribute
 *     values to the according event parameters. One can use mappings in the \c event_log namespace.
 * \li Event composer. This function object extracts event identifier and formats string insertions,
 *     that will be used by the API to compose the final event message text.
 */
template< typename CharT >
class basic_event_log_backend :
    public basic_sink_backend< synchronized_feeding >
{
    //! Base type
    typedef basic_sink_backend< synchronized_feeding > base_type;
    //! Implementation type
    struct implementation;

public:
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Type of the composed insertions list
    typedef std::vector< string_type > insertion_list;

    //! Mapper type for the event type
    typedef boost::log::aux::light_function< event_log::event_type (record_view const&) > event_type_mapper_type;
    //! Mapper type for the event category
    typedef boost::log::aux::light_function< event_log::event_category (record_view const&) > event_category_mapper_type;
    //! Event composer type
    typedef boost::log::aux::light_function< event_log::event_id (record_view const&, insertion_list&) > event_composer_type;

private:
    //! Pointer to the backend implementation that hides various types from windows.h
    implementation* m_pImpl;

public:
    /*!
     * Constructor. Registers event source with name based on the application
     * executable file name in the Application log. If such a registration is already
     * present, it is not overridden.
     */
    template< typename T >
    explicit basic_event_log_backend(std::basic_string< T > const& message_file_name)
    {
        construct(keywords::message_file = message_file_name);
    }
    /*!
     * Constructor. Registers event source with name based on the application
     * executable file name in the Application log. If such a registration is already
     * present, it is not overridden.
     */
    explicit basic_event_log_backend(filesystem::path const& message_file_name)
    {
        construct(keywords::message_file = message_file_name);
    }
    /*!
     * Constructor. Registers event log source with the specified parameters.
     * The following named parameters are supported:
     *
     * \li \c message_file - Specifies the file name that contains resources that
     *     describe events and categories. This parameter is mandatory unless \c registration is \c never.
     * \li \c target - Specifies an UNC path to the remote server to which log records should be sent to.
     *     The local machine will be used to process log records, if not specified.
     * \li \c log_name - Specifies the log in which the source should be registered.
     *     The result of \c get_default_log_name is used, if the parameter is not specified.
     * \li \c log_source - Specifies the source name. The result of \c get_default_source_name
     *     is used, if the parameter is not specified.
     * \li \c registration - Specifies the event source registration mode in the Windows registry.
     *     Can have values of the \c registration_mode enum. Default value: \c on_demand.
     *
     * \param args A set of named parameters.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(basic_event_log_backend, construct)
#else
    template< typename... ArgsT >
    explicit basic_event_log_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor. Unregisters event source. The log source description is not removed from the Windows registry.
     */
    BOOST_LOG_API ~basic_event_log_backend();

    /*!
     * The method creates an event in the event log
     *
     * \param rec Log record to consume
     */
    BOOST_LOG_API void consume(record_view const& rec);

    /*!
     * The method installs the function object that maps application severity levels to WinAPI event types
     */
    BOOST_LOG_API void set_event_type_mapper(event_type_mapper_type const& mapper);

    /*!
     * The method installs the function object that extracts event category from attribute values
     */
    BOOST_LOG_API void set_event_category_mapper(event_category_mapper_type const& mapper);

    /*!
     * The method installs the function object that extracts event identifier from the attributes and creates
     * insertion strings that will replace placeholders in the event message.
     */
    BOOST_LOG_API void set_event_composer(event_composer_type const& composer);

    /*!
     * \returns Default log name: Application
     */
    BOOST_LOG_API static string_type get_default_log_name();
    /*!
     * \returns Default log source name that is based on the application executable file name and the sink name
     */
    BOOST_LOG_API static string_type get_default_source_name();

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructs backend implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            filesystem::path(args[keywords::message_file | filesystem::path()]),
            args[keywords::target | string_type()],
            args[keywords::log_name || &basic_event_log_backend::get_default_log_name],
            args[keywords::log_source || &basic_event_log_backend::get_default_source_name],
            args[keywords::registration | event_log::on_demand]);
    }
    BOOST_LOG_API void construct(
        filesystem::path const& message_file_name,
        string_type const& target,
        string_type const& log_name,
        string_type const& source_name,
        event_log::registration_mode reg_mode);
#endif // BOOST_LOG_DOXYGEN_PASS
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_simple_event_log_backend< char > simple_event_log_backend;      //!< Convenience typedef for narrow-character logging
typedef basic_event_log_backend< char > event_log_backend;                    //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_simple_event_log_backend< wchar_t > wsimple_event_log_backend;  //!< Convenience typedef for wide-character logging
typedef basic_event_log_backend< wchar_t > wevent_log_backend;                //!< Convenience typedef for wide-character logging
#endif

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_EVENT_LOG

#endif // BOOST_LOG_SINKS_EVENT_LOG_BACKEND_HPP_INCLUDED_

/* event_log_backend.hpp
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
*/