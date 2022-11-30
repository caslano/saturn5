/*!
@file
Defines `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINUS_HPP
#define BOOST_HANA_MINUS_HPP

#include <boost/hana/fwd/minus.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/fwd/negate.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) minus_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Minus = BOOST_HANA_DISPATCH_IF(decltype(minus_impl<T, U>{}),
            hana::Group<T>::value &&
            hana::Group<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<T>::value,
        "hana::minus(x, y) requires 'x' to be in a Group");

        static_assert(hana::Group<U>::value,
        "hana::minus(x, y) requires 'y' to be in a Group");
    #endif

        return Minus::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct minus_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename T, bool condition>
    struct minus_impl<T, T, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::plus(static_cast<X&&>(x),
                              hana::negate(static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct minus_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Group, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::minus(hana::to<C>(static_cast<X&&>(x)),
                               hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct minus_impl<T, T, when<std::is_arithmetic<T>::value &&
                                 !std::is_same<bool, T>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) - static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Group
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_minus {
            static constexpr auto value = hana::minus(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct minus_impl<C, C, when<
        hana::Constant<C>::value &&
        Group<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_minus<C, X, Y>{}); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_MINUS_HPP

/* minus.hpp
QB4jYiriCXhWxHf61c5PsziVs6wV5kpz3HbsSFMpFHch+SF9lNo/vdmIz/5XcK1Xr1tLdZ/6Qd3jA9Kbjfjsvw/rakXeIvAv/6Dq2wPSC7cBTbobY4DcYlqR27hhRHltZUi91mN1sQ/vMRi6G41ifBF79PcGQzH0ODCcgRZWKdXFKiiVE1dv4LdoxxNo9xvQCjsH740DWsmLbuWOSCvT9FZGc8qwpy6G2xoa1Za7DjM/+hHINdGQhQjkQ7+LQEZasdwI5H/9LgIZV3EK2Iu0YgivBc3G/Vga76ApbuSZ+O2WZ7KhlEwhl+oTCuS6BCerBaxoWbw4Gzk8Ouu+cNb5owPzXB9hyOf0VpBWf6pX6iG7NscysHOfilGdm3V3uHPdj4cH58bI4LQ/HukW59GjYR7d9zghnmOmGAWbaWr3b+s5KaqtpnXhtrZH2no+0pYY1ZbH6nbj2t6mkRdVTyJ76hVtbU+RLMpis7dVnP502/yU8neOzsfrWDpg6g3NtEhTlTyzb5HZyZLJAthoZgI+4BzWFwAx2g27DaA2KvsDuwD0ur9pa4lbsb34kRjhyJJ+PLPMLHhxScJtmAT/3HXj8HJ3Qv7w8sLaBQnOQnb/WgzvnwxN2xspaOKTFJ7KvA+3FncGhixWHB2mpqqMVCl+a7L93KZvF0NTx7ApX0kIYEvFHgsTcD8ihTm/UW6KcTEVkQWhAL1Jx1jgTnbDPhIY6a32enFIAf7HRg7jJwcWmH0mPAUPPb7R7FthDsQXsvGHSYJ3sGR80LuMy7ZQnK0fgb2usAAm5S9jp5crZ27DOJ0U9wG7qUpJkZ5GllEfXkOdLUEqvYBUOpkUTaX3dCpptHmO314wkDZs73+izY6X+9Pm3OH+tDl1eCBtJnzwA9r02n6aNrGHNNqEDv4IbZYlhWmz6q/EEBZ3C3a1ezgx4KUv6wzosCjrzd5ucaRSaVavYa8ANBd7AWEWK+cDX+qA48jRGo6rzIksgUCCIydvTjMbJFCTjc1GhtLW3Iu3C4OSwjfWDX5vN4htmg5rH+PTAcVikbI5zapQ7xfWOi1V12GoUDHNBnMBep8k11sKlrKiA5r5h4tCE7vjYsTY7niL+B3IiCTF8IIRX43iqRcoPUY8BviU8VhvikExzMlfMq9dTJ5z64Z17dIU9ugbfar8FO6RN/h37e1T2S8x4S1KqLQyEd5i8UW1QGc8NjdDYrUOQ76wYZC4LWb0CLbECTs2WAImZYPFB6S/PlzLgLS0S0niWvmiWhlr32TeHMuOQztKU327SVliMbUoM31Su3Zbmvxzs0Ec4dtgcZtwMwDkq6LRzKQkAwEKjFGlM2wWfk1sVNYyGidCQ5Haod3Af+mjMhoPKUGrseweaAvgsZXDcOCxZAf70z+iu/jrf4S72KgYqjOIMBlyuc0kzVLykqp7UmMfHS3aqnvG419Ldc9l8FcaJZenGKShrBBqp7fm+LZacfm3Hg0hYCnbMqDSM0PxKhMLCLErqzMJ6mVKTgoM7VglG0c4CfF3qvcms02CISy4XodaACXDYRUeq8Ne+q/aA+TCCLxG/A5gMTUhlTbblAKzstCizJ6lWBNNu031pY2s6XVEJnMr9kZ4rH5bvRaugPjKJt6rzACGvrP6ekJmulwJXZys5CbNoR4mzqEOxs+h/g2VK6F/g9kGAKm8iteoqBuTi5gyFPUZK8HUKkwFs4gtobeH6M3KcuDNRzUCFhkGUF5iVdnU18NEZqmvh8lfVlphZbbXwyyIayAcZeB7fSyupbGY+dNjMZLGwsaaXwuznbaYQgSTKy2qUINauXB5EdgG0AWYnymGdxFY8fvYRu2dRsGLjMzk1/SeZWZI9zIx/EpIrGa3RvJXJIlprDDy7k4Sk9i88Ht1eRJhN5VND6ep65PZehuuUBaLSR4jGwE5KtGKNfWhY8xM0e2vYF2v9mt/ATv1av/2D73av/3GVwe2Pxw6m2wQreyFVyNj8AQWW2zxbaW2H6Y3a1mJbyuO4spSmOkrkI9nIB8fTwRpi1Mt36out+CX0jPslQvaHNTZ9kIiikCL24k1XtRqoF5ZbinmVe4fWKVFq7Ieq2zsV4XXWDiwxn9pNX6FNeaHa0SFjNWrJg6suhKr0hddq1eVBrGilj7Vf7gZOA9jQd1gaHKohsrCQhfK/ewUJduqJHuP1643V6YrjmB9u9nn6IK5rN6bosQ5QUCbHF1Olt+rxyYbBMrL7D2+pS1gBkBG1RHE6HXxm18rXbnNgd9CzW/tuRYE/xAwJ1jq35H/8RCSAQTUPsIhZGC/x4f8kOq/Hh7YBbCEoEEMlejbimWZCYTEXvoS6O0ukmLZY1BMucbbDY/b4FGb1ZfQrE4Oz+rhfFZbaVZDc2VYK5c6mAHdC1xG15qAeLHKdRYn+8f3eFTw+92ahhmyBPulbjmGQVVQsQWCnqluy3Ig/y4MlvSJUmHF+wRKOuS1e0HBhnyONpATGA2frR6CosLnOMqmvxKWFo7DbPwrYWnh2M+Gv6JLC2ahLts4DyJJoD2fA+yLEL+spJACNz05BI2UJLA6SCPcozjOMAcMBA422/U3FCUoisGCTMIIupVh/bQE9dMSi1Jqw5tqFEe7Pde6IfnOuiRTo+I023dXZtvzLFvsSq5FuWm/pcDlMRSxwT08Ds3aDoNmlWr81OzAtREDS9K+M4cGA3upjvbA85wiiqPNtwDwPsr+DKZHMZv6N+zbYW2+XUJv+3lPtYGbSwOX9RPiOE2u2GuAwa3oMICTuTGZXYlg0QkHxncxXw+Pcmd1z8CxmQzYpB/0Le/AoJV50DehZgXGoiuwCDVL8MxvnsW+W7Kexy5UCTV4kSaYBhJwcrm5Vpxp9S0PpR+fV/iCBaRwhUXdlMwmnccG9CXHQhcbFU44SaZVsi8Ov0WBgeJkSwgbX5x/D+0FwZCnIPhqLhXzWHu3Xu0lDufDcALu2lE3aYVd7Ox+MvvkLUlgemKUCCUOursZ4zoEnsgsSpYy2KNaXfFnAOgB/WUZAMFSHBBrCGK608We4gADmWylXnQy1Fusv6RgP7O7Kaq7KHTHmz2GFaCCszH0Uiy7YmefflwPxjuQSJoKlPOvG3HXCwslaOIPyf9SAoUL5eQVY5USa2AQXom23Fq7aqiVM1KSC+/6AOoWkXcJTJYnXponzfYYa3MtTkQlgSMOg13IXPGgTZP1nG/PR3Ky4iOmw6YEMh04YsGGPlWPf2cDERXT2liolNhcyowiHto1rmqLxSCNVOLIIhRq6g3ot2ULNW+FmVLw4vYfZEzBexyHQGfOYZw5BxNzCt73qRTo4HFs3kso3JDLDUINhmxnM1/SLQgud6qRK6p8FV1Khq+ksxas9nGKSd2Y4nNY+D2A3V1hsbpEbkTxcyKwmp1+MWJTgi8jltIZtk4eL+qXnISBhdysvYbm0oyfmEvJhOow9viLYVTx60tAYA+8GG1AhDcBVYD6xHtGKB4sG6lFjqvAD7cWyeQKmFQplb0TC9Wu5ZrIxQ5CH0BNuA0U+jElG9J9uRj8TLnRSlD+SbpjEp7EBR8nFyprhwhxk1H19SaamMdwYxvrfAHxrCJ9cQP7HN5q6Y1V/qVPzYwXp1RfTzb9BFVKA0yi9aGLfR+L4jIFgywqNBuT5S1WA+gMVz0Mi5SCW6jwuB4glVrEMoGblCAPxmZ3BDesLLRfu3kBWO1b5ioLrMoSG2hCU72S1wVGbVzVz4F/rqxd0dltypYuw8ul0I1M7RfE3cLexSUeKQU//+FWv5DcjJDve35lWWn4kvt8K7BmsjLPPAf75SpCZYwieyGK7IUWuUf15Qc3m+0t4Dw8WYd4W8hsy7xe8O6J4RxK1pzgnWwkNsWTkP151GbkPCp4Mfwe+8PzUXzaFIOBe57X+dQHaN//vK6lPEYXaCF2+Xc85iWQbiygkHm9dDlxWSpvrT+LDSYWi2Vn3wdVPuP5sL4Xanwk/xE4pbDhz+MuAEt6t+9Vei+GuV1TVyytAqf70spxdCOSyezeOyGlnNV9jXnSkFy50QbjcsqfBODxdKaFbT2HIgEPqtbmH252WDrRzbz/tKq67wKJVOs47GwG1YuJ7+F9z1H022rUZ3jlT5FurTHMOMID79OieYeTz70gsU0MMVkSck6n3dEhyL8ltRjMjBceqUZXbIF5y2ZlgQ2NqAUwsX0OVnkXlwYw/xUDppypnABCQDEB0C68OqmzU5cCY9T8MyAHMh1ntnyq5jPZ0QWTjxm27AhMQqYr6QIcyOrCC940zsOwDCw7hKxnIdbrBL7z4zXN0JGqihSDOAjGlRV8h2SrqlCBLTDCqRI/EYpcSt0XfvkEpmxJ8ar8FhAXe+97Ghyuj9iK52BwC/Gfxc+FjZh58ChXpBnChoxLioWJiDIijf0XElJK9qgufhUJ+yt10gYdZ58AbJgE8v1Ww8bLEUPBm0LfUficDhZGTepDFyjINzvybLQlWfPvPpVklr66epLh8i0LL9/ygH3sKarFjSRHMhiZxAsY/PjSd4l7U5Wh9o/FMdW9l6P+GqbYJhyxH7pvUHd2KnhJj6KayDHfJk6Qy83A0DKduAdur/CoTq1bh7/l4tgjl4OsIQDVvUjT+1agqyYuzcyUZsk/t5num5pZnLTxCqUgRVlq8R4UxwlvSmku6nBK5FayAvUg9DZwKU8HikRlsbc5Lbi85jK0EEOk1lnBcFyjjEPiKKY1z9BfMO5LrMq6kHJrSG1f2dpgMawoftCcprbz89uuojXK1QaSAKFmR7Bh24hyD9+dE8RJ9tZUug8H7GW5vQ+vmc8xr1HmEOCSkM++xjeO+7QEmESbBUCCTRyioOmqFOp3t8U6fkGdj8KQY6DnL0rI+VXXp6jrJ3nIWdz2DVES14ZCaPqDz5a+j10uXFQ9Bpe6MUndaKVNjWnqRgzEnMaSOdBSLlozCqsrLBPwFq1hbyU9NKIckTbiHZKvkol9FEyHtmxIp0+itflH0+vpajBc78TQrA6mOFIoUihg2RmOnAsGjG9tl29dcM3TRCzH0VrHUU7hZkeLkRPa59iroPG+n834M4rSKm7+Y/RKtMxmqMsPFxfjrcYYI1YcFR4ppeSoz6SRMpCg6IAVR4sWTLeQgoLmWdLzrWxcIl2VSiNymzgUMpqz04x8ISFwV8DjMUIS0JH+TaJ/rfwOJHwk/cSjWqciy5SnGaTBeM0isHBAu6+R/48a0o10ZM/xC9dAkSEn3Zqi3JmqtkNrOnIUEBNEnbIJ+U/5LDBNvqiCJvjqbTT5Q4uVJvQ46kE8ZOaZK2LB5aiMxRIJar5VKbGA6sGbeSt2K46kXN8MHIpke5l1k9l+bmMs+zMCIQDanSl4CxOtcfjiWOtTSGaM0OHLNbN3n0KRhG8w9xvZy+HMwGDFYr8pzSwm0CqUdJYvlLBtWAIg2amSZGM/x4TFZt9WfAcQd0RAJKBTcVZMVOpRBkhnS/2Wt3nhPHNp9OXM8lpmqM1n6dBfYIhO4qku6Fp2s+OMXRlRDmodZ6nGRqzWwfhogxzHmLFsM+LfoujJSr1mMqRiILYij6V4h2Ht6PLaivZzz/nQ5wZ1UQYAS0Vrt8Eixjc7ugzZvzPyIKidPAK8OsI8d3Q5ztC9e/eCyOKNO/HijDW+iYTIXWnWWvg5G/dSY+bCgrBAgXaX0xVaNpAi7OrlF1VXkbq/rFT5tATSliuB6h40+aTYt1G8FrDhUKKkGASC1eBJcrejd/AQBj2hEBNj3W7EPr+NXdsBmno/aeo2JxuNC+voJRiU7BDoSIyno9v4j0LtRvd8rZ4d69VBvUAT3jEBNdJb54AyrhO21yv16Ae4U6Fo4JBiVJwhpX7KXDMXtOYpu6cYeTjrbFuhsgKDLHuPFynlVpDG5n+hnIDOGuz14nz06Wht4MQ72qrAzFz7ufs+oTirwILmf3VnJ5mlTmg9H4NvjwlXeEWvEI8VjgQ+wI32u8HZTm/1Htw8VNmtLEszK0lDXcp6i8k6q1QxmOobgUxOF5BpbaiPr56CcVTHnoC3RlommUXeNxEjwP5Tp5E+Y09p9CG6gsWr8iFNgl5jDGrseXqr/RMX9tyX3+nLP+PL7/Llh4QHPiShE1JmPzgFLyLo2jhLQQ8XOjg83MEP3tZ2QI8ERGBAQbKFkA9zzT6pEzkdalj71fiDXmMsui+5Frpxwu6wFUuDwHYCEON80hkwlDNLQvdVBxZ35yaZpDygr1Gai7dqggSZkh+053dtmgaJ2VIiXksgTYZiRml8YLziTFaWWhXrtm0Lk6pOGrs/Gdt6/sCE+oAFCptEfcSIAmlAASXPKud3qXI+I0LgJc32ExQwucNXgXdr+io60bDyVQSFB4bzcPRKfpsyu3qKo8vu6NyY/kOSvPOW1sFRhLvJh8GMg0iLXLNyEWWARpNR4SoPalUEr4+mPtHlSJ9Gl3KozpvbtAYNNfH27gXQ8yS5ossgDcKei7jmZnjVGBirLElWFloVc7WSnfSCll7PYrr3pxmp6tSaOnESNrDAwiQMMVxxxlAsxmY6mHQt9tvBAgkAMRbR7lDBfi0JCr+Mx9j0WDueD7JAizDw0o5etUZTT7K7Crn27z3knXi7iWu/7NG4VtnHfoHGaBBX20JTJOuU80qeTVloBoOgu95IlxGyu0N0Y9NoFwZs7q6PkeLZEjw0FMsWXdSCE4vJQLEi9jaWNDVHzjsEtqeDCd2R6UgWv3Y/RMx/lP3lBJr/LmT+o062s5dCVf/YdMHlLW3KHGXshC5SWlzKWbnSbBDHBgQl16oYwNhAJ9ZlLlZwj4Uv1yp9VdqoDDE4Usq3Da05KJlAk1T1ztg8vKo3c0uisKNBZtNzfJQPSiYwvuag+GlVb87mKVW9zi2XCzsOgjuZUzvf9r5Pg1HVmy0d2zY0B/7yJBHjL2tNFC53Fe0wZKNyr8oskxJylKZIvZzNsVW9N1feU9WbJngbQfjOOq61LOwYKvfOFR75l5GWJPB6lINCzWPo9mBZ3PReW2Csus4pxSi7o+o0vCP3DhYevDMG7zL6zf2PjyhX0x67B/5oZfwSEB4Lns7ZgQcucgY3dTcYNbTjhxhSQVHGTlSBnHJvslB7B7j03qZ31T+p6r9VsI/fx7M1YtyEXYObAzETGpXd8slkMVvusYjj5R6bOIjuHfCnUy0xfuINOMrpE9Wv4M9USBkkt78/BG2qwCUT1fN4tMMGz8MwZ+IW1B8t2QEzApc/j5NPQ8f90I9Fi8TL4Td80SLpqYlqCGuZoZF9kDVR7dHOh/jfj6E2hYlqLybBm/9l+GdCo/85uil9uvBwGbbQe7XwMK4pyL05gjcfUiaqXVjhV1DhagCk0WmbMWvG5kuzMreMFXbU1c43HngGUxmGIxxigAb9SwAq7y3e/QTCAJ5wO/MQAxgbftykJZ+eJ9Rg4MFFQs1u/udflDxE8B4GOFpL/zDCcNBYDG6ST8/wNv2A0DAeQP+a46J1okrtgzMcGDRR7cNnmBMwgAOGjqgnZgDVxixaJHhvw42p4fFYysfjxn7jMSdqPGb2G48JhMO4iWo35v8Gb1OfqH6Pz7/GBocYNoeJ5sfbP5CvZwgP4cpFVW+G8Eg8EhVmDS9Su2j/RHULXqlpER7ch8cn02ofBPYk
*/