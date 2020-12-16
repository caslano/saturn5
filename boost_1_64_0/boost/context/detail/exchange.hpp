
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCHANGE_H
#define BOOST_CONTEXT_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

template< typename T, typename U = T >
T exchange( T & t, U && nv) {
    T ov = std::move( t);
    t = std::forward< U >( nv);
    return ov;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCHANGE_H

/* exchange.hpp
nvlkahvkz5d7CqfKWHsv6FSCfJBtk8VAqJoiaaoM6kk3T5EfyuD90EbNR/34gLSRynP6TFmPSob9OG7fhxr5x/yiH/dh6IvF8MNzBx8lHEurIHhI6+NIqzr4oU5+UudRQAt/di706UAGgm9iS5o6lQbW+fnGMmu92jc0NqVzNMm6vjW09ppLq805in2N/n5Mt5I26d/LvR7BVZ9scinuwVwg+qLvNX0R9GXcG56k5dfJUBANAFW0P9Ms63TkyzAX+QLOUVUf4XcD5V9PP+yXG8X/v0nK6jk2XxfbPf6b5dTOstB0jZcq5SXc2y+expDk71s6HH+DA/WlcoCzJLgTxDwt9bi/OH0zpZf7Mhil6NlZjIWxUu7hrBC7/xWQ+RpXZphOSIzSXpTKDUBTynwaZZ2sviaywnH/9UZfvjjuv6HjTXAieDLebtGxAX2G9uDbjXIOt0yf4pmmWwNaUpfZC9Vxy/k+jXqhczPoB+WxftwejEvCVXzEofshYL/0bQ2s0/KPvBeqtazP/4/1W8n8mb01P4/kD/csGs09CymzSO9VmD44pUwf/CJIS11wJ1t+2Kb7jE0vmPxfmX6wsXQfMDL7HP2r80z1VTF9AaZ13on4VZDmKkx6pknTmX5dqy46ZeDYxLtTeYhVMUf8PE0fJXuGGqfqIZz/gw1OcjwHHkEWyGOokg3nUAVSVNNl14YPoE6NZbWfeeZKuJ0PNzp75RfWdi71im5HFd7mo20HqUBhy8m3yCR3DE3uCfDOEpumb2I8gvPIyt8o7puj5gV9efZUMnLbdTuYkgWW7NSjut6vb2M2SvxSuXf3t0ZXl7s/GaQvr3L7J0Ef/x3asK9q+vXr3bO/+XMfvnOp6TmerFsTnsJqvMJQesIL4qRoH+h+kOhem/hmj6G/P4XuqG24wdiTf8m3b7/xdR9vjM5T/yO4Dxt7U9XkeejPzpD0TEgr7uOm/sOa1AYE/CAPBS/8HZgj+NQOu8/JfBSNDTqySW03vEdl/Li5TX67jm4SXSn3bdxG12lLYXw0Hey71Eh5W18twfGbWCf1zRN8XW98UpPLJ4qn+X0+X9Nt/ltmMzz6T9N09gKCO7FFT953C8UVG8qpz39sk3+nmeOoir4f14Q+f+V2630T6h9tr37buD0zQ9+22V699ofIRXGwPxYQDPw3S5fLof/W1KTfVv0OMV3WdaWtvkFLk34LFZfxDM1Z3kLgIUoz6tsvVh4MXe1/5OEESuv6qn7nMJ3ANA8LScNcFX2J+gq+0FNA3opn9w2eSjh41vN2e/aT6td7vc4+e8H8gHjtMe+6OqMznC7k8duRH0+PFYLvhs4ZxI6dBvq20ulbLjWSRb8fQPZsjW079uHpkbZH/dMzja4t9irPFZ4usmJc6Rs+5xfYI62TysbX+UyiYfhnXMv/s1SnFA9wbT+fIzpG+ZF4vtcbm7vK6CreZ7P3AzqRhylwuwk3dl4xzT7luIhiE5X3teZbsk77lPPi5bs+Xm6Mb+XW0xTse8wQHvqEB1yDOR7eVSnKD/MHzDfwlXpHDXmYci46x9vUJPXA2Mbv32b4XqqOq3x0LKNPnjRzn+fKt2duTfh7v7VJ6gLcJMEwfab45y6tdgrnRYXqqG0ZiY5BrgtxUra/AM/21zY7dqJ4/o0yGafEZ8RmLq5mucBPZCh1TGgdgov4GF9o0vBS7u5WVmUA422x2RvNKQ7nxdvpgpEl4UXWh3aqbE16sRe1T6iHWGYv+Gu1ZvxdrOnqcJrwLH0uOz/m+36pkUdrjN68GPsAxoKN8XQZtE/n3Zi/3pxB3wx0cZ3O9tkrlEfAszy+Suuu1vmu0U34Ie0rovpOtOO/3/uUX4M=
*/