/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP
#define BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(static_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct static_cast_eval
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
            return static_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::static_cast_, Dummy>
        : call<static_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::static_cast_<detail::target<T>, U>::type const
    static_cast_(U const& u)
    {
        return
            expression::
                static_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* static_cast.hpp
XV+WwWCNL+8ouqojcx9y6kKNok2JRZ2vZpiNF5Nb0VKtLpI1OeZqizUGGu9DypshOnEo7Ns9yfyNStHdGLgjmVWXMHtmsUWSdZuLmt1UI8ybFbWxCDdeT+yu02E3jn24rS5k7Wdtja78CFJxo0AH+4w45MNtrQqSwv/jWCPECb4isbhzeHUPFNyhdSOXzmSNcUdBN04zcDtu6w5kjrvZOTktcIvcOHOhUKdKKyRrgwBbW18rSy+0rSJIzyjWAfY2KDdL7irr0gxcTPu3sKaDZuD2logb2zg1OosmrTua9OdEFZ1iTS+lElMdIO5AFm5Rp5vd9/Tm6IyQrDsctXG8hqzRpUbwyAsMsQMc7DMRa387a5ibFXWVtZBgnd5YkdUtrFu7wlocNJSPmHy5caMBGqP2IrJuGm56YY0x6GZ6cmDXKHBzTFHzpjc99Wms214Z1MaY67HtM8ja38bG18rK28LCw8QEso4XxevawqSusAaqI4rk6Q3lXWWNG16of91p1n4fwo3vopdx2DgeoFG43UWmTeAmBmIoM6dbtw1jxlogo7oitjCQZtris5XEu9vtG1/bPTdEF7mwhazNLTxNTIIcHTMQazgvJSmsOj9BommjknjbuIFRU22RupKMRk7WlVwVFSZrIKoq3iQoweUUcr8U2rbSH2LdkhTYkuQPlcgW4kuJ5E74dh8ibYO3Xgg6PXwz6+eMcTdz0M2R
*/