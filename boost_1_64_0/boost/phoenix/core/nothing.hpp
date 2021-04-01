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
Q5jlH+Eqd77jX3ginX1/nAr+cVIh7VSJ1Np/Sg2+kxzrBJM1LqmeuFgve6tj4hwUKkwTNWUtFze6NBToABebPRtvwWcN/gElNLrgxFI9iYe3mpLk2aHH8NEfrUiR8mhU1vQ5r+wleszMGmW+qC6OONwWJ2fIMlppO/Wzn7h5RvTatEdI7wdDI0Fwmb3y4IFz0ZWuvQqIS9YrbBt/joZUfN0NmsiH8FkzM2EZi/x6bIl48VT7YACAIpDm/1pUkGpGtdi2KBZxNaesYhBioxyhTbLxzNR2XZ+RhSOKUoyNMMTt/tSuD8oo4FoLdYLn7PgoEp9qMC5GkQug5IInk29fbH8QUdoYOTC7YvZ7lI98tXggnsYVLwq2vyxtOTD9nVZkGD4dmoTJadtFiBl/Lk4SOYl1MfbaZiRpmCx4XzPasxhMe/xkCARK//srA4AXNyqyOsgDWivGHRmelDS01Fhuepx9JbGk1ZyByduF4lU87tRYV6CUxoZ+jnqQxqZparO8tbDGQdyPDASWHADeZxY4bETQmU9HH8LzuwFAxgl/PUm+V/wCfFIDZWiiwg==
*/