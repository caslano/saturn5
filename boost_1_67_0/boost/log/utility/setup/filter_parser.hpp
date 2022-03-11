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