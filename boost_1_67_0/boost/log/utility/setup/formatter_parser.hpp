/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatter_parser.hpp
 * \author Andrey Semashev
 * \date   07.04.2008
 *
 * The header contains definition of a formatter parser function, along with facilities to
 * add support for custom formatters.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_

#include <iosfwd>
#include <map>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/expressions/formatter.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Formatter factory base interface.
 */
template< typename CharT >
struct formatter_factory
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! The formatter function object
    typedef basic_formatter< char_type > formatter_type;
    /*!
     * Type of the map of formatter factory arguments [argument name -> argument value].
     * This type of maps will be passed to formatter factories on attempt to create a formatter.
     */
    typedef std::map< string_type, string_type > args_map;

    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(formatter_factory(), {})

    /*!
     * Virtual destructor
     */
    virtual ~formatter_factory() {}

    /*!
     * The function creates a formatter for the specified attribute.
     *
     * \param name Attribute name
     * \param args Formatter arguments
     */
    virtual formatter_type create_formatter(attribute_name const& name, args_map const& args) = 0;

    BOOST_DELETED_FUNCTION(formatter_factory(formatter_factory const&))
    BOOST_DELETED_FUNCTION(formatter_factory& operator= (formatter_factory const&))
};

/*!
 * Base class for formatter factories. This class provides default implementation of formatter expressions for
 * types supporting stream output. The factory does not take into account any additional parameters that may be specified.
 */
template< typename CharT, typename AttributeValueT >
class basic_formatter_factory :
    public formatter_factory< CharT >
{
private:
    typedef formatter_factory< CharT > base_type;

public:
    //! Attribute value type
    typedef AttributeValueT value_type;
    //  Type imports from the base class
    typedef typename base_type::formatter_type formatter_type;
    typedef typename base_type::args_map args_map;

    /*!
     * The function creates a formatter for the specified attribute.
     *
     * \param name Attribute name
     * \param args Formatter arguments
     */
    formatter_type create_formatter(attribute_name const& name, args_map const& args)
    {
        return formatter_type(expressions::stream << expressions::attr< value_type >(name));
    }
};

/*!
 * \brief The function registers a user-defined formatter factory
 *
 * The function registers a user-defined formatter factory. The registered factory function will be
 * called when the formatter parser detects the specified attribute name in the formatter string.
 *
 * \pre <tt>!!attr_name && !!factory</tt>.
 *
 * \param attr_name Attribute name
 * \param factory Pointer to the formatter factory
 */
template< typename CharT >
BOOST_LOG_SETUP_API void register_formatter_factory(
    attribute_name const& attr_name, shared_ptr< formatter_factory< CharT > > const& factory);

/*!
 * \brief The function registers a user-defined formatter factory
 *
 * The function registers a user-defined formatter factory. The registered factory function will be
 * called when the formatter parser detects the specified attribute name in the formatter string.
 *
 * \pre <tt>!!attr_name && !!factory</tt>.
 *
 * \param attr_name Attribute name
 * \param factory Pointer to the formatter factory
 */
template< typename FactoryT >
inline typename boost::enable_if_c<
    is_base_and_derived< formatter_factory< typename FactoryT::char_type >, FactoryT >::value
>::type register_formatter_factory(attribute_name const& attr_name, shared_ptr< FactoryT > const& factory)
{
    typedef formatter_factory< typename FactoryT::char_type > factory_base;
    register_formatter_factory(attr_name, boost::static_pointer_cast< factory_base >(factory));
}

/*!
 * \brief The function registers a simple formatter factory
 *
 * The function registers a simple formatter factory. The registered factory will generate formatters
 * that will be equivalent to the <tt>log::expressions::attr</tt> formatter (i.e. that will use the
 * native \c operator<< to format the attribute value). The factory does not use any arguments from the format string,
 * if specified.
 *
 * \pre <tt>!!attr_name</tt>.
 *
 * \param attr_name Attribute name
 */
template< typename AttributeValueT, typename CharT >
inline void register_simple_formatter_factory(attribute_name const& attr_name)
{
    shared_ptr< formatter_factory< CharT > > factory =
        boost::make_shared< basic_formatter_factory< CharT, AttributeValueT > >();
    register_formatter_factory(attr_name, factory);
}

/*!
 * The function parses a formatter from the sequence of characters
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT >
BOOST_LOG_SETUP_API basic_formatter< CharT > parse_formatter(const CharT* begin, const CharT* end);

/*!
 * The function parses a formatter from the string
 *
 * \param str A string that contains format description
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline basic_formatter< CharT > parse_formatter(std::basic_string< CharT, TraitsT, AllocatorT > const& str)
{
    const CharT* p = str.c_str();
    return parse_formatter(p, p + str.size());
}

/*!
 * The function parses a formatter from the string
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string
 * \param str A string that contains format description.
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT >
inline basic_formatter< CharT > parse_formatter(const CharT* str)
{
    return parse_formatter(str, str + std::char_traits< CharT >::length(str));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_

/* formatter_parser.hpp
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
*/