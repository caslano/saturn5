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
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
*/