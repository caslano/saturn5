/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
tSf82hIOPZmAe+IANeeRbrwz/LoB7djwMxdorYlvt6rnNQkO3tDNYtGrDjyrvlnNj4caBOeKha1qjFUVu6Ke89sD3Yjf2iymdeJBXp8bz6ZI1WKqV8Jp6vXJL1Sv4R3Wa0IYrRZVPkIbxAjdqrrUWERNoki+oL13dILfUJWMQeq/H+yu2cZBWi9cOOnMmDOaL3/ESokN9UGjE0yDUXf8R45TNVsUi2461kUf6nnqvUtO0lDPY7Nn+P8L0XvWT9ROUldDLnDBUdte9P4RYxa9iMttkrvoXLS9vK01M+gK3qFjzQzaRxcYqWG6wMjjAqOVU7c45h8IW/rcpdwGulDb1YWcEzJj/KlGv1TlhVgocZ5jcRtbDFruKQY8nMuNZRP4AX3TtEA6lC5hTRstoqVNopK4cwC1+B123uKXh9EoyYM2f+dHomgdd4+LmVadLfmRh+4cEckFkj4V7U88LvNyCiDKEw0ILyQeiiblcxfSbtmfF9pTOINTmHc2pzDNTGF3TuGF0eaBaxRPoxf8vZIQiI8mZ/b2bHAmUcI9hn6t3hRtIaYX40gyiYH24JhsQPTM8J/7asWA+D4CBsSfI9mA2Bmhr0ggWn3rIy5u9MTvRhp8ynm5wW8SvLmLuVp+eznVbx4c08Vf9OTo9HZ6HnSsHR1GAqbWWEQM5O17KCooX3/EmToJR207OVVrXkm8tJ8yeiuKakSOPv1qlIjr
*/