/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// No include guard - this file is included multiple times intentionally.

#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_CLASS_TPL_NAME)
#   error "BOOST_FUSION_CLASS_TPL_NAME undefined"
#endif

#define BOOST_FUSION_FUNC_NAME BOOST_PP_CAT(make_,BOOST_FUSION_CLASS_TPL_NAME)

namespace boost { namespace fusion
{

    namespace result_of
    {
        template <typename F>
        struct BOOST_FUSION_FUNC_NAME
        {
            typedef fusion::BOOST_FUSION_CLASS_TPL_NAME< 
                typename fusion::detail::as_fusion_element<F>::type > type;
        };
    }

    template <typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FUNC_NAME<F>::type
    BOOST_FUSION_FUNC_NAME(F const & f)
    {
        return typename result_of::BOOST_FUSION_FUNC_NAME<F>::type(f);
    }

}}

#undef BOOST_FUSION_CLASS_TPL_NAME
#undef BOOST_FUSION_FUNC_NAME


/* gen_make_adapter.hpp
/tqIv6vEX3fxlyDeDYCrQTfgSnTTDBP0crKgG4QYBOpIsKjz8olhOtkkCLJxe/6Pt/eAj6ro+sd3N9kk1F2QldCDtGgUI6AkopJoghtJIJRgkBapAQGDJBqkCIRA4rIQFBRsoPhIUREsNBVCBymhSVUpKl4IYJAW6v7nnDMzdzbZjfd93vf392OY3Xvvfs/cmTNnZs6c0jkEmr5VoquO07Ut0f0urtGuH0mqV5jUZCNsS8MH45FGnGuP0/V8aKynWygGXm4vT6DtFp+Bl/Vw0hh17q1tgTLgMu/KnQ1wFEw6B8yYGQpp3e6Bf0Ig61slNrRpjIskbxgTF8OPCwNwp9vabnkwk0zm1oXO/NgQ9mdnf6Hsj93rGc5N+QKc+c+EuJ3h2hkYk/ns/xj2aIx98LaYULMZ7sO4hWDCOZsj+21CfRTQCQPLyRtaGCN/bZM5s9raKOTgIu3c1kATz5W1DWRZv0267HNbF3+FVXLmbAjXMg5d9DhdHck00JkzIMwk7P06hoprofo1u7hm16+F0Kl9zoAQOaGSvPUR6zZpbIWxSEeayooNp6uTnQ56eOafDqwBg4tZi9nkUI00GRmqX2+hNklTAtmifJMxwqGCX7xeRjif1FNmKvJti8eqpsyMxJSZsBu4auIu2ddMXB9ynS/aeZZZai4ZoXd0iNPNWtV1SOs74oKHfQ5NcB3UbrLPYoEUIrpHpqUdG5bo
*/