/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP
#define BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(reinterpret_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct reinterpret_cast_eval
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
                reinterpret_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::reinterpret_cast_, Dummy>
        : call<reinterpret_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::reinterpret_cast_<detail::target<T>, U>::type const
    reinterpret_cast_(U const& u)
    {
        return
            expression::
                reinterpret_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* reinterpret_cast.hpp
2FZfv7LjQF2aOR9h82myCZAVtl8pq3T27kh0X+7+qNKX+zrEn8o7O2DiShMidooVJpdPEVcWcZuAW20J+V6Ce0EqK5rPJBxWDKjjuHI5iOov/WOxW6zpjX4/tWJNVXp8PqJgbo/G1Qlsw8RVA5+WR/1peGxBodBTZ0HKED596A/LID6hfgGs8+V746PSJPcQaYpQd3NIU3aad9/sfYWWwFQ5kjPEpGjymbfcEDEd3i1jn3KNMgWWpryUgukUnGdVjBartWYnQWkQO0DFrmSFSSxRWuIJCVN8k+U6x8sAXLExbiKQ9JVwQ+mi707vHeWcmUPH5xDz9D62REd7yNwYop5PZx/G2KQ/Gv/UO2bWV857oQ57LuQCtJbzbCHbibsH8IxbzCXNJrfCv9uJF4xn7sLz7wEthU+hWrkJ8xSI4VgELIKhRG8yVlm+wRAZatwb/o7NjpAKJnucTdwiaks8KwBjxRNPAJpeTiSJblgxLaZbPNGKCJdIxnGICBGRzs6GJ/nwok/VesMY4ibgwqfJ4dP58lA4T6dN+NLIsUoOZZufeKQW+g/0l0M/m0rR1a/XVythoDajkcNRXBQu00ardlg7kkPq2BFchVzsOfnC2XS1HFTbqJVdtGmBZciHpbkUI2brxJboqkReDimc
*/