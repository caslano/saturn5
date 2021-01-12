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
Y17AkWfTsRv8ReBJ1lGyyUvjW2dgx2vUWJS2poABv6xjPq+hKy3hv2Dv/LnEQuSyy0eCXWGMMRM8wj6kAfjYeOKOkfRtI/MVCK+YDAeBJ5Wqjq+4g4yfAxPgABHEMiY4U5u+8Ip98Fo/cAl/cwlum/kb+LBIzW+C6znwrPbYM3xge214H/nGlvj4uvCKIW04+0fAwazkmZi3rLGSWHcA/QaX5iG/A3DEHmOJB3fgmzqyjsOY
*/