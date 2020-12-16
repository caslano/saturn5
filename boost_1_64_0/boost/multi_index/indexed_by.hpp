/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_INDEXED_BY_HPP
#define BOOST_MULTI_INDEX_INDEXED_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp> 

/* An alias to mpl::vector used to hide MPL from the user.
 * indexed_by contains the index specifiers for instantiation
 * of a multi_index_container.
 */

/* This user_definable macro limits the number of elements of an index list;
 * useful for shortening resulting symbol names (MSVC++ 6.0, for instance,
 * has problems coping with very long symbol names.)
 */

#if !defined(BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE)
#define BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#if BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE<BOOST_MPL_LIMIT_VECTOR_SIZE
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE \
  BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE
#else
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#define BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM(z,n,var) \
  typename BOOST_PP_CAT(var,n) BOOST_PP_EXPR_IF(n,=mpl::na)

namespace boost{

namespace multi_index{

template<
  BOOST_PP_ENUM(
    BOOST_MULTI_INDEX_INDEXED_BY_SIZE,
    BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM,T)
>
struct indexed_by:
  mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MULTI_INDEX_INDEXED_BY_SIZE,T)>
{
};

} /* namespace multi_index */

} /* namespace boost */

#undef BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM
#undef BOOST_MULTI_INDEX_INDEXED_BY_SIZE

#endif

/* indexed_by.hpp
udAbpfOvqKNp+257MpUZ81xfhvDU8mUNb8bEYw+LR5JlURkUqUCtNB4HgcvaWRQWftlEZP3AhDIRZBKKtmMO3sv41GloI6HBXv8sjcFhE2Jm3Mwu8rV6kIR+lAZ37LO6GTfx7PX17wd9fkSOXvHs9RJi7OgVz4b/2uCv4ASNv0jV2+oDNb5u4Q8ldi7f1kH9bI5zWWOgG0HEtm3QGOql695zGoNsNXr72OhGg6EsYt80mMlytE0F63fAYJQ7jvwb+hsUEQvHzNsQs8MZ3WwwDEdhzV7gBcgv9ZFYh3+kmZMYbJ2A5O7Frvfx/bSyCt08L93+/LxKvSONt30/4i8iyD2QjOmJRVLGSZDkXl/P0QOHJibGbSXUr/r8+/ieZhbB02x5x36eTB3Ft85UXyVk5gZuGQqIAHUPgOedRu46t9kvXScN/aqoBXVvzOVwbOJyZV7JKnUSLWcfr6L/AipTiLwqCx+uXfRMBKHb38tl/kplcuF6cCGw9BvHZ0yk7yvv/bQvrco8zVzfEXqb1Na/lXIzEflh5KnSFDiEofZ+Xu+kMq4jqiCMVVXyhdqL1aZFD+0DX3so+gzTrzI5V0SylFmUJEQOvO7RMCfQLhSV3VfJIgz9LNW3hgz7hNmjjih3Ms6cLAgrHB9Q+XJi5miU7wUiTSuYAEihTaopd6nwlPcAllIzKKk2Ynw5qOx8qPbfYNona54jNWbaJ2ue7F3L27GfqzdEH4l9IMXwLBPXT9cA1/1Sd75Hvk9s0N/nbV8Ll813foyM+MM3Am55OSDyv0CceDkgZ4n/2IQ4WyzQ90Mv3kI5fFVAdf1wq+EN9/sQ3aPmtB1no+8Gw2FH2dSuCsUHz5N/x/DB8+Tz9zL4oF+JPdsMxo5eEb94b4pj0Ij37oO4roK274Md961xPMqm8SJYEzRiN7YTjPlbAPu0iEFHM+Dz4M33b3B7n8zUAY2T2T21LbgDMBjfdH1FmS/r7zDm1Xsgs+Rd4uQDCQb7k9RWD2JYPuxNI8xDEId9Luus8B0dXx6ZXp89Pou1mdnififgzZwZDDCOqyKmc9vvdgY5ioJ2/v72s9rW6eLK8tpKY3v0q7vVHODN0B8sd7sQaW2Ft96/+tJehb0FsFfOzZwCVav6+5fV95/r79051WhOHSdzfBXAyLsgDnqCrYVQK747MhwwwGxU0/tLiIP0qlLUZffXNGaeI9GwN1pYHYe5LuG8fYBzZsmw8E3YKOXwfEG755uAA71Fd/mV0yy9OG++8e976vyGXDKd0/2V/5tvaQuXsvAOv6ACo2/3Ud++o795rkfy4Zv6DJiK8/rybh3HFfVcf/k0BGzj79G4MuGqTAufWj1z2sbfq/EeqW8cv6Dx5RPHEeb4+wy+fwIZ9M7q+zU+153by0kKwjza8wOdRyc0MH18uXtWY3V9Pgt1TGfukUpbR9BjmKp/BqMQz7cPdJhKXW/BrmnvTSA3u6wObGcW1+rvP4Z7Us33V0yPg/NNXGfegH5Rp0OrwzB6HfP9RA2QddvUm8g4vjdx4yr3Mg+WWNym41HKmwjLtAKjg2JxeenkwFznGOU+vSzLuHQKV6i6YZw5raJtSrucP1iXwywtx4fietngyz0wVbBqyX7IyO5FYZbPHwbcDM4qH9F3WQcwLH9Wxx6K5yLIqaGxPlZttrBxshbbwjAIF+MsthpsaWi9vlSX59B6/RGDD6nXH8V0cRLtH/ZssHntcfkYcFj28Py9jHjdhBMzt1znNieC0Eucosr7ax+zVoFbgePqbz5zVv2yZ+zpAzY1FqkurxIZXCqU6he9qasm0UswyVyZ660oY5izC8fBOAhA3UN71JuAGbZXdnWd38sIQrc=
*/