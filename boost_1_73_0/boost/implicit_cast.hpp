// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_IMPLICIT_CAST_DWA200356_HPP
#define BOOST_IMPLICIT_CAST_DWA200356_HPP

namespace boost {

namespace detail {

template<class T> struct icast_identity
{
    typedef T type;
};

} // namespace detail

// implementation originally suggested by C. Green in
// http://lists.boost.org/MailArchives/boost/msg00886.php

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template <typename T>
inline T implicit_cast (typename boost::detail::icast_identity<T>::type x) {
    return x;
}

} // namespace boost


#endif // BOOST_IMPLICIT_CAST_DWA200356_HPP

/* implicit_cast.hpp
D7FivMcEaKX6yr+Jc4Y51LGU9i+d5F/S8UoyK0zncmTauVS+kHYu7VnnMjXtVNdyIoPGSifrMnozfmW+Js68Opc72bEs6VtLzAG6bxAkw0aWDB6avbibzvWdBKbMGsMmGmUmXuQN9PoJnz89wusitcTYqOezyC2lFvqTRQqW92Fk3dapW4X8J+7VHy7iXSyRG8T/zJIxHBvjrSw7818ASHkII24QRvVZJna9AdcMGvhyHtgx
*/