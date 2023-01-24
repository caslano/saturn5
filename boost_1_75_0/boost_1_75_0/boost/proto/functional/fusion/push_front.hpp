///////////////////////////////////////////////////////////////////////////////
/// \file push_front.hpp
/// Proto callables Fusion push_front
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_FRONT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_FRONT_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/push_front.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_front() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_front() algorithm on its argument.
    struct push_front
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
          : fusion::result_of::push_front<
                typename boost::add_const<typename boost::remove_reference<Seq>::type>::type
              , typename boost::remove_const<typename boost::remove_reference<T>::type>::type
            >
        {};

        template<typename Seq, typename T>
        typename fusion::result_of::push_front<Seq const, T>::type
        operator ()(Seq const &seq, T const &t) const
        {
            return fusion::push_front(seq, t);
        }
    };
}}}

#endif

/* push_front.hpp
arGLtPOPw1zqqBsQEyfR3YOV110SFGedOmsVPU9G37owwf0yC59Guha6djNcQsDLRkTLUiTLnCYNkm71OVYlcFYyO1oWBylVQ8tabcraVJrsq1kD2lUgH+9QvAn3CB9VaOY8BOCOUp309oEP3Mx2r13r+VOiC+MF8cPvR6471Y+U1DaVNEIXwrPy7yP7n2Kxyq97jYWSY2f9er8GUL2WGXfCf01BHUOmIRN/Y2m/4RYjum79hSbtkStEvrt996+mCwsC8TGpSdnyUmb1xExAuV4mney//BdIKikvr8CFtDPqJ+zycjVQ7PhTqb3xB//fwk9kQBmjP7he10aC3EqMtuI50lk3Zv54Dz/qjWXN/EiJhS3pORyJgNcV29D3ZDn5YYaL1XjzCox4yyLdEv3pV271GakRaJhiIIjc0kpPpde3TelrZYRF0eLTn+Va5A5MpThRdI4xQn/tqnp6sKL5w3uUQ3RJURXyLmbLxNYQb4bfCLGiGRpOpZ3EIe2Mez7LkHyqBf1VwhPG+QH5gb70QrGyP11Q1EKL1NaN4G80g6LliBQ63J8WHbV7s+biMdGaLh82v3tzdOPp9PB1g3OtyN0bgvKhJcp5pLLTvpENknP+w9t/xxVnMezs+eg8lHL9LN6tBvJE/pij9koOz+qN1xnpdeqhVqa4hFqKwulh0ucKiWgW3JNfo9Yxa0ONqtM4R28f1OlReNmgk1rD
*/