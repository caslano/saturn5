/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2014      John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_MEMBER_VARIABLE_HPP
#define PHOENIX_BIND_BIND_MEMBER_VARIABLE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/member_variable.hpp>

namespace boost { namespace phoenix
{
    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_disable_if<
      boost::is_member_function_pointer<RT (ClassT::*)>,
        typename detail::expression::function_eval<
            detail::member_variable<RT, RT ClassT::*>
          , ClassA >//::type
      >::type const
    bind(RT ClassT::*mp, ClassA const& obj)
    {
        typedef detail::member_variable<RT, RT ClassT::*> mp_type;
        return
            detail::expression::function_eval<mp_type, ClassA>
                ::make(mp_type(mp), obj);
    }

    template <typename RT, typename ClassT>
    inline
    typename boost::lazy_disable_if<
      boost::is_member_function_pointer<RT (ClassT::*)>,
        typename detail::expression::function_eval<
            detail::member_variable<RT, RT ClassT::*>
          , ClassT >//::type
        >::type const
    bind(RT ClassT::*mp, ClassT& obj)
    {
        typedef detail::member_variable<RT, RT ClassT::*> mp_type;
        return
            detail::expression::function_eval<
                mp_type
              , ClassT
            >::make(mp_type(mp), obj);
    }

}}

#endif

/* bind_member_variable.hpp
6B182l6ECv5kP2Q+jWgS0PIo8liRRfic3KmZ/hsn40+FeB353xL74GJt5LOpuqHduNJZ8ROnWKCXU/mCYNh9ABfSnZHGfa34q18YyYBDJ6BuL2wNqgXnlOyO9EocGbyYZUzW8murfMTZwjxAa2+TYQwkSlK37/HQUSCbvqhKFuydt5z9xadmYQ80/6ppar9VlhqOR9QR/Ye2NEiC6OPn/ln2RJiNuh0wNstsnexzG9y7Eoq/VogzetlvFa0EtZPJzkrDA3UBrml/q+Cm+plAZl3HzixN3hJ9+Te84xO00eCOxOyN8DdV1PlsY2TMw2OafVniWUtKEX5R5NlAAaYO9a3t2A1LeteSInfkzYqTLXkRuZFjh+Yw3dmykPfjZSnyn1iT2EZX4f/A1QDLnEwMe5DJ6tTIwD1B7RzHXJN5+b9xdlz29L0L2YinCY5uV525BXeyy2UMgo+6WBX4jJYy9jy3JQN/dx/ls7GE0tKc5OSwwndUo6A2GzmCmo/UFQ2mvnn/nvxLyenn4V+pdzmYe0R5FDPKjkmPtAfEHoWAavzsn4uWHQAmHJ5IXdke0TfnuNKaxSeii+VF6wq8B9O0cucPmiMMeIrNH+K7VZkGPRA7fw1ERjeJMmEtx7yYNmiz0CwDY6zxOmG4rlEyskZ0EbOZ4WsRapG4YVvh/Zvh65tg0nZt/yIZVh78zW6If5aCOzIbZtG0ewU9s1Jl
*/