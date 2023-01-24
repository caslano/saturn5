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
N4P2TgZ0krsRV0wXM3B2rs4Zvrn8uQcn6+7BjVmb0FiDUbY9Yg3idWFWJhhzQdYlGQyJQ5fozyW0SIg2N2xw49tG2NemVNQE+5vFTWitH1QtbZ0+xk2t0Ya18erWBsFLdM2X17CtiXeWbqVd4YWaq/Ae+XALphDuQJqocwATxzGd7t4/6NK562mscXf7cXefXT/URFMj9OisU6MiAWs/kIfTWAOU9IkKDRV5DKGCCakCcNs2a2o+A0bcREgEuhmqFKpN1qi/WcNoYZMX4ONabg/s2rIhyLIhkGQdSMmcOKBOAJGHx77dlEEcQxehx6ANabm6GHGGM9flqrR8LE+OWZs91EJ7MelhHw5YeyLWRYRdR9eWpAPjhSMmOOmXFDVriFApQ3AeUVlzTYmIOIW7Em6R12bIFp9kCON1s9hMFbyZPJx1xt4KqQX7cNp8M5oPD7aCCsKypLG2oLHGp4E5GdyRKCfPkbobkjZuJDJwjtoLHolD0Tw5VwRn4+4u1k/d4PQnvAXuczDs8jQ3S4uKwmOuwtSoupKMZjjdtxirXbgR61a0YQIdN2BNn0j84ZBNY03mZkSG1oojNRGsBcytC5lzC9+9ZeyNE2LTGGyNBXEHUrgtSdHcO+XSCfeOiJMunYjj2LoJA6dbtz6bOOXMvdoYkX0UT06wfqTFYK2t7WlGsAZjLsAa+GcKdEdZI9ylADHG3VjVeda4dEbs
*/