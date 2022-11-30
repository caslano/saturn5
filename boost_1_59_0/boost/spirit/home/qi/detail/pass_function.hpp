/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_PASS_FUNCTION_HPP
#define BOOST_SPIRIT_QI_DETAIL_PASS_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/optional.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <typename Iterator, typename Context, typename Skipper>
    struct pass_function
    {
        pass_function(
            Iterator& first_, Iterator const& last_
          , Context& context_, Skipper const& skipper_)
          : first(first_)
          , last(last_)
          , context(context_)
          , skipper(skipper_)
        {
        }

        template <typename Component, typename Attribute>
        bool operator()(Component const& component, Attribute& attr)
        {
            // return true if the parser succeeds
            return component.parse(first, last, context, skipper, attr);
        }

        template <typename Component, typename Attribute>
        bool operator()(Component const& component, boost::optional<Attribute>& attr)
        {
            // return true if the parser succeeds
            Attribute val;
            if (component.parse(first, last, context, skipper, val))
            {
                attr = val;
                return true;
            }
            return false;
        }

        template <typename Component>
        bool operator()(Component const& component)
        {
            // return true if the parser succeeds
            return component.parse(first, last, context, skipper, unused);
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(pass_function& operator= (pass_function const&))
    };
}}}}

#endif

/* pass_function.hpp
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
*/