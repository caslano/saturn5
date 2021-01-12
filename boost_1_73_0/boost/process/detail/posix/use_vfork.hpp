/*
 * use_vfork.hpp
 *
 *  Created on: 17.06.2016
 *      Author: klemens
 */

#ifndef BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_


#include <boost/process/detail/posix/handler.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/container/set/convert.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct use_vfork_ : handler_base_ext
{
    constexpr use_vfork_(){};
};

template<typename Sequence>
struct shall_use_vfork
{
    typedef typename boost::fusion::result_of::as_set<Sequence>::type set_type;
    typedef typename boost::fusion::result_of::has_key<set_type, const use_vfork_&>::type type;
};


}}}}

#endif /* BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_ */

/* use_vfork.hpp
aRU8x/0UbH0IglLOmQs1tvopZJJ1NQBW6f9I72ZJVQC424Pl8ZqyguUCj61vpiLCQ5kc+WJYEz9dCP6y1/ycCzqhQwTaFhYsGG4iC/TPfkq+o6KtXb0NgGymy20mpi/YK9YWynyRD1OllswFF1tlzABk1y4xWCUknAsrvpDG7kr2wnxoQE4VqJBIbwJJ7RexaQrio8VAsQ25rcSVgfqSfI1xXhBAgD2vWEnVg1K0WhBl3+rm
*/