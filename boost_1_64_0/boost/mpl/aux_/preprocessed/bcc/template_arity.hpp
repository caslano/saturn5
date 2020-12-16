
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
0o8hBL0ojZAXJpM2F1b4HEP8wiVmlEgiiPiz5Zz8DFeEA0eIXQBgyuo+ycExjqC7sOrnkJxHFgUlGvD+bUTyzlSHc4IhCcH7lQ0QlCT9toe0PPQ4DP8XCMyOCXq2r5hAQ3BIS6OWg6oZvZpm9NLM6KlmBKTkEbsbgCo7rf8Bh91fG81ke3ux90NLEMcKg5AQVczXc8lRiU/jFnPRfBhujrEk5ATeGqvGGo7w2Z9jmP0TBAYCp3LdxQQxzPNJInxttsNbEPiID55xCS3wo6WYUW1lNdL+H5kSgvDOktQ2xBaEhSTt4R4BUAjCdkXAEXOr7s1B/xskYaUc5BMfh4YTFsGA4AR8VNaoSuIVGRmBe8sQ2iNDEMgh7/+1sPf/WNj7PyyMPPF1LCwmZGH/Z0ZJYKWkdoiXanwvNHUUhwq5Bn89nEBAAcoBCVaHw4VipRB2LAZOcysW9V0z42MpEcE0lKSDrmyb0NoWfMCSJ6uXwsLLSBGM6FiI8mD45OBSCB3YF+MjazyXvxdMpv2cMh1dHgvg8NggpqB1lEYLceaUpLA1SpItTUmqo7GtWaATmeNPA6hIePqkMjwBgt4IrIMiiBbFz2VjBg/B0D4VhWIqjNaoaNwqFY+FJL8HkqZNeE1YRcKWqwzeSD4/JKCwy9LqAqvMq+JTMgfgRQKFYZEqqJgV5fgHA9VJBpNGegFk8CeWWnzM6kJT8Y0HoYIhFAxmWT8E1uaEVltABvREba4ns1KrW2BNqhi8KZakcXiDWS+6Ip9qXyiJG/491R+hhupwFnsNfRRbyrdyFHZC/bwkT1wHcDyc8mVYVjXi8dCUMB/cLpcwLlYHfYiHGMEYZjKEMSZjGGAK5I8uFUwpi4sTqCYdTs+O6tLg9CrBqFVtFI3SeZiDitgQpjH5YFZ5klPWzpPOrqVTTX1q6fI/9UjTYaA0O64AEyz6RaBgRk6iF5KUb3yBFjJLzQKkBn6A6YE/ufZOgaBlGgptVVjQWp0LVDxNCG+Nyoq7Q2VJPVIzS02uNL17tScn8FRN1BnHqz3jePIE4wkTjFdrgvH+14SCDHHYWhD/f4ZaT5x5QC/AwrUsq8ZkXJJQox/AlPgHVI2AAKUYqMKKBHXgg1NjhIPzP8Y4ctQe5fHmr6PDX5AG30GqeoUEzY6wYJsXoHWgg1TojAqQQQcB8ntLzYhpkMvhVPULfClQrFa0rODM7nK2PC9iRXMtKHCUagN/ir4BC9BLovgIqQrju0wpYFsKNm28CuKFlhQQ75OkoW0pAsJLhSrepWBwUhWDj6aBKRJbUhofOoqKI6GC01NaNak5pVF4IygFbOpMKT+1ZUoKiE/K1Tek45uqsD/4UtA0y3SldNe0VhWbMXrEZtNHpuMKKgBD+Xz4nTJOcj+PMdn3OQOL9tD5FUyVAkb6MMIH6rBpxg65PCugoWGY01MA3LNTMRytAUPwTmgTfsFNGXfhgiIcnRwIPwCWwBGK5UAEKNYTAU20KL7v638QIYNv9eIcSaD9ba4AYMFbpVs7O6e1dOCvTXS04t4miqlotbAKxyI68fkG3G0JREOCCvoCFDQoj3Eybh6OMbpKeHu/Sja1Tp2ISnCFNLiGXn1MqXCGe/Gto+q3YiRWOGMoKD+PVlg4jlMwLLgkLLrbB1vLHLRP0FD50yIqL1QzlV2YrSLhBSeVUcsMmOFqlIHdFQhrGBkaHpAhfEQA+69sUVUw+F4LqlRwfDNXUc1bgGm8BZsG7PROBGMBTQY3rUGAq1cmU7oULqnWVF1UIFRUL4YkpdXwVDyax75GRTIePh+bT5pcqSp+RisZu4D9DrxzrlxXqoukWyTY62Ogypjsx/FtnuhNj3Qehko=
*/