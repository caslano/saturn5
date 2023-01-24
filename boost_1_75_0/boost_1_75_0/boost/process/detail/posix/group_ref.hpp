// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/group_handle.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>


namespace boost { namespace process {

namespace detail { namespace posix {



struct group_ref : handler_base_ext
{
    group_handle & grp;


    explicit group_ref(group_handle & g) :
                grp(g)
    {}

    template <class Executor>
    void on_exec_setup(Executor&) const
    {
        if (grp.grp == -1)
            ::setpgid(0, 0);
        else
            ::setpgid(0, grp.grp);
    }

    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (grp.grp == -1)
            grp.grp = exec.pid;

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_ */

/* group_ref.hpp
M9dqpOegnZgsG5qRMbO64ydguLtrYu7cc187EPFHoYbIc+c3NqiZpI/Zbin0sR6G2qO3R33ROp9NaGtXC09bovAKCc9qzJFQAP4+mLfnqOpTsbJC9aBux92c/DuxWLiSlunvir9NB4tQ6ygRF39q+yhioj+eK+X1hf4SP+v3iX5vocL03NzJvOQ0LPK0hCOpvnkkdsNVJ7s+g4JITofLyk9F/qSL2qprOkPEZq0Zd2BcujknSclGQPq7u8wD8xwOsKy8rjdm0ag/Iy6qq/J6R37qqT7HTMvLwIXTx43dRsmqxbhApEz7F3caBIWm3ckYstGTdxEUn4f0gwLyUVrw28Ds9IxlwtqqiOCn+EEhoY7+3NkaR0dDNAZj/Z6to53YvafUIQaX77/Lrzgd/LkrdePn47/hXx8njUY17oD23/vRR8CyyPvKg/vYWSl2tk8Uom9P9iK8iznxYy1uiqBaDzorvKNPkjETxO2BWKwFA1bvf7CH6w3PILGHY/FjWqMU65if78SKKEnWBX9PZdu1jrVJZ7UTJtgTkeyyGM0ypBXOoZInY/SYiUcRvnWsIvqjXLs+GValV3H6AbNdTfcrq7q+XmTMHio2ir5TlU1g6e7C6a46a3w2YGEnGqPDXOcrq5Y+uUeECh/xMiQLeMpIsTh8d3ePQfwtWbJ4JLl4TFYkbjs57334g1ts8NbVp6XDg4nKGzdN7Hch3eWT
*/