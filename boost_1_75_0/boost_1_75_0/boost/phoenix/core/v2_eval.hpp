/*=============================================================================
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_V2_EVAL_HPP
#define BOOST_PHOENIX_CORE_V2_EVAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/lazy.hpp>

namespace boost { namespace phoenix
{
    struct v2_eval
        : proto::callable
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval const &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename Eval, typename Env>
        typename result<v2_eval(Eval const&, Env)>::type
        operator()(Eval const & e, Env const & env) const
        {
            return e.eval(env);
        }
    };
}}

#endif

/* v2_eval.hpp
W5/+/sVzJ5e+j++2jbpu0Se4LnHvT/9iYVv2F/g+W8ZNDdqvbnjfcNxbByJu2nVp9JITdsbiugXfbbvm879knXrG6nEflzXk/sLfWCytY/C9NvU7bX+d0T03JnPPXGlNc1fDKyviYt5ZMfv/fmuNu7OgPVvPtlqvgev0MEKWGwgZC81UD+Ft0F7nGwn9Rtu70LnGmgj5B/D/HSZCpwH+HvCthut5oOVDus9ARiTE7YXwJrjXA74M4l7Bd+CgD8TC5WcfYSVLxO9Bvg+yLwUeC6zVL4S8roK0tcD3PFxbIN2vcNVC3NP4npoRJ2CEnIQOAPJvgLhiSH8+fsoN8Ds4tsZKAL5zwc9mqldH0pzRJX7shj3Ki38hl198f8uv2/pbfm2HyBz2NlffPzWhyCqQ1iX9s6uXMljWQeQgKXTi4HJQL2H2SUkG+pkLpRzvSYulgZMEvJIz+Jzk13P4QecU8KoOL75lN9gf+VC9ssOL77gNPqm6jFcPPWeprA8NPWd1mXM1x+jVuALNMXw1bt7RaiVZZ9HRaqW21WuaQW6bvKkZwrbJxwNJlcpyeCCpal3x8C2n/+6sXo13AXtV/+xzKCP6PunDfvgTF+wHMFzwr4mWaQx47Cn9C6qhyR1gfi8Vgj/D4gSsDajZ7L2n/pIHL+2tkCS7/ySSy941sPTgJX0bjDwFA7sRtS3bIUnxYJIE7mykGgaVrNcbMpAs
*/