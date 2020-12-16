/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC_FULL_VER,<190023918)
/* https://connect.microsoft.com/VisualStudio/Feedback/Details/2118677,
 * fixed in VS2015U2 according to
 * https://blogs.msdn.microsoft.com/vcblog/2016/03/31/
 * visual-c-2015-update-2-bug-fixes/, via github.com/dodheim
 */

#include <boost/type_traits/is_constructible.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
struct is_constructible:std::integral_constant<
  bool,
  boost::is_constructible<T,Args...>::value
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#else
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
using is_constructible=std::is_constructible<T,Args...>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif
#endif

/* is_constructible.hpp
tKYyGsdjVR8zZ3k0hijnt7dwhTCRj14CnzkkXPjRqB3T56wUJvfRnNqi/65y6QUeB1ltdT1XuNBjLDtOlK/2Md7GOffZt2h3h2kMBzaf+y4R3X7EaOn20Qh6dqXbwhx8Xi4mjeJ1xBIYtfP8EEZy2JjSNcLkPTIN+D2aj0EgK66+IKCHR1yD6b7Ux4iYSOKgezGy/Bhe1hqMdz5CN5z0qmOhBdehFff4F3tMrBfELD6dKr+MAh/eqDcqJCtncocwcnxDv6cuRNeuhYvVxsl1ITr5C7u/4CTY8jNkxfd99SF8qtPrQ2pvtEH0iO0L/ni9IYRBwWgFl8ZfVU/xRmG05cP2gV7RIraZ+JhjwuRvC7HqaRQmb1sIeY4wJwMMw7c1xjSZ+8EWPT0zF4b+25yD8R55CWQwRwJMLz+OOZz2u3fAw83M04Uhkwr4L4vrft5jZyvGvFCY0ONrE2PGRY96LG/HgKWtNk5P3iybbG+LoPvP/tRf2nMw6BxNW7nwUdEjt4pYY2nvJhsX6sL22LHZxtl9XO1tiaCLaVPHga3ChLb9VIpeeplLP5VtH1be9yKVkV8qsPg+kd5u6F3elmDcOzwvGb3CYHggbtP13Dpj71Nn4qIfmxad8eDNoefaMMPQEezXiKZr959Vz1vCOK+fmGfaR94Xeqbd0tLc0ty0/lSfaVOj+0zbr++EXV/thlh1S7yxvrlpY+H3j7ga3F/yXnvJ2qW1LdSHDDFiuHyE6zTzTqKVC1sSBdiiEFbWjsTOsrGMTxH1Gr+PzRY26thUy59PurjQr7DaPjFSEqIzmNvllz0uRNc6ij+vD9NdtakRfzw5TZic7RIWj3NEz3Urycq4erro0W4VjGtnCJfjVtbZQ/q9c57u5+3b/nouTSXhQfTv5e2pZ3TSgoh9Ltz8MM56D8C09avw+wKh/bFLc95DEKdWGyesNrKTC20kt/k4ar1rkN1H38YGYxdnYaaj3hOg3xPYhGHMisLox8QNv08L7buX7jKmjsoQXRIRyQNeVocxsoEt06VhjDixMd+5PBdDO2TIyjeEqQ3V05XiuIqU59lGpngkJjjjt/Q9DvScX/1Aczpyh07Okh6bK4j5wpcXwnvvmQUF7LPSf1IU2ouV3VV9pbsH2fil8/zcvbj9OW+cBWfspAOcXqzwftShSz8rOWS9UxQfmyUsxHRvsjPlpe+Gr7L3GLr9Wh0Ia49w7C+mPfKMnd7+KhOPt4bi+8amBn5Po6nmlON7fyfxHb9SfSN2fS2xupb66g3VjbUx9LB2pX8qrbfb6FKVGbXLVNfH4utrWzY0NzTFsuG0i6Fgpfem3dqV3qt2XvFK0+bNuW2uq9uwvmkjY0tEIa1/UYZrjpcXxFvXBXHr9bN0334dz8pxDpaIHv3qocYPfHKOcIVeAbRyr+tOFzbiFUSTM2XOEMZ6/dDyLb/dJY8XrtBrivZcbK6w+a9Hqu+hp/D7dIoEopODheikWT07M0F83RqmM0Gx3id/o1e/furOfb9lr3yb/HlrHs3rV1b5L2w3GPoHY/mQdcbib9o9WoMO2zD3z6VN3XdDls9rvxeveATmJfwDO17Mm8/BuecZj87+O+81JMPnS4L7OlvXJH4BnyNg9C6M3nUJzjX56/YcGlYIaI/a78iIZvg9HhqbFIH3G3p5iK4ovt/w3bs5NC5p7LLz0DVhjF6GMnW8Kojxdf32e3RW7Hx9GKNK7HbeEsboPTpDPyugu6OnR7TKL/TpOmNBCEM/JzQWYcCc9peE3kMjHaUZIwO4qPfUsLhdx9Muz8dgOXxAPGzJGw/p37JVqH6yKv2mRiqDVzPf1/gdliNFEKYLE4jdSNWVHvAORTI=
*/