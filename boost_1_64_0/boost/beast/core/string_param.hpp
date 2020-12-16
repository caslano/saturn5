//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_PARAM_HPP
#define BOOST_BEAST_STRING_PARAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/detail/static_ostream.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {

/** A function parameter which efficiently converts to string.

    This is used as a function parameter type to allow callers
    notational convenience: objects other than strings may be
    passed in contexts where a string is expected. The conversion
    to string is made using `operator<<` to a non-dynamically
    allocated static buffer if possible, else to a `std::string`
    on overflow.

    To use it, modify your function signature to accept
    `string_param` and then extract the string inside the
    function:
    @code
    void print(string_param s)
    {
        std::cout << s.str();
    }
    @endcode
*/
class string_param
{
    string_view sv_;
    char buf_[128];
    boost::optional<detail::static_ostream> os_;

    template<class T>
    typename std::enable_if<
        std::is_integral<T>::value>::type
    print(T const&);

    template<class T>
    typename std::enable_if<
        ! std::is_integral<T>::value &&
        ! std::is_convertible<T, string_view>::value
    >::type
    print(T const&);

    void
    print(string_view);

    template<class T>
    typename std::enable_if<
        std::is_integral<T>::value>::type
    print_1(T const&);

    template<class T>
    typename std::enable_if<
        ! std::is_integral<T>::value>::type
    print_1(T const&);

    void
    print_n()
    {
    }

    template<class T0, class... TN>
    void
    print_n(T0 const&, TN const&...);

    template<class T0, class T1, class... TN>
    void
    print(T0 const&, T1 const&, TN const&...);

public:
    /// Copy constructor (disallowed)
    string_param(string_param const&) = delete;

    /// Copy assignment (disallowed)
    string_param& operator=(string_param const&) = delete;

    /** Constructor

        This function constructs a string as if by concatenating
        the result of streaming each argument in order into an
        output stream. It is used as a notational convenience
        at call sites which expect a parameter with the semantics
        of a @ref string_view.

        The implementation uses a small, internal static buffer
        to avoid memory allocations especially for the case where
        the list of arguments to be converted consists of a single
        integral type.

        @param args One or more arguments to convert
    */
    template<class... Args>
    string_param(Args const&... args);

    /// Returns the contained string
    string_view
    str() const
    {
        return sv_;
    }

    /// Implicit conversion to @ref string_view
    operator string_view const() const
    {
        return sv_;
    }
};

} // beast
} // boost

#include <boost/beast/core/impl/string_param.hpp>

#endif

/* string_param.hpp
fit83+DZZnlWjGe3Sn4nKy/nZPHKPwZ5AvpMb/aJCJs+04fhyZbwGr8hHPOelnfu9NiMeTrNbt0Qh+3Q5Q6T51un+Y4Umzz0Yh7W2oR3Y7jLJrwvwxuH7PeDVQL7w1UbZax1O9Rs42pjmzHAeVCPk9slrNB9AepvuUpwHXA5IOXV42SSpDu53jzjugi/fdr30hfKVCrlYqvUzwiMbi1x56Qbs4M/GjvRvzs7cXcjyOPC/YiUlzXSpi96zDlAa/TxWzzV4+htIgNTMf7Ww9nUHndDS98fxjF2BFoedxw5PnZEBrR3D9aFsqmr7gyPtYSbv+EFJ/gNrwz6DV8W4je8KvDeNn22lvQTnK3ZnYnVH2E+39ex/q2je43f/HmLbt5XRt50T931WOOzzefPFT8276obH/31Na3mxV55KO2Pdmd3ddc/xZkbRg+us7ium8XrF+eyMfobPju0s4EdgYOAXYGDgd2BQ4F9gMOAo4HDgecBRwAnAs8BTgdmAGcAxwKfAl4MfB14KXAfMMvw26txfcK1zg6rvRr1VBtYvjGWCOxPOzZ//BLGTwhh79bH8N1V1RfYEHgmsAn9Znzln1dzTTCLdtJHGP8bvKeN8MEODOAEdgNGAHsBI1kf9YBnAaOBA4D1gWOADYDjgLHAS4FxwKnANsAyYFvWUzvgHGAj4EpgY+B6YDPg3cDWwBeBHYB7gCnAvwJPB34ATAV+DOwI/BTYCfg5sCvwK2Aa8BtgN+C3wO5A5EX1Yj2kOzhP5Nx3B3A4qJ/53HKHVR9gJP2teFdWO9r5deAdWaPIlwvsS3u/s4CLaed3hPZ9MQbkCngmcCjwAuAw4DzgKODVwPOAyabOPHAs8ALgUuBY4BrgOOBtwInAKifkCrgWmA3cAMwF3gGcBBwDwSgATgZOMdMHTgWuB04DPggsAv4dWAz8BlgCbOH23VE2AFgKzASWAecAy4FPACuAzwFnAv8GnAU0PD57zVTgPOB9wPnAt4ALgM28+P030wcuBJ4DXGzWE3AJcBlwKfAu4DLg48DlwI+A1wA/B14LdEf47thrC1wJ7AdcBcwCVgHnAlcD1wHXAB8BXg/EsK5uAEYDbwQ2Af4KmAj8NXA78GbgJ8BbTD7IxW3ABOB6YDJwA7Af8HbgAuBvgbN+orP3neDfBzoCip3kVZ0mhc/iwy7swi7swi7swi7swi7swu7ncz/6+X9Pk06d/v/yWuj/V93Ms9KeofT/GW7R/99xs43+P3mt+v9Pw2+v/09+6v8vttH/T0UeO4JOb/vT6v8vDtL/3/9foP9/juw5di+6JuPb/ou8xpNL/tDw152f+un0/6tu/mXp/59o/yFjUqBNdnZ4zyHswi7swi7swi7swi7swi7sftr1/ynT/198Av3/5Vh3Hr7Ov/4/sf4/eAP0/1usrNb/X2rV/yevVf+/2Up7/f+GK+31/59CmFX/vxR+q/5/E/Hb6/8/vzK0/n/XVYH6/0vagU6B/v/SWur/Xwu+Lat03VP/X9ejrptdqwL0/xGnbvr/S2up/7/f3COo0vmpof/PfDEf5LXT/2e4Vf9/SR30/5eehP7/dYibpstB/f+QZSCfRf//Avht9f/JH6z//21V7fT/R1VZ9P+Zlp3+v1odqP8/vaqm/n8f4aH+P/MRrP+/pcpe/z+n6vj6/+dV2ev/p64O1P+/tsqi/8+8BOr/s3/VQf9/6Uno/yvq/5s6NYnEtyDfG1ZT/79naP3/pUH6/23Xyf4ky834Fv1/tcb0r/Y2gO718fX/rXHht8Q9wznBZaf/v1Pi7IZe9zAv5YbpJGv9/6p1Afr/Ol2L/r/WZ33zJhm/DS9uTM+DFtWr6iKtr/o=
*/