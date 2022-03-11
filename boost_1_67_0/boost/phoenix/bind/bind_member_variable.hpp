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