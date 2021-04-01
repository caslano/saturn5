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
ZEo6So9FUj7UpMY+Oo6np8kWQGnADr1hZFkyI5+KvLgMwS3wCf7dn/AGrNEJR9YvN+UNl9jtZHVUUnRe79ubQvxCoPMse1K8FHPJRTxrl66Zl7UKmFsK3tNnwPFm2DzQmSUWoIOfPSfpL3OkA//1hCBBq2St5UrGFsJbdV8lco6Fsimup7zRYC5lM7oDlFgnRahQLFE+gvP2E6ayx4Lx8a7M6JVLbWyTaDINmbef/7bvOWRVqTVpOtUUOOHAeH1MBblqd4YIkKCV5V5E5jnrrtIl8UFD8H/Ra/Rf/HBd5DsLM3GK6a4ogN/5N/7NF2az/biS81HJMGxh91Hmm2Q9O7Lyc2e6utwwWem6bc4NtOWLbp/wCMG1oiTpiYDTCF8kTlazhlW9coZZ9vHlOcgx5myQZb9dPwRonjCMiZSrxbDpfcU9tz3Y/RdYDwO9yZfrHa7T0cfUuas2Q7hMzRXPlzSJj7Y5h0fmrWFG7ynlioDGD4M24ZfVx8Ike6RF7cR13HYms71l0mumFRexWEj3RAMm2g3knCjAU8NBfjQgpHjLOZg06dOlIoFN5w==
*/