/*!
@file
Defines `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SECOND_HPP
#define BOOST_HANA_SECOND_HPP

#include <boost/hana/fwd/second.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) second_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using Second = BOOST_HANA_DISPATCH_IF(second_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::second(pair) requires 'pair' to be a Product");
    #endif

        return Second::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct second_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SECOND_HPP

/* second.hpp
1865nS8Wnh/sbaq7WB6yco4GKyy/2MWhPK7TadQ273dIfVhPL4Hl2baHdf4Zy8o+/OFS8+c7SR7GmV8Gy8KiiM+PL4fPIyDqFbK/9OXD8yge2/zJq8RncFm/OVoyNqN/L8q619WgPPp9j47KNuuPNDeBaFhvq1YPQ8MAoexwd3uMGAkL01FOKhyOyrNdqGRnFjXa1QKf5GtU3q1A1Wqdtpqdy75j6AtA6RzjbaM67wVAjMyOQXQ4H95lrZ9gb1EeLpgVVT+I2rAN7u90Sw3JIkIQ8WE8uozohacB4HHsyNhOhvg275jkLG2r3tV2YB4ZARkB/pi3J9tftjGvIZXRs8H1pm+qgQH+PnxMwUBXxkt6Sh8gB3Xb9oPrmA4McECLmH+5ztluxldxMRHGXM7TirZbxl1v20HwCZ45FbSVMh2VMaNUzqpzUvSdDOfew+18EX6CdzxFnR0TXaV13cuAE59bGBnHsYNN9hzYCSZxnlQGr9jQDNz2zYDt3vrPsvBe/p1ljn/ujOB9y0KXYZ2kKZlWEWeG8vCe2apWHTc11r9/uH0AmICYjomieu7P62ZUzsB8uOtVtRrrhg8YdmmMLcR3T3kE9N05a+zAmd4BnWHytu6bsjjAyS82g957Uznn17rxxkrDyh6DfVrle++i3poNyuvgXPDf9hmx9945wXzlvnae81AzJpxI/v45XlHl9055gaXtmkrC0GMbAHN1+4FF4gooyOMxH/eLvWuCAdly61ueO1/Ujnl03zXJmd/4fuiELuvG4S5GIA8m2i2orPOlGWoP0zdWj6kR6J1gm+gxV3mre6+9xLoj2+LnOj2j75X97rWsOu867HfswmwS30t5BIy5bisFbFj3ziQWKgmJIz/bL+Lv30dlDUwrXTfGq1A/5AU42Afw+4V595mifs0a1TnlrYL6k305sx48PFWezH9hUNjc/6usuzWmccF5EHBrwjHqlOQ7fjjmHHl3ifGqvGjF0Onp+kj7j++dfGu3oHJupwbf2KqpQrf3YzzzFOOJUXrRM6G540M7r3cWdaryK4sb1Gno8jxXXiHHs94Ka3spGOhoJ+eOQdABXN2HZeI0RsHHBGkRzcutcz+fA58pxkEzPbSDFbXOeUJihvwYehqk4EKbMJlg1aH4NVTW+d60suqlZOEwBWIW3//fEj3G9EvL+VDx/1T3FMfyau+h78B20ghnTFxqacVY743fU35zdhgct7U7s97ym2Po70HlrIrGu7a3sb/4oZ/i2p5p8e6/r5pG90zBXVJO9hHndojZvF3Kkpj7zOY5Yqic23DdaA8Vx77mSnGuPa6oUzCpG9FKW/3nOkN/57rE2wo5DVPciM7rrsS4PT0aV8hxd8a3xYhfctF257XpedWyu1YpfJf6Knxn8o5419Qdr2sWwzq3IF59+okkIdQHmcroWecG0UnBWWglXRZwTXgv/aZCbjStG955VtE1gFYKnU67Y3HnSOVYNlSqr3U3sHTixZrp/ucpD7fM60paLu2/rTutFvQO63VUTl0x1fKmblvNgvUfJD188xhacZSVj13E+yjq10xarbxSkg1bD9t/0Dn4ErKA6KwAaPbHW4cBOSJsTmQ9/A6V0zNRCQVyGjY7hV17tgn3Q+WY/7por2Od98p4bef1Rk7obrxaogcLKgfyO09wGaxoed+ZMj3e2ZMUY8ypnNt4PwjZVoYBHRxu0hzFu7CiTs1c67lRfVPkbIsLydLPrPCT3aOybtuJxvW9HtVFrBjzWBb1GlZXfd12gv8/9b6Kyrp1b6VRptEQY3G6hznlcR1ItPhNVr0fuBTMAzXJ8b8/Hd5REkM9sZAD7NB67lvJ9Gx2brf8sPM8vWM=
*/