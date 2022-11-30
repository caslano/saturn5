/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_FAIL_FUNCTION_HPP
#define BOOST_SPIRIT_QI_DETAIL_FAIL_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <typename Iterator, typename Context, typename Skipper>
    struct fail_function
    {
        typedef Iterator iterator_type;
        typedef Context context_type;

        fail_function(
            Iterator& first_, Iterator const& last_
          , Context& context_, Skipper const& skipper_)
          : first(first_)
          , last(last_)
          , context(context_)
          , skipper(skipper_)
        {
        }

        template <typename Component, typename Attribute>
        bool operator()(Component const& component, Attribute& attr) const
        {
            // return true if the parser fails
            return !component.parse(first, last, context, skipper, attr);
        }

        template <typename Component>
        bool operator()(Component const& component) const
        {
            // return true if the parser fails
            return !component.parse(first, last, context, skipper, unused);
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(fail_function& operator= (fail_function const&))
    };
}}}}

#endif

/* fail_function.hpp
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
*/