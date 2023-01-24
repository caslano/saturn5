//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
KH4Ctw3RT6kkBe56d+HFrlhu24s4d+Kg9dYma/qRCu4199iX1psd0G78PuZN+J5T4YNEeotF7LZu+tiVtqzCN7HCt8IeXp/oz493yrjJToUvJbzeLtZanPI6nKg4a0WFLyO83kZXbqQHMsJX0C/cyV9qdN1c4Rsj5SUjqCLWJjn92XArg27h1VPdSwrlC6m/pkPuV+GjnRfmWygDelvWwrRvAhimrVi+TBtygzwLvXcBkDK9wmf2z4O/2RZ/tm3wQZatsi65TwYigyw/lUP6IMty/RFtkOWFNjX4ZoMst6KRP9sgSzbliVm0fQQI5WWZ9spEOU5rhzbKUqyVGhllWcY2GIZWH/5Ka/XpWsMoy0tf6eZ0gMY9+5XeuLraSOO20EviRptpS/KmGGjkuqHyXfqjSos6krRUNUmN9PM+hBuU1wZv5FJq5BKtkQsy59u2jNhky7SvS5THadQr2VBt3Kb4LW1bM8Kr5z6y4Rir7JnS033bvqJHa/tHX2ptP/O6oe17vvxxWbuKQHDuh0yapt9vUjV9SIXPCvn7ui8pf797UCzCdenSCl9OPPy3odHNcejghCueIAmSPKv/2umQvVf4rrOUqZdyYkkac+wMmWDXEtm1YSTXp77QWjn6dWP68c4X/2EzRbWZ6yuNTXzwC2rimugmdrhmlSG90LLrbOlNLvx0AO3Qsk5XPLe7MmRs2PJTvdg2rWFwDRqF
*/