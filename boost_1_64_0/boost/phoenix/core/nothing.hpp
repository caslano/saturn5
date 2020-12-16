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
Zp+0794B53IyXoPey2d9jTlGVo3Z0m57cV7SLzLN34q68f1Qn2QGZrWOrD6D+UdWj5n14Gf9ETtZVWZ3Ar9bhvWFzI3Zxvo/1cb8I+Nj3aOOAeeJDLL6vOYHDMVYF5LxejFrutD4ux4Xm649q4f/+w7iI+Pjcuir/s0RH5nJ5wH9n+qwfpLxPNw1H+uGuam0a93x9SucTcl4fX76pMcHyDsZj+904eFS5J2Mj5nb92aIr0jpyxef51uirpeY1tLM45Ow1nmS1eC1dMQwCc8dZLx2rdatQx7Gk/E6u9Hj7gCcTRWzO+H9AGc3srrMvr2RWxdrKxkfs8Mf7A3E2krG4zt0b7cFzm5Ku+rWaZjTjjGm7d6eqPEQsZPxdnUf7B2M2Ml4HrZcfwSLIOP1sqaw+t+InawWs0KP0+uxZpEZmPW+/OoZ3iWQOTMLnjvO+Pk7GZ+bVV99Z/ye4lLTsX465dv/4HmTjOd26x+ra2K9JuP9/LlzX+O7WDI9s6u3c0biXR4ZH5fNg85fxnpNxvs5b+T3q/DMpdiLZ8c6Ie9KDHMOv9AjduV+HZqlYKz1y0zbuaYOvoE5TcZz2zmq/mGcy8nsmLXfvsz4mRRZLR7fcMNBnMuV+53OG4V5G0/G68x32Djs/alk1swu9EvfibyT8Rzt73x4EJ5XyBowazy6iQ3yvtx0Hl2ZuQjmSsb7klu8E7n1IeNzOir8UHPEvtzYTweynBGvvJF3Mhtmtp0tMZ4RSrvZOQP9sceRVWZ2oHl6HuqFzJWZrv+E4RgXMq+y3wVlT/b2h09HYr4vx/PRe6sxUTcNeY/V6doz27nk9ypYs8ismb0+2tf4vELWmVnwY8cGWHdjjf20IzvVKBb9LCKzZrbZwTYJ/SSryGz2cAd8ZmOxwrSdfduK63DOIqvErOWzbX2xnil2ZcQQzCPnFcZxqUbm2bz9dKxnZAZmXm++7IJ9eoUxPgPZHxcW+mKvIqvJ7LhzYWWsZyuM8VUl8/7tGz/UPFlDZpGfdvZHXZPVYTat4ZZJOKOQ1Wb28q8vDiL2lTpdI2ZNb1bD3uFPVpfZ/KohFZF3MidmVVesuIAaJOP9fFwyGeeJNDIXZlu61oIVkDVlFnhz9Uj08yudzo3ZX/kFhVh7yHjszV64v8HzChm/37hFX21EP8lcma1etnQe5orSLvTISpx3CxVr7LkDZzeHOFrrmJ24MgRz04uMj0v1aIf1WCfIHJl9ucphDeYRGR/rmW8Hv8TZhqweM4sxC7BXZZDx/BXPWdwUY61c80DGhqM426wybWcx6kA9vLsg42P2ct51rFnBZPV5TSxp+iPWLDJ+v/C5gQE4v5DxcRnYqtVJvJ8g42P93Rizn1DXSrv+lT33Yt7S6uzM7Fy1+KWoa7IGzHRtKk3BGZOsEjOffsM+Qh7ILJmlD3Afj/gU+37Q6GY4vyhWb5R5JGpQMY81lz7G/qfYpu9+dsJ5XrGV/3o+DGuIEkO3a+OLsYYodr61Y0vMTeWa0cltjbWk2MlXZ43flVWsSkPj74DOIavI59+/97/GmqW0m/DtSezTVxU7vS8SVqjYx5OOtsbeodwvZnrAGNSL0m7Y+gic53VrTNvdXvPLdMwHxeovu74H+4pi652MP6viqNiXlmYzUZ9kvC+HD/WdgP1WsR+D7xm/d6ZYcWXjdyO8Fevy2+0WmvkqfanpPLAt5oPSbkR/R6y7gYqV+H0HC1Zszvz6GM9Q5X4lJSk4n4Up7T4btwP5C1faJVueR3yRiuUta4P7RZFVYtZ4+kl8FhlDZsXsda1xJzRbq1zzrO4t1roEMjNma868xLNFomILC13wbi1JsWrfZ+NzrmQyc2Z2/Ro=
*/