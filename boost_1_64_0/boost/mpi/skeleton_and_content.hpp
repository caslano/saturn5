// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file skeleton_and_content.hpp
 *
 *  This header provides facilities that allow the structure of data
 *  types (called the "skeleton") to be transmitted and received
 *  separately from the content stored in those data types. These
 *  facilities are useful when the data in a stable data structure
 *  (e.g., a mesh or a graph) will need to be transmitted
 *  repeatedly. In this case, transmitting the skeleton only once
 *  saves both communication effort (it need not be sent again) and
 *  local computation (serialization need only be performed once for
 *  the content).
 */
#ifndef BOOST_MPI_SKELETON_AND_CONTENT_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_HPP

#include <boost/mpi/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/mpi/skeleton_and_content_types.hpp>

namespace boost { namespace mpi {

namespace detail {
  typedef boost::mpi::detail::forward_skeleton_oarchive<boost::mpi::packed_skeleton_oarchive,boost::mpi::packed_oarchive> type1;
  typedef boost::mpi::detail::forward_skeleton_iarchive<boost::mpi::packed_skeleton_iarchive,boost::mpi::packed_iarchive> type2;
}


} } // end namespace boost::mpi

#include <boost/mpi/detail/content_oarchive.hpp>

// For any headers that have provided declarations based on forward
// declarations of the contents of this header, include definitions
// for those declarations. This means that the inclusion of
// skeleton_and_content.hpp enables the use of skeleton/content
// transmission throughout the library.
#ifdef BOOST_MPI_BROADCAST_HPP
#  include <boost/mpi/detail/broadcast_sc.hpp>
#endif

#ifdef BOOST_MPI_COMMUNICATOR_HPP
#  include <boost/mpi/detail/communicator_sc.hpp>
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_skeleton_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_skeleton_iarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::type1)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::type2)

BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_skeleton_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_skeleton_iarchive)

#endif // BOOST_MPI_SKELETON_AND_CONTENT_HPP

/* skeleton_and_content.hpp
p/6k3ExbbjApN8OWW5BEJY+ikiBublAyaR25IFNRKZkRMhp5pIQXZNro1PtMCNnCDnFhB5mQnRAit0NC5HRIiOwOCeHVhKBxFWenM0fIxNXDfJc5zLl2luC3OSSVx18mNk59qi4sIVOzM0rkd0iJbh1SIs+REpIb4FwtrHgEbX1uDBFLlIYIdxvblEKmORtezmxcnsGpNBtkqHUiwDHFQcMu7HbIL49XJree21HrGbbWZdNBp96XipNAkInIzbtFvKpiIl6FG3yEtIiClEmPzctWjJMkyLazCAuYVdS4L0cGUZWSEZc5yfMGZhQ2Lk4Ch9mn5ZkIYxHZTnPSq5oPeNQAyUonJF9JrCjjlTrgd2mSd5kNYMSTy8aIJWVBYqkPS8DVpiDXUpwWMFjMON00VBTdYzCxuLroouZaDKubM+e7YiCghXQmDgjI3ndRHuzsw0nYEdEocC1l1pNhTuJH6TDjplfDqx1Xw6zYNN0rvzUnU3J0f2X8dI6o6zJMSAnhHxlQtfbPTpX6qWt/hm3tFzVJGCuFNbW8F1p03N/ctP3NSdvf7LT99WJ/hXMETurwynIhI3eXycG5lvGVZUOSNEd7rXPCxtHezjg634GjRa2yZgWTsvIkK1XRCWCW2bpWI1EXafQ1pIqxgCxJq0xxlWdRXISWkhTXs17LLz0dzOmE3OMoNrultpev25NSeVJKr7MZuj3hXa29Z+LoOUpKr2baFHVEy0iHUplaQMp6g+3JU0Q4AqFVqatSjvDRqhQ+kvZk3iUvUVn2xcilaUE8e3UKz+an8mwgVSZ1k1KW4ZSk9CJ4djoRzFI9jRTmtSONIOZ5kkYWixbCgCTVWS/lMkrOdGVh9DoujDlaeImYYlQ7s1KyxEpxFs2cmUY6c2YaAc29FaSlNVmRnVgg07YiMxdkyNqbJLw8thXZJvjiwgsiMjomQm5HRMjpiAjZHRHBK0RIXqhyOrJQsh0tlFxHC8XrqA3lmqudzWD1dkKF/I6o0K0jKuQ5UkGkMmdqLLRqqHVpR/kTcFTG8tIMvS4b18LBVMptRq9MSkfFVFYtPRRaBO3IdyR6wHHYslXzgaDwf7JNkOlsE8j6nMr4up9pFTNNqBy7FJapZDFwufPx1M7nOHY+17HzmY4iKVc6L0gKFtounZ1il2bZ7FLBVKfqtTbT0S51WcvaTFPtrbja2TT1ohptt0uZUWOzUlQYmdeisKewvgsVOmE1qzph67vWa2wuGkyy+WdEm7jP2U6TDjNqnZohWemVtsz0SluGg9ImQ4XEEC1KBjWtppqZuupnpGqqHovSIaD15NDCXujRSZ9z0/c5J32fs9P32Yt9Fg4SSM7DLD5Tu99FxjlVS70v1UpP73RJz9n5DpwtShVmpXO3SFaqrwWzrIqptXvOLpZUdTLTyQaRNVwrgnZBloPVZDTTqucZQmiLjSdJ2qGRpaed1ti5PV93q6taDBbn9mRq2lwoujkhVarN0C3Ve6Ktgfy01oArVc93pVoDeVox1K5wsQbiDbjvMJ7kdNSTCHG/618ui9GXpoeN9va0myB6F+UU3vbAe5D9XKRx5ao9NGJLOKtxOcT2IORg/dsDuQiG+vpjM1b4Ek/yltepm45seR35HPkc+Rz5HPn8Jz8YT7Ac47uu+ZY1nsBy1+Dmy2667mLLXYSb580tKlWGAsR8bD5h1CU3i1aA2dHLiq6S6vqwYqgx4AfV0e7IzsCcUBD1KwXSNBcrQo0+NxoV9k1PXUV0Zv2wPtQhf7moRWJJ6jqijYt6hXUCpAuLmSCOkhQMTHUQAt2SMdA+v4oCqZNkCMLZ6AJuxu7aztdV8Err/C9vpWgMjPovo1ib4MQ4/pg=
*/