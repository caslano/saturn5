/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <typename Function> class fused_procedure;

    //----- ---- --- -- - -  -   -

    template <typename Function>
    class fused_procedure
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_procedure(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) 
        {
            fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) 
        {
            return fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        typedef void result_type;
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_procedure.hpp
S1hF8zvUJB7uA7W/Z342SwVK+2skJ6kg1UOMCoNIyJcsFayFboWluEFiz4MkGFyA8guWrB9mkE76qq4Oy2rUSd8GOQXKKt9VhZRVlmim9wGyCr2EmoSLmoBEcAAq8wTKAudSCWzYrzIvdDFVJlBC6e9XmYV6ZWqQUJYoCcVUGSdW5oASTGRl0Na8cRdlaz4MqpvN4gloqxcURZvFk2wWTyiZEk+yWTwRj6V4Ep7c828QTc6haPIkuiKMa5cHQBktUlg+SVFQajPD0Pc9OM4aYIVU9wFRoEUgFNIQeNkGKXksW5JL0aZ0Fiu8ujGSSBz38mK58IoGiMaB2gWVcBQT9od50Qz689RIVuXiB7CMp3omtIsVsnVuU7dnFyV6ayQEWxSPq3PAsHeSWMx9rqNXoz8wFupzHRJ3oMLsW9IUD799nQyt0zLY39t8acBHhoFz2w6vIxxUTiI96ZsGltTvgEzLexQ2UmQnO6wTFDAdvPbGgYFNUjshW2ZFKjv46zsxc4tl5tYWyqS0hoDQkB/m/SPEPBjDaIVzYrb197lWdXQoRqDLKU6DpaiII9MDo8myhf4yljwuPFWD5DEwVXLVRPXr2lTiqx3gCWrXL00loWPrjXTdwNeVN7IQUsaseMlQZMXP02UBXebR5dEbcb+4T+wuKdfKgciwg/Prh1438WuIlooqbFLMCzI8g0hDyV184GxpcOy5HXSOXckc
*/