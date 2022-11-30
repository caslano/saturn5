/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_EXPECT_FUNCTION_HPP
#define BOOST_SPIRIT_QI_DETAIL_EXPECT_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/multi_pass_wrapper.hpp>
#include <boost/throw_exception.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <
        typename Iterator, typename Context
      , typename Skipper, typename Exception>
    struct expect_function
    {
        typedef Iterator iterator_type;
        typedef Context context_type;

        expect_function(
            Iterator& first_, Iterator const& last_
          , Context& context_, Skipper const& skipper_)
          : first(first_)
          , last(last_)
          , context(context_)
          , skipper(skipper_)
          , is_first(true)
        {
        }

        template <typename Component, typename Attribute>
        bool operator()(Component const& component, Attribute& attr) const
        {
            // if this is not the first component in the expect chain we 
            // need to flush any multi_pass iterator we might be acting on
            if (!is_first)
                spirit::traits::clear_queue(first);

            // if we are testing the first component in the sequence,
            // return true if the parser fails, if this is not the first
            // component, throw exception if the parser fails
            if (!component.parse(first, last, context, skipper, attr))
            {
                if (is_first)
                {
                    is_first = false;
                    return true;        // true means the match failed
                }
                boost::throw_exception(Exception(first, last, component.what(context)));
#if defined(BOOST_NO_EXCEPTIONS)
                return true;            // for systems not supporting exceptions
#endif
            }
            is_first = false;
            return false;
        }

        template <typename Component>
        bool operator()(Component const& component) const
        {
            // if this is not the first component in the expect chain we 
            // need to flush any multi_pass iterator we might be acting on
            if (!is_first)
                spirit::traits::clear_queue(first);

            // if we are testing the first component in the sequence,
            // return true if the parser fails, if this not the first
            // component, throw exception if the parser fails
            if (!component.parse(first, last, context, skipper, unused))
            {
                if (is_first)
                {
                    is_first = false;
                    return true;
                }
                boost::throw_exception(Exception(first, last, component.what(context)));
#if defined(BOOST_NO_EXCEPTIONS)
                return false;   // for systems not supporting exceptions
#endif
            }
            is_first = false;
            return false;
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;
        mutable bool is_first;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(expect_function& operator= (expect_function const&))
    };
}}}}

#endif

/* expect_function.hpp
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
*/