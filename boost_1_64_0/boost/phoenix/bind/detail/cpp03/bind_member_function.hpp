/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2014      John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/cpp03/member_function_ptr.hpp>

namespace boost { namespace phoenix
{

    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_enable_if<
      boost::is_member_function_pointer<RT (ClassT::*)()>,
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , ClassA >
    >::type const
    bind(RT(ClassT::*f)(), ClassA const& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return
            detail::expression::function_eval<fp_type, ClassA>::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_enable_if<
      boost::is_member_function_pointer<RT (ClassT::*)()>,
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , ClassA >
    >::type const
    bind(RT(ClassT::*f)() const, ClassA const& obj)
    {
        typedef
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
            fp_type;
        return
            detail::expression::function_eval<fp_type, ClassA>::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT>
    inline
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , ClassT
    >::type const
    bind(RT(ClassT::*f)(), ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
            >::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT>
    inline
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , ClassT
    >::type const
    bind(RT(ClassT::*f)() const, ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)() const> fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
            >::make(
                fp_type(f)
              , obj
            );
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_member_function.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_member_function_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_member_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , typename ClassA
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , ClassA
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , ClassA const & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , typename ClassA
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
        >
      , ClassA
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
      , ClassA const & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , ClassT
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , ClassT & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

#endif


/* bind_member_function.hpp
5LVm6mZlv8JcdknDPtex+LCf4updCnv5ZY3mfeBpsXga0Xns955B2MglBMtw7JmEm3eJx3xP7CF85HKU+a4YIty8y2Lmu/rZLl5WAfO9a5Jw8y6fGX+oTfh5l2osx5mDhI9cRjNu1/OjcdTKRsd6XxzChXw6Vx4KY6inmLHh4mtCmFh/zfWvD2FJqznu3cPpbZpUPasczEz8/ykZs98/8dzSi89XXUd0/Ifp/a1OFW8I5ZTLSLLX7Lv+3fbFQwPxOfLcO4xPWvC4EG2wyxjfR8L+c/RWqLgDH/0OxjTu7u+f7Iz6rWryDPMbnSBHF83vfBgDyxW4qPvUEXk7WN7fisZKO4xUi8vWHZZlcGrKX3nwm5JGbj4zpmM2/5haxn5OlC3M5BRBjK/hn81eploZST84c7bcsfYEyslqPVXOpAv/99nyKuJ3m3/214SDCcYNlEetM7tX6Du3+WrjKYjxh7XiQC5raIuYxndkibaYaX0IfVFAOKDUQC5BaZEX08mfjWlLmaYurlq0uxkaLV1Jng2+rIoVFp7IqVnEP3N9hrZI0tKN7FOVfhNtsaQhgseA9rmj9fYV91e8EbmDILqwDyLaIqaF7lxmVvDdXSDoFm4/StWoEwY8IIPkjzGgiIGgv5iq5Cgf8EE+kg+iLTbVXWHISPTFFr0fbDjtEqJxIYPE6lz3btAA9Yw0bBBeI+F3ZXiNjrxo/bEIdI6ToBTK0A4v1jR0wb0tWMJM613CNOJpbKMzTGv7tAhfqqmlCuMfLaDr7YWtzbQVd/NpeH4sSA2xjV3TfXdFw2ey+pXEvpfhyCjNI2Q7axxZ+g7QyDpyhcJFuR2z7bF8GWFihw0+jz1NWGeI5fzuQXTXhVnmd0/CxA+Z7LdG2PAQzJjsvQgTfgLJzOfnfczlh1Mt47HlIbwjI8/ps1dGY0lvDM/d9yZc7NTDc/HyqxQ2UgVYx65RGIts+kXifoY2zk4K3C/OEl08R5O4GmnJRxI0NdazPGvur75FqpqZv5/1R/YBRJcYawm7oY/9A9W8Pqa/r/yL+T41I85xr+XvwzOwGbD8hHWZuErn1SXSTeMkfJ+I4Z3gM0TxqBRpBKQHfn9C3in4i57HAit3aHIMKyID7Oi57OxbHH+cYjHlpfLlhc1l4N450EmCzxbid0nyw3Y5Dr3TWCknMbJsv74/ME3hNbNFx9LNU7plb5V+RrlkupzJ5cvVXHL75uC/HpVC/Ztcl/Jtw2esTHy6LD7FZB7xhQv1St3wCV6gpf9nOHVvGdulmXU0r20Orwwm+myjdllevYKXLt8up3ylVLmRyZQK0bzCJXyStkktPulkPlX08o1c1vDRdXx9KauYUP20H0XpXybT95bz+Uq1UM4nfbl7dgVoLfNhK69CslAs5FPVPNBbonK7fqhzQGSZMDKfsPhkkg2vlEYE6ZzgUwueIb2+0jrILNKU/rRTd7VsplBKN8oivddfgfeZ6k7wnhBCJHW5by3LcjeK5VIxlS8m6xgftbyexp6T+fVk4TVYKtVRw6o9COzpOvqZJVsZdVTMZ0tojzjZNo+gZ4fLeJdTxkY9UynmPVnVfd72zbAPp1WsGVnPa7W+rjwmeGTzyTS6Xq1azQgmOHyAxxo12uZgiQjXwtF9LTU0Ct0fOCblqSRLpVqh7JXrl+PFXZt1v2PxyicROzztpatFwSvD1wq06g9rPsk+4nPEkanYqCB8XTlzOT7qT4laL1O2dfyUI1u+UMohImJDVrxaSaC4qCDNc0wLl9mpx1GLTzVZK1VypZJXk/UVuNTS/9WcSDx4/rBwMDcfTnwvSr4bc7laOZUvVZJUyzx+zh1z9DDjNRDXkcdP/8VPqN8=
*/