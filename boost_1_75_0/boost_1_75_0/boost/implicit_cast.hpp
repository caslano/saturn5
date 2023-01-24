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
temR61/GfnR6bcfPZbBsv0SHohtirSmdo3pTKY9MPzq713Ke3GcbKL7TFuqwOawnsaNoTVpvHekL+CJEEq2GzE0KkfxdO1X8afRMF4ecLFfaNgHV5zYrQhNCpGBAqyEKH+AC2DHLXSPDhbek/eFaI+6/Uu/Pym/0y290y+Md3pvAAPzqvJTcgFAH3oHwZu3jJ//dRD9zpdzFsSwxdLAseU7fn3MyGKMotYBkJx+xreA9YqtXnqJTsjziR1WPblGTZFowN5/D7AZxZLHWnI0+G2GoYAVwpnkQ9NqHVXxg1OZT8QeGeyCGILG6/jPviN8Ow8mv6nS4lkWC/nmlr+oIlMu7N6XUcKN8IEol/d50s1p6O/XZOSUmtblzVk7130QGs2f8sgey3zy2uZRdYF8A5ajaOQzPNUObs2GOlxHvTD1gs25Rv2DGklAbiYLYROEUV3RZU4Y18nsQURdi3c/iqjTorM/1S/rL+hvFeXfOie/v3tcLDn6esG5B6Quw5XpBJRcnM51NykZ5C8TyW5BBT/j48+j9XsGn6i09YPGCKRWZ8GwdAQadnnK81I7QqDzaTZ5Np5fx5sX/myZbUUPCP/HNGedLkkmkQ4QHLPF15ntlf0wx4u9w3OuCXDbd3mj4szj9frZc/fx7rk08RhO0YMeuOH0BhlzFMP7suECPEgZIn0vyulCnn4mE/8+i86qXpCuRVtq12nnwL0qy
*/