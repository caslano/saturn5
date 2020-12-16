//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_HPP
#define BOOST_BEAST_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string_type.hpp>

namespace boost {
namespace beast {

/** Returns `true` if two strings are equal, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.

    @param lhs The string on the left side of the equality

    @param rhs The string on the right side of the equality
*/
BOOST_BEAST_DECL
bool
iequals(
    beast::string_view lhs,
    beast::string_view rhs);

/** A case-insensitive less predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iless
{
    BOOST_BEAST_DECL
    bool
    operator()(
        string_view lhs,
        string_view rhs) const;
};

/** A case-insensitive equality predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iequal
{
    bool
    operator()(
        string_view lhs,
        string_view rhs) const
    {
        return iequals(lhs, rhs);
    }
};

} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/string.ipp>
#endif

#endif

/* string.hpp
QWe8v9T7DjGfr/M5b0F4nh92YRd2YRd2YRd2Yfezuh/7+/95vUwyV/8nfw+Aufavsqz9XVz7X8+17yyu/dP8a/9eKtTan+Fpeu2fLf7sUGt/8vbQa/9c8V9mt/Yn/yBJK8Jm7b+1jc8W416Qf+1fdYK1f6Vl7b8laO2/LWjtv8Nm7R8RtPY/+rqs/Wt1Rnaq1uZ1XSO/K2vkcYe+OuvAqPvv+8vi+NdOizntWru1ed3PzmzWwlzDsj0pY1VBevONqa+eABzGtek5wFbACTx7mkR96Qp+83cWz6IKfuA3eOfme094zmJdk60Ir7fCLuzCLuzCLuzCLuzCLuzC7qdd//vV/096/b/Covvfiev/PANraOA+UAOsOzNu8a//qfpvr/tP3o56fT9H/N0Nc/0eZdE/HqV5U7T+7Szxn2Vo/W7ZN+C9ahK2I1Bvl+9se6sZ5tbpviK8A/V+RIX4J0qe20q6hVKGeN5rkirxL4SupBc2vzFav3eV+RxccdhncMJ/XTsh7DGcWL/7eLYDURa9/S7+b5s7uEEBagDqD2oIvtjbdN2L6UBAPbJuUoQnlfXhj9PshHmkbq/OT8B9R7yDMYH3HZkPD5q65dX5GVuKzz1MKi6dhqCAfDEf5E2w2A7A7iBHsZ10OG0ypG5PeBePznNIvXlJP/CONH4zvgPvB4wDxiBulS4HzSFCl4F8bbQ8b4UfIDrhHl2mLN674udfCT3fCH1f5MT1Pl2YOPzXW7lr6sZTTu+SuFEG976YVotq+wRLf8iWNPuoOObzL8I7DHsjMdpeYa3wuFkWfz6cYr/QmJUay2fV9jaF+r6fJyXNWN1+iu3nt/XYLOFfh+yT10i69XXf/lh4S1Wc+CUvzG992k6wf9XBdiJYBjxaBrJsbSf0vZG8F2lZPewvEd/phD82iFyYY+zluHpmapYkV1yal18aKB+0O2n8B5N/MMvtj5/NdsFf4k+p51FtQENl3zFIdtgfrHHht8TNde70BN0NpO1e2glPXr1R6lAk5QbpBN4xuvQPtMlA9WHPTacrbc5Rpy3tpkbeboatj/CqXzk3OPONCHeRmuU+z3jO84qRSLn46jdyp6pnBmRtuhGpthgtXB6P08yTyNUzv/PVSRLqO5E2HJdLnL3eenh2A+K28UaqhV6vvmvsAnlvibeh8Y67H8IS8PwKc2yXtNo4z8HYvFF1dHzqcKouCJuKsA6++qrXzsh07nA51b9d76sU5GOdx60ivC5VAXreO8JRX/gt9aDLPX485EjqZZmlXqzhPRkeHbLeBqlE1ttRKd9FePu3ymlsMu5xnOZ8zX2Vass6+7PE7Y+SeVQTY75zDzbbDfcq43rPVfqu187CM6Heb9SYyATW24GN5rPbneci3gJ1p2O6M1Klss4e/a3Ujas/+u+7Kgpj3Kcqx+FRrztcaqDTpTY6Uf+sx9skfwu8l4C3lTHefTdymuiNUAmsy3el/rt6nZg/PKLec7/vsY4JQ9FOlA9pjw5Op3rM2GnkGP7f0HhJ/xrPb1WJe4IH9zIx/zGSboMI8wbcSKPQudnlUntcTzjeQE20ZTkMSfNc9znKiTJe4vjQEadSnL83XgFvd+a/o9RNZr0DKtHpdsWoDQjb69qvoj0udRXobY9XXYj23uotdfjL9LDkqal3LuS01PjctdUTKX3iCossWMc9f1kmbfDfaRmpkkEJlOu7pSzPGyNx297HsHiYYHSWtotH2B+kLV73tMX+fxxtfTaaz8DrMW9yZRtfLWlEGm5YhGxWffVdXHPlnVl4WzMVx3q5Rp4tw7N05hv9XuIPhd9XxovF30niFMJ/k5T5ZtjKXS7PpuHZUuE5AJuPRfKsCM8=
*/