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