// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

struct area_tag {};
struct azimuth_tag {};

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP

/* point_order.hpp
6AuCeixYfH9gSL9wdkzE4kngHuqhRcOuRrwHavZx47OT06fOhKfOzIa98SuUW4qQkC15ThLOjMzSW/Pmx2fnGGb6hfDOuwfRYJPS9W66nXL8VKjQhaGhC+Xtd1GtNrhNp4kAmLaFWgPoMRB428RDb7Bm/PW5l/T9/LOKk8W6lzOa26mcZU0Gq6OrL+v3gqc8mbxKdS+PJaBTf9kN7N6/ZkM7lnefs+1M332WvGN5LR/+9vvJueVsMi7cEqtO/NjPjGeXswSwx/7rVK81ID3SU1x2pGtLWtf2KEHr3I/d5xOX630+ZYkZ1qdDKMN9LaFO21GO25JdkOsdn52l92LMTs+I9Pzj5+Y5HiWtKfJVrPK53Mzk9OR8CPwzjwlRfkKWU/GojB8zznRmZXpM0ic4YoIjfpzKn0N8anIa5WV6ltLIn5B0RH3gV8WjMlb0ZjmN+kBHxoof1DdGdMSXscdzfHb6MY+fpvYItxl7/8QzVy14qR9Pn1OiDH1GiRnx/tOT9BmjzAn6TI9Smj5n6SNqHx2nDxWenKEylDd7htIj4jd9KS1gT6D3elC5mcdRmTn6jBMuxdOzFAv4GcEP0aT0yQn6PkMf+SLdUrUe44FoiEbiL0o/TZn1KGn2GTeHrLNN96xZ1+MFdDsTzjrzz7pLkHWmn3WG7p4h2H4DGg+E9NlX+iwrfbaUdXaUdQaSfcbDwT274WCcSYCvbp7zbp7+LM99rycPXU46dL/Si071PUkAEvmhw7Oq2gyp7urN3muttA666+eQfFfPrVspHVKYUWMQ3kq/sCpyOZ/fLUlfRP7wQ6rnGJQBf3AmPE1X1j80OXYrDNd9w4fPKbytdoEhMstRyIKfxmOWQ3SyCpjKNztRQfbFGfBQHDKjkFHv7Ix+2AwgmS+WGXshDNVvAEsy++ie1/6YJIW0gNpGdMJH32u48TIkIsUTNxtONe1DJQnf4sJFOE/sgBO3fr6/St8STiWBrcZ48Tsy1a1lMZ+T/iE0VCvKX45ikssEb1zMK/GmIH78NeTHX9WY6/0xaBljj3xzLDvLM571lpG7eS7fykj1drMU+fD5InmBziOrB5d62d9xffrR9RpNpZ72hSYe3rUBvI77blzIJZ9KeOxYuJ/k6QDllQ8NHb8kfnq+sFRuHqRY7F3DB4QwVAoTpwsT9Dbf8dnClH4tNEL392wTGdTTrvGjK6GokMarG97+/eLixgHJ0dBxydKB8Hg43AmvQv2gXtzdSz/UFxcFf8O9tie7r4hlAvLCgjZz350cGSvQ3vlA+MjwSHirzCSrye7RA24nGSMV9BpWxa9/bNfESF+fjO8e4L16TxrkOK/yd3H61fcIrPeqPjzk9LN3Il7VbwTpYLxn9b13ZDrfknz8Q+Z/4q6cfv+dZD30R4R77Ah6/v2b1YQe5630mHWUa+FFGn/cTOH0yDm8pX7yieOrrkc8BNmbXmnhGokuyzujRlHZM5FXByd0rexu9cBsyGr3nv3iEaSh48LJjV+xD+8biltD4+fmC6emRh5F126n57G6+MIOOc53lHJXkPL1irtwfD8ZP13KyzZlXz9tC9J3kOkrqXROyvVXiL75O5avkXRuEXL3b6w/9x+uf5e3fiz4A8FmAu8OBullxXnKux1VsnVTrj+Xz/X3Kb1wR0n3a3nab8n2fN34/g3j+zeN798yvn+bvjfk9+8Y379rfP8efb8iv3/f+P4D+n5dfv+h8f1HeXzB9x8b3z+Jejl8yvj+aeP7Z4zvr8sl3z8Lfjh8zvj+efDD4c255PsXwA+HL4IHWaYvKfPWvqTM2/uSMlv7uUweg0Z/7xHsopHYTX939/dt6tuc25zf3Lcptym/qa8=
*/