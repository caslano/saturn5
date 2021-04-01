
//  (C) Copyright Matthias Troyerk 2006.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

#include <boost/type_traits/has_trivial_constructor.hpp>

namespace boost { namespace detail {

/// type trait to check for a default constructor
///
/// The default implementation just checks for a trivial constructor.
/// Using some compiler magic it might be possible to provide a better default

template <class T>
struct has_default_constructor
 : public has_trivial_constructor<T>
{};

} } // namespace boost::detail


#endif // BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

/* has_default_constructor.hpp
Mh3gjLfg959uHJHFiCDE/hfbvTRHUjXeMFdctngibJnuGMNkgW+IXLCIoxFqNKEeMrgajMTG0rkYZCLzjoM0iH5FiGIk2ONqkRRg/z//WSiAk9vqP5M4hNFAzav/i+G6Xe8+vRTVUOaqOFYxy3y6bD7vZVUgU3WLZpb9AXsGto1s9WSzxvNvBthfVso64PiZ6kZsaw3bB1FaAb5fp1pXS6H0j7ljay/qUYW/aI7aJTGRBOae/jhR8veoXRJv4+gNrI/K72Lal3yqJgdLj8XQ5dEvZeehX2EKBuBbCQiQEIhHbrsDRHJH9U8ZCinYjXqoFwz4sweHsXfrsxlq3ZAsHc/NkvYoAnLOxHfhxRNnoYfR2ZkDoeaDrYuv6al0bopQmDiG7rsH0RxfTm6Xa2wdA0dPGRdZIjvepLx5VsTwuwrItHSUxy5yDdVt4jErVF8AUTDTiyXoJAd3hDvsgyarske3fA5hOr/jn5kV7Ng/mz8ho+19OBfoRjzmGHvmLZJS48b6c/y31MNa9LYj48OOPg/aCR2H0HordzCXskltSzaMELdEw9uGlZhKKA==
*/