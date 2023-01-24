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
KL35Tf30UaW3vKqfPpOr36v66UeUfnilfvoxpa8vmeP5U/rKPXP0zwNS//wcerPSlz6qX36x0qce1U9vU/qr987xfCn9gyv19S1KX/ayfvlhpR9+WT/9XqW3vqKfvlvpk6/op08q/YG5+kfp17+ln/9orn3fmmN8zc//8/M/zc//8/P//Pz/hzj/W9T8eOK0fnqr0kez+unLlL7uV/rp7Uq/8tdzPB9Kf2YOvZab39+X+tx3vpjj/T7nuk7yRVrnowSK5vJTESz8QRy+r7iraFp5ufyJJt1mdfVnSWc8W7pZ9XtV9f+rv5vfd1e7mg8URhVmFI4oHFU4rjDbnltHJJo69MvL5V//yuR3aKZd42o81b+kxvUMfTanH9HX29vPXs//aX3uMrVNj7fqzvLaBqfLIX5aLAuGXGVlc8ab/GX3K+KJ/PjbcA6fu8Mhvw2XS6IXn39a5V9s/QGV6Rz5Tv42PRVt/vr/cpmIViAsfMzA31rk7ywKzviB4qeAt1ws+W3AxxRnX/quS6Q/NuOWxUQnvyd9nH+KcAZ8BDi2WMZnXLNEykuBDyOYuCyg62tYM8EZ77oU8zt4JfAhBA28C+i6DOsfxwF+eJkslw+mbjVjPWY3ZOATZhk/AvzWUqyT4Dbgfgv2fuCHgOdeQdT6uIEWARuvlGW5gBddRXQIchfwB1cTvQLeDVx7DeoFvh7oWoG9L8dRZ324LEY+
*/