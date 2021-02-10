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
SCRgUEsBAgAACgAAAAgALWdKUo1YDAY5AQAAEQIAAB4ACQAAAAAAAQAAAAAAduU9AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0MFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL3A5QYOAEAAA0CAAAeAAkAAAAAAAEAAAAAAPTmPQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NDFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSc0eMvjgBAAAkAgAAHgAJAAAAAAABAAAAAABx6D0AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjQyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjDJm7HsAgAAuQoAAB4ACQAAAAAAAQAAAAAA7uk9AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0M1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJSHezR8QEAANMDAAAeAAkAAAAAAAEAAAAAAB/tPQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NDRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSzwI3PicDAACZCwAAHgAJAAAAAAABAAAAAABV7z0AY3VybC1tYXN0ZXIvdGVzdHMv
*/