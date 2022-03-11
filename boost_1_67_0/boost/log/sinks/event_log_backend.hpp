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