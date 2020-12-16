// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CORE_IGNORE_UNUSED_HPP
#define BOOST_CORE_IGNORE_UNUSED_HPP

#include <boost/config.hpp>

namespace boost {

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES

template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(Ts const& ...)
{}

template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#else

template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&)
{}

template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&)
{}

template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&)
{}

template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&)
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&, T5 const&)
{}

template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#endif

} // namespace boost

#endif // BOOST_CORE_IGNORE_UNUSED_HPP

/* ignore_unused.hpp
ebBV6m8cNGTPqsmPdArfCBHzysTtUDFrZrTLf52usIgmhmJUUn5xWLuXclE5tnFcxMM6sEvVoaB711QxMh0zkb11OeGUVJKtahDIrlfXPDip+t/O/M1tA33nx/y6EF7SAJYlF2dyU7P5Qg3ummzK0Zpn5rYjUaa94zyDzXV3tekVVVuFujx5hpiDy9Dc1pf49fYP92d7hoZ2DQzuJCp5nPnCxN0X6ToTcbCvf9v+HTYNf5h5GCiDe7J9h+hl2kBvVjuDARsa6KV/afJw38DeB420UI2wSqbceWpgr0p11GmE3KUjI+xwbuvIdoy02Oz/Bxk2/Y7bP8yZ+FRmBzqb247mu9q3tje37YjU/7bTz3xz20yJpiFU9/ChYa1gosW/s7v6ewaz6uOWu+kPou4iDfYNxH+S33pfdri/d//e/ljD/UP0acqefUq5+wcHevf09Ssm8+fuvua2PST44cXmtpy2m3zhyAiX9aLekX2l0lQ0snuY/uzo2tTRvimzWSE9+3bt3t6bGBz1j6TtG5BhrbWl9/yRoUppguIbNm8nX03UvH5uS/eGkQPFGbpMFzXvLFajkcH+fdsPDvftHOna1L2pI0k9MjvdUq+EjnaTigrRvqljc3t356b2kdlcpXr8Qro6tyoh2s5a9HxwVxr7aC1Ho91naOT7LP3cTD+fo5+ryC4+T7/vbHZ3ptos4mhxJq73PuprB4W4Mjxmf2EljtlPW0b+fbJ2Mkx/LUZ3mgIsdlDEd7ZpTL6JpJ2tzobr3H/TPa8R9bmq3GQ0Hc4pXxXnlAdTBn0UdonTUe4W62GM3xV01HtnicuREoP0m2I5em05OL/64teqvOJPl1HQhrDO3xF9Dv2cFyXpTPvu2Q637p24Nhnw0jf6fTBTZkoXlvmHos95J+eJxa33/jznl9IePxHbY7fNr+H2oJ+UvH6OeQW6zheMrtNsMIPt8DBsBzQcXtuiXc0cx3fcVF0KubHOrNhOvxbbaZjzU+mOM78U3f1O1N1+mx++/+G7NRrjI7662288/ju810T5QhngTiSXwX//dYjpWp5dN45ouvkA0uxM/EqtkIe0FxOPTpcdK+XnGyx7Vjjb/dvKRmNZK3ml1LHlH+LY8iiwyeP5lp/JU7S5f4k2N8Z5lo5zbCiljg1NqySbyyf5HcfYUOZ+GNbtBMgr7L/l4+y/l87mU+bDk8S6jXN+l86Oxgln64w1pvJKgkmHeZ0i5nWY81LpStPxgVOAFSkMVGF0MgbN2wjoP6V8XgW6Llbntd9+krC/Uy7t6k4U+yanmdYBtEuZ1q1oDdhKpZw2ry9ZJY0Ns5RPHFSpwT7AY4OQzzInnxZPX/FIolKyVnAumWMehUbEaMYbwChf0HVA1/Ih7sq36Qakcn7Q8jHr5N+ATtWn/eS6rhL7xGN0mdhTra6cq+TWJ3SZjzdYnrnUPrpGLM/jOb85p49qO7ucsHOXkM+S+L7FtvdCpq1TtHrLdZj+4696hnpaK/avF6lyXRiHgY+Uvw7PGF+sMO+9zZVEUxGyKKM4kb78b9O8NE6jfXfmHB7y8M8wXkFYvkTiGDDf91P0TJGAspHzGqb1XTinhVG+IcYQ1EN9Z5QyGCtWbfvPaBpdVNL1IH9kBeV9aw3jURiPfQfEWLOnYSq6HNkQtPk1ZxsZ1DUMg/1uiMHx7KmoQuII5TBWY+RfwXWgFoBKkHy33tPkWiQbl+v55JhHY8l1oAQ7BhgHKzXt8wb2d2L7RMDPzWljammMw6e48bbmGaOYFFwE+CaptifzmX9Kb/K7DNJx8WycJi4f2kqIMQRr4cjKpOy4FuBDnGF8dsx9BzZu6FwFyG/SYFxMGJPfcnZwftQ=
*/