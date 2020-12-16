// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace expand { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::expand::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP


/* expand.hpp
ht4wnaT+3RAQU8rDuxDF6OvUnBspfcrDMVbDhJpOXr6uen0Wf9jZx5AWXf9F5GSxdflgHdsbK4/uJs/onQx789vi9M08cqnHw/c/UBGjT/RFl0BMzeiXj7NjDaJgl1QiWOQSvvOyL3de/wx4oSOfs6CqYUU+RyK7OnA7J3p7P0rEHoAbiGU+XtSOHuijEmDmHgJ4HIPyzv5tcW4C5baqyDh1is3+3pQq9xm5Ae9ndS6qUbWShgkPZlHq13NJFjX77yYL9Vv+b3LvP3uQ1H/DhDayenXVf2MgVexNvQgqgwQvBflNvMJUIN5AvlJRl/QmrZc7+TkUvau3rumMT8aUTGrfavcnr2ECj1Ki3yfLsrXhsLdVkyVKKqaU4Sy8/nKjEymEPr3FPHdWsp0Q5Id0g40zyN3JQf5e0IYgSKp2nIQchUD69ridFMTlMIPIuhx+qu/4kLz6ak9OSGWQKyPeWO8E/8UeKUvMpZvmyLeYQ/U34YYJQwotW3EcNXZ/L3JQfHZuEX/sK7URMXtT1N6DHWoHSekVMqGQfWj8H/vjMn3oaHzeHrFq/dFzOVNuWrf+000r9fzKvoEr3DLy/teH3zmUnsb6l++36PpaKvxSegh/tIPmEJfT0+5f6+NE8Z7nne3V0yoe73u+Pp3mAhtRRzJzV+5fPDuVOzbEaVwlT7zpTa3kSw/J4QiSHFviMB6P+BxrfJyFICttJLSMgoNzq4QK81Cb5cGzlO32Nusz6J7afV89qZn9YjA3sy5qxeCd7u2AIDdToK79aS8vL7adZS8o3P7fJ/9oeY9kYnS3zX3kt7k9O38B0Qh1985tJaKyPUOdArOil/V2DhPiK7dCkC9/BB1Z3+BeSv8Q0nKzPqSvr3mKFhI9yEXEWkaxHpjmHdEv9Fbz6Q7Qe/UjFz08ivKS5h3ySfyuF1Eb5f8RBUxJ1Lwqvn+GtLuLtNzL2zc76jdaSkMn7S9O6Z6ifl19iVY1T05Mj9bap0CZgSx2nc2RUkFSuY+HoC8lwCps8tk9X7tn6uv7891rZbKzVEQ2LoJqoCBkk1czNqOgZjg7N4ey+WMIL+6vbHxLFS3YmzfCuTqTnekGqSc+zVVe7vehBKkyRm6MVUFQSrJFy/7HPROmkgalGvY6h124WjhDUixHdZlaWVocmaxiHAsHKqddOflMsotXBfCu7dBFYMrMowwMLoIMrukPo9ceDSXcTK0s+gOyQPmEafJqPpyzNm7R1iRa655w7k+Okvcpokmyt6ou41trUd1uGdkRzdloX//sK1fLRUtySStjt+gD+bBzfrKirxJHqv0iCisieo2esNW6qyR1euX5ztC9o8/10/ZO0Qj5OUikjH8xZTN6HAVMCJT6fjB0MX1RxNqhvOCwRAF2uWOEvb67GmHps9bjK+47xO78ttwOz7qQvx/1Qf11pXe25Z+0vvw+xY91jW7pjjz4oz/ItT/k1PX5LlGI7uyV3BPp5q5OsWz1308JWNHGHAr/d1e19ok+b+xdiGQgry1+6OYq+igpBbrp0X8y0eZ2sdbavVt0KNXjYE0P9WTR1Nbv4fO7PSj5x6XVjNPBaou4/B9T+e/sKlylkRtxoSqPJ+x8g+28nGc+14e3beIxNtra1Tke4EMwT0XmqZjGknlEB5MD6Mt8f30+VGWaICHzFDZPEYo2RUULuaJt9U8mdwsVVHmEtBO6uKQVOttD9u+TIU2WOyf/I+54cdMNP7JYxhIpCTM9JHiApmyoCkef1z8MHlSoYDBLsqmPN0AdAf8exvn1RtW+ort78dvkeTMv2oqw8svmZXzOF/5Blfe1dlpRI311mga1ID+FZdV1TKOYc0U56sVLm6JoPbUZeVo=
*/