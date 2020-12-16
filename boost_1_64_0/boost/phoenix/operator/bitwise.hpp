/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_BITWISE_HPP
#define BOOST_PHOENIX_OPERATOR_BITWISE_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (complement)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (bitwise_and_assign)
        (bitwise_or_assign)
        (bitwise_xor_assign)
        (shift_left_assign)
        (shift_right_assign)
        (bitwise_and)
        (bitwise_or)
        (bitwise_xor)
        (shift_left)
        (shift_right)
    )

    using proto::exprns_::operator~;
    using proto::exprns_::operator&=;
    using proto::exprns_::operator|=;
    using proto::exprns_::operator^=;
    using proto::exprns_::operator<<=;
    using proto::exprns_::operator>>=;
    using proto::exprns_::operator&;
    using proto::exprns_::operator|;
    using proto::exprns_::operator^;
    using proto::exprns_::operator<<;
    using proto::exprns_::operator>>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* bitwise.hpp
DPSNvkA//hsBFauaO3i/7AUiV9YjvMk8VfxtKa4YduLWK+XHDPxhfkpIqhwtC0Qv6jf7JQo/SJ5RkSgJaaayolOlRO1h5aR7voFLHNfPCLr/fDf4Y6OlsXu7k4ZFZHcCRF5UedowC/8zs2DEZAPM90+0KcjP5yEd8R4T9G8bu2JsNNNKXhXMxrI2dD3qkhHZSiz8zV00IuwhwQEnySkWJyvVPdbF1b0NP5NtbaY2VLfD6jB5z59yu6UMPLUvoIsUIJCY8iZm0A4ZM5TtZDsfbL8FzWNblEvgdA3Q2zg9S6efoU+tobHWkaLZZnoGvVEZOIBcrlxKxXxQbBgi2ghnca6crGLMxR/Sa8L5TI1zuuDcFGWcTQQKB3DzTNifaL/vqK3pKHBhRDJ4eBkf+sHDVhffG+oGTpR2bhCXbaYiXqAWKcRxcTpdd6eQTXBxYkK7gSVunJyJogjFYl93s7DYRvR0VGEHsndGJg7wX9J3LNrfZbIwiPpoZZQaJVsu9svyqDp+/zf5IdP3Q1bdSec9sJl+jrjSHuLPjKNeeiIf1+gHTfAfLFlr1ytF/bgaHwMZ4bIeHCJhwNc5JdJxWqW5cKCNAV9S1l1fmgZDSHGsoZ5443RfeqX5A53peeMk23mjGzLhUEvIz2RZVjdgChAMmUrJzK0GYJXess02oVz2WtKhdZGSWeSDb7bjyw+jrPt/5B3iz00kknihJbvul3KgJbr5xDo6Vs61iFn9cwl6C0pbjrnY3oz515pceCn3UejS4DNOZZQ0XJ/Hl/zMOo+33CluH9H6wHKlQxn9f5J7GsqPy2VORNrrZqTd2XXfRzUGrHjkGNg67EaCrdGh/mV03Ajh8IRaII8zNJHP3XT6OwKnFSFWLKs8CE3qZuAvLZeVL9fNo6MJxMHqp/9pvdwDfj8v9w/eoeVOi/2fJq1sBGj+nJ/JTm0I4/4qN1fAq46bY5HcMeIiTFx6BcYo5yPHMP1no/nyaKk9o2EZ2b90g7QgX9uD/fOn1lXsojtEPNKvydiTa9H/sY+ez9WAPoT6ZSPLM9bKDfp0GFVnUN+ZfyJDzmenOOEpwGNT/TZvMf+ALMie0i184ymBkUMwj3yWhqW4LG6Be1aDu9NhgUtX4O7FtPWShQxvTqVXXlz0tUslPCQ8sDlxD6nON2RofkMgru4giOhkOM5m1FiG8Xyhqc+t/BdSovUjBWQQAECpy/JlTrU6o/k2VvTDW61lWXj7V80S4niOJv9XtyJ9IheAdue65GbQ5TO3vphwJSzfb6ZbvXYhN3jeWzwO97lhWMX+trjJcoZDhwaT03+gu/GowJGKqTdvYa48lm7vTwE/TIE/xQ1pH0oWG1W8iyQK527nIZf0llpM52Xd0y/72mUI8mMpTvRhJEH2alvryMK7Eqky/sRGf9K30ZHtjNVvXCSYYdZQAKkYC+a5WYZVgXL8unAlHz377cTFfLy4uueK/YTDNl10mXbJwPqbnPkGZH0lUcgFfoYxwrT2XxG0dXtZDDUpnN61xt7tTIkuu5m73ZORqtvv28YNfMlIgSeS+4wrDtXaj5ZF9UFFI+1py1RatAUlndudIUIKuUt2aHt9vA9SbT9hpHI1Un6nhdQghdREQ+1ZR94kVruF2kXvrQrEvhl9Ru3ldi7/KfyMelkqdyNB0D145OOaHtG6/8VaRY9iQcKSqj1GVTEiZdddrGpBHTrB/D7DQAdwBeQauIMXw/NrbIukAxZJO6ef8FjfRfLbFVzlYSmr3PEmVzmCNtz2SFlrAwjAGuHMAl5kX/krzXN19oGeks7+kYJ5jO6p/gLwfgXwZeIOWl3lHRPK24MWOuNV0YkanbANnR9yaXWJu4s=
*/