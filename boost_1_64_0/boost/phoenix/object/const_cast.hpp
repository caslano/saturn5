/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONST_CAST_HPP
#define BOOST_PHOENIX_OBJECT_CONST_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(const_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct const_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return
                const_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::const_cast_, Dummy>
        : call<const_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::const_cast_<detail::target<T>, U>::type const
    const_cast_(U const& u)
    {
        return
            expression::
                const_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* const_cast.hpp
WsBzl3XVMOqK7GPyyWkDXm7KDDQhkC8/C/Or/DyargXeVTe4Bh4A9SWFoInOu+EMJS6wcvXf1zZyEGUYmka42rhwZ5C57FKQBYTG9lyIIj5cyiwHvh8uFJmjPfpXzfHhpPLSmnARJTE0HysXjXlQRTQZg5ttSYKe6x9ObHdSbCJ3vlL8cTpPnBK4UZsC0Ew9TJ1t/7S139Fv1FbNJiEubkqH3a3FIa1nP6Qj+E5G3tp0xcpx4f9RCtlQ/+YdTepBJCMl0qnr6GLb+WPNf9l64zcVoGqR/KbZbsMQ20pIbjoFKwDD3BwiqADTDKBo8C2kd3kQ4j9xSSRFYt15eklGQsrRvVgV/jSAqts0g+MN4YyUbup2r+hcysvnfxIFvLkZPig8Ae7a/17qKpOS/PhSlxWCncrtODtaYcZpbKrzHihnJ58IRxlsVVe9J811kpFhyTY7Lgqeq4ZCALdJoMvWSu8Q48wKsN4u3sSnEcO6cS9Q6nKA25jAUs2TE+IjdYTsMFL4b5JDa0twjhpYwyEfhpy4ZOtB2pRJtiSbUeG3RZTzYs22TfNryVMGSA==
*/