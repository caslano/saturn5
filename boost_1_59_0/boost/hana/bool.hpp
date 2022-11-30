/*!
@file
Defines the `Logical` and `Comparable` models of `boost::hana::integral_constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BOOL_HPP
#define BOOST_HANA_BOOL_HPP

#include <boost/hana/fwd/bool.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/operators/arithmetic.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/logical.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/eval.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/eval_if.hpp>
#include <boost/hana/fwd/if.hpp>
#include <boost/hana/fwd/value.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    //////////////////////////////////////////////////////////////////////////
    // integral_constant
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    namespace ic_detail {
        template <typename T, T N, typename = std::make_integer_sequence<T, N>>
        struct go;

        template <typename T, T N, T ...i>
        struct go<T, N, std::integer_sequence<T, i...>> {
            using swallow = T[];

            template <typename F>
            static constexpr void with_index(F&& f)
            { (void)swallow{T{}, ((void)f(integral_constant<T, i>{}), i)...}; }

            template <typename F>
            static constexpr void without_index(F&& f)
            { (void)swallow{T{}, ((void)f(), i)...}; }
        };

        template <typename T, T v>
        template <typename F>
        constexpr void with_index_t<T, v>::operator()(F&& f) const
        { go<T, ((void)sizeof(&f), v)>::with_index(static_cast<F&&>(f)); }

        template <typename T, T v>
        template <typename F>
        constexpr void times_t<T, v>::operator()(F&& f) const
        { go<T, ((void)sizeof(&f), v)>::without_index(static_cast<F&&>(f)); }

        // avoid link-time error
        template <typename T, T v>
        constexpr with_index_t<T, v> times_t<T, v>::with_index;
    }

    // avoid link-time error
    template <typename T, T v>
    constexpr ic_detail::times_t<T, v> integral_constant<T, v>::times;

    template <typename T, T v>
    struct tag_of<integral_constant<T, v>> {
        using type = integral_constant_tag<T>;
    };
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename T>
        struct comparable_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct orderable_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct arithmetic_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
        template <typename T>
        struct logical_operators<integral_constant_tag<T>> {
            static constexpr bool value = true;
        };
    }

#define BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(op)                          \
    template <typename U, U u, typename V, V v>                             \
    constexpr integral_constant<decltype(u op v), (u op v)>                 \
    operator op(integral_constant<U, u>, integral_constant<V, v>)           \
    { return {}; }                                                          \
    /**/

#define BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(op)                           \
    template <typename U, U u>                                              \
    constexpr integral_constant<decltype(op u), (op u)>                     \
    operator op(integral_constant<U, u>)                                    \
    { return {}; }                                                          \
    /**/

    // Arithmetic
    BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(+)

    // Bitwise
    BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP(~)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(&)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(|)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(^)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(<<)
    BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP(>>)

#undef BOOST_HANA_INTEGRAL_CONSTANT_UNARY_OP
#undef BOOST_HANA_INTEGRAL_CONSTANT_BINARY_OP


    //////////////////////////////////////////////////////////////////////////
    // User-defined literal
    //////////////////////////////////////////////////////////////////////////
    namespace ic_detail {

        constexpr int to_int(char c) {
            int result = 0;

            if (c >= 'A' && c <= 'F') {
                result = static_cast<int>(c) - static_cast<int>('A') + 10;
            }
            else if (c >= 'a' && c <= 'f') {
                result = static_cast<int>(c) - static_cast<int>('a') + 10;
            }
            else {
                result = static_cast<int>(c) - static_cast<int>('0');
            }

            return result;
        }

        template<std::size_t N>
        constexpr long long parse(const char (&arr)[N]) {
            long long base = 10;
            std::size_t offset = 0;

            if (N > 2) {
                bool starts_with_zero = arr[0] == '0';
                bool is_hex = starts_with_zero && arr[1] == 'x';
                bool is_binary = starts_with_zero && arr[1] == 'b';

                if (is_hex) {
                    //0xDEADBEEF (hexadecimal)
                    base = 16;
                    offset = 2;
                }
                else if (is_binary) {
                    //0b101011101 (binary)
                    base = 2;
                    offset = 2;
                }
                else if (starts_with_zero) {
                    //012345 (octal)
                    base = 8;
                    offset = 1;
                }
            }

            long long number = 0;
            long long multiplier = 1;

            for (std::size_t i = 0; i < N - offset; ++i) {
                char c = arr[N - 1 - i];
                if (c != '\'') { // skip digit separators
                    number += to_int(c) * multiplier;
                    multiplier *= base;
                }
            }

            return number;
        }
    }

    namespace literals {
        template <char ...c>
        constexpr auto operator"" _c() {
            return hana::llong<ic_detail::parse<sizeof...(c)>({c...})>{};
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Model of Constant/IntegralConstant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<integral_constant_tag<T>> {
        static constexpr bool value = true;
    };

    template <typename T, typename C>
    struct to_impl<integral_constant_tag<T>, C, when<hana::IntegralConstant<C>::value>>
        : embedding<is_embedded<typename C::value_type, T>::value>
    {
        template <typename N>
        static constexpr auto apply(N const&)
        { return integral_constant<T, N::value>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Optimizations
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct eval_if_impl<integral_constant_tag<T>> {
        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto)
        apply(Cond const&, Then&& t, Else&& e) {
            constexpr bool cond = static_cast<bool>(Cond::value);
            return eval_if_impl::apply(hana::bool_<cond>{},
                                       static_cast<Then&&>(t),
                                       static_cast<Else&&>(e));
        }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        apply(hana::true_ const&, Then&& t, Else&&)
        { return hana::eval(static_cast<Then&&>(t)); }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        apply(hana::false_ const&, Then&&, Else&& e)
        { return hana::eval(static_cast<Else&&>(e)); }
    };

    template <typename T>
    struct if_impl<integral_constant_tag<T>> {
        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto)
        apply(Cond const&, Then&& t, Else&& e) {
            constexpr bool cond = static_cast<bool>(Cond::value);
            return if_impl::apply(hana::bool_<cond>{},
                                  static_cast<Then&&>(t),
                                  static_cast<Else&&>(e));
        }

        //! @todo We could return `Then` instead of `auto` to sometimes save
        //! a copy, but that would break some code that would return a
        //! reference to a `type` object. I think the code that would be
        //! broken should be changed, but more thought needs to be given.
        template <typename Then, typename Else>
        static constexpr auto
        apply(hana::true_ const&, Then&& t, Else&&)
        { return static_cast<Then&&>(t); }

        template <typename Then, typename Else>
        static constexpr auto
        apply(hana::false_ const&, Then&&, Else&& e)
        { return static_cast<Else&&>(e); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_BOOL_HPP

/* bool.hpp
6+3IPV1dub6speHKlPs+BhZZgg/43wW5ZoG84vaFtFEkD79weufKzmkWx+OBoY9vbq7f2BSH2a2GV3bz6sfN8zacXPBr/HzoRjlqsxN6ao437ces0UAIpFv8qnz+A9wt7u8a1s7wVr5hVTolxE4MWtfe9rWUsTtbxRLSDg7PEdyOga/pEhNvIqsb3yJg16USwWCnAPy6ml3p3Q12gJvY4r3brDkgDrNCvPHoN3WwGViZufiqVikogVHjFZlbdKvogPtR1nIXIuaca3iCxRwAwuGydyj6rViORCsp7KIWmG+d+iA/3pQUmcY6E/gdopQ5aPR/XZWb4H1BO/BPS4bA7mgAeyy0dRygkO+5CVW+OTl+RJguNvN9retFgHoQQjrwdOu0gl0RhENYkGhXFj34ukotcDYrZpPwcLbth1xNMnimESinDOaZ1ZxN03rnGOyt4Cxcxp3YrCkbxd8iZ3MS+sE3OswQ0XfBdzewnCD6w7DAIC0/DkO0Pf8xfexjkhyAV65GslutwCK8GViqSIG1jYY8NBe0+5YTltnq8Yq4eNzdvE6r5XVsg8t8zLpNLrDwxoQGJ6OY9KKUzTwETUbrEQGAXwzF/L5U3LcYBFyi63K/Os6bh9K4KwNLtgonONUdZvmPSAcZCzcWRROmIOCbvnqD1FVw9tHH/iCefNjkH6ysAC0tWA5xwr4kMazO+OKmXSYjOqUPBWKNda7JSkNEj5rGGobHzoKfsIaEOkREwLdkB9ZJE4R6R9JfKMwq1fVQ4EXaSy91yaCL1aY1bO+t3cHx7K/hPEVaAIfh7KV1r60iDKQreeMQZAWrhai15NNHSxAd2RIl8dP7xpf1f5eh6kEDWtzfqYAJIfLlzNngvnmjizl9gdSd3NObgzb3hlGwWnkaW/M8SU8mixvsWA152oJcMoiQv95PBco+SqD2R5zT30jYDaWgdI8jbLetwqDrPqEeOO/QOlEHx37Dr1hrzAE36+5Tl/8HySX7Zk/VlcRu8KzqnFAek4aUvRRO7Zaibxei5YKu0wFea0ui5IyLbGpXTEemTB8vZ1ACKIjaPq5BZP0YhFEVknxKnYQJQmMrrRqGCAkUTjEblyMzCJfzwesrmb7a5e5pjf5cxD4bLsVukjWZXtuCpceotjisz5RLNNbEVpJ6MJYillMYFcD+02WUxnSw0NiGTLaGTJHsG5mDn3ylIccLSpSEeBLN/kFtgEM3KPJmojnp2hb600XWNcku5SamZhChnZVzMfyZs7gDaNYWouYYOnoakZWPg8HTJs8bVxdsFi94FATb3+rcM554YRwV+LJH88MVRIIiGAWpeyeXzFElXY//66RqNQ2Xt7TPUxwNdxEvfbU/eyeWd/MouNCqn/xPv4uNcbvBH2HFLoGilK7lTR+WzezdBJYuIEA10Cc7p9Te2hRvymAsKZmji1hdkjzT+Brpvxezwq58BFrEnTlRdKKgQDbi6wz1g23a2LiyBoUNelH6U8mmfVusYhivy7cbcaybH9npIi1RA6lrHntICNqlCL8xdzit4K78fm+TIgbJt2t4SZQEM6EDOjbx4kmK06rtkToRSqAlF9iekodVmJMhBiKZQqNLmHsNo/+i4TCnHkeBeY074H5B45i3KRAiVmyNQuLMQ9zWjUnrE5HZ/lm8T6xRDpD8q6xVR00+P+gUwbol7PBIQBYkvUdkjOgVrUhfo2zQD7KP0JExW4ay7oqh/kF4mEECBYcWHZ4fXOqEEushESZ86CdjG7d7PiAlSViDed2WIdFgGpXlfYa3BIUQJkaiKddfgfJduPd59gYPFQunT5pBMqrdN5xoS1JrS0MaeJjFIETTeoOKgKyqu8QPCi5oVxysPqjyScShUI+VtzDpSNOnloni/csFJKg+z/g9muRpTsZ2yPtBH9FM6ktzBwDcpt11E01Ss5kz6rq2q/eF4S7QxZ83uDyhzAf1S2mXWc1opZMccmvDnkUobDtHolSW7xQmyYpVQ/cAE0ZIx+XIhQuWEWpfGMDJHiJWhpgEqHClQ3TsQ6i4eUMFMei8JKh6aJNa5PVrzGqkqHrbcvrLi8EcIESz9ghRcklaIwk52Ued0iCYhECY/f/OgfBRzBJnktOupyl89y7fTdJpZevDaA2SJYzE66NBi8Hie73XDgoRg944WSoku02Ma7wdZjwEqXTNnY6py5zhjClfvcja2e62mAY5Jq3DhTwUnMcLYu1kRknuex27eLL5ELRmSbJymYh59psiaGDRDIZOQFkOz/K3pXqF1GtQW/xipN8hgM18OJqVzDBcYSNM7yaozWRN8HcMYx1fUEZdZ5HQCJrsOX/odRDUX/yGPHiJv5x49rnNalIJTsYlAqJ9AGItHCISWHlnlqB/T0HQB19EElJknviVHUv7g76lrykacklgYTIUOb7aCV4egUA+2wuAXpjKdft9eX9712eF4Y9+k76xHyLIPstNouhCKN9mKfG+yNTLwUAynqGL+bEadJDPKkDRQDaaZmL+w8k5FgnQza4o4v9lWsYD4STbzP4v+x+NQl7EJadIgOe9jmMD8Kl2VJPc4mjDNs99mvAsxgEePAWd0Nfcr4hHTDepLFZVvjHaNgLvvJ3s0btnL0eC7FjmUaLbYWFBF91ufNcvIRDwLzIOgl/ALvPGidPP0G3yV9QPzaRdLv5ErpPQQ25npBO3CWHyBFe/HWL19ZVe4uuQWEPXPdJPcg+Y3nVwz+oHS2ow7BGbHnrwPzHz+U7twB4W3QRRoLQSRt+oAdZw7imLtiH0uCTqDUkRzT42OkstqlUsth6kLvKcqIM4NJ6iI5HSZYmus6OO3okoWFeIdsJCIF1kzR//e2LKw7KyaLq9BfhDgYnonfo4B6mM5+BbzcDP75KZklvjLkUzNFcGSVPmAym1GQNMmextNinZ7HsuHiWzMYbI8kZ+O1Pl73A43ltDT7Dyxqfu6EQMHXf/kpkeZyNRjASMYRrK4DSdv2C2+waPVctKDEb1zxSPlasD2UvwUFhICp6+Vhjdb2boPoMOqxbYGEPJf/SFvKLip0H5XbA5eqKZmTJMZjGfx1PpL3ZpHJ1l82TMNOz7Z3RFvvyLOIhMkPT+9oWCkVRWqC8pYitXG6k/DabDnniR2qVq+vVYhyIGyBtFozgktJc0HoR0Hd4x1qk28o3dVgAafjh0nnDzoJd7iln1qmk9oIsmKMK1wfc2AqZPCSyGgdBgWIxMngad5slY+xUujIyFAEW9iTWEzgGaYhidiSL81v2IGWJUsy71hUy6ytBspeVdYZmVIwiuzrwNhUh3o0BH3Bl/R8WJ+bemIKYX1M7Sz+7f2IMbTkAs4P5u6i89RzQJpM/vX+rrFjVisu/Cvo0jLGGDxjHz4NNkkQp9j2nkJ+RNPJ4RckzZYNq+WVaMEv5PtS4oocG09kDMZMU6ndEKVQoyowQK8LaT2VoIplb438OAFzPYYmq4/nIO41DjCL6QdzjFNHwugn/l6uJ/0hChytigMJtxsAO+vYvZnsI+09iXRmt3a+oJnllOEzGeUxzLFhcKCAWkJpJJroZ+DqXeN56zx7+jkb4fHkJf+gkPgE3c4Yq8HjgKvFC+RNOJEgLGcgkHHgN23p6tKzYjsYZRUTPjPJc6Gjec2eSvlWzUbu+1Z4lfiirgSPFgujdoK1m8560Y2VajH37j1+CpG/dXMK2HHyYNmEKGxuVLjd+BmT2+xTfJU73V/0xmDn6ablxSuYo/DXtJmd+D/baVopVEPMKNU7u0FrYYZMvutaaamMOFgQ2xY8IddtQMs2DbBvBU21f4il0CqbKO4qiqlBxDHq0R1d4Sr2vtQ2SCqZomtffBU5vweLcY1MQZXUYVeFQKPCUlhtbpGkOCWjuBcrVa3QA8dDeOYDw02QavpwAgHqDZL0A8EKEZjzSax5EeqHfP4B7yoGDknvfVNhU5/bnlbI2SrQl6kwRzHhG11AXWBowGRBJoqvhZYHepQ9kjaKYqHEZ5btvrQ5qxLJg3iEQLT2QIbzx+cazvuoeZhLeSSvt4YtjJoCn59x7jYiQn7kpnjfeYnEK5yaLlQz/cvJVCUcQxRtr65N4YEL6Mw/dGIWr7eUfQ3t6518Mk2Yg7++TMOIQY8aRLoBxaZHL+9cp2Xm5SmSB151AvhLrJAzOvdXbCMuKilVQXDe0nUUE4kM+HsueeRSdybAWiG79JIqBXKzCGla5ElXQmE+YocdCe3B2fQw4xKR3z4F0lMRx413G3+DuJcWOo0Cb1qBnCUtiIn7hOgRsbXpLc1EEN1L75WgMSCaY2Ytm7HH01vVAf5vmszUPffzS5/ucAekqOH3uMZKlsJVyo2SkQyn5rfefPjkdFMONOjq4Fd8Ks1/Ztk45alJVHoqh+bQgi0xjcgoJ8B41s65HJGNiKMVXYWDX+qrSWFAvF0fh3U8QsiBa8BLDK5nF37P/BlTeiNdmiitCZLkT1gqO+ibgPk8bE9w5kX3lVbMRcLaq5BV5d+t9esk4H3U7mrgDutpKVE/XYHbCS7LaeY+h5774cB99utm1l3mK5Lw+/avyL8t4tOEbcfZ1wjLid1KF98CHKuT/6hNTx3p2riH3j9cAjd5VDI3hXYASrvyzwoDSly6ijCK9SOFFtt+k6UiU9CZ1Qz5U3yHdCEieYLgAeKRvpYsQY9sotJjVF8oSI+iXoDM4VE4qjcNiKfLYO8cxzB1NpX0YCPxYMmfRT29/xssSbNeCEzWUO7b9EjX3zlPeY2fyIKMLwQWutpmea2spEaz0e3E1liZps6F/A6Y+atGfiqW0ZXtl4bVflpLz4vGZQ1Hs7aGiGLkmqb+EAnGGMw8zzTmnoYh7tTr070mrImBBFYAF53BB3Knx993567685VSPPjXP0y7mxKkdjywFCGeaU+AjX0RBs6f78kVn9+lVwnoRgjDNlmqS3YyETI50HiUHflwNjaOMqdKh7l+x0wE8Fki3LoLKBCaRl328K7cd+hWpOcrnQFWO3UvetCXV48oer7QOL5YOA2waCY4mLmGSDGdK0HdYkHEtsU5yKMfqHy/R0YUsyvdEmMpLz3ymizag4/PRJ8I5np1MWaS3XaOU6j0MW0l9dJEYOydZBNbi31ySqDpFIpJdy3N6Pk55UTlTcnzgoYZFCJAw+VEAGfr3fUpo9JxfH8AwukMy1ieKVvuAeXi8/unrfe+HRmfOrOiW9DVr4tTOA5Zdq8kuEsBvbzYfroKGoPlkzMty0uydVRkbXry6FuqVF7wZyAHdNS+WbXvZW+t83ZU/NitJ9P114ZO9PV9FbdjNbwdtO4PTFxG/+naxzh8JZDxlnnFb0PFOMRU1rnkJPiI8Of4pY31bJAUT99iKSL/0zQhQXYbNU5z60ebeJ51OeSHX+CMAorI2IPrOFoRE6a3Pim69kktdVLaHN4XpVjDShrd/eKlm+z8o+mxDT+kCMcU5JxoUFO2g613iq6yE+Y5yYTL+BLI7aBipx8MAqco+s1U+P3gfUc9Lisg8mtiXPb0wLBwftLvtyugAmGiELLTCWGRIm8xq7tfqZbhac9WwfjzYTs9TzvERPzi4hjx03YJy5A4N74jcr+WJWqN0qwYjXVGfhElz8syKg8oX5VyLSHumzMDd6y/gXUVeNqbvOIGYG3gq1IdTPNDzFS+HpC8kIvwR0Cz6KNlz4QL1XRXC+wZBBzNPimhSBopGdIZwgQpbZURZsjOo8p7MxHfiqpruPbLo8crEhuOplgBeVuntTQX8aB0do+kgWM4wZrUVrkQWk1IN6rNk6IYoZLcwedVVQ7CiLs5biLI6Ezxt9KtglzdOpiZUOKt5YvNrhGdEXNuQ3uAzUa6dRVLiVezVVg1ePd9B3Lm1tFbua5sXJuTfRNk9QL/QcaKcHsfOG7kCHyYOdWxyZrHvOP7pUTg8ib9AxKa93CnJ73LCzQxf6xDmk8zwxEg6rvVNSrLCEblL+JeSWMtnONhgtA8hjRE3p1ou3y1gtaIp/PVnthP5jxSytBq/v/9HuhB3zQhZ3h+kD43KWbcVtfWmIZkzmVru9M1GUCIPraRydRMcWdj5UeNjgzToFj2MTDRSF0x1h+6WHpmhSVHXtV5zHITBXKSN61aKSOt9HUtdynNdthAVZcZyc74FiCoOtjuJztG0YsaFq0NKmFHt5ByNrFMyVBuhUJP2DlTB8bXKSbS7EkpgCH9Yp2kNcFYGkFSI3qdlKVTm4pwib1RgJU8oVMTNoD9nWTgXW4xV/VgoDV17Jr8/3kDZOtKC1vCp37b0o57o4/jUT//HruPqNi7zQ2IB4rgtZl+04Fc9FxbZmNlz15gt2Js2kBw+yys5pLX7UCz9NxEX7gClZB/yBNj/DpuLFBN3WQHvkWn2YtiGBDNnHBnqFAGUM3fj3X3hlaGMsWeNgTkOvx3aj3IC/TD3LfSRGTXWEglaeWcsZo5a4Kylg93bAofFld+/pXpd/QO6Kufa8QFDpoOR8/jUmBpeU78sAC3aCp0hYbfNk4mHBIxLQWiC9w5nrG6YPQ9HE9iqyiq19raPLqErFkBFE3h51vSQiTEmESqI5/Xj3RJhDGn6an3/qK1RXlxdmhhIDprpwLbaMo8uedKzVK6jCVTVhoUghetddvzs6PA12iBJHAQP0XijCpGJ6MWWr/Vw2T1qskICBWh3yLC9Y1Q21nP/CI9V6AaQYYmoS4Ex303ZiPkXVRCfSBYM6rr2w+/sXPBA00DQBoHoZ1RLEAUSq0NlYxlVWlpjs+czAlTvt/kPiVkvJv6+4gec6kWrI2UWttnL5G41Hw2J7eoDpfNp49ROKFnDDRiryKfDEoMDPKuHPzB7D/74dKOjtgb+HV4Cm3ESK2KC0L/3CJAm5Y+LCfT6t9vso6+1w0JrIVwi8QbXbZzyQ7xWQYY1BAYzFzZxPHgCmlKNHp2bx7hZgIFJK8J1iFhH22GOPVwU8LLzPFl8Xf4ZRs1Fw5w0rUXiuFl2P1Yd89EwQZkXBSUzbOdwOBdjbmJCgWVjT1v+D8d4CiMV2wsX6L1pnWqyAekP804QRThEEj801iKsEfp/vLhGHALsWZlTDTX+6ttUwThxo0pcb+2Afza8Mw5AEeRY/kryPhgqAkobBxChgSnWDAfE+qibFNfrzXsqQ6hp9ZX85ZQ9+6MfBrFIrdbHy0/sQfF7L7pdBa5C/dVGYTkLbENIwykwklGYmzhRgOs02SG8RnYi/4l+T+JaxBR4SbEuCoqUAh8YZ4RUuimwD4NACFBy8/3x6O3GXlGbRuwYMEeLcjpbV5+LlFEnNu5wQf62Pjuc1xUVzZadurcf5c4w+XPeO37BMbXvvpOe25BNkjWl20d7rFvKXWJRgv+CfZ5rEwNxKe4q2ruHWQKjcn0ZI1lKLDZS8O1M6lKScI7dfRwa9eKSSnDKDyHFk8ktblsZetHy6QEi3xffq7+pDFu+Y45davEV6wRvbrEWUpyx3urEM7Ct3kpbIRtEms73EHV38aYMz6uI9GKtoHfyz6EAxHL4DbGgrYSdQWcXjJf+zpxVwn/bQqvECBpVRMNyRtopTr3Lnk0pZIzWcmT5YSboqFhC1gwpjxk0oy9Fy3Vwv63iZuw05emRt5oe+zzlko3j960AbOK42qUF4YDSFIlPvI+0qAwpy
*/