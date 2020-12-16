/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   ends_with.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c ends_with predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/ends_with.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value ends with a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_ends_with = aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_ends_with :
    public aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value ending
     */
    attribute_ends_with(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value ending
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_ends_with(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
ends_with(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_ends_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
ends_with(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
ends_with(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_

/* ends_with.hpp
QxW/I8uE66u9TMDr7Q8qL7Gwlwn4o2TUhGuZ2I0hVEd65dP0U0aK/eUsKiZaZTMbHC48V6LDzR8pi6b+nSw8F7KnvHvAjLdCMVuIHI4TOaygvunQUuUwNTPddxpCiFurHCr/8JZBOcyNkkPtVxk5fAZ6WrEqDl2l9cteII+yw86Zal5E7EtY0VrHhwSwFXgVeLmblu/GkClEOJY8ZYMZ4m6Gc679XDz+2voNVnmC19pHMDJwtdi/Ra2ZbpMv3NvbZTfiz4pdC81znvd4F/kaZu5oyRGzC2g9c5HCo418DBPzAvzK85wZLik9b+EMp53611r8n+Y7k1jvxmVv3+F292TpXurMTsJf5ss0/s2dWjFtZjHSqn0qUHjymHxr4RMz49coUruH+LUfv9oK30Kfp9yY/LlI7DJ8LztNI8uNmc/qLjwTfONI1Qo0J7bVsLcx3xvHXNyRpr7PE/7zQmHHPz3IK+4ywd8Iz3FOV03zTN4+ELOhhKSn+HUAv04WsxE+W3ltA94k9jWEaqAtTHLH3FYSqyYr2G5UpKckcOPXr9NTm8Qqs+pmf1awzFZVR5bZAbynaZndrOX0SfCP0LPQFuhpRdoRU44zvmc5rq8v5e0PZaju+Gnq+XnQWjdfd4bK8KwZpeUVOkKKe45np6f8tZGz2CWO905Tsc+wl92ddc/JdNtp5mTsZXdnXXMyoNgXiP6M46Gg7ucrCdjWH2A+JpgPxBsz4m3yIXa/dGbb6Lnli91xalQ+XFi6YNb0RXXNKV8ubu43Y7FL7OMw/I4x76vp/LjYL3KOIKQjIUte4Yd1XGTNlyp7vtr6q/Da699sl+99165LzHmIL8Ttj8y4KItEqcn5/uOiLTvDx0V75D0l1rjIjImek3HRobXJkeOddMt4J6OOsX1GR9W16gvkeSn4W75T9r6Rq9J5nrH9BtNWhsrb/cL7GCVukk2O8CtKjphSsbfL8Nrnfu0yA79VZoyMfiz2u5zTaQ/fcXymrXpCzO9lHmWSVb68/lI3it4OQmLyfJvYp4T3H7V8rRe7hzkf38/orH/5765ZYlSd00ll8jJxM8F3ODyboN1QgS9R2pw5lP3R7RmLZhDnxGHpSUnpCU3TfR3pKdrbHHUzEzefum6ST4/qJ/ZVnoIOgbosoeqmtJEIfk5GUkrChLST0grS+ib5E3LSzuNrqU3MfN0DWhZGEuizSazn9T1Cv4lJ5zSJ99PMtx2h5TOYFozNTPkkLc6bNd/bFmcJzwZyrW9UGkr8iNs4wv6g9JuXjNT4MXcYiJ93TPaChvERcJvW348YMyiOMujeOfjk382dg/L+k/flfS4GpoxuMO1oeWQZRea13xw5Fx9HOd2vE+u/gfzQrVr/539gyun0WfOmzsE4rvmI/A/iL5Pw2toBW3mEN/46XHkjZceM5YeI/U3SviyFLPJi2uxRwvtzpyv/K6Ee5H1KbHlFbqC62+8Tg/n+1AfBfI+rLiYdtT231M8ZdawL7OzsyNOKjyWAmeDv+I6zy+Rx+awZ85xMM2ZxX11Zs+Yx7qLHQ4ywzL3K48U+05rn6jayzjd3gVwq9sfYZAC3VtmyyQC8Vnkx45KeYn+c09LJNt9+WMz6W+em1D9vvWzmSy8Tu5mmPvlQ3ntZ59pzwKZin+R7k9xoatqBStMG3Cj2ydKHONCJ/MsN1tGL0lOT0n09Ys0nKX9KZ6mfrWOCvrw3dQJrgC9CC8iwl8CXoRrTB9U6LI65VVeOEz8Mr7+Iv6m/skWudRxg5CpqzID8qGxb6roMSxnIqmPt5aBu/D6NQDQDTwUfIB+mfBgm78W0vKWzyiokny7qHpD7GOMKdeuzlRHTP7xGeC6zyT0=
*/