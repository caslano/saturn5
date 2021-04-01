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
UFWrDA733Kml4piqMVjI8WfKqYVVAB1eLFDAPW9TJBgwFs5hU3Whzt5iWyr3BBhuYDGOcCLasNmBNPyoXfI3eXrwDr6CWFqkPCyGx5Lzbae1NL7mgYnbZVbpAMUisHAT3CqDz2UPF/J3Q3k2n2BE0bbWlP20aBR16OHb059ZDwUSsW37IMaVBKbn+RynG4LmzGy0zGLPxXuoQTeZuYrPntH7+vn5AvEXM92hHZKqFcHu7tCW91I2bVwA0CHKPqTV64TcPo3np52oSY0yS2xTsT6ymOyqjRXX5FRbnoVqX1tNs+7O6HNJDRqnvmTEYEOiX1c/Sy3r784BbacdQlQG/lpM5D1G6mTJjSvqPoCN34Jw5r4/p2LhyyrGweiIrOdd8kkMbMicc4nSNPB57wInp1npT7P006unDkaHp7DOkxCP9n2D+UNdI4ZOZAnOFfZB6yD5BKV4vurJqVmd4plC1j2TDKyUHEPpezViQ4d192guxqDKpdVQM3EUAK57VUa+K0rwEVVJxmQGY6VRZut+cirGtsx300wskzFyT2kyR5wKhqa3v8e7KwGWWw==
*/