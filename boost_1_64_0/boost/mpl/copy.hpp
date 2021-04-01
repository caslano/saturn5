
#ifndef BOOST_MPL_COPY_HPP_INCLUDED
#define BOOST_MPL_COPY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Inserter
    >
struct copy_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

template<
      typename Sequence
    , typename Inserter
    >
struct reverse_copy_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(2, copy)

}}

#endif // BOOST_MPL_COPY_HPP_INCLUDED

/* copy.hpp
JyzQBprWDEUVYClsT4f0PgbXEWCXJcxuMjSHT7EOYJ/Jn4ba361XeKebu1S8BFC9bY/H/h5ZdMVLPwoZ7ykXehr0gjLIF7HPegTvVZqAAWxnjLeLj5WbCWTmfkTaAfK8tCbju35x1Wyk3dfy4PE3WacI0IENvykYcXWWv8Pp40TBB04joKL+utlaWgfkHlYdnmOj10k9Q6fn7KFwUwg+hRg8R32HNp5ehkTfgR/USR/gebAsQWlsX0Yil8VH0eJI0ILJ5OPxlNyOggGGEstnzETv+PX/aVtoKy2uy8IH6niwXAH4drArFtcVrtZq8wmzhp10jNOECm/B+9e7OD4i8kSe+J6HPlK/WcWCirc3VA4U0RmGdnZf0R/KfI1dtNKsONnaPsyQe7bUMboUhO9GVFWee7VWlffkd5N99K6B6W8tATDayAWlkH4FMm7vE8deADchbf0NCtzQnboZF0UMLNGhMqz3H34D6o00u5G5jZ8AiiYCtj4C2UGXOGXMDQxLl2K10NpADOwI085ZcZrPCENeFoBvbbFkawbOELBnX821gOTIeQZgBDCdmw==
*/