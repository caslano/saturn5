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
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
*/