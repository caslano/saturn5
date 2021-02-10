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
AOAFRvEJapVOl3Bm+T2TCF0xSU8hJ9WFHNTejKNdpiTjMWBaCLLtQZkCsV7M85TiFONauDoE8JSSyyoNnux8TwFbny3ZJwG7stZByQsVAWbABcc+o1TwSGcwMAJF00jHk3wqgmDtoxusnwmaAHOEoHHxR55kYadk+1jW59BiWMEx4PWsY1axKTN6Nr+eEkstraIj1gLwt+2oH8Ur6tmyz0QaawzKCdkmsoXBFeGV+brWPSF/rJ44andXtT/EbaPPCLT7yESlA2v2GXeE+rmyjPHE0ENFycO40KIoOxx4SE51ykAqibtqx3IyE9zfxxwvJq5qnu/uqp3S8TYnu7h58zmADCyRZXmj5OJx6bZS2iawa48NohDZkKnYcGGuQRwEBGRfTxLwoABsQvXG5LHaSyfFDJAO5n0Et660YbU6W9HuGu4RuyDg3ekYOEupu4W0HWS5C7/bxMB4HogN/gCM0kCmr3E3hCVqnuQIyLxIxQWURwFSuD03JCQCGLd7yA+lVGWLHIHS1mhGM9tgDqr3WPKsmVYt9UpzYbGDGl3CH0I8VjW8xbTIr+49PrZYNmN9TjtLfbIg9QJop6FfareYajoyWKUCjQQJ6hiBS4DHCXGSC7vvnrZNLT8cN5OLJEagsOI6ux6v2oSprC7Q
*/