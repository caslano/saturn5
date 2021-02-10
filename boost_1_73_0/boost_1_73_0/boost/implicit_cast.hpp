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
+HqLkJNvf7zO+nYmpLogl3EaOp/8weScvNksUppL9tKFCvJzFO1MMLEipOQOz7zQAgoCniupRYF6YwlS/WUydizH9/SxBFmqRJaUYQKxytFUhwEDbZJrUZJloQqWJCskL0gKibLuXlwQAjDOeep5owuAKULRsyqFVqFoho+lTBD4KS38kYe4w8BFWqhEEuJyWSQKrpmItfwl+bm3CLm9raigl+OpM7y9xeDeSiq+xLaTNRUtyHYGo+nQokPb9Uqs3/IVp7iZkKOysFdVJlDxZ63nyP7omq5ttW4VMbovUs7DStbYZM9yXluuZ4+d0u8euwR51zqvYCi2H6+kjh+ExHNj6tj/dDHTHNVAcxbcsQU3JneLQZbO4wX8PbUtXz/P7xZUciaCiFbSMCYDWlXcnkeX8BRHhdElpI6nIuM5lfVe+vWWIgx/ZaOiiJ7Yp4+bwI0PuqyPPSuPZk2ajLX6jJ1TuAHH/GJ5DdPHsiH4YKY6SJsJd9g+rY9LcyS5MnatO3Fq23qLJfxs5IhDhrbNtRdu4N5M/DH9aA4+W84QOp3yyDLBWRAZQbbMs5SnCmwHRraHrXk8KADmbD2+mP7gCqnp/DTqZnyqeq3bqdAl/mAVzXPA94KUWjaXpm+OqOW6Yxc6lc8FjFNsfEy2
*/