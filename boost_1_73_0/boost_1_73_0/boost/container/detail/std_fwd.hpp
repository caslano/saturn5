//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP
#define BOOST_CONTAINER_DETAIL_STD_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

template<class T>
class allocator;

template<class T>
struct less;

template<class T>
struct equal_to;

template<class T1, class T2>
struct pair;

template<class T>
struct char_traits;

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template<class Container>
class insert_iterator;

struct allocator_arg_t;

struct piecewise_construct_t;

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

#endif //#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP

/* std_fwd.hpp
dGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxNT1BUX01BWENPTk5FQ1RTLjNVVAUAAbZIJGCtVV1v2zYUfdevuPAelgSqnDTFsm5dMcV1Fy+OZFhy0wAGBFq6irhSpCFSSTzkx++Skmsn7dA+VIYtWeK5H+eeQwXLARz9sMMLbDj45pG5b0YHnbegWaP+wdx8HZBlj9B9CLik83ekGsIO9ZgdwnehHuHAobI+1xt7nWXfkW5pi7Q/QwteZvaS7nTIHj9S603DbysDB6NDOHn9+ld4AS+PXx778I5JjgISg3KFza0Pbwp358+KPTwEGt/6gAaYCJ4ETCuuQavS3LMGga4Fz1FqLIBpKFDnDV/RHy7BVAglFwijeHYzif7y4b7iedXH2agWdKVaUUDF7hAazJHfdWHWrDGgSopA8QuuDcVsDVcyoPQIBpta92FsEUxoBeyOccFWlI4ZqIxZ69+Gw7xtBHUyLFSuh/mWiqAy9bOubqiamm1ArQ0YBa1GH+x6H2pV8NKeiSK6uW5XguvK35VFCWUxVA1oFKIPR1COumsBIenZ8u1KWFP13NiTVlLbbPeVqp8sJFr7QGXbSEpHtNC6QhHxPrSywMatd0Rss/QsO8q/MbJd7QUoSVXBIExgkgxgxTTXPlxP0ot4
*/