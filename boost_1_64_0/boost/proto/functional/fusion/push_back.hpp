///////////////////////////////////////////////////////////////////////////////
/// \file push_back.hpp
/// Proto callables Fusion push_back
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    struct push_back
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
          : fusion::result_of::push_back<
                typename boost::add_const<typename boost::remove_reference<Seq>::type>::type
              , typename boost::remove_const<typename boost::remove_reference<T>::type>::type
            >
        {};

        template<typename Seq, typename T>
        typename fusion::result_of::push_back<Seq const, T>::type
        operator ()(Seq const &seq, T const &t) const
        {
            return fusion::push_back(seq, t);
        }
    };
}}}

#endif

/* push_back.hpp
54rU2do6eXwulZd2KC1n5BmBa5IXbMDG/Z50+BjgtBdgeA2sIHHBMMSZ3X2VCCv7u08Zom68bENezt8uXCup+gHQIC/hri6WixV76PlssEM+c2QtQ/xKvke//pjtIvul3T9t1zR0GLobo1u+eImut2nI7Q94IvDUDi/LLH5thMFheypY041NzcESnZi0Zg8ocL+8iRfb0ZxirvRI4m1hZBX336Os5B/aFV4rMcJ/kelsyx7MeI8IRXTHoLsZUMTTQlQKvYXESwBfraGm6TDo5SaFqdMlUOAPlx3r0AbMGD+kK4qvBBX8yypWAETNO3gQnRpjXR2HRTjqbsbV3Emn/BpH8DQcsr+Tgx639XZYZHIWL9lESxsC00i+Ljwak/hwLFggo3yYH/h+nFDe8XZl7JjWjKt2VyzoIPx4Gy2eXk3suwK9lGTiNGZ85ya94Wx6Nf+mVn3Drk9L58pgJCvLqNgrgZUYfBAB0xMhWAvenVGyfXzCC7D0x6bvMwZyrXksiK3HJzukIzALbzc8IQiZzDFfu5emdlHB8qV3R3dohEG29SVL5d8Fb4TIwg==
*/