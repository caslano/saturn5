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
nio4IVQOwOr/2zkpqMIB6CPfyYgho/d4+sg+Ee+7OU8cuQes8b+XUsJG7UGj1vd1YpiIPeBO+4FOi7cTAWqHeskPdV4ucy6sX/aGWd0/nfF0+XRR7do8tds7ov0oo22U2j6gHvLjgsK77dSngZ3ET1JaqDhHaB30TMbi1elF1w3tq3+ac13Re1lt0Qj2bEoNsL8FJ4g/SynJ8wbNfdCuWl0m6jM/15nxrS5sRXTtfmGzklD062PzTSkVjJu/dKg=
*/