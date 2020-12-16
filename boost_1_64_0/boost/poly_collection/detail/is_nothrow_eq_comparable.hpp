/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_equality_comparable.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename=void>
struct is_nothrow_equality_comparable:std::false_type{};

template<typename T>
struct is_nothrow_equality_comparable<
  T,
  typename std::enable_if<
    is_equality_comparable<T>::value
  >::type
>:std::integral_constant<
  bool,
  noexcept(std::declval<T>()==std::declval<T>())
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_nothrow_eq_comparable.hpp
VZrzO0Wam1L9VZqtdxdpbkr1176H90Aa29eR++QIuu17iG0M75vn7wnMJj6FfyH6Zv6Cw3sBs4m/4C+JPs1f8MS9ia53m/QeGs2Dk3Ry6tM8Zu4ziYFjn6L/jOi2P6Gk77kv6Jv4DH6Z6C6fwUffD7Qp77F+pqFtpvoBS/PA/S2sS3cm7K4HEJa7GcLrkGZB1B3lv4twDhX7sYTpP1Bgbqwqy/a454MIzwY/eaqRfKA/2IkhT7WWLsduJ4681VqQker/IW4c91jjfX/3w9x4eK0pTPxwNwZea6pu/lJjbrilYW+3TsNP+in++pECe+NtjeT9y0dNxdOMruf+/Y8hrHMLwc6fCbf5Fo+daz+W8K7tKCvbxccRbrNtMePb2mvjeRVovp/fR7hNt88a/8fHE376Vo3KR3IfILxrG81wwUE3jlpZj5VDE7gJn86Lhx0YGilybvjhE10Y3vsZvyc5sOSLKd/A+HJjX8UNvQAOZnW81Ka/81j+9YnnQWh24E30PS1GPzYYZ3hDKBQuI95+ZXd9pemLhwbS58gXfqL865rHhcjAPuJ+lxM+do0nF7ev7ri38x2MddzdP7M6XsIH5t846Y+3tEKOLso2NImB5gqc4z71lUnsyMJqm5gby/Uw6lq6bLscPoZra/XOQyp5qmxrT9dnxnTMVh9T85jQe55hYFbXCCJ5tD5MtszmwhX3g1Nny9sMm0DqZUU79Tvd//ts+e7E72p99jcLBxPMGyiP2Gfu2SHv3EZZ+QzE+MNecSYMFG2LorE7skS7haYdReiLLsIBtWfCFqVFXpxO/myStlXTxMVVg3YrRaOtK8nz2FpWwQobT+Q0G+PX8KiibeG0Thk8U/Rvot2C0xDBY0b63NF++7P1/VtE7iCILOz9ibaF0ew7l/4OfXcXCLqFewylKgvCgAdk4PwxB8SYCI7F7V5I+YAP8uF8KtwQFneFISPRb2HQj4GNTntLoulCNonFue6t0APEM9LQQfS9Ovy5g2OPLv3tjmwBXcZJaEaFon1G0TAE5wfQhDVt5y0YjXhK3ei8po1qmsOX6i81pj5awNCbh66taTO3rGl4fqxJDbGxPlC6mobPpPULiWsvw8WlFa7/rG0lHGn6NlDK+o8a53I71rpH/1aEmTptsPc8CWtPsTK/k7cmuu3CzPL7IWGmTplM/uA2hJ2YgjXmy4RxPYEk1/OHbxOYG0+nSv924rmMTGe67RQsmoeX++uEm770sHuYtxNYVxfQ/ejXtxcYg6xtGHdQtGXupCD792Wis+doWnehtNvuKGiY65lucL7+5uxqav3+1zO0DyCGxHDA9IZrM5JWr+tD+f1jJ9X3tQ12jvsZ/b2/AZ0B209ol607yby+yNKt4yT8NIvV/RZ9hsgelaIeAemBP2Pci/iIXMcaLXdhdYgdkQKO5Vp26r2WP04ct6t2lN7cWgbu47Njj86jatsb5wdzOQ69O9gpe5hZnnr4WKOawmvmoIylG1G6D/J0ndDrpH4YpVnoPfVA839FpRC/k+tSNFJ8hinx+bLBJ/YixBfuFr1C8WleoKV/KU57Dg5PSGZjyeuqxcvHQh+U+Q157We8HinLdw/G6wl+ErW7HbwQvbHy/BV4QjdgWRd/seoiaael7yfdTfOl2uBvhm59H+fT8aJ2XEVlGCg+sj0OJ4FgQnU5kjLfk6ffn0ZRL+umkVeXcd8JU+ZdRl5drxt3o3YWAX3QldvhhfFZlmVLyXzE4ON7ZZV0EG06ZHzy5snSw73BOc2iQ+lnkJ7XXR743aRTpix9dawHTzUx9OBpwYTwVLkzXu4yTpO4HcVegblUyltJ7JDnty+Ah2GSFKhh0R4ErmQdrRk=
*/