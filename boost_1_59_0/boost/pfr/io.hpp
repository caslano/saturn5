// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_IO_HPP
#define BOOST_PFR_IO_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/detail/detectors.hpp>
#include <boost/pfr/io_fields.hpp>

/// \file boost/pfr/io.hpp
/// Contains IO stream manipulator \forcedlink{io} for types.
/// If type is streamable using its own operator or its conversion operator, then the types operator is used.
///
/// \b Example:
/// \code
///     #include <boost/pfr/io.hpp>
///     struct comparable_struct {      // No operators defined for that structure
///         int i; short s; char data[7]; bool bl; int a,b,c,d,e,f;
///     };
///     // ...
///
///     comparable_struct s1 {0, 1, "Hello", false, 6,7,8,9,10,11};
///     std::cout << boost::pfr::io(s1);  // Outputs: {0, 1, H, e, l, l, o, , , 0, 6, 7, 8, 9, 10, 11}
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Synopsis:
namespace boost { namespace pfr {

namespace detail {

///////////////////// Helper typedefs
    template <class Stream, class Type>
    using enable_not_ostreamable_t = std::enable_if_t<
        not_appliable<ostreamable_detector, Stream&, const std::remove_reference_t<Type>&>::value,
        Stream&
    >;

    template <class Stream, class Type>
    using enable_not_istreamable_t = std::enable_if_t<
        not_appliable<istreamable_detector, Stream&, Type&>::value,
        Stream&
    >;

    template <class Stream, class Type>
    using enable_ostreamable_t = std::enable_if_t<
        !not_appliable<ostreamable_detector, Stream&, const std::remove_reference_t<Type>&>::value,
        Stream&
    >;

    template <class Stream, class Type>
    using enable_istreamable_t = std::enable_if_t<
        !not_appliable<istreamable_detector, Stream&, Type&>::value,
        Stream&
    >;

///////////////////// IO impl

template <class T>
struct io_impl {
    T value;
};

template <class Char, class Traits, class T>
enable_not_ostreamable_t<std::basic_ostream<Char, Traits>, T> operator<<(std::basic_ostream<Char, Traits>& out, io_impl<T>&& x) {
    return out << boost::pfr::io_fields(std::forward<T>(x.value));
}

template <class Char, class Traits, class T>
enable_ostreamable_t<std::basic_ostream<Char, Traits>, T> operator<<(std::basic_ostream<Char, Traits>& out, io_impl<T>&& x) {
    return out << x.value;
}

template <class Char, class Traits, class T>
enable_not_istreamable_t<std::basic_istream<Char, Traits>, T> operator>>(std::basic_istream<Char, Traits>& in, io_impl<T>&& x) {
    return in >> boost::pfr::io_fields(std::forward<T>(x.value));
}

template <class Char, class Traits, class T>
enable_istreamable_t<std::basic_istream<Char, Traits>, T> operator>>(std::basic_istream<Char, Traits>& in, io_impl<T>&& x) {
    return in >> x.value;
}

} // namespace detail

/// IO manupulator to read/write \aggregate `value` using its IO stream operators or using \forcedlink{io_fields} if operators are not awailable.
///
/// \b Example:
/// \code
///     struct my_struct { int i; short s; };
///     my_struct s;
///     std::stringstream ss;
///     ss << "{ 12, 13 }";
///     ss >> boost::pfr::io(s);
///     assert(s.i == 12);
///     assert(s.i == 13);
/// \endcode
///
/// \customio
template <class T>
auto io(T&& value) noexcept {
    return detail::io_impl<T>{std::forward<T>(value)};
}

}} // namespace boost::pfr

#endif // BOOST_PFR_IO_HPP

/* io.hpp
UgFOpoaKky2uaIdWGFZdc0A1DDRbGOwRiZASpOTNY9hrmviqOePSpsuOsRp4TEZr6smkkpAtEktskWJr2912Z3jjXggVhrg1g0fCf34I89L28PEEixmSjhR0HL6Sk9MjTn0vjisEYMSFVNFPpzgFY+UoE2lAT3jXEQORkPXtu9hG+na6RP7B1TebdN0rYg/mS1VQai474FiJG6WR0q+guKYpM7Tc4/3bInBmLR6YX/ZcZ1WplyY1llPwd5iV3qR8Q5KPBxMXQpM3jMY122ODD8GNUnw7bos+Kfaw4mWbhPPdJu8567ekJ6KmrdgNIpz6CoRNdzZEcJ1SSlaUuiYWmhTqpm59tsx7KLMZiO9jHrpv/h7/Btq0RVVp31senUGsWCRgdR0hx4a8qcxkVImWS9IPEKpVdUmSMNLVk9Rp8vtHkMynLU3oyOW8C2O1ImY8twnWsTCX4mrPXrz2Ig9Ssj3ztERRbuERWtNYzNx+A6UcvwZDscQ/l6ML9mED3UPbnBEUdtesQdyVeB9AR4q+xPnWvm/0OP/qvXj4bX9I+Djdh12QJ15KGhyP3eLQp/GfVhirzzV0wbIqdzR+CnxQHoqowq67qEY5GJbAaz78+AD3tdNwR7HxiXFuzzgXSYf0fDoqTR0QUuE16S7vlSfstWKdq7SH21HFbGN+7CdCEDjZvk9Lz6DYk0W4Lqq2wMExcZoOumlzu+SP1CxQeT+HT1E4FlNiUL5vMQAxmWNHup/fpwCC2x93Nm89s5Qk+7mJxMapQfVXb8Gemvf6GOKac+/j/xhOEwI3vZCZ5MyxirH0aBT2+nHbs+knESEF8VQ9ITagHvZa20PlV+NAmI0IwAHltNXysPCXhO2e8bPY2nq73/oOCz6KAZlXHRqjoLIBYiG4k+EF6+jWXxCfj6xvVqUa03j8Bg4YxcSlFyJEX9cOAkYzarVbP0qgOOVadlawOX6pVGgDINnKeQ+1+joIaJ82Ve28c2fS4EMimYsXQJoKL0QVo4UCZrx8q7nOlrUWyvo+Of2aPW0hYWcvDbIyB7EL37ZjXtGXLxn46GewxnT3CxFw78iWhibPcv0ZT2/Qr4bqmv6uZM/5uLj2/bZidP3Hv/3WZfb4xJ4m+hZ/Bm1pr0//b8bPkI2Z48+OLUGVk9SZszrGL1u97CSEwTvKAtXTMt44s1QWwQvKrqE5U1CtZjYTZu6bEdQeYhu2iCTmO/1cykJg95CPkU9cXgOgSXqKfngYRRHEvqFvxMJ/RJAfzgABaoaFdmvQXaRSxbz2tQ4V9YUBLfR42LqHwdQz+0mrR7lluc3Bcm7Gr9N0cpfAuiu1F5pOEgptKlPYiZRTFQHUdJWrLXNzjOYf7IZoSghX7wdCGCj5QOw2LYPgJy+sPL/nktGLQ8TgGb/FUr8MB5avHV2pbbsiH+XpKQfPVVKhtOdwfogldHLR8dJWYGVVTD1CL5vj7eew84/YdSm9V5Jxx3bE9vI8WX2qkqeZVdkdNpEKq0ZCqcZkhkH7pV1lqmPiEVQLy1WNAc0jdbrhnq8HpoO44iRWXo0dZF8bM+DhyJOCKSrRyyAiRfGKUsZnzMpwXtmOkrsXpBFYwj3F4Ze3a6rqTXqnntSuOxaW+qaOJmLD73N/+p/GmLKP5aqT7wn/+syG0oZdjKBZGviE7aPDi2kIljbPgsJZWVbfB8AEfhY4GVZqwl8LG8Zvh98b2KCe4c+h34iInfbz6H+Zb6sgc78Q3OK+hOezv7+/F2tScLh/7Pb5+wOQs/9gZ3qqpwenDWELkEHM5kBYPP/+zEzZXTOyNJxVi4EKfpC275/2nHcboIlaAkIE0hMMVnEiFljvzbHdm2G5N8FwbYDjWgPEtvqLbPb/H7f+Zj/tPOt9dgyo3tVGMgZe3Y/P796pDDZI6qz7p08P99yv54AzkYHpbHB8HBUuKK6Lx2V5Gdmb+PNPziMkppgBzVEHXLefTAnKMGRe3xDM8Ol+68PEEJ666NZokc3RQuuD+ZZ7sw33JiuuDXZca4zY/3YLLLPSBjfHeJHiHHPq9x/gfL/4+XQILJ8uQeKBEj7ibdaeZDaf5dwR5yJvw2AKyO6NzGm89mhwWb3M7M9JXfqgM/91ZjSs/CdwYaOIPYktbb366OiB10FKT11ApNhObaR+CjAbfQ3pFiiwrepBw+vRfyz61Xx5dQ5VWRvU+WRM1oCsbQoHMsS15/pU+KlEL7qiFt1aKLo5T1iMBQNg97uX/6b+30uXdDzYlW++xIwppCaRRhUFW8eRSgkJTGqsM9Y4NcbSI6LNR2kJlCBKrDcmGA3BihpMPZNQDBkd5DXMCMEwt+wufer2Xr5+HnTv+vbuXD6OtM945zryrjrmfrbfnrxnnzjWPFwdnmljd0cWutg90cXuDs//oHByXt/4PEIdvP9hhR2SwQTtZ9M6qL0fxgTkmFMAy8K9Am+f6VoEds6KEgxwJHSvsd1dK3HnUCGnNBdT2nbxy3PQugrJcZnAe687xHkgPzrLPhTfZLl/c8PhT2WkXDEQ0vuHA+6JB4k7GUay8lpeT4zIasPBl2XeTTpL2ro5Y0x0L9WlxixZItbeJx3VoVp9oSfioE/qNP/eaMGBrza8Y5uZ4UmffYNnz3Q9rwEviu3UKs6IdKAFEZj555wUIv1NqnAcOt6o5DxmJ4xxwL923aV5TZNQd2F2s2YirOPjTeFCDeAldWiflWgLX32Lz03tbgltc46glwPNG6MgxsWYbDrp8Gc+IDJwkB3NjUaftrzfG7C/EVg4ydd4fZRIEOK6S/cvCpZFi4PKyl4YxIbFQjjYqDZIf8xvzNHnisUfBV8qbqVgx0qikee8arNlAa1FxHmdksItfRvNche27IG9M1ZtyzTY61AN/kpfn8sn9iRS30I15+PVBRbTxBOF5bzdO8js5JW0EsfcUoNKNb8XDfLuOhj161iNAGAfbTYYHk+1jIiAfRvWaFnpimG8Bc4VDueqWFhQS9CEvwp8Wtwfqnt5WLO/PWcIqSdKETa/P3ZciBGzHD+xTwB7XcGMC72MKn7kwv4Eu1+vHnpeRCcdNBOhgxlGYau7ZrljaiXYq9CPicE8CUeL5r+WcKp0tKM01PI32/VoHBp97V1cYWq6PyO3b5bUwHKFCza39RxpVWajVq96/FvEp69tC4QA40a3pPzSzz7UPZAf9bczM2axGmfNTomBMjvUO6KVplseorBB3dUpgaBJUQFjedSf2QdTjNRKiEgrmbbrRiB/e7NmVDC5rJRHW/WOD/CSUvoH9BapoQFQmL0/ttUduxz3acf21nzsET4JgyDdQKEn9+hjrmRS2F2vgoxUTUiHKNGEcPvuIzZ0s0wfjznJD4/vSKUfPu1o2fB4Wep23CXpLsd3oPS1fsF3PMPbGRq8bdJPZAkZaOsFJUq6+uDbtHx2+9YQmNtiyeP0NeZpVj7HW/EvplIa1UBJw6AJsLQfztpNBiINV3U1SF304oIx2uTcCa9IwpLNIs+T7h7Pxt0No69wTriGzKZAEM8x+e7Bjhmwu8NOrkoIb+IEXrJYx9SlrksutYYu70FKwDUImp/0zMYZQQ5WbyaK4qYFXgTGnevzI6Ar1u1NlxKXFZgRNlQaAumQlEfiGiMceXbFzHA+lotgySbVM/H6E3O5pCTD/ZEkMWLurTqhQTYJ+eFHABcfxwqPSJUzeBolMgNYyevMqr9kF7u0z/PHqF20IzJH1vZfldX8nIc03AZpJ/uw+oxiXXwXqAeflSdv0LQi12pOKPQtmX2cEGgUAh0/Nmy5f0x7lf2JsaIdSQnjwChbswHxSTjD1H3MA5a4gNuil4MKjHGiIub6fE356k/ufshMR8Vhvy1enQVM+OXRAeNZ88HmGMMw8Ru8pyuRcW8ra+uIhOs/juJS0ZEvxMHs9dAgtM5Gv5zhvTCt6s5DbF2HfAwDAhfsFofZKs6avWeA0whsWqubwbiSOB20ePXGFZ/EKEBQHM/1fjYthSHLkjz7633zVPmO653X68V0Q+FUAEru8DP96vBSUQn3pjPqFy2YPm+RC0HaM4bpJCU8xdBNVQwdyXQyTsbE1XhhL7m5LzwFmTtInn2V0ewCR49W4f2RxXxMy4ZJSpuX8x4xLIWxwGsW0wlNmHahG4qBC0Yp2nJGubEp5RP2Kj0HCeZHRdfAXDq4tOgJacIK0KX1lCmbG5EZTu0oqkjEKfzxxkP1wTQtVv7S3XhW6zpvnGpx/JDi02t2WkJi36vg+TQH5K0jJmWDxhbP4Xi30BAppTsSh9JbaLmszHCfF9SxbRoSLLNyhlsWaC5v0A1vTFesHZLbpmUJt5ZIgrXgPiWihsLa6xr92C4o51RP4vsH8RXxAQEYBhu9bMENcawgXwsoz9HHgG7IceM+HW6JGzCaAxDBxO9aiqBiVVEKaVcn0QviTkoQkgTPtzrFixITBTDZxFQEW6n+Ls5aiyML6ZUURhm90lqCkiZ5eSIi3TH5rn6CEaNUySfPTkOG62qOgoiAcL610FBWLREUglfYpKEUah8+IpsqdY1DWF2S4rZPlWUOA/6Un2Cr4tCYcZoUdr6pfMeZ3bXV/uXPeKpN+X3t1nmXmMkoEuq0AoMaI7muxxhsJe93hniHcRtiodnZ3d79YqCyHh+NNS8g9IqBt9+c3xsiaW90QL6/UBwLRBFFK8bGmDTxiZl5rkFJQMXQrMICv5EC5a7GZOgmZQr94xP+4oYSqK2Bp7BZ4EK+MHXg55XN24HXgiLPdLKn+C1EDIpYGOBIIQgrd/2M9N5SAz3SGorof+y2oNIMYba2l3DAQknx9W4gcLsLZp8BCfhHH80FDpZTE1E+nVeFrHz/SucneM0LrU1YCpkQupPcN6mSK6RIpbsb2I3MNO6qZ7DiewUHBdFR6bnA1KsUBaaT6OJjbuoYT7hGiMlsnfq9jMy9Bvr6BsuttK65qZ7o63szE3Wd3BWCjXLb++mwI0Lz9LktVq1agINdEmUhDGX9+TrWYPB7iPJ9m8MbHBEUOxYzFRqN0YuYpUSA7dSTtsaXbO5sREDBukEEzGYcPMzEctrUL5hE1UtmPjy3zTiyVqRdJnj/08XcWAJ7v50rB/og0jYwPTdckWYb8AjyV1QRMJwwsFE8uF4Lyh3RFmlj/kkIIfIM7MC6MQhM/B7kp0TbvQp6Bgwkx76DEbDKgMrTCqhNBIDle8WgaiIJ9HkQnbw3c/cd5JYkfIefaBbNtiEpthnE0mCBuDBcT1Pqi+3ISm7p+g9VzOAJqJOVdTDlSznpVQTEaYg4QbxxoRy1ZH5G/X31pAHSSD9n88ulLxrTov8Eo1CNi+uWo/VKpJUhWjEAaR08piWDLYOPkpGR5xxxVuNrODKEwe33OSAeZKxmSfjTjgONKsJhk9TG3Gd6ldoEhgWRfFDEsotiA8JTikPJzgeRZmCV6dGWg/Oxo30e0IcQUMf3nBDLSsnb+6b+kArUERAF9Gwy0i2EkRnU5Qml8MphJgSRecbXDYCMMwO/IjbjgaCBAzjkH4lbKNNPg0lN9QUawoPpks9dlAnQnoEEMIZdahd2Svo3/QEw28w+7Bqw3XwzculAU8GJb0PkrRCDfbUPCHtUoahBIaIPyp2WIekngYB7ReCqAAAs/9MFib3L+tXOJRWHUZDKwTwjRXnK4hpJApDyg3kFDSBqQIBdScAVf9FyJgKIggVRZACFumNcJMS00/P7MZ/X8At5738onN+xXZjTU2NIwYx0GhEK7uzrTTo7AaGEKUN3dQvTAsLRA+5M5mNYWBBY/jFITYhoxav1CcLcR/Lz3U57kqb+kgFyS0F+fGh1Yuo/de3+qbnWfvNN/hUrZj5e3cKxHX86ro+ckQz7bUB/ovsef8TgFfxwj/v1x+Fw9t0XcXAQLUFxlRMYg1WbFO9dJ6GGe863FwkJOGJVcLb0oKKdnXBjGQZ1ccXb1rBbaTxjtbxQSvNUVdIpk96kGMosOjJIgO49H3Dd8GP2NjFcadlfaSPSFp5fXhp3tnQ4IOx/bJ8bQ+bODfMYfamHrHxxJNgBF2HXIZXFddsY+FK45HSa5UF/kHL/knVin/HQbqEJMlmwH0DgujbnldbgTHOIMpWyjxCdeHtAOMyOjlTpR4CWNEwFpfHhlcdhd+E0SDwGWPtx7ZhOXnvk01bmtxtDNXe7rlv51rOOs0d+YYXS7lirECHHaFrQrxwd+I7c6TsMEU7nsT3LDwlpNj+XBeTPPrdcLZ4CxTGmpX61zpum3uxeVoquXOrQ+c/lpl4vyUDXgeziYPDHsTjhXHgpoCcRWG9a/ZsiKNFD13otoQby0+aRbQz6QyUf2V+UGfH+3UIKaCNVAi/aw/XxPvCp/Ap5KUmhe7fmzqqV23qqNoaO/HXQHSf5veq5K/6AOmAxGWm0gc3vDJjSLIvmfVceeoXSDeJBjM3rJqJGou80FnmyoegxIZIoJ0OlHsoO+LVtSV5JpV/HNq0kFWPog3AWD8BH3q9mO7/xaLAgpWvfz+E/yrtE2uGdLquw3flhslEEqiNCbk+6TAsnY39m5iPm4JKVPcrpZR4Ai/bSW4uKHdsq/k7Xg/Bxgk7hEcdEuR2QiTVWfw1e9TKeJttGFHXkTt2+hehCzKP5E2CrT+KdRcGmjZXAJ2Lt8DHZ62Vm53N42ds1aP9lA2PxO/f/IwDbkPYbwZ+zl0RSII6UKTdKCDNNzybaSCfAKuies4sQc8Gla6o8Zs7FkYmn4yLz4+98b4SpI38sER4ClzzNiGXBhZxeW1267tDJJjgf4nP+myFVXbI+7bPZzEdzu7ulqJ/Su35E7/oeofVr+B/4fXaP3m3jR3MHbzoAjB8bNsG1lGcAMF3TclWI0rB92USbnar44t3LAVu78FvPuunj/9jPqkJwG3+KCvrR9HHzqPMSOL9+fp1U+vYdfbusNVLrfIrHhktz4bN+sCldGDyQe6khc6nhkShXHQNKd16UoAem0yiYm0GXuQffLrrZ8WNLRo3OnjRCFLbMsDu1WvNZP1ZVTTj60IvyHRqwnOmytyU+FjCnbAb3Sh6LC41KMjZZhfw+zTODW6w1lN+tOyYJfKP7m3nAI3a4nl/oCSIj4zOteoXBLi10iOzJC6qNvMd2twZh1fkYWWkOy1MRIiB31Q4BNrtLokEh8ibjNAIJidmVJ733uXlLeu5SMn+W0pREe+gSxF5+Z2u997tL2HQ7PzRz7Uiq2svGlkfHjNma77cZYjcqXMEDpVEH738/nvG+lLsnOIOSh8UEQ9ExOjQ79krBzm7H32VpU4yli+0vs4FypJ9jKxP1u71Z6uklR2e/iTvN6xXpr16Va3dmGWXnrYpn15x6VehGScW413IgqcTeAkJH9SuIdiFiZ8UY2N9sWxr3S5Dq6iaP663zDUe3NSfn4/EbU8fzlvaOmbf5V06swBBYMTY669teKEghfCtRP0ZGsXPhwcT6Jl0LaBOHCTwFOIte6fcdvY3Vv6R6O47XiWXnTVQgaPFN4WzmJcVYD46HQGJcZl238CH2gjxvuD57MebHi+3ZybcE/XueWxqPo6gW1Yeq/ur2cCOFieaNaQHAdxyvXZW3n0ajsQjtV264h9TpDL/0AYfmoWJ93OQM4kJwLA3xVNNe4ib2T1s7AGM/
*/