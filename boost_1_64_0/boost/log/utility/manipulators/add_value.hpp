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
sCpt/NW5N1Vd4Hi22wRgS9r42/nZ+C9Tz0TSFnab1Q72w6ss/zVgX+6ddCHDVxplsB3fZDu+Re7D28AltLUvY/hehtW4HFU1sC3yYh5/CNAj12Cv7WwYz3M4MB04guc70q/cLJ7XJHu5wj3QyT2oRu5BdYZrMDwO+Dxtgy+o9lL3SdIH9vYqYD8VsZ+msb7FHMfTgS1oU21Nm2o/Kddr2/wb95SaBcxheLQR5vFHmdd3aQs5fmWZl/ITW7VO23QUbdNnAK/hOLgW2Bz4d86X69iPc4FDaKP+jLbEo2+FbIn/a7bExLejtA6QUZBZkDsgayHPQ/ZBDkOi96Df9oTsiaFf6Bf6hX6h3//PLwwy9Y+3/48ZV5Q7RSgAp8gBqEUOQDcLB0CKL9TIA1iIZ81zaS9VeyS34fm2ps18fZRpL5XMNiqAxbZsfY+zUfLWcPY1iTrhO3B5nxPI1t9JfbdAN/fC1qRvWG/NY6231dzvbO8PkzwJuO91O9UZZZZv70/2yPmyPFhcJdwW9W2qJeOdWIkLzx06niWNd2LJEX2jwxt6/YlOghMQJ2XjHW87aQ/zm41bA3ACRnksnABpEy1IXsAoT8V5AchTLi9giufP5QWo9kkJ5Nvvax9ME4xvo4GC9O9XY3EnC70ZDV8DOAtYgNzrvWV7x2HumInTpxXnFOXNyMGszcdbZMv7XWV/e0XyjHc5zh2/tm3Y3jiiUWGfbeYdiR/mMuIbSfy0y1U/7f/9998ToK8DfaSGGmA5GltslN+V9ns8s0Ub+fNFF89jbhCdriVDV5W61aI7D+8TdOZ3Sf5GMYY+XHRVxZtc6RL89uDg2fvxDDKkvDQtAd28D/X0SDjTNUebLvbNtDBvxy0x5s/suz2NIiLdcRFh0VWrYDbp0dXDOJ4TvedcrM75AMoy9M3lnKcW4NlY6lZN8YflOI0t5ztZdNUl/2fIr+ZpHcd9PpBR1pT28ceQNkn6xvYeWtre6I8k6Q/Zp0LOU8aspT3axYfL8cFt57vnRIZbMdyX4bYMj2S4A8NVY7zhzgzXjlH5rT5os8gRaMf14mzl0xzjN2bzcMkqCuDTLOlaBvZpjrF+P+TSDK2Cfl65lvoOj/UmRAKUIygcnP1h/vUVGo5lXo3kvPpR0h1390KpkyEzINdClkJeh7wD+QwS4dK1epABkPGQ5yHhuq51hCzinho13LrWEJLpdmupskcC64FabXBFajtdbu2oa6iVExfmzOtJpj1f5TfyHncNMvMyLuA+GinGTImQvHbbjcpr5/iY174PwxGPq0YM8iv/276i+9SVoH0Ln5EHzT7PleNorvbaIjsnyO9Yyb59JwryJhUUFufMyKVtSeaJhTPk5zu8QY5bpKHFsbbkaWO5rkWI/lt3G7TkRZBcSAHkBsgCXLPX4ejP4O83ID9AolwerYYrDP4lSdpA4MOQUkgDPUy7DrIUEoHGSITUdIf79sAI5/olx1Xh+dBcZltzR7NNXJKm1N0B9RgBGQeZDrkF8jTkJcgeyM+QaujbrpAhkFGui7WfgL+5Wmmt9UbwZXJrKyDRxpiCnOGONL81vEja/QZXDW2iq7x19ApJF2XuA3K9hKO1ZI7R2yU8DmMqHqttp0BrspzXcUlbxxyfayXcF2fRTGtDLkuW3zVGjmFJ11DSlVffAZWMtLFl6ptglnW3hG9xYTyhz+s5nnuCpX7XYRzXlbp1UXVjmrAyac7CulQZunuwLt0LuQ+yArLSL7zK0HHdCrOt/3Ze2txIKy+tQaSPl1Yr0uSJmXuExJm61u2UTvPpzla61ZVMXabSlZi6Vmbe6T5dG6XL9elaKl2mT9dC6Z6IsO+JMsKnM8s7z6c=
*/