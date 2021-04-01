// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/comparison_adaptor.hpp
/// \brief Comparison adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Comparison adaptor
/**

A simple comparison adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x,
                     BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};

template < class Compare, class NewType, class Converter >
struct compatible_comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    compatible_comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    template< class CompatibleTypeLeft, class CompatibleTypeRight >
    bool operator()( const CompatibleTypeLeft  & x,
                     const CompatibleTypeRight & y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};


/// \brief Unary Check adaptor
/**

A simple unary check adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct unary_check_adaptor
{
    typedef BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type argument_type;
    typedef bool result_type;

    unary_check_adaptor( const Compare & comp, const Converter & conv ) :
        compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x) const
    {
        return compare( converter(x) );
    }

    private:
    Compare   compare;
    Converter converter;
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP



/* comparison_adaptor.hpp
6BbsktaA7DVtx9oGquYcceWn01WOZ4aoo6jXGi03g4njm1of8fCrPIJjbcfSrvESozP6XF4aczRdRaPcPQI1wwgVb312AgghfsTAVcCMJ1XRfhN5lNF1gMxXts4kPropoW/iG9XWePWLd0OnNgYFKwcZbqqa8IMIIqEwheJHxbAMiQTCgsr93e1qMz/8oDaLLRyIoP7KozWxn6SE/uygnfKbCSL+EzhiFnqn+m27PiP1CyIBjNruPAcwCEC6QEj18JTqgMTOz5ggLTO7MX1TfGu+ltFdC4lS9Epth+J+izaIeMWC0pt+DDA+6q4HK2605DGhYkfgzX55IyrjGyKY0yBGHFrg8lAZLMN7YXR+quIKdpnazk61kOLu7A8VstEyuhfDyPlAE6AOT2eIRK/E4iNuKNYVXjQDPUp0clXin/+yPJ6S7+OQqBs6PZ8SzPfXctWKlmVlQk3jX1wRjprXqvCcLXGm1Ro5/CQz5Var8mErxJr4sqYiK5OSDTxQaLqnuaZeFhkLowwmaTf14fCbGn7hNB80CjRiBeCZCrDmunPf4/lC9MdR7R/30w==
*/