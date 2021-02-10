/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_function_object.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <class Function> class fused_function_object;

    //----- ---- --- -- - -  -   -

    template <class Function>
    class fused_function_object
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_function_object(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq const>::type operator()(Seq const & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,
            Seq const>::type 
        operator()(Seq const & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq>::type
        operator()(Seq & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,Seq>::type
        operator()(Seq & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <typename Sig>
        struct result;

        template <class Self, class Seq>
        struct result< Self const (Seq) >
            : result_of::invoke_function_object<func_const_fwd_t, 
                typename boost::remove_reference<Seq>::type >
        { };

        template <class Self, class Seq>
        struct result< Self(Seq) >
            : result_of::invoke_function_object<func_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };
    };

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_function_object.hpp
/jKge+y3P3n+/Hz4/OXJz8GKoF9lMsXVpWgL6FsYaeB0c4F9rrHh+fDV/j/9aFxafuwzDvzzwQt3NiUSDcJsKJWu321HENpZCIoZUMDEY7O8u2ti+zrm23prH2UUdRxWur+H/YdxgfyvwruEmZIOWaehYAobEbQO4CKjQ3mR05+Q0RoZVYqBKDB5VeGrkZ7JSmN4NcSMbCMSHq5l7AREg5esLQjEcJSggNfISuJgPwvarNjer42hCAvC6RZaZNi1gGOhkV4ko3cOcusBoZHTYEszTWvkBRwqyHsBNEaKNgaQuNooeywbWxSpCvSw1VuC29sxOocxrUvrbQUhEIjybmtE7axNHWocdJTpzAsV6tGcxZqG2A4k5ATDG/o8s+4ETEywVhUVw3RwOFGh9ODyTR1LtvWPnx4kmYDgR2jQIQTn0K07jclTxh2BkPcoqYAWBtAENVpLPL3Ntvdq/1/qwlp7uhZ6kyYFWospOgFdR9Tmq5/Ozo1aVDicPcgQyufQPD2JHf7/s0jLm7m313iJA9zQpVTm3EwsECMlWTC8bsjNjF4rYme+V+1awun5pIVsxuQdjgDDFqYUuuXWmsFw66xlGHwf/s219kMWXg09O2tr9E1Xxjngxff3Ia3oY7oEV2BZjq+wpQb2tJqE
*/