/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   add_value.hpp
 * \author Andrey Semashev
 * \date   26.11.2012
 *
 * This header contains the \c add_value manipulator.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_ADD_VALUE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_ADD_VALUE_HPP_INCLUDED_

#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifdef _MSC_VER
#pragma warning(push)
// 'boost::log::v2s_mt_nt6::add_value_manip<RefT>::m_value' : reference member is initialized to a temporary that doesn't persist after the constructor exits
// This is intentional since the manipulator can be used with a temporary, which will be used before the streaming expression ends and it is destroyed.
#pragma warning(disable: 4413)
// returning address of local variable or temporary
// This warning refers to add_value_manip<RefT>::get_value() when RefT is an rvalue reference. We store the reference in the manipulator and we intend to return it as is.
#pragma warning(disable: 4172)
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Attribute value manipulator
template< typename RefT >
class add_value_manip
{
public:
    //! Stored reference type
    typedef RefT reference_type;
    //! Attribute value type
    typedef typename remove_cv< typename remove_reference< reference_type >::type >::type value_type;

private:
    //  The stored reference type is an lvalue reference since apparently different compilers (GCC and MSVC) have different quirks when rvalue references are stored as members.
    //  Additionally, MSVC (at least 11.0) has a bug which causes a dangling reference to be stored in the manipulator, if a scalar rvalue is passed to the add_value generator.
    //  To work around this problem we save the value inside the manipulator in this case.
    typedef typename remove_reference< reference_type >::type& lvalue_reference_type;

    typedef typename conditional<
        is_scalar< value_type >::value,
        value_type,
        lvalue_reference_type
    >::type stored_type;

    typedef typename conditional<
        is_scalar< value_type >::value,
        value_type,
        reference_type
    >::type get_value_result_type;

private:
    //! Attribute value
    stored_type m_value;
    //! Attribute name
    attribute_name m_name;

public:
    //! Initializing constructor
    add_value_manip(attribute_name const& name, reference_type value) : m_value(static_cast< lvalue_reference_type >(value)), m_name(name)
    {
    }

    //! Returns attribute name
    attribute_name get_name() const { return m_name; }
    //! Returns attribute value
    get_value_result_type get_value() const { return static_cast< get_value_result_type >(m_value); }
};

//! The operator attaches an attribute value to the log record
template< typename CharT, typename RefT >
inline basic_record_ostream< CharT >& operator<< (basic_record_ostream< CharT >& strm, add_value_manip< RefT > const& manip)
{
    typedef typename aux::make_embedded_string_type< typename add_value_manip< RefT >::value_type >::type value_type;
    attribute_value value(new attributes::attribute_value_impl< value_type >(manip.get_value()));
    strm.get_record().attribute_values().insert(manip.get_name(), value);
    return strm;
}

//! The function creates a manipulator that attaches an attribute value to a log record
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
inline add_value_manip< T&& > add_value(attribute_name const& name, T&& value)
{
    return add_value_manip< T&& >(name, static_cast< T&& >(value));
}

//! \overload
template< typename DescriptorT, template< typename > class ActorT >
inline add_value_manip< typename DescriptorT::value_type&& >
add_value(expressions::attribute_keyword< DescriptorT, ActorT > const&, typename DescriptorT::value_type&& value)
{
    typedef typename DescriptorT::value_type value_type;
    return add_value_manip< value_type&& >(DescriptorT::get_name(), static_cast< value_type&& >(value));
}

//! \overload
template< typename DescriptorT, template< typename > class ActorT >
inline add_value_manip< typename DescriptorT::value_type& >
add_value(expressions::attribute_keyword< DescriptorT, ActorT > const&, typename DescriptorT::value_type& value)
{
    return add_value_manip< typename DescriptorT::value_type& >(DescriptorT::get_name(), value);
}

//! \overload
template< typename DescriptorT, template< typename > class ActorT >
inline add_value_manip< typename DescriptorT::value_type const& >
add_value(expressions::attribute_keyword< DescriptorT, ActorT > const&, typename DescriptorT::value_type const& value)
{
    return add_value_manip< typename DescriptorT::value_type const& >(DescriptorT::get_name(), value);
}

#else // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
inline add_value_manip< T const& > add_value(attribute_name const& name, T const& value)
{
    return add_value_manip< T const& >(name, value);
}

template< typename DescriptorT, template< typename > class ActorT >
inline add_value_manip< typename DescriptorT::value_type const& >
add_value(expressions::attribute_keyword< DescriptorT, ActorT > const&, typename DescriptorT::value_type const& value)
{
    return add_value_manip< typename DescriptorT::value_type const& >(DescriptorT::get_name(), value);
}

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_ADD_VALUE_HPP_INCLUDED_

/* add_value.hpp
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
*/