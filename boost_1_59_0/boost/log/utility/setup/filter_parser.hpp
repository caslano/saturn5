/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   filter_parser.hpp
 * \author Andrey Semashev
 * \date   31.03.2008
 *
 * The header contains definition of a filter parser function.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FILTER_PARSER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FILTER_PARSER_HPP_INCLUDED_

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/phoenix/operator/comparison.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/detail/code_conversion.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/predicates/has_attr.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The interface class for all filter factories.
 */
template< typename CharT >
struct filter_factory
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;

    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(filter_factory(), {})

    /*!
     * Virtual destructor
     */
    virtual ~filter_factory() {}

    /*!
     * The callback for filter for the attribute existence test
     */
    virtual filter on_exists_test(attribute_name const& name)
    {
        return filter(expressions::has_attr(name));
    }

    /*!
     * The callback for equality relation filter
     */
    virtual filter on_equality_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The equality attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }
    /*!
     * The callback for inequality relation filter
     */
    virtual filter on_inequality_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The inequality attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }
    /*!
     * The callback for less relation filter
     */
    virtual filter on_less_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The less attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }
    /*!
     * The callback for greater relation filter
     */
    virtual filter on_greater_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The greater attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }
    /*!
     * The callback for less or equal relation filter
     */
    virtual filter on_less_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The less-or-equal attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }
    /*!
     * The callback for greater or equal relation filter
     */
    virtual filter on_greater_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The greater-or-equal attribute value relation is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }

    /*!
     * The callback for custom relation filter
     */
    virtual filter on_custom_relation(attribute_name const& name, string_type const& rel, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The custom attribute value relation \"" + boost::log::aux::to_narrow(rel) + "\" is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }

    BOOST_DELETED_FUNCTION(filter_factory(filter_factory const&))
    BOOST_DELETED_FUNCTION(filter_factory& operator= (filter_factory const&))
};

/*!
 * The base class for filter factories. The class defines default implementations for most
 * filter expressions. In order to be able to construct filters, the attribute value type must
 * support reading from a stream. Also, the default filters will rely on relational operators for
 * the type, so these operators must also be defined.
 */
template< typename CharT, typename AttributeValueT >
class basic_filter_factory :
    public filter_factory< CharT >
{
    //! Base type
    typedef filter_factory< CharT > base_type;

public:
    //! The type(s) of the attribute value expected
    typedef AttributeValueT value_type;
    //  Type imports
    typedef typename base_type::string_type string_type;

    /*!
     * The callback for filter for the attribute existence test
     */
    virtual filter on_exists_test(attribute_name const& name)
    {
        return filter(expressions::has_attr< value_type >(name));
    }

    /*!
     * The callback for equality relation filter
     */
    virtual filter on_equality_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) == parse_argument(arg));
    }
    /*!
     * The callback for inequality relation filter
     */
    virtual filter on_inequality_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) != parse_argument(arg));
    }
    /*!
     * The callback for less relation filter
     */
    virtual filter on_less_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) < parse_argument(arg));
    }
    /*!
     * The callback for greater relation filter
     */
    virtual filter on_greater_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) > parse_argument(arg));
    }
    /*!
     * The callback for less or equal relation filter
     */
    virtual filter on_less_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) <= parse_argument(arg));
    }
    /*!
     * The callback for greater or equal relation filter
     */
    virtual filter on_greater_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) >= parse_argument(arg));
    }

    /*!
     * The callback for custom relation filter
     */
    virtual filter on_custom_relation(attribute_name const& name, string_type const& rel, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The custom attribute value relation \"" + boost::log::aux::to_narrow(rel) + "\" is not supported", (name));
        BOOST_LOG_UNREACHABLE_RETURN(filter());
    }

    /*!
     * The function parses the argument value for a binary relation
     */
    virtual value_type parse_argument(string_type const& arg)
    {
        return boost::lexical_cast< value_type >(arg);
    }
};

/*!
 * The function registers a filter factory object for the specified attribute name. The factory will be
 * used to construct a filter during parsing the filter string.
 *
 * \pre <tt>name != NULL && factory != NULL</tt>, <tt>name</tt> points to a zero-terminated string
 * \param name Attribute name to associate the factory with
 * \param factory The filter factory
 */
template< typename CharT >
BOOST_LOG_SETUP_API void register_filter_factory(
    attribute_name const& name, shared_ptr< filter_factory< CharT > > const& factory);

/*!
 * The function registers a filter factory object for the specified attribute name. The factory will be
 * used to construct a filter during parsing the filter string.
 *
 * \pre <tt>name != NULL && factory != NULL</tt>, <tt>name</tt> points to a zero-terminated string
 * \param name Attribute name to associate the factory with
 * \param factory The filter factory
 */
template< typename FactoryT >
inline typename boost::enable_if_c<
    is_base_and_derived< filter_factory< typename FactoryT::char_type >, FactoryT >::value
>::type register_filter_factory(attribute_name const& name, shared_ptr< FactoryT > const& factory)
{
    typedef filter_factory< typename FactoryT::char_type > factory_base;
    register_filter_factory(name, boost::static_pointer_cast< factory_base >(factory));
}

/*!
 * The function registers a simple filter factory object for the specified attribute name. The factory will
 * support attribute values of type \c AttributeValueT, which must support all relation operations, such as
 * equality comparison and less/greater ordering, and also extraction from stream.
 *
 * \pre <tt>name != NULL</tt>, <tt>name</tt> points to a zero-terminated string
 * \param name Attribute name to associate the factory with
 */
template< typename AttributeValueT, typename CharT >
inline void register_simple_filter_factory(attribute_name const& name)
{
    shared_ptr< filter_factory< CharT > > factory =
        boost::make_shared< basic_filter_factory< CharT, AttributeValueT > >();
    register_filter_factory(name, factory);
}

/*!
 * The function registers a simple filter factory object for the specified attribute name. The factory will
 * support attribute values of type \c AttributeValueT, which must support all relation operations, such as
 * equality comparison and less/greater ordering, and also extraction from stream.
 *
 * \pre <tt>name != NULL</tt>, <tt>name</tt> points to a zero-terminated string
 * \param name Attribute name to associate the factory with
 */
template< typename AttributeValueT >
inline void register_simple_filter_factory(attribute_name const& name)
{
    register_simple_filter_factory< AttributeValueT, char >(name);
}

/*!
 * The function registers a simple filter factory object for the specified attribute keyword. The factory will
 * support attribute values described by the keyword. The values must support all relation operations, such as
 * equality comparison and less/greater ordering, and also extraction from stream.
 *
 * \pre <tt>name != NULL</tt>, <tt>name</tt> points to a zero-terminated string
 * \param keyword Attribute keyword to associate the factory with
 */
template< typename CharT, typename DescriptorT, template< typename > class ActorT >
inline void register_simple_filter_factory(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword)
{
    register_simple_filter_factory< typename DescriptorT::value_type, CharT >(keyword.get_name());
}

/*!
 * The function parses a filter from the sequence of characters
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be \c NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \return A function object that can be used as a filter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a filter cannot be recognized in the character sequence.
 */
template< typename CharT >
BOOST_LOG_SETUP_API filter parse_filter(const CharT* begin, const CharT* end);

/*!
 * The function parses a filter from the string
 *
 * \param str A string that contains filter description
 * \return A function object that can be used as a filter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a filter cannot be recognized in the character sequence.
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline filter parse_filter(std::basic_string< CharT, TraitsT, AllocatorT > const& str)
{
    const CharT* p = str.c_str();
    return parse_filter(p, p + str.size());
}

/*!
 * The function parses a filter from the string
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string.
 * \param str A string that contains filter description.
 * \return A function object that can be used as a filter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a filter cannot be recognized in the character sequence.
 */
template< typename CharT >
inline filter parse_filter(const CharT* str)
{
    return parse_filter(str, str + std::char_traits< CharT >::length(str));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FILTER_PARSER_HPP_INCLUDED_

/* filter_parser.hpp
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
*/