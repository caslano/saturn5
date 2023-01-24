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
D0j65EwDWI6B5YMtiS86/xtKyA6wNkc0rDv5T+es29FsXr9+d8UFV1576kXG+FMv7jKvvnj7Z1/9IXzhwT+4hNs3Z3c9es2+4rduGH/WRze8tfSTG9p95910+fgrbrKbZ2zZyJ269R+H3VuL3xx79zdfL7/vl+tLHmre8Nqjv+VEPvZo9PuPdWudT3o/v/Dtzu/e2O+rm/jBwnEln1Ss+scX229r/7InO+ybZ9qav93x9GPf3j373X+cu0Pzc+wtj2vt4dv16QkP6Je05I782LhozPYz/zah+KxNE1sfyJ76/oHWqdnPuaZ+uLjxuL8s7pz5VvfD5VNSV1TcU3mo4rJXfqmYn/GnWdv33Tar9hldjffphJqaO+bO77z1hPkbtm2azz2uqYvemr1gR491wb2PaRuvyrjxxC+ziluWfjS9JfseW+vhmq/8d5+1rCNhxgkdN9/h6GjtfqnjH09N7foXLOUvgnb+FVwvGwiZAvep0P734GUkpIE9MUDOw7OuCEKugOsjuOKAz4F745Dm1khCwqMIucNEyKUaQv4JHftzuP8fHvPD/UZYdXdy7MxtPcj1Ae8UuGJAdpcef9+AkPvhXg98P5rwNxRglQ74hTpCIgB/A/C/Q1xmNCEbIc1BSLsCwqmQrgL0aotg52d48Iq/vLwD9BqFv+kA4WfhKoO8d8L1BvCWgayDenbONgXP5OD+OOjYCtd9ILcR
*/