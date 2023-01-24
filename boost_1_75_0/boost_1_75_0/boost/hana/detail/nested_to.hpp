/*!
@file
Defines `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_HPP

#include <boost/hana/detail/nested_to_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_to_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(Algorithm{}, static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_HPP

/* nested_to.hpp
6FrWChR/0On9rPb4P/QVmu2kIgH0+sZwiIFBXp5GV9SE4tH/Ep17Q8dkk3A6kp4GEdwVeh81/J2++Cw3n1Ep/FOWkW0/91SILsRglPeZYMQIccEovnmQsR7GKAH95xpVPPZpxCOrG+WwktB0WS0uj1XGFuHqcEMJ2Z8G0vVDWoOmy2LfTdhw2MfVfUJnkHS2j5r/9VQjulTZDEuFsxZcg9fvaSraTX6Jmn9QXShprOsAmcvEIW0sce++mK4JYWbRT6eJrejMW9yOTZhLlxm4upm08bAhcWmEyVxcGqET77jMPcf5vmRLIxjgL9GzXEL0wC+ta5gIL6P8wiOCPqpB9yOJXomtkJymKySYnK2Q9NDecfISgpcOFWyFJBKLhMLXwdZmyXbGhFRFC/IvClT70Hnz6JIH7mdAYaPUwugyCSuM6nodSrajO5TsfB0sQz5A01MJSimx1LaXKeuhQSaR49wU6RveQj+doc4AWN+lzIIS+ecaiaxdNJlNRwMqkTtAxcRh2LQdJXKM7I8DWxzrjbNFZ+/wQqfP0HQ3VmTorDqBuHJSaboqcm+nIhdjg8jF6ChyK4Wons1esBXRB4QVmLyfLT1B86mLVwf7lDHhnO1rvgsHE3o5TWXwykniu0O7bFy8hVchq8SxdF0Kzfzpl58K/PpzdvklFDmjChl0vmntC2fCvICK4YvmBZVy8LMEY8TXBvE6MB7rVBfF
*/