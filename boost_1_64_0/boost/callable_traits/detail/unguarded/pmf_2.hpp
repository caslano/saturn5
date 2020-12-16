/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false, // IsTransactionSafe
    false, // IsNoexcept
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    false,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_3.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE

#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/pmf_3.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#endif

/* pmf_2.hpp
gufCrnAynA+7rOBbDs13nfmm247uF/KtNlLvUWip317b0e7vq1z5fsI92v2tpN9B5vunoX7rhH7fTFsR+R6JqIiKqIiKqIiKqIiKqIiKqP9M9bt8/+dOOv/X+P4PfMMvcZ3/X6CfWnui+VaG78E2fCx2e945J4AHW+4zUXMRzVlZ6q6XlSgy516KPITxgJN0H6fbb8kUs4fR+M0w543cua1yH2Sy7n2ZVhkWd/H6rQp0gu2XMPlcdt3Dz5mOVtV5n6sljLomfle9WHk+RbI+YyphAt9Yi7k6dD3dT59p4tPJ7I3/WcJqL8/cxjMSzTPJk0mlRSVW1ZnTJeK3pz+b/7egG+Jf93dquGnmjILvJNwMzzOzhuB+yVbsWem1yl7jc+/NIRyzP3YnclLVuZZFJVOySidOyhfR2YPf6YWA+zdVdtLTTvZV9sI+W+y3ufbLFxSxEcfsFbhe8q6e2euRJPJQc273CSLH+C+3BlTuU5WzIC+gQIqr7mgXNwt8nX3DQ/M1ZH+v7rl5Qc800PJ7QOSTyOc65qzFWAmzkZaxW9bzMCUOlfdpE4aoT8XNJXZt6zR7tF1f8pBhHfedDHkMT+keUviS3FVhd2Wl8TG6X/Yiyf+rokfyi1+Pjmch19X+z21n32mm+HmX2+FX286ZtzVe1rsBTFqpO1mF5lyx2hKvPb7W9gbbOR/gZAlnhJ0kbrjBQPJrkdWashhnVXfFuVTS6Zxf8brUm4FRub4RcjZNMS5eEbOzoxJddSVrXElO4fiJVrLuFz/3eaknvvHkyvNo7uTXveROWbWWPWKdWdgl52yJ+yejXfEgUVVnFr0jz+wY5dQJydviqv26D0uaR5l9yLGS3s/t0N9HSB6aO/WfEP/n+WaxqtvEQc9AdZ5RR8KYafbRbZY4FSG7y6qa2pvfhrl34GlxP6UyDZXl5uydlt/oQInDGp/IJo4Jlst9B/4z5+CNEPf3+9hFpWf9mrxFdp1Pm1Vo9lrXFT+5JkzsU91t7whJQ2PzO4iX8BJd58+dZ9rFYnFb09S7bJE7sXyroZ7BqnnCiukE9jClsEKt2K5n3W0nup/fwXLl8Whx30Zl5/nRLvcFEl8nDk3FvpVjL/Viiiu8yyW8ueHDY7VFgebpcNzPEvezOLMhQ824ZV/MerK+pXqQv4nqbyD+FombMkr/FO2LnGfFI5u8m+jO67nip5nbPhAV08afL/Y3qKzhBcVhYpk7vI3ivp+J03yRM4hBtYPKU8MgtCkd3Pm5RPwcY/qvLSL3Uln96xnA1CdR5eKmnruMnHhJnm5Ve4/8dNWrKeaZ14l9ursO501w9UEV2zQ87YNeFfkM+TXPYi4gRe/Q59wRtJwrIvKpco5T+Dv1t2B+Cwzo7sFa/PZE90UP1r976H7kpfqMXvBS19kkCw5zzh6/1aBz9iosZ8+yvA+J2RZjJu855szTNmImTbWeeeqY6XuEut0JQ88oGQOXi5n0aa7764/8fnPv/WRHfg++9xxM+P1e3nMz4faBhd8Pd7fMzdy9Ye7w43uOe7jmjsH7n0nN+tOR33d/pPvYjvRe/iOdyznS+/d/rf2LYeaoZG4pxa/vm/JtgIY56HrOfWG6X2wJHA9vgZfBpXAmvMtmHSa8E/mhgAwfh6vhc/Ah+ClcA3er+wPwEeTaPHQdrAcfhS3hetgWboAnwsdhFxjwNwI+iVwKn4IXwafhPLgRLoWb4B1wM1wLn4VvwhfgN/BFWJPyfxkeBf8CO8JXYRf4OuwB34LD4Q6YD9+B5fBduBjuhHfB9+A98H34GPwAboa74HPwE/gS/BS+Aj+D2+EeuAN+Cd+Fe+FX8Fv4E/wexlEGP8Bj4QHYFNo=
*/