/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_META_GRAMMAR_HPP
#define BOOST_PHOENIX_CORE_META_GRAMMAR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/default.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // The grammar defining valid phoenix expressions
    struct meta_grammar
        : proto::switch_<meta_grammar>
    {
        template <typename Tag, typename Dummy = void>
        struct case_
            : proto::not_<proto::_>
        {};
    };

    struct evaluator
    {
        BOOST_PROTO_TRANSFORM(evaluator)

        template <typename Expr, typename State, typename Data>
        struct impl
            : proto::transform_impl<Expr, State, Data>
        {
            typedef meta_grammar::impl<Expr, State, Data> what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return what()(e, s, d);
            }
        };

        template <typename Expr, typename State>
        struct impl<Expr, State, proto::empty_env>
            : proto::transform_impl<Expr, State, proto::empty_env>
        {
            typedef
                meta_grammar::impl<
                    Expr
                  , typename result_of::env<State>::type
                  , typename result_of::actions<State>::type
                >
                what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return what()(e, phoenix::env(s), actions(s));
            }
        };
        
        template <typename Expr, typename State>
        struct impl<Expr, State, unused>
            : proto::transform_impl<Expr, State, unused>
        {
            typedef
                meta_grammar::impl<
                    Expr
                  , typename result_of::env<State>::type
                  , typename result_of::actions<State>::type
                >
                what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return what()(e, phoenix::env(s), actions(s));
            }
        };
    };

    /////////////////////////////////////////////////////////////////////////////
    // Set of default actions. Extend this whenever you add a new phoenix
    // construct
    struct default_actions
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::_default<meta_grammar>
        {};
    };

    template <typename Rule, typename Dummy = void>
    struct enable_rule
        : proto::when<Rule, proto::external_transform>
    {};

    namespace result_of
    {
        template <typename Expr, typename Context>
        struct eval
            : boost::result_of< ::boost::phoenix::evaluator(Expr, Context)>
        {};
    }

    /////////////////////////////////////////////////////////////////////////////
    // A function we can call to evaluate our expression
    template <typename Expr, typename Context>
    inline
    typename meta_grammar::template impl<
        Expr const&
      , typename result_of::env<Context const&>::type
      , typename result_of::actions<Context const&>::type
    >::result_type
    eval(Expr const& expr, Context const & ctx)
    {
        static evaluator const e = {};
        return e(expr, ctx);
    }
    
    template <typename Expr, typename Context>
    inline
    typename meta_grammar::template impl<
        Expr &
      , typename result_of::env<Context const&>::type
      , typename result_of::actions<Context const&>::type
    >::result_type
    eval(Expr & expr, Context const & ctx)
    {
        static evaluator const e = {};
        return e(expr, ctx);
    }
}}

#endif

/* meta_grammar.hpp
dt59C2pJuabvocIYfJZFZsUs6+kF1EQEWWNmT6f2HYbYyRoxuxhn1QpnG7IGzBLPbvgMZxuyuswOlj7+ArmdYtpP81lZ55FbMhdmNlYeDxADmT2zE7NKje9NyXg/G4wcNB9rORnv58lqO9ugdsl4P+u33XMGMZDxPHi7ZHvjfBZh2s97s+b8hTMKGc+73+UtkXi/RGbN7Gp4B8QeTsZj+P7E5n2Yt0q7Neu/aIKzKRmvedvFp/TYq8icmNV5WnoS6zwZHxcPJ7M8xDfVtN2RDkfGIkdkvJ+TPGyn4p3AVNP67Hyt1Ac5InPm8a29NQ3PlEq7aQsue2ItV/oS2CWwIeYYGZ9/115+vwD5I+PxtXK4bYPnxmmm65L1xOqHEB8Zn+/df1qwDWsyGe/Ljex6vyE+xeoc8L+CeaTcr37BT9cRHxmvl80rWqNe8smqMDv61U6M530yZ5N1YkYxztfTTe835/Kvy3G+JjPJw+CKRXjfQ1af2aDAX0pwllLaze5w3ID4yCozW7BwVSD2FbKGzEbd8m+B+Mh4fI6Xnw1GfGT1eA1uMYvCc3Gk6Xl+2amYy1hfyHi7Hr1S7TA3yUzeD15Y0xx7BxnPQ93Jf+DsFqlYHX2lUjwXk9XntXTetQ+eEZR2e3oO/gW1S+bKLNvvej2cFWeYxpfWftAd7A9ktXlN/Kt5ddQumcn7gnlOTbE/kPFxiY51a4a1h8zk5xketTmN995kLnw+9HmMNTKVjNfZ0CG/DsWZgawGswTbY5/iXRBZTWYv2zfE+qKbqcyHzpdQE85kfI799KQG+uJHxvvS8PSEjzBvFXOvVrUi9j8yO2YfHLhwFucCslrMvohMO4B1l4zHl3JrzHDErrQbveE/qXhGIKvPzCY/MwJ1Pct0j5vxTY2nOF+TOTJr/83WIsSuWP3fJmFcQsmcmT2p5OCJ87XSztDG8RjmtGJDrjStjLom4zU4OKu9PeqajNeZQ/Li9TjzzTYdsxOHjc8kzmR1mT1MDtmG+Mh4TfQJ/wM1MZqM9+WYw5MdqF2lnd+q1OGIj4znqG2DbxrjXEdmYFZjzknsOXlkJp9l6f7TAXuOEl/pT5krsafOMe3n7IcvpuJcR2bD+zKuQ1PETlafWbWgh2+x35LZMqu8Z9kFrNdkLrzmtyf6Y78l47nNqGjbFbGTNWT25vs+qMH7ZHzMzlmf9MGaNdd0rBeYd5+JPYfMmdn03V/Xwp5DZnJWfPngGtZdMmtmz9O+WoDcKu2iLrVrg/jInJh9+EuHKTgTKRbZ71s8PxSR2TP7wdsyEM9/80zXrPz/OBTjPEHG+zltdgn2Kk8yPi6p6XNRZ4Fk1ZnZrH7wBrkla8D7eX69Hu8qyXj+okfMxfkllawRszm9ajzH3CTjuf2g3gc7EV+UaZ21aPLFZMRAxtvl9dowA/smGe/LS6fN8Vhbyfh88Elajmf0ODKeB11Pe5yJ9inXbDHuA5xDcsicmX1+JBt7MY26SY5mXqj1Hc5E801jeFL8QxL2TTIee/e1d65ifSHj+XtxzPx31CAZj++u2y30M1G5ZmT8/r+xPyjtkit3tcPeSFad127PeIy1boFpTaxqf+8y9gcyfr+jN/zuoM7ITOam5yrs0+FkbswcmxzFWpdAxsfMblw/D6wTSl90Zwf8jHWCjOf2o33GdyyGhabXtFyzxQbrIJnJ+56r/VyxTpDZM8v7YYMl5goZv9+BaYcwnnFkdjwPC3NmYp0g4zGsXnFxMOqMzJbHkND9EeaR0q5tUfJczKNo03666X8wfmeLrDazMzMs8Y7Ml8zk50peWOJMFErG8/d3tz7Gz6vI+FxZ5BLxE/JHxse6affer5E/Mgc=
*/