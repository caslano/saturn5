/*!
@file
Defines `boost::hana::detail::variadic::split_at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n>
    struct split_at_t {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename X8, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7, X8&& x8, Xs&& ...xs) const {
            return split_at_t<n - 8>{}(
                hana::partial(static_cast<F&&>(f),
                    static_cast<X1&&>(x1),
                    static_cast<X2&&>(x2),
                    static_cast<X3&&>(x3),
                    static_cast<X4&&>(x4),
                    static_cast<X5&&>(x5),
                    static_cast<X6&&>(x6),
                    static_cast<X7&&>(x7),
                    static_cast<X8&&>(x8)
                ),
                static_cast<Xs&&>(xs)...
            );
        }
    };

    template <>
    struct split_at_t<0> {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)()(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<1> {
        template <typename F, typename X1, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<2> {
        template <typename F, typename X1, typename X2, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<3> {
        template <typename F, typename X1, typename X2, typename X3, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<4> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<5> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<6> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5),
                static_cast<X6&&>(x6)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<7> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5),
                static_cast<X6&&>(x6),
                static_cast<X7&&>(x7)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <std::size_t n>
    struct _makesplit_at_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return hana::reverse_partial(split_at_t<n>{},
                                         static_cast<Xs&&>(xs)...);
        }
    };

    template <std::size_t n>
    constexpr _makesplit_at_t<n> split_at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP

/* split_at.hpp
e3UjDZUUKN0Ry+n1sbKa2oVVfTRWxV3Bu0DO29ADopmM2gANZQkZSIdZfXLp2yB9wpHr5M7jv7TxWNV9dWsSvsrOmoGns5I2SwrdvH+tGNx+wrHVX9HqtkdU6wH4riL+tMJ/WeEBcne5J18BvIyq5Zhf1s4b0sQI+A7EEzagt8lRky3GVjSp+r/3Ri2zhdXdO+4nESLIydqlNYL3M/p5gv4d5kNKayxvV42i/nPaKp9tbdBLbVrv/MT2ZV+UA0VdpcThOxXJewiD9KqfkiWUyr5/eRRwc9fjAeJ3VXpZB5uR6TOube9yT7NY49oQm3i48weCBdrMJo3tU2RKIKYB4sWzoaKjb5Uw/7sRo2rsbaMBQLNi9dDccklGwPydKHQbGBVIm7KcBPzG4WOODSdm7e+/0uzWCjTOa1ZUrn8pugSW96Kayij5tCzixXjVfnRHlMla8oafboXrfJb1NM2ubFi49yvshtZYCi/c77zZ6n0opjqMqHSx297A81dvtEmI40NKPXnc4m7IBfcWyhFOm82pahEHVVn2Q7thAh8YWPjsNau0D/CabK0kvaqqHDd5Y4Z+9cQ6cF9X1CoHTXXpEL0JfAguxYNe89b1ZFP/SL5vFiXsBr9vp0EJlvhAY6ZjzaX/fRmRKBpHjo+yCylgtc6QM9aawgAcsco+7w6hHLwOKWyN9B1iX3tatGoy//lpLuTZTOmbWPScHAiexVwPrZTVwrA5CWNOP/d6ZZr+q4VaiSQSMqTUXIgh7MRkvhUZXwwO3eV5TvQH0SoTWeIqPNuo1hLpPoCanpZ5uSb+FjLHbovgixmphm5B2n2+UueCEGNe/3583dpow9wSuk6ygnV75x97HFoEwGbHa4pu3uMxuAtGrDVdeZ7Oqqi8erfOwNOZsZA8IxzRUUaEICgheaEunjK6vZnuwkZLUNJM3kqgs7YElKdEStPNY1FuecsT/m47NDf+Le8sG60GkpyIhass4OjgVEwAwilnr/PeGXnUJYD1uDu2RPc/UY8726O3ScvGmIO4oLBqtMnHh48/8QHXPpysK+eedcWqJTtSu17GTVqLD26tcHZptgFBAl+KMalm2sIZBomcHCmIptddNsrRocAzT0HE2aF+5XaFzhBLKQsPaqIkNPd8fg3fNe9d7Q61RaQMaAfKMRB/wDYLCI9G6ZJhxlTCtrcTfTvXuK0BI+7t1nff5o5CE8gYDgDm0BVJcVzBjrSRhu0Hc+QlE86YUd4DwSkpijBtQRTXdxPKaZAxuz4VkiPZDh5QOCl3DPbp6SV1e2KFXrHKEP0wKpdJpVjaeXaoVTUpIxEoQcdJcq55yVy5RIGUIPadKqLDm97HPF/9W8YtdG7hxOfWkR3PRKQ/1250bC9Q3LvQtkWvr5yMmHZk7e4zIySoFHD2takfs3CYwfpekXN66F44Ng8S/Np3ANHMmJueWLiAuDf8Hc9saoq6tt9A36elDYFA+I1zGIjdh/4V45WgRou68/4gaaWquC4laVs97ianE4tJM6oB+HCFfj0zP/YiOQfiIoU/u2vVHqBlPwHVZgqvzy/RKMTSly8MEEvWhLA4hPH8IfjkREGqmRtr1LWU92Vh0MaBwKMczfhO3nGzdYXYN11RROBais03ESUIkXs8RE9ThoGA53dmDLQMZnduY5Z38O1XiM2FFuFphjA2PBMmuAX3xrJDNCzg5rXJ2BKfDUDzrd2yCRbPs3WIEUDm65G7S54d3usdtcGXDk+mkJY4lYjrlDat59wrrdsgxFJe6ocLCSBQF8XADAJLVBhzxVKmKQ8INPj7RdK9IeNwcPK3t2q0521q/jW5JP/BhvHphSykdQhqs7e5CCeCJxDNwofTx9TglZY5rK9prYaSDsNuBVUo5j7SX2KGDr3mbt9LoCz7CdpIwcaYkr4f3e+QmFRk0lnVQdPetWoJPH5/6g7SebZ/qbXpVk8PdbiNyOEJhkJ6L0uJTGWhZ2BdHIH4TFMkiLEvRwHRSgDmhL9RPXXwT1UyEAwqr1bhkNtlYZhwOvw5tSMpxVkmZq1GbfE1ZPFNC2L2RGFW6TIGdFkaa7zTds0CKOszvwR95n6YfwZNI1sSQNATUzkzF7tOC9a8NzEtZKIgR98/lFqvbgAZv9JLeSQEWTi8XiU/LHVXNi92RBp9bRoYf40v9bCRt2uuMIAxaNdQI4/84dgmNsp7vO0E8VmgNzp/A0eZ6/+OjihOGhTin6xkiKY1Iq3fn1WkbEziuxqgYNW65bsrC84bw+SLOLkmmZCduDrBffdmybj6I9repfKDou/9J5ozAgybJdv6VpnTh5y7yZpaRaV8fDPjhKxaJQFWy6iOzuE2nJI+Ef6Ihp5kyyFA30ptZ6xqvbkPH+zrAqLkiyYDD/eazXM7g7yOCC289hDch3zMpRxv6/wjEx2zT10yPipG9phaJFelqlxC+Sb+j4pcvVTQbAk5iqKEFkkrV49Q6HwFxZF/em4kNLwIuZFlcn+6ejXY5GSM1WRssIxcuvWOQepNHlfhgPa988/OfcRHzw+YgfSfKRqgEEp5A3mGIBikdBFFDrRQIZ/veS91aRJaow3h47sFguGmYuk8ij46dfPxRAHW7GVhlzvLiSJdu6rDfacoasEZo2PjcJQoanIWRdkilvEcAABgV8BsKNZiCVv5AZr4HLVYW3ho6qsSeASMlGbgtQUlzbeZlz53AMh/e2E58Mg3QkfaudReX4Zm30EeZg2k968o56fO/EFXIfnxlLgJJmkcot87wQMUA3ayRqaC5XKdkiVD5lrGS58AzqkILeQ25G02IgGnoQ25vgxgSSOhIeo8/VRslqEhC0qnpG2OBySu5WFGzr0w8FSrtc3eA/7EeH/T3g/cXji/ly/idhSFYuAVK/GDPlne+nL+bWw2mVDwDG4vcgyaiWjRwwwMBX5QWxPEB9z97Vrikocg7tKQjbeL3IZbpl3ycSIEird1WUN9U0EZ9eUt4qLPxX6ow3gyFC+Cm7Xfu/9MSSqqF7NvhrAVN0oPUtp77u320pVrcZZaxgZsQH+dCucdvq1CumLvq86xemO7O0/DjUxUB8jPQxLipML1xlH29VnjePBNvtOKF4F/7/k3XyvM39JBI0LZrvpS/H66/9ojWVkrHRgazJ0s9lE8YCU9clnxtoUka30trc1+txPjXJ9k+l6wGbsDIOSijbrjYqL29rfEoR+FfWORMg6sBP8K91FUOPT0rk7NCd+k4MaUN70McVq+Kh7L97tVnX1oULtk/lpnla/RQv2vnuh+QrnGCMhtULDfVjYzt5YKIXqYN94cD6F/SOp9MZ/J1PMMiwcO+mCeF5350BmJPnlKUrA7ENdttBLL1ElgEWpba8yrIFa16uPa0564AKfwiyrvd+11UDcp6jGsy5rNEGulDrZRZrpHwvbLwLdKtiAtZvMUBIGuGSFO8DteFi87PNq5I3IxZwkTR9scppWKeffLmeU2xGhP74PiDnBluJGSH4e2sa40aFQPGSKfVgsZcLCuQceSWQ1cbgCJdSJ3V5qwBJ1DdLU0QNEh6Ahm2VVBF/vP2AK8XpxQ+bUrvU3Tsnu4hYPM9Nag+jCT5yuiTjkrYh8CpkSFD3uESMmYVDFjs/5kukZ4EEEcHNs7cOMQstAXc/HJrqsHSgLk57zvaksQ8G0t7BjkAz69eE6TDIf7FGwHM2EqkYLL/IiDfMOjyLweJbmXLhOQjd2O06sV+6VhUNiWKODRv7+ylLLLjQgXCfu1NiyVVLg6CaAE7JzbAnmQfAyUAwqqJHAIMWSusefzvMj4tgfSdjBmmqr5MIiFs3Q60R9T4q+fnppNYMtCpXC4WhaV+6mffr8N7KgaZVAoAhyRcEjlRj6lChCAA779FBf3uuvG3ntCfbgtnTXjrs0DMUnuC8QayreE64Yx+LL7xU43vZ8u330Ql7ESrBg+sLBelC+k179qogM7fZ+k86nSDQw2/kJKezg5tw2MqmC6qxOQaFJcWzIO8FxJofv6cdEXWhhdFZ0Tdv/CtUTloUgABiz504T88jY7JvgVLPEQZQqifHONPZi0MBCHHhQyScz8NMjVi/TbizasvKlKM6fOOYWp5PV7ni4dUAiVGDlcPLkUYpEGzQ9geEXCQ8IS0W4p4wExuI/nXltii7aOGC3WMtibjypD1guVSrdQwinNupPWPtsbwcTVz61DENanQtfNqhq2SldcdN3SCaQXANk5vDKAuk38YfGuQisOIF7Aoj0P8T0IfhwC5fO3WlnVsAKGhP+I4hBUOEmvNUCT/jhrYtcG2EjPipM6p0AkSaC5N4RfvWXQpt1kUVydJfTIDBKKLcU6Lgvhxums8XRX2Ot35hJqGbCOq+wwNM5PM5c65q2vlxplulj7u7yWlLvXhB1XSa0Y0FiEmdkAoQNahB8/OwJjrOHC1F/PGF2eQDmBCNT2e/bBurv6Ge1+d2YPk0uUma5YO3EXo0p6VRC9XiSwvSiGH4i2SEihuv/96vzw9ZXpv0jZNirVLq7Q4RIUBzU1hRFK8e+tZYGlB4Ca3WxB5Cupomd0ZJw76uTen/FvAJLiqT3hZHKT0wAodGJntCk/54eahRrJn2WDW0AXtlS0I/AzZ5lI2jDs/Xy/T0wq2DUojgVN4qYqoPADYLJdI0KQqYwtZm3WuZ3VTJAGAPCT8lCK5gf/bfJ/fpv8n98mT7dASDH4RVgUmdIPnt0bs20wEOOmEVG4a1WRIaSCTkkydNyFdq3b+JMZChmOd69+IyUqZlHyGkAWwVrexaaWKYZ8L+Db6Nc9x7z+wQwEsMSOs1+LaHCVSjXv+dtX42KAj64HIOZf8UrOMa19UgNlt434d9B+rkMHcNjgBzn/xTBuEk3eO3fcEMNEXh524DeHngokpsCkYyThXieuFZoalTcTHyGtIScHmSruxRyYArDsnhebrOlHGGgucPlf7b5n8k4efn2HTrJ4w4K0FNGChqL81UyWSAlkGKAPE3GSh9o3N/FWPzmngem53rCvuUMuef3HlypcIVUwCFhDo0H0IsLyeWwaDG6RSclqrbkrWvpP32CH1oGs7pEZ3OI08V05zKMryDzbYp7y0QxPu1N1dKeORSOvGdCYIjT5bCl4ygG8iDVmgUCzZHszKHEIDYKVUJ6sJyLBT7Uyg+lfUlEOIRjy8zlXYtywn1nQBuTay5/qJ52K1JP6rfErTeeaK1zfZYRgWgWTaUAher+lxG0NlJ6Pqcr33OPuEqZjEYzd1r94+TR4ZwfFbKS+JanwxsQIT7mKxE404JaVadiB0x05fWdjiglB/NINNu6S57O0YR408e1Sf/lHGq+I9PD9swhtI62XUmvLilnW/+jyHUI/Cx6lArK7fM/tJMHIiAWQovZnbO7FG7dW+Eo2WmUC5n6pJpnOq26H5CmWXUDgFMt1KDVv/u3AHjcbR455aSMPtrbXnBzEEA/E53qZt1nKZyjuJYk48qfSXioTBdUl125HA1DjIFcnmDVmDrJM2cbdl+Axr+gJxq6BjfZkhYo4zqvuvZ19kkm51Fpe0UrnQUOx2SzDRScCUFWn9pg+0Xo/T9T1GsZhjWyfRuPCGZUdpO7Qz7yEI4KCRJ1wYZyJJNAR6TtDc9p6a7K0R0Htw8QLNzQvjn6cBvG42wpW1XgR561f1nnDQ3O8mNh++zeCKzb+LJmt7DOYn6aZlYR+cYKAVKaimq8ckVkyUJWA0wwefrhLfTv4DJLmLQ8zz+EjDTkBhBUm16R/3ilb0BKHDI/HdajI7OMj3pWJQQix1miv03oZZJK8+t+ZngmZwwJ1oETiSefVIuLQEinwsHZAkmIzz/vGxwkUP+U/3ZuMzZLLoGyztqaNg5u9nLruKgtlbNn3Jj5bVseU+2nH2SxAf3G5iNyChsDYQluMRHhlKXJo5pP/lDzjxjNOos5Gi/RxN+4CWGnDzFnh4MqyI7a3cYvaXySl61cjZgKub37Qy4f5sRMxAxSCc1sXehgGuiYArAayXZ72zu/Kw7x/4S87XtyTgtjK1mRkwSDGlWV9W1+vpdVKVvWqrWQ/ikKM72H6oZIOjzL7Bfkpn6kC3WuAhaQAUcV5pjzk9MFsh1IRNViK9IOSzEclb1Jbwv/L1/3R00IqMiMpxpaVB2sC7PCvFhbJZYMcEqq4voSw227MGrua3lIZhlKo2pjiZukwjUK6opFyXIxezLngfbJR6BtT+dT7nXeO+uOG/Bnk8wV8XRRfafkL7TtQU7aAdg0xPgt6qaHm6bySQg9+cG9D63YvwkgwaBDscyasZTfLSRHdOtAZbPSals8kXmPaPr8d3sLglo9nnC96rHbeI68RyqNw8b4Gb1Q9U7SW7NV9Aw98NfOynDzWamS73tfP9rnR1rjIDa3eVvBefQVOUgPGQ3NoIE3IulqUm/5c26XKBewoiTfJOA0venw/LCaS807pyysP+FGhAsRaTJGuqpEStd8ZmZfqgEKAcLepPtfadllNtx7N1NDmj50sbaGBFOxJaph3zcHjqXcrimgIgnmAU1sNeRUGimPgodrQEQJAvuzy+GIv95B91wNpXQcxlS+Nx/wDhHHnbSs3M2uTh79bB0gGVEqDYMIIgyEEhKjfV4ZSgwC0Y4zyUdhFfY7JCi/g/SNYL/AluqfqCrXX/5cUCEA7DYROg3l9cRCn3MRo8O+k4PZc8TYWWDh5d1DJAI69EWpwcDAECwdDMXybdqGG/5tq+Pg1Ml14nHZ5UyrraCUF/Ce1UPZRWzkKrslRNKiFktdoBExRGeIzAADQ0m808PwXDSs12sQjzVmLeo/IZCfA7oowGJwfkfQlkCxvuVdEI+fbKSoGW+SpPsauPEgYRGx+UFPVQ9BTTW3NrTDhQt2f0L5VN0qJrUJ+vu9R+Ftat04FbAQea2xX/GzxFvEAImqNyvJzR3WX4tQtjPN8lELUHpKLLJmsXaflKM/iLm6iwiHOkgUoMkPLN6rcchk/D5urKUvZEOGzAVdpYn6Rx1ty0VBxwbKAWVCWqKGbQ8NYBtpSPYBWRFsk+xAQCMESEB5L5lOa3GrG75zG3n6vI52Y59mOrDNgXcd+YjDpiceI9PTitQIj0VRYYMXM/Tut1itiM3D9CaqVDycK34EGlhzLii8y9G3YtGwT6aqphbBEsW7uJNgHpniBY40UiVbqODCgV8PTrvfPOqsmw/BCJ+43CtkSN4/BscMLDRc9VIz3VNkAxmqpaCRDvStC5GHANWlHjWcWI1S+YL8TWaisuayBagj+nEu7W8HLlG+YYj9bsPh4o7kIm6IDK54YKgKAVzz4q7qyU8PBoyXa5XAkGJYvtCFDv1fAfd6tOikV+mGLz5VD3w0pWGvO2DMmpnAQauIxRb7DAaziP4bQvlIUDZ+3olwyHJ318qMXnLG7qjl76M9rmfYsXwO1GGM65/RgkdQMNqwLU5JjiOFFfgBhuDAnVbACGRt98JB+1zsQ6lNgZriuQDx49bdscmcscs6WdUmwktv08B46DFiYt9CmdkYr6XmEZQpvMzLDs089GSzFG7cukr8S2cWXVlGxJ2t0kJuUvBJModXoZQVmHQ6RbjXohOZblkMwUm4yWi8qR6NhvQ8MRmvCXoMZUAR2VtZj4GmQbrBkKFeXy2H0dYwtdRQDBTUwJWOupDLvSFkykt9GWAtGQ4e4a/CoLFy7e1IbA2G0WugcWSKG0qrPUkrVwCuUeqn9UolfHwMVG9k41fo3bwtMUUINOAbvHxRQwiy7/+2ur7rhBghrzcIosEAERW4JtRXLi6SExRVEgFPk4Z9f/5AmIn2DPbcQJlpJ+/Hyzf0EzjguMbYQ30bn7KtQwQVG2acdawT+QNcaQTkgBr7GYt+5uujwipyjYjR96/ruUB3k7hdiNmAyHDObUr63l4EErtcKb/wlBVBXIbzDonYnKcvAY2Go3x7lR4Aa03VOP3oWZS1jYPGvyPsTa5TPLooxmezSJcr0zMu9flg+tB04MZubrOiX6RuROX42EhmsHTzLJQy1YCLqz+gzewaoNFFTLgXwt88UiFvHN03Jd8G1MEi8a0TbzvQ5QiRNQH7c+GEs6jlBUiIPDAckrXZCUkV0nqZgz8oVkQ5Dc48wKAqZ5E8C6MCO3r0+omGqW3AvsAuAPfcPeQfX1Vz+fkc0rAxElpfBUUQ5jh+Q7m/pvsZiCANzc2lIkIaqzNAlNAZn+3OLguK2k6ekVmO6ulMhR/rnQMA5VcU+ado3bTrHkDjXo/YiEIw1yrcIEj5uO/VwxvymNSAeW9Qf0QY4I0nmMW6izmzfXSvXYq5RAT08W7ZyPaQ23zleqss8PVrWDIKEcIXidfuzbvQlXbGQkp36ajNVoLHiNKQ1UvfDts5xDCchoNQxgswpALWSSDMHAVyI/Pzo4WggtnlpL085V5+Slc6t6rfXDPNVsEIX/MQ7OelpKUDs6oWGxOh1TLq9czw8mAlF7E5jm8y3FCM+wWypsdMrM/EgBktVUeGQWwPPDBobeCGQtYKSOaizGW2uL+s8yO16JP/xCZjiES+cfYPnMPibzVMebRP4Q3AAAD4C3LXL7qhnw+WcXM4YH0SwSylaAcA4FjpR3QMAoL4LpEPJ65O3iBCpEToQPavxntBLGFgkxzF73SPOgzviiboFxgDmnCQasqBPhI0jMHsDcJ3MWj5VrFfJUIwqYKDMvrB78VGOPJfEDd0fxfwQFwgTkIwgWsrhkfLsctrHzm1NO4nlpZKia1YBFDhHntga1xDVyt4Bv4s0dA3bDD3QIY2u6YHS8++XHsMXFKDRfc3u/AGcy5yuqC2Yj/G034xHWpfMRKqM7bMtG6IKzjCwRMLy9hrpTideliCvT9m0B9Z3GQuv3dIuSfUdFx7DeuRiCOQ4TQOTNiCQUBlBX5vIns45b+yjD4kUShkGzaA7O6ATBtfHw/I9UXrhhTgRah08jWAVYMuvkkrgL5SR7c9uc2MAFxsUWWOPX3Brt8huUmXFy3Jz7ghle4XNZGGgJmcwlk6Qtb0dl86cK85XkbW3STJ0lnwUQvKLZrW32AbUSW93oWIgFaI4sQpyKR3+OWIncFJZ0geUkp9z+DqapLPMYiID4O0n8j0+9aBf8m3jlzPvIDLnw2wTbZkxDuDjHkPrZ+r+qGwp4KK84noQzsAToLIPTGiTXNd3Ftdf9wGooWYhDhi6eSfrbckjFGQ=
*/