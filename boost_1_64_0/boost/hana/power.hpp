/*!
@file
Defines `boost::hana::power`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_POWER_HPP
#define BOOST_HANA_POWER_HPP

#include <boost/hana/fwd/power.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/iterate.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename N>
    constexpr decltype(auto) power_t::operator()(X&& x, N const& n) const {
        using R = typename hana::tag_of<X>::type;
        using Power = BOOST_HANA_DISPATCH_IF(power_impl<R>,
            hana::Ring<R>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::power(x, n) requires 'x' to be in a Ring");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::power(x, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::power(x, n) requires 'n' to be non-negative");

        return Power::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename R, bool condition>
    struct power_impl<R, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr decltype(auto) apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return hana::iterate<n>(
                hana::partial(hana::mult, static_cast<X&&>(x)),
                hana::one<R>()
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_POWER_HPP

/* power.hpp
pK3qtterE48LhnS3orxNb0i/EEsPwGtEc+GQF+YL1XuR2J5l6fei5yHt9R6jxKn1thB6acTXej7Sj7ZlHzF3ruceqmHxdO5t1w59m5D2BtBMZp5r/nx0xqmXRN4bkedmd7Zc+t+vHehPgNzRfiqlhbWwJ/V5n03z8HwUMVkujD6FryQtPmlljdSEIbN9KYdT6u3dsJv62ggP5jeXcXkbux75Jtx8Oa7PFy/r8skUg3je/ApITzFvKO/MlVyei7S+5qQEl0V5v7gy8gjrBsYwS1Pe067r87hlG2HaXPqGyEttlQmz5iUbPs8LsM5I3RWiUWc4Pxd/iC8Hu8t7jBZ7/Rrk5rWHeL1wKPPaU74MBsM9Qc6NRD07GrtrPzSWPRpL51kPo/yZ3WiKkQT8NpTzZrLjo9DaPtp+OPkg/XQpkZ1rqYu2qLU4dutzbnPb4+fe7sTt1x/4oI3NYDlx4Si7vTehK0UHuS9TQy1WplAMISTCaSgwotz4d8IpT+iVGLoh06bpKPjRIrGgGEYJrRS5LM1QlrWQbhoeWS/RXvhnaX+rvMcVTjdileKZQtAI3l+h3jhW105oXezfsh5qOSR9Po2vNYuHdozT9aItmkIrVVBXj6IRnKYTxkooi1XoIadgsVcGTiML0fe5NpCoeftWtmDof+ijGGXbD9mFcunUw6HETHyEzyR8pIBqBVdmavDZmcDDnfN5ecInF6VtNG4HJvTin7E5FCym20eTca9FD5GkdTH6j2bw8PWDh1E8wMjjBzMettB5nzdH+8hrzYMYEY8L/zzlkeOe1ZSmOpKHzBIe9J6W8JDCZDbLzGDF4PUj8ogGPIp0tTPayjTOaEoSbaiY0xLmfELbiUKVOYSN7ixtj59hwY7hTMIHc2zIZG2aKrThaAZMl/a8hD4TVdvXbgl5VQMzFY/jRm9xnG5wYdWhpa4wJQmYY8vBC9J3jzqR13O6E6qo81aXhVh2r9oHmD4L77lJeUzY1gy1FSopz2OAonwSy2XwhhljBQ8erbxUNYvjktKYzrTuzoxKVs5K8wtO02IPKSqp8Om1nDeN7nUgSsZMF1p3RaeStoG+ms/RS/9idiao1rZVoWNli6TTvnVjTtuJAfqkrtZalJCEj90aa/6IMT/BaW5ni7zuTN+NU+I2eFQL5Um3LpLysuxUUchK+EedWx9RvkrKq6E3pS5LKn/refkhKZ/roVBVU1D5c+blT/LyJ2RZl11nW6FmDcoIwy39Lm2Lc7OTDSfwyiK8wfAYfjTnznB6K6zK8cepFI57FfYaHqMgDaT6pacl31SLLiuKWjUFiE5TtIi1gFMS9DS09hLaTORW12XdlcJbwEIOw9skaNcfFPpJMVASOiXqvoP2o3MNhcS3/ygv666Fl7fZWfvR2RxsXXBk1VagDfXFEL2pLcm3E7pKFBkUkLaTvk7aX0K1ODlCvaQL/MOszXlRZ4XDomKK0Bkt6eov/cu0zX1t1VDUVRgnpllO23zjhK4WdZc3Rhnlvw09dHL6mT19Ql9gTy3yVrUiUWbjMz1iFzL6zL7jATNa1TV91gwzWkyQrf0F2jMzWltVWVVaOyM+vePN42f6zoRWia6AhKNzN6e2trc3HwL/FXIEiAvgnCizclqcYEPvvpABaagKrlPRb4BwLjjNIGRXNbUdHM26j4W7Bm0P8EoW9rOPcjorqq6rusEWYTptbK551WRqN/LVtC6s7VxXrZmmPRGlGGQ/AF1iI6idY03diRgbcm0/gCNNByThl/1qJhs0mS6x3MSkO16LwCTzM/3Kv5qtGchFptH+W2D+PRjf0d9SCIhoFivwWEKfCVMParBV5+nHQDG8x4+KdILTDaLXhSw=
*/