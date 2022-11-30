/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_NOTHING_HPP
#define BOOST_PHOENIX_CORE_NOTHING_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/void.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/value.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    //  null_actor
    //
    //      An actor that does nothing (a "bum", if you will :-).
    //
    /////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        struct nothing {};
    }
    
    namespace expression
    {
        struct null
            : expression::value<detail::nothing>
        {};
    }
    
    template<typename Dummy>
    struct is_custom_terminal<detail::nothing, Dummy>
      : mpl::true_
    {};

    template<typename Dummy>
    struct custom_terminal<detail::nothing, Dummy>
    {
        typedef void result_type;
        template <typename Context>
        void operator()(detail::nothing, Context &) const
        {
        }
    };

    typedef expression::null::type nothing_type BOOST_ATTRIBUTE_UNUSED;
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    nothing_type const BOOST_ATTRIBUTE_UNUSED nothing = {{{}}};
#endif
}}

#endif

/* nothing.hpp
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
*/