/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_PERMUTE_FUNCTION_HPP
#define BOOST_SPIRIT_QI_DETAIL_PERMUTE_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/optional.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <typename Iterator, typename Context, typename Skipper>
    struct permute_function
    {
        permute_function(
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
            // return true if the parser succeeds and the slot is not yet taken
            if (!*taken && component.parse(first, last, context, skipper, attr))
            {
                *taken = true;
                ++taken;
                return true;
            }
            ++taken;
            return false;
        }

        template <typename Component>
        bool operator()(Component const& component)
        {
            // return true if the parser succeeds and the slot is not yet taken
            if (!*taken && component.parse(first, last, context, skipper, unused))
            {
                *taken = true;
                ++taken;
                return true;
            }
            ++taken;
            return false;
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;
        bool* taken;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(permute_function& operator= (permute_function const&))
    };
}}}}

#endif

/* permute_function.hpp
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
*/