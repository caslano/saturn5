/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_OPERATOR_MEMBER_HPP
#define BOOST_PHOENIX_OPERATOR_MEMBER_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/get_pointer.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/proto/operators.hpp>
#include <boost/phoenix/support/iterate.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(mem_fun_ptr)
  , (meta_grammar)(meta_grammar)
  , _
)
#endif

#include <boost/phoenix/operator/detail/define_operator.hpp>

namespace boost { namespace phoenix
{
#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
    #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_gen.hpp>
#else
    // TODO
#endif

    BOOST_PHOENIX_BINARY_OPERATORS((mem_ptr))

    template<>
    struct phoenix_generator::case_<proto::tag::mem_ptr>
      : proto::or_<
            proto::when<
                proto::and_<
                    proto::mem_ptr<meta_grammar, proto::terminal<proto::_> >
                  , proto::if_<is_member_function_pointer<boost::remove_reference<proto::call<proto::_value(proto::_right)> > >()>
                >
              , proto::call<detail::make_mem_fun_ptr_gen(proto::_left, proto::call<proto::_value(proto::_right)>)>
            >
          , proto::otherwise<
                proto::call<proto::pod_generator<actor>(proto::_)>
            >
        >
    {};

    namespace result_of
    {
        template <
            typename Context
          , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_LIMIT)
          , typename Dummy = void
        >
        struct mem_fun_ptr_eval;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
        #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>
#else
    // TODO
#endif
    }

    struct mem_fun_ptr_eval
    {
        template<typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
        #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval.hpp>
#else
    // TODO
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::mem_fun_ptr, Dummy>
        : call<mem_fun_ptr_eval>
    {};
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* member.hpp
1yvqO2Rh/5btGJhMMCEBagPsIacokWp0QsMKk14pkA2aoJe4i0uBuNi7TrqzMwOq45zhqwph261zULcITeyy0cTNFk1c0UV0DFMCEsCnsbEbVzORjmqPDlZYRHaxmiopErEMRS00SAX0hpd7tI4H4laOYsTkQVqMNMxV4q3YVQUN9LeYgAUzZYbYKx4CoIlt8bqgETR3Ciq84R2e+SFOjhCFBxEZ7QHoBYwe7GUmUJaaEzkLegnnrgb+rZEKbct4BifIy+8Ax29kPc+pzZ+4VFOqCkHcEL2j86+y+Xqtd6WFOGJVXnBAnr3mhgdhBQAMT9Z6rr95h9R1CsDI4ckOCBCabYx3I/6PByd64CzclSDO6wUIEyjKTc3gBp4mUwsbKOF5d05vtJnx4QFunJyT0DrE4RSvC2BhGwG/yGrCL9eA0xaXq6Ny053UWoY/qZBc/3rDV7kd82AabbII+RRNyOuRkJfeThOdszhpnm5VT9QMd9h02vHB3qV+cVNvLUFsipth3KmYg2YyPQVn2MvDXwwMxZ2F/4c7obNskaKuGaMHgzNAEz21OxBi0CvAyef1s1LBGP8p0hbdrZVm6DZqEENrKS3EUkwJYKXhTTHOy2qEjytS0AuvNYejZ/MCTyIzU6f0KUZYbrS6+czE/fJ1woqz2PdLqTNbCM/qk4l4k4oaQfHq+j5vmDdW/C9smF+zj77PHQJWRuZBLkuz9W2GGJwted+GIxqp91eXSUTBaDZZEdzNCWJgczweBaeCN33YxrqqSFqZW6kkpRXmiafTDGOm9M1SJVucnwayxWhG9Nf/jiJX649Wldv3e62z+yOZpsAOXO7dyQ68pMyLyjhcQcJH5hIf+cjkBK1cgX+82+J4rlX+f24mjodMHrDvMIAevCEGkXVzZkOlB/oWOpWEH6iHdYoe1su24kB+XNRrsYapY20qXTOLkSdVottV1sUyUPrpg11MdItYkDXAcC7hTq4DVGFP05qiSNkm0luQErR6s6UBLd/K1hyUp5XyoPoTjqvG+eKC5qKWhSjDV5o5QnhoZNk628+8yLLnbD/zI8uabD9HRJYhfFaYjsYG1q4vpHgZd0ylLrZ1Tkeu6pyOfahzOli0e+7J9qsv5ZsipCQjxczmyMLnRD69NbJcV9waIaVu9uMQ3w4S0rDGCnMs12hrF30SdU3fWsH6K6iNKFXnqd8YSmX5/55G8hY+p4ge1EfK4w9h6eurVizXqnJiph6Yq6wtQI5VDr/L6MT8Qk1x4raxAnpSrsBuKuFnJBX787M9SJHcOgrBLoGah6sLHUGstU2cIEEty7EWVXPxluy6Z9jgFWY6CPkT8d+fa4ax4clxy3u9dlPFw7WWiVQcMSJNvkoCNhbtjGGhuCq9Vcr60UstyLS14LuT6JmADYB9v8Xgqd8VHQeUTVwQ7H8K0THSQ5ICQ/c2kjX3VySvSXk+y3WEirhfeQzPb4hkkklFvQf+k7R6SgM+TyVEIAFnwdBKsuSRccEi8MtXkb1GVJKjHERd9qRxWp6YNjWVfB+JryHifZxL54PF0PkRmHw4DYeK7D8PZP971plW/JeTU9SHY73EU58JTxhwgX6nVrp5SekWT61087KysK/SzQtbB8F2MWx18NsJcHi7E9BeCmfhpSnr7avh9ALnLu+SFZHwLpMQ9yZpODVkl0D27QKybxeQfbuCDD/3bKT2zkeP9ypgSPTCZyL2vMOZFNWE6AhM/QW8HBZ6nKKBdErkLLKW+jFBgozLKSPMFZUQoQShjLScZHyTNbb29SPTRNRFWjlrSDSXWRTmyROZNot1o7IpiXiSUMWTq5OIzyoS5A1V0pOXThKDu2H+BTaxzBXK/9M=
*/