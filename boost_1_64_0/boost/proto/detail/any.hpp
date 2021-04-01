///////////////////////////////////////////////////////////////////////////////
/// \file any.hpp
/// Contains definition the detail::any type
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_ANY_HPP_EAN_18_07_2012
#define BOOST_PROTO_DETAIL_ANY_HPP_EAN_18_07_2012

#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        namespace anyns
        {
            ////////////////////////////////////////////////////////////////////////////////////////////
            struct any
            {
                template<typename T> any(T const &) {}
                any operator=(any);
                any operator[](any);
                #define M0(Z, N, DATA) any operator()(BOOST_PP_ENUM_PARAMS_Z(Z, N, any BOOST_PP_INTERCEPT));
                BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, M0, ~)
                #undef M0

                template<typename T>
                operator T &() const volatile;

                any operator+();
                any operator-();
                any operator*();
                any operator&();
                any operator~();
                any operator!();
                any operator++();
                any operator--();
                any operator++(int);
                any operator--(int);

                friend any operator<<(any, any);
                friend any operator>>(any, any);
                friend any operator*(any, any);
                friend any operator/(any, any);
                friend any operator%(any, any);
                friend any operator+(any, any);
                friend any operator-(any, any);
                friend any operator<(any, any);
                friend any operator>(any, any);
                friend any operator<=(any, any);
                friend any operator>=(any, any);
                friend any operator==(any, any);
                friend any operator!=(any, any);
                friend any operator||(any, any);
                friend any operator&&(any, any);
                friend any operator&(any, any);
                friend any operator|(any, any);
                friend any operator^(any, any);
                friend any operator,(any, any);
                friend any operator->*(any, any);

                friend any operator<<=(any, any);
                friend any operator>>=(any, any);
                friend any operator*=(any, any);
                friend any operator/=(any, any);
                friend any operator%=(any, any);
                friend any operator+=(any, any);
                friend any operator-=(any, any);
                friend any operator&=(any, any);
                friend any operator|=(any, any);
                friend any operator^=(any, any);
            };
        }

        using anyns::any;
    }
}}

#endif

/* any.hpp
kr+nh/wHGt8WLqU66rY3/sMPp1IV09AWc/ceshW+Fen8XCL7Ig3w0nSH16audJ1AccMruGrGU3qaKUvrmbyQJ7+ppIyKrQCB2r7kTinm8UXQ94OgawtYrxKEx47nd0VMdkl0XG2uRtmkoOgNjPMOBhDq1RIPtv+Qz1LDd+5aB0y9xu6nt+KWT1w3BuwFWNybSq/qcZ8CTjq9wzv9zAQ35l7tsX9NmV1zXlNlPYFMEuG3WPziG73YngZDAogsZt/VO5nUDZ6C6AuZj+3b1YgYuvQuKhF5pfNswjv0Y+AE+4uZ7S5TA7isfCNYEK41X95uT7iADtDWXFYIQsDkVcxYqaDnNcDkeIEa3uBuQRGd0YuR/FTotsit7rvvfjHJ44VlNP+ssdsn5sZBd/fRQtpZ6VkH6BHu4Fqzq3AIeurKSAe4XKz3nx46Op1wFvn/AegP2skReizx5sfTHIKMyN/Id4diZbWKtoaqbqpR68ESphQGEl/TRfH6mnYjJdT48PJD961Wa7UKIZKbx07v279mMxE8+LsjPFinFz1AWPqsjHnsA3PImi6YJtlm7Q==
*/