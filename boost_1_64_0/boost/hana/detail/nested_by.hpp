/*!
@file
Defines `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>

#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename Predicate, typename Object>
    constexpr decltype(auto) nested_by_t<Algorithm>::
    operator()(Predicate&& predicate, Object&& object) const {
        return Algorithm{}(static_cast<Object&&>(object),
                           static_cast<Predicate&&>(predicate));
    }

    template <typename Algorithm>
    template <typename Predicate>
    constexpr decltype(auto)
    nested_by_t<Algorithm>::operator()(Predicate&& predicate) const {
        return hana::partial(hana::flip(Algorithm{}),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_HPP

/* nested_by.hpp
l/HJ9DrBsXDglyz/xghj4WzD+y6LyXQ4xcHZi+LgHOGLgzM/1hpLRFt09D5qUwED7/1KxwXzh81xeRTBUf/4pomx5Y/fk+3L9KzL9Gq5j3LlViF93LbI67g6ug5HB8TykXF8LARlNvByaBw3ZdVRT7tbpuJt8BVm3HICtI+JI/StgLJTixDWL94635QvoZChyPxjdJ3sbEAsStsEAszH6LHCVh8n5r3jyVZ/Z8Oxfbr6lmcHTZEMYsfxCSV5ICRJSgcWMDx8EIpndBKbj04mfot97aFOTTHkUl6fPdFtB1eYTGFFvx2HIQdP11NefLH1rp3VJaINbRy8U3gcPJpTVU4qyYgbhLAx1KBPK/epQuenkc7rSOenk87PYPNcrtz7PlfkP4vyn0nz8A8o/w8F3ZmibX9EdOeUXNOoe8Sp7EBaTTxD6bytroR77XyeVy6+e/W+QMhzIclzPsn9Y5LnopLzBpS7LJXBye9Qn503BIz6ysWs7J+y2Fc/E7GvLgnhI2JfXUqyXCZk3lfo8HKi+8UG1xEqKGq8GRGWo4noIiN4EMKOzSuYHq9gdfmVkOkqkulK0uPVJNM1tp5jJuaAmYoPutF7PJ1D2owffX6Sz6eWuctjd5z8JqS0kUoBmuvqne3CqkBVoWHu7TVj765VY8rS1jsNNH5+y8bPkY6676pi8KCm2cGu5enU2pyrigB4MTu3kTxm2DjWixqjCIYab21s6WyK6biyBIst1bB9nHGuXVb94IYQcnS2dMRdikVtTTr6rA5jGoBAUa5urw9p3R4J3R5CutVje/ky/SZvWVcP2SZFW6HgywezQzkNuxGw4xRsGXo06Ez+ExRsYKgfh/huO9wEuvUKlu/LoD+589lYyP47PqeMchmncMED5bpK4gBrn5pY/7pZ9K9bqH/FqH/dSv3rtlL23Kwr1Vo02+sW7IOQrbhDlHWnGF93UVl3E91+xW1UHlcE+5Q5yueyA3lrG4rgyEbcw+p9L7MR9wkbcX8IH2EjHiDZHmTjdB/G72FRt0co/76kx0cp/2Ms/ypgyij/ExYOXky2p4RsT4fwEbI9Q7yfDbABm6NfzqB+OUWPpy4+5p9XYx4wd2qELDNprfIC71d2DPKBp/tTfdH5XYWzMO3C0tQXXjLzUMn1gdjJCrCxnz/xrV/p0Tfg3noAE7VeoIj1gJJJj7mX3fVAb9rADL9aR4nNYpfSnmS6gmulWdpZLkzF19WwV8BzLltjqDmuArp9lem23ckNZlZ3FdIppi4/CHVE3uL75r5sduVQzuRlID6/vC765xti7L1JfeiPJffYyaWtMdhUuzO2aduub4ly3hblvEPl/JmNgzvYOHqP9f33Rd//Swgf0ff/Svz+xvjlGL8PhTx/p/yraFx+RPk/Jro6XxzSQ7MDbL9X4cYgddDn9Rj5hI+R0ropos9o0o13bLJQkrfbvwLlyvSavvhvvQ9U2dx9Hwoodyo/275vlJt/yO77RleyekLmeG/boJDbgKzszRuMT1vo6u6zHIIQdr4qq/Tac2yl1z/KK/39YxzS+Pj6RwXSinZ8ZYl15gj3skqWTZksE5gsmwlZNldyCFm2IFlCRHuNX//9Kiq3Pz4yYHgSz2EVCrYC3gbHg01w6Xq71jFYyIVlfXkjCrYu3cXz1ijYGn/erVw6P6xWwTL5XrX2qIMOx6NCYdYvtgPeVVuh3/bdCWwsR4R+JlbiI/RTTfqZ5NLqfPeI8TsZOG5PtqQ8X6A8Jexkbmgwl/XWCgJG7bs1a99tKv2x6LdFGvYD+uByj3FqSYYpRH+Ur12pCMfXroNDkMK2KfMX1oFHyHHvkadMTjPn1DgD1v+ENNok7wKM728=
*/