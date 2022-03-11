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
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
*/