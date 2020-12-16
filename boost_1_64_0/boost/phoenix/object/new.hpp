/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_NEW_HPP
#define BOOST_PHOENIX_OBJECT_NEW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/new_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(new_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct new_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
        {
            typedef typename detail::result_of::target<A0> target_type;
            typedef typename target_type::type * type;
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type *
        operator()(Target, Context const &) const
        {
            return new typename detail::result_of::target<Target>::type;
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/new_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::new_, Dummy>
        : call<new_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::new_<detail::target<T> >::type const
    new_()
    {
        return
            expression::
                new_<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/new.hpp>
#else
    // TODO:
#endif
}}

#endif


/* new.hpp
43Oiveo5kQDJMjY+KNrLB0V7+aBoryMKCYrBtm+5zRbHqmhvnhwpKgxwd0UUt/uRJjfbAchni0caHfeBhFjOaETG5l/fAZD7qxZ5obvrodd3VME+4q5oAaZoNQsRKG8QIw71a2ckIAMTvfkbIqj1yz05qFy5tmXAb9MurRevANEJ40oTMChbD6UNsSEYCfFNbPs9D7P2CUS49ykXqUf5LtEm7PKn6vz7afloWGGLjouQvxSNXD9pIeluiV4vWAMgMbsZKb/xvrYbk9/Ag4Y83au+eccz1SjeaMq0r1Vz8ST0sSOcj+eYJ4sUy38N73D7KaEMooBeeVKkhPtvA3e8YxAZj00NHadQjskRT0PzcDKSpmnSbkjOGz+KyXAaTx9oOZ/H9hVJOM8USZjG8naYmad9wMsfnhQdpwCT4ZA4P6HOkx8QGe1SFHWa0DbBvSpClPuKVzX8+pl9e9NapR3hWtl3IBg2TS86LHD/MYxX0w+HeFW+hDGTndcDdIIhrgPg0sZiZjqXuKdpia8eFiW+riapz95alRL36kjJk78/xLF8RHKLVuK/cG747/ho8++yUkV+eUMu1HKpi9RrJ+Jx/hXU3Eoo1+RZcTyWeCUMcMQkjPLhtcQfFCnis6Mk3dbQZCUlStGPZM4XYctTnl4Rcy5zHEGm/2C61HdJw+3PyMgkbPghQ7GBQ1NcNm28wcZcYEJgHM8HBEwrvmdhGZiT4rpFP3Il6QKx6bud19KuxQJTG2eMuHyS4GrLZ11MdQi97by2U+dcn3/7c+19VY1Gb25ynpwvuo1i4GotpluRulrkJukCmLs7Y8X53ii4yqYfX7/UmpxXtDXu+TZpkQKaGhq6lYXjiWXaGfdBPWOVhsYRIQPg5RmZtlBF3CgP4kJrus72FoZQl9sgjv9uO6DOXl8GXu353QFL9S+COknclGcElqk9OAnlVGbwkoy1kqqI/BnYo+GKSpGQS12DpAgUnxYrtgF8ce5mf2vAq1Chmk3xSlilpOianpZCapDSkv4ZMf2XfUheSnn/tzh8fbNXPekpp0bGe/Bc+WE/D3ufstAifp/DaYHblp84beOCH5dYruWYLvaJukYzKu+/vauNN4P5rchENHh8aCG0oZUkbinTe+ywKeQO2YbJqfbHWhQTi+AClZSxnCtxsRJ2jlTf18pNDB4KPc1fSI/w+98C9xGiV8ceEqQp1sAqdfXvaNQ9FSeEY0g8kvTSL3OJzlK1xLHY0KMfRnCNUlpY2QY5WKT0tSp3YZXkvN6rTHnlrafF6zpPGbShooqHipNVyjBUlSf3FjXkzvBYiVLWokj/NJZQmX6axGkVCyE00TfUSjcycKxoJYWBi1MxlxfFZs7nYtWEWGIo3QYIRPrjgZRrYUpwtlGxt2DrlaQ4koXQovQ4Lzfuxc4Uq7E7KFtFao6uV3dX1iFFalfpYt/fVA5+UaVxuh9PW+XKoWbugw+rD2GluquNzvahFL6fyK2BLh+M4V/KgNykZ5mcnQQ98dYS0qQkidaSU7wutUHL/UU1cvhmodpoA0lCXX15BbWJkLuuqcxkNWD3a8ROUok98bZYMbliGCUbb9lQOj2/H4vpOS/FE/3TkQxC4E3PMBfEgXLeQDwQiEIUP5R/IJfSM+KRhB96yaFtAHkpWzhyx3HdxEhxX/EA4PCaPwdtEUrQpkpaW54+UcPXSlxkZYZNNNIB/5/NtDVxjILK2lFZlosGbuO6DqmWcEU82JNfoWl+9+4sT/ZOtgIUXE3gLKQIdDD9PNkVOv04AOt6Py0yWXrQEMVLtPxtXdnqRQraMjaqd67GqR1kk+hnERL/lkP2plz5z/vZOpV+3mYTfrFChEhWzKg=
*/