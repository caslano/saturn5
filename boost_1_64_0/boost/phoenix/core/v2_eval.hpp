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
D23SQzehVG63DFtKg/4T0R0MHIE+xDqST5AnOEycXhiMEBTBuMyepyem11h8YXHB7v0YY4kwd7RJ7SJxiwQ6v3TGVaQ5F5KBpKm03qYBINBhQdR+jDML2Nmt6zo1DE7GWIOdblo/lBqKt9CudBLsiGFA7kwogNQ0q5fW13ciAlxpwcpllv5I5Ogxm747zfccAK3gViPBrUSXGOCaW7FjMJUaZMbXIdVnmCgjn85FROQZxGRydKc99lIVdcsKHoHQA/MnAnmgDKlsW6xR1FORPfYAKJB+y6x/OmDvTC5C8RaibAiaFTr61HfPd9FOPHKWvOgVau9TDbrRXSsu8HZTksbRkwOK0jKxUcJT8KefOzkC+gxlajTUaP0ZMY55eHdorGLeBjg3KwbzTi8ElSwYnMnWnHZVFnKU1A/lYpUhQK5kFZrSK6bPFXp1hb6+VC+g7K3v7YciyIWchDRDpYfdpfp09tbWd3v7o8K7F1FxZ7qLFA2uV6JaKP4+nG/Ivm7i4Jg6sVFBpVKXVeFXUslEzCDTOOeJQ9AhAMZxGf1Af9HNFAbfo9fLf2/snA==
*/