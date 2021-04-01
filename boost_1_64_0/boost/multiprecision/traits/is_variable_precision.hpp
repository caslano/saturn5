///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_VARIABLE_PRECISION_HPP
#define BOOST_MP_IS_VARIABLE_PRECISION_HPP

#include <boost/type_traits/integral_constant.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class Backend>
struct is_variable_precision : public false_type
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct is_variable_precision<number<Backend, ExpressionTemplates> > : public is_variable_precision<Backend>
{};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* is_variable_precision.hpp
RMp8obl87951sEV8xFU6Ho0TpUZGWEtLy1X7pgpVcD2oldeFTLHLBkDk+u4u7GBsY3bfJAbKdv8fezln0bqwFaCNpf54xMh/e3pYT+A95KfgxBPoDOS3B/xX/3G3vB7FhozWHF+8JYXZ9BgPlwVy1QNIOHfxnnhrS/UBeOh3kSWit6PJ37AjISFoIvsl6fmKS1gMGbjeb6uMZHmiZeYIF88TjQXKH9E4s4vMKVOHRiyMwX3alLjWmEREbfZ1mvhPPxSVIXOLduOcpXA6HlYPHjeqCTdoDTAAR9hDKTGHvExGeC3nHrYbaRGT2RDL/BZkpeFD7OD2h6VuiNsigfLJxKR6uFZtzz92Szwbst4QsZARdt1rnotSdX+nsI3A0Ots2lffvQaEHjvkUXBhPs2YiHpV+3QJpAlQJaCOFx9QAKHqCgGkd1UCr4D1kinfIUauBY9/UfQCbD3B2kO7wE9qqh1MVk/KxGBVVQjc4evoF0ggT46gZGRTqBd8yx+mKKa3hoec5+d0cjIie8elG39oJQm5SYZsh6/junY0ZcoaVZmyDrC27ERSQocXVw==
*/