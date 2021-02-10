/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DELETE_HPP
#define BOOST_PHOENIX_OBJECT_DELETE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(delete_)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct delete_eval
    {
        typedef void result_type;

        template <typename P, typename Context>
        result_type
        operator()(P const& p, Context const &ctx) const
        {
            delete boost::phoenix::eval(p, ctx);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::delete_, Dummy>
        : call<delete_eval>
    {};

    template <typename P>
    inline
    typename expression::delete_<P>::type const
    delete_(P const& p)
    {
        return expression::delete_<P>::make(p);
    }

}}

#endif

/* delete.hpp
7XdQ0/Ggpmfv7LQ3pr52PzeO3B3sWT/e8U/FkaZXVuuNH6AxQBD9Ye+nD/3x0aezD7+NT88Gw9E7pN7C/SyZZ8FnuRNz0OVsHrCP6/siAsFNZ04T/AO2d0mmGVWv8XOUCaUjE/C+khRNQs6qUkMwpwLGJBNBaiD2bkDfgBd3Be5CnO9xLVP0xnImuIG0GEcpqOJcMbhofr5EW3HgCdQO+UpwUQIfFAaWIhF0xUIupvJqed2eC98FnZTDJ6tsGOb6dN4f/zoYIntu/IDO0kyIPpD2LCM7fkOe3sOZyzgOQoB+4/pLSeB1p9773mCY9aKvIK7d1b2GJx/7H60lxq/Qa3d1r8Hwl94HG0P4ClJe06vAR8f9d71PH0bj05OzkfjxZWefiEGQddWHk/foAJS6qHLR8MPrHVyZZNqGPxvZGAVARyfDd4P3JThcDGvMINi3yKCgDfMmqGVgCSdzF/hKaXVyqd6IRnf3b+0O/K/beKVbLwNUCKBIIDLIHC7S2m9E5xWSRvtMHpmBTMmjsgH7tgS1zagsYwoI/gVSYcASHkpECBpY7NQDHakdk6t7EAQVuCjXzTKMK40OuSiARXE421GhMfNuApo73QRlGvxsND0rAbl3DMi9+yZA2mJoQtQ2YGhV9X9OFhXlyqTE
*/