
#ifndef BOOST_MPL_VECTOR_VECTOR20_C_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR20_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/vector/vector10_c.hpp>
#   include <boost/mpl/vector/vector20.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector20_c.hpp
#   include <boost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/typeof.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, <boost/mpl/vector/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_VECTOR_VECTOR20_C_HPP_INCLUDED

/* vector20_c.hpp
/czr5StfNN8jpv2baH5wdB/BQvXOKPtd4TqMMS5MXifvLVEeBxoP3OO5eID3sFt+dzbA81Fk3kCZ55v9oeyunzfduMZS4wP3Rb8H5r4UaBe8j6g88kfh9Vnfu7RX6sHClfLo5Icy30iv3qcdfth4TPR9w1LzHuCxeb6j52i/eON791c+5xD2m/lerT8d4WP95lLzP/vzu5SM99e2d7vy863n/eXod8/Vm73kCdCH1BebXzqAkjiTeWDkt9NPbsQP+P2ZfFRy9LvpY8T3p/sdSYn3Lnp/cKxUnuaysD59vn5p5Hd+pL8Z4UPjTv3K/b73r+rVDuoLeFTeQ7/wXnQ/1xzt8x555o8psc/yfuny6D+jRP973te6r//Rfj4mn8/8GG8/nud7KOP4xLd43nvk+rdUzsd6zvy9kiXiwqy4eh4+hvmNk8eeoN7Tj60pkIfWDhUh3zz3mTiAe4Eo4UXpV3mrke/OSRTXtvb8xpX36/QDsuTr7zSee7P55QmOExxCf6nq2UHy5Z2NC4kv2r+inxnt1wLzFPRfqse7bnfqHym/W4apt+VFRz6rn94mOs/GGabL51ea34IcMx/vhS37zHhMvf7Ia9o79Uxv17fHXtv5Rj5yu+frdNdB/7jT5W3C57UvKae6X6me83uCesaLPeL5ZaEdaJylfOfpL31u3h75W4zjeeMg6HH6Iy7Cund23uqfY/qvTX9SvnL07yZozxk/475XvdjTknwR6iM/nHxnyhn6DdH68Z0U9eqlw1uo5zsK/crb5HvbahdW8j5xXPXxZ63Uj+YHBnxKnP3c5XdP0ffn0zxHxc5vi/k18Ak8/7Xnf5P8zb3mZVT6vPe/lJvn1/9i/ZTdSWF8Hd6b9t6mX/ZDOd6q/EXfBxeKU77X3lRTwpObf3sxJd8Byu/7vVraGdHv8Yjb73D9tY+Zfwvra56khG/wexrkkX5/pB9+71BeCx6Q977QD71E/P8TJbyi9zXlyTcN9ruHfc5jh3kl8GvM71TX7WLtZpXy+4l4Bj+b+fYJcdZU+Cnm86Z48XXjPzHzoV6NfkdEfXemeFC/L9bR/R+qX+R3Y7kl3hNVqj27TTluIU5zfPnwvvQnH5zyW/UcvCT9NVAS35AHuNNz2Uv73Ox6W6b/6P+ZF+OJ/JRJ8vuvq0du0f4G+xGuj3gpM7qfTfu4TTu8VD+zUXs+Q3n1PubqweqNY+YBci4Yz079bu4ToYwZn43uMxqn382+MF/zLprE45Pgi5nHbHGaea3Jr/J//EPx11bxQZI4b5PnyHaqnlPfz+N94lPGS671PJfIe5tv9pV6fmC+eJV7jOlvonZ7lLhTHqX9KO0B68d7n4s755p3bh53QbP5WkvNJ07wO0/P9zHuGeX56PdmNonrsIP0e0zeql65rNReJ+pvEa/hvTbGD55RDpr0w42br3pb3lUeuqKdv4P4G+UrUzs1yvVnXxnvevrF71KfnqQeHSfuGqt9fMRzslu9/Wftg3zip9F9nfyuPmU38c09ieL46J4A+Yvx+v3G45fd7zqrH/JrtCvt5X/Ac9SXy988YF7rfzzf6q/20T3jdfrFyCnv83uHjOuA8/5Gu9RLeeNeQ+YxTjnyfqoqcPH/5yvOQi8xfs/h8nEtnZd2KMifa4n8FRnHbO85agj3qQTenPfucn0Xm784zHyQuHm8WeLgCMcrb+u8J6A5zfX6lfHsFt5zYHy93zj92XT/fwolfqu86EHvSZQ36NvD8xX9Pqj3n1Qjh4x/p+dqaivvHTEOo36rl6+vdF8rkCPa2y1uUY4KgvMVZ7zmoa/LlsfI0S5UyYPtVx4jOXxHXJWonf5JPbDdv8OTsY5Xe68cPD4=
*/