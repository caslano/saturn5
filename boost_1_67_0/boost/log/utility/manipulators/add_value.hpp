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