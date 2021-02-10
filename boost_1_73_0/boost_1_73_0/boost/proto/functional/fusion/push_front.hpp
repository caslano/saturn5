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
ZGF0YS90ZXN0NjQ1VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsELooQ1AwAAOAkAAB4ACQAAAAAAAQAAAAAAwfI9AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJMk8pT8gIAAIMHAAAeAAkAAAAAAAEAAAAAADv2PQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NDdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSW66MclYDAABEBwAAHgAJAAAAAAABAAAAAABy+T0AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjQ4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUi3vUMmGAgAAiwUAAB4ACQAAAAAAAQAAAAAADf09AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLIRkaLmgIAAOAGAAAdAAkAAAAAAAEAAAAAANj/PQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKu+ZuRewMAAIQKAAAeAAkAAAAAAAEAAAAAALYCPgBj
*/