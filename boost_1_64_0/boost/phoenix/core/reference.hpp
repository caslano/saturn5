/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_REFERENCE_HPP
#define BOOST_PHOENIX_CORE_REFERENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/ref.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    // reference
    //
    //      function for evaluating references, e.g. ref(123)
    //
    /////////////////////////////////////////////////////////////////////////////
    namespace expression
    {
        template <typename T>
        struct reference
            : expression::terminal<reference_wrapper<T> >
        {
            typedef
                typename expression::terminal<reference_wrapper<T> >::type
                type;

            static const type make(T & t)
            {
                typename reference<T>::type const e = {{boost::ref(t)}};
                return e;
            }
        };
        
        template <typename T>
        struct reference<T const>
            : expression::terminal<reference_wrapper<T const> >
        {
            typedef
                typename expression::terminal<reference_wrapper<T const> >::type
                type;

            static const type make(T const & t)
            {
                typename reference<T const>::type const e = {{boost::cref(t)}};
                return e;
            }
        };
    }

    namespace rule
    {
        struct reference
            : expression::reference<proto::_>
        {};
    }

    template <typename T>
    inline
    typename expression::reference<T>::type const
    ref(T & t)
    {
        return expression::reference<T>::make(t);
    }

    template <typename T>
    inline
    typename expression::reference<T const>::type const
    cref(T const & t)
    {
        return expression::reference<T const>::make(t);
    }

    // Call out boost::reference_wrapper for special handling
    template<typename T>
    struct is_custom_terminal<boost::reference_wrapper<T> >
      : mpl::true_
    {};

    // Special handling for boost::reference_wrapper
    template<typename T>
    struct custom_terminal<boost::reference_wrapper<T> >
    {
        typedef T &result_type;

        template <typename Context>
        T &operator()(boost::reference_wrapper<T> r, Context &) const
        {
            return r;
        }
    };
    
    template<typename Expr>
    struct custom_terminal<boost::reference_wrapper<actor<Expr> > >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> > const &, Context)>
            : boost::result_of<evaluator(actor<Expr> &, Context)>
        {};

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> > &, Context)>
            : boost::result_of<evaluator(actor<Expr> &, Context)>
        {};

        template <typename Context>
        typename boost::result_of<evaluator(actor<Expr> &, Context const &)>::type
        operator()(boost::reference_wrapper<actor<Expr> > & r, Context const & ctx) const
        {
            return boost::phoenix::eval(r, ctx);
        }
    };
    
    template<typename Expr>
    struct custom_terminal<boost::reference_wrapper<actor<Expr> const> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> const> const &, Context)>
            : boost::result_of<evaluator(actor<Expr> const&, Context)>
        {};

        template <typename This, typename Context>
        struct result<This(boost::reference_wrapper<actor<Expr> const> &, Context)>
            : boost::result_of<evaluator(actor<Expr> const&, Context)>
        {};

        template <typename Context>
        typename boost::result_of<evaluator(actor<Expr> const&, Context const &)>::type
        operator()(boost::reference_wrapper<actor<Expr> const> const & r, Context & ctx) const
        {
            return boost::phoenix::eval(unwrap_ref(r), ctx);
        }
    };
}}

#endif

/* reference.hpp
YU6nKGZ/KRFzM1WxW2GncE7ep9g3Z1Mxb9MUe+W1A/tRumL69MCtmmUoFtajd7JmmYptLnLZrVmWYh/r+2GdyFbsj5jf8O4+R7GYjYb9muUqVudeEfKXp9if7X9J0SxfMYfv/3DU7Kpil/oe3qRZgWLPJ/S9qVmhYiFbNiO++4pF/74N62CRYq/D83FGKVbs09xP8L68RLG8tEt41i5VrGqVHk800601tezr1/CuxEIxp2+Wop2VYnUGz7itmV6xAaGdMP8MiuWsXIF3CQ6KRY5dg744KvavhMP4vNhJsaq7s3M0c1bs65kv8WzoSlaF2Sfju+KzJS8ye2b52xcaPxMmq8ps2a8T22kWSlaD2c1FbYs0m01mx+9X50V7zdYq17TxXIT3n8lkBmZbQnNDNEsnc+T2ddR21DyZA7M1VgkVUGeKVTp+w/jO6mtT6zlmyDWMJxmPYfuxPvhZP28y3s/a89dvw5iRVWbm3XeY8dmXzJZZtys3EPt4Mp6jX1b9Yvy5e6VdqVthI81iyXj+gnp/MEqzJLJqzFwL0+M0SyPj+QtfOOAPrC9kPEefrUpej/mu9GXu3BdTMDeVa7bJ+dwTNb/O9Dmg1brooahBMj7Wnqt6FWA8yZyZuV2q112zCLI6zByG2W9EnZFVZ9bl0gRrzVLJeC1dnDrBA2symUuZ2ZKtCp6+G/GR2TL7dUuqAbVEI+TA7GQn2zuoJbKazGr8+LHxZ/IVm3bzK+ybwco1i3vuC9csnKwaswqBX+K5MZrMktn0w0uMv3eLrAaz3j32emL+kdkxu/D9GJz5MpS+bLqpN/6cHJk5s8671ho/KyCrxazNqR6TsF4r12x+vOQN6iVep2vLrHt3f6zJQWS1mQVe/j0PNUFWndnxM6cvahantBuRndYCNaG0W/ZynvHv1ZHVYZbq1gBz+j6ZGW9X+Ogl1h4yHnux7Tnjz3Js0OlsmHWNc7yMdZ7MgllhdvsQ1BKZObNuqzwSsc6TOfNr2q7og3lEZslsz9uf5mE8yfTM8jffxHPjaLIqzH5Y0KM9xpqsSZnpyboMn+WBWiJrWWaVyX7udOQKzhpkLZh94/9dFva/jUazIeu8eQ3W60Cy4Pfm+97eGPpEYX8ga8ba2cwy/h6sIrKWzFyfzDL+rSk65dRnNq6DDnkPJHNh5vv5KZzBoshiWF+6Hy79D66ZoNONZNa0vS5QswSy8WXvHK3JHBccMO7hm/E3L9/bjXadUfPBZI2ZRfsuxXu+xWQV3pnO4Gul/J3emM0Yz/fm5jXiBuY0WcMyq0RWc0oVO6zzZLbMltdsG4p1kKwms3Y9R6IvDltM21UI+G0m6nOL8X4VyeznjvJEfZK1Z9Yk5HcfzFuyBPN/ft+hJZl+0KJTOJt+i2u+tx0btnTB+exfNI+Y/dLg4RrMPzLXMrMgWza6KdYQX7JeZfl7Z+sqVMC7hHjFdrnVXoY6+5exXszI5vff8gnmdJJOZ1WWdy8lR+5kFmXWRTFPMu93Rv/0UyyMLKysL95kfZpVScUcS6ZrltOugGbGpLL7qRa8g9bkcizmB2M/PRSLTSnf4naWb2t3lW/x/9bekfm+H5cUv9K/cX5R7Nm/qx3AfiRYCbNuZPVWNzb+zg7a6WNbk9E/FVhfzMl0Ovy96ww3smNvBkzS7F0R68vMSWlH19KlNnxnvhl1yCZ9u32UZlebIPYMR7Ibzgcva1ZA5lVmNckG57jnaObelK5p+88133+OPuhsX82yOuJvwGbYK31xohkVWXbNymSL479pqVkKmaHMbMhe1rPZr1kGmVWZtSEzPN+Uq1m2jzGGZmRjxqWnaZbDrBPZrQPX/q1ZLrNuSuxXmXU=
*/