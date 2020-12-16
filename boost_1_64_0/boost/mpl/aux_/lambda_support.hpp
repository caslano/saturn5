
#ifndef BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) /**/
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i,name,params) /**/

#else

#   include <boost/mpl/int_fwd.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   include <boost/mpl/aux_/na_fwd.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/tuple/to_list.hpp>
#   include <boost/preprocessor/list/for_each_i.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC(R,typedef_,i,param) \
    typedef_ param BOOST_PP_CAT(arg,BOOST_PP_INC(i)); \
    /**/

// agurt, 07/mar/03: restore an old revision for the sake of SGI MIPSpro C++
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238) 

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind \
    { \
        template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
            : name< BOOST_MPL_PP_PARAMS(i,U) > \
        { \
        }; \
    }; \
    /**/

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    /**/

#elif BOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(BOOST_INTEL_CXX_VERSION)
// agurt, 18/jan/03: old EDG-based compilers actually enforce 11.4 para 9
// (in strict mode), so we have to provide an alternative to the 
// MSVC-optimized implementation

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind; \
/**/

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
struct name<BOOST_MPL_PP_PARAMS(i,T)>::rebind \
{ \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< BOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/

#else // __EDG_VERSION__

namespace boost { namespace mpl { namespace aux {
template< typename T > struct has_rebind_tag;
}}}

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    friend class BOOST_PP_CAT(name,_rebind); \
    typedef BOOST_PP_CAT(name,_rebind) rebind; \
/**/

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
::boost::mpl::aux::yes_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , name<BOOST_MPL_PP_PARAMS(i,T)>* \
    ); \
::boost::mpl::aux::no_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , name< BOOST_MPL_PP_ENUM(i,::boost::mpl::na) >* \
    ); \
/**/
#elif !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
::boost::mpl::aux::yes_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , ::boost::mpl::aux::has_rebind_tag< name<BOOST_MPL_PP_PARAMS(i,T)> >* \
    ); \
/**/
#else
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) /**/
#endif

#   if !defined(__BORLANDC__)
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class BOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< BOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/
#   else
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class BOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
    { \
        typedef typename name< BOOST_MPL_PP_PARAMS(i,U) >::type type; \
    }; \
/**/
#   endif // __BORLANDC__

#endif // __EDG_VERSION__

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

/* lambda_support.hpp
vJtf3Wzf7Df5EC3ePePMV6GzHz6aRndOX7Fr37Fdw2XSXdWbXbTDvN43+VsWE9LP5TGuULc+cx6n4le1LXLQhPyu4RUBi0NnDnu+5+hmleAvk+lLvS/mVOsIMzdvjg2XGOs+sWgr5RM7RuSOoka6UdYsR71x5eaNOSmjFaUyyNu1Fu9+L7x7beGNmW3xbt6lL0bd/b5p6mDF8Ztc0t9uinql8GCE4tYOKk0hcc30lYeu6x4dM1iS4jl7TL6fxuE6lQsh7zuXUqbWtIqtfJswZaaQxNyCLdJL9zc03Tr87VhmjeiYx2qZG+snagbtLG98MGLIg4/Rn/Q7hJ6uFAl5kkxiWd2OCvFWH6U4eA5d4mLD4Cmzg2bGpIguv3rhqeNLkZceuexXhw3tavx/1XfR1rguuk8/qCFCHJJoIXtgWfPj5QnbaJcu+I/ILtFSjPr60mLIxgjjMwrizzQXv7kz8qFbS83F4hrKizU/9db8kle/fGe/dvo0J/foqzOzT232yM0q2T3MPC/Dy//1B/UgHWb5y8fHzynXJmswnVUqhdZpVZ+YfnDD6bdbV6+tvZbRffZ51v6rayd9HVtqLGSY3Y2b/9f//2D9k5asH1fScfpBOnPEtYfPTwWOcHxRmqSWbHnB5FJ790ahozk+Uq9qTPVtDIjHTkT5fMjSemI4eIvWiYzpKxSfWdW8q9gu/8G+POZC+cOLyjXz5Z2ayzRdx9C9vEY9Pm4bf+4r0STzwZVpi+8Qb7quf99m9FbhfqIq+euix+Vx7N/fq2cx9R23SiwqzLc2zBJXyZn2unT+5VstX4YdnD1vXNnyy9KqDme7p06/4fpQ+NQoG99DZWtj511xbngiXzbrgfQCk/oDWxQ+ft7eqC2UV73q7I1nyd88D1muVL/S9k6p7OQeueoZzyaXvtf7vNnIdH7L4zgLSgTFam3YBOfAj7JXdP3F2exHzRt/qsWWWQ//f/v/f/v/n23/l2Wmsfesj5f9/arJNCX9zEGjuswnl69Xss4bXjC/bXRm9c4qAlv9wJWVv5w+aCZ/3xC9d3iY2WHGjulN3yKMh51mj/pUmjps7aC7jTtDdRu7zl3+tWTl06FD9Sh7yenCcu+m5A8Z1nbLmPUrJOatQbTr3dsZ+ouX1nbsdJ2/++qylrSIMeQP/rVmQqMsvhXsTt0fO1KufYJ9u26doVQ9+3DUOIctLdm5mjOvhXxRuSHiuFT152FnpZkf5uWdrKZdmvd6EqvjS3SJWsXuiLFZjl/fLdu13lrUbpWzSszj5dsIetUfTUeVKknu/0WKc9o0tclpcsqbQzkGni+TJ2+su60+uWXB+biEwNIFtVs/VNX9S/u/2Tj6vzT+vzW+NPss/Lem/4+Ob8NYWv/V+f9Hx+cjhyL+p8v/734+mT24w7m7+P/m/+Y/2Pzt934Gm/vCdE9NFRodXDrXWSGVAnAWgKOCS+XCeY5QoVmDa82N0xKA01bB7hPhwjG1+/IxdQTgRqrQ0HNauHA+wxxddt49GzLX/cJKrbr8hcsOKX5LsJuoV3RKvU7kwKTYA12ZzaFDZoyrM7nicOn0bcmA4155V8v8v3kM2dNh6hTyquNRt3sia5vGjjXOW5mXrmfNrb175Mri7Q8tZmwZPkxG6OCx0+/lrno366m1mm5VtNydlPGSFRhk/sD7zs6obTf3CHUW7Sr1fu8789isF+tfqNYvyN28Vvzkq1MFQ9/FzVo6fGT6z/JJa5feXlWpOG1niu6e46w19/cGP1q5+0wkUeyKqo+66GwRt937k8XaGUMld2Y16B08X/W48/FXF62c+b7rZkUtVz5xejBpkNxnip905LwU18k2M9Texo8wjB0=
*/