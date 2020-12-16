// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_PIPE_OUT_HPP
#define BOOST_PROCESS_POSIX_PIPE_OUT_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <unistd.h>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct null_out : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor sink{"/dev/null", file_descriptor::write};
    
    template <typename Executor>
    void on_exec_setup(Executor &e) const;

    std::array<int, 3> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        return {sink.handle(), pp1, pp2};
    }
};

template<>
template<typename Executor>
void null_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void null_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void null_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink.handle(), STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (::dup2(sink.handle(), STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

}}}}

#endif

/* null_out.hpp
isX9fiuifdrUgdPK+S8Ja/9/UdyrmP1P+iQHxyZfhFyMLEf66rjzfnq/BTxen3g467BG+/1dI96ZXO4pXbM+7D0ozuikLOi9Fz7WOUXvvcj3DfSSd+HvXPouZewd1yZiLtaKXpb8AmssnQHXwn7UDW0kLQtm0N0+13lHmGe9fW04P+GI/UCvy/1BWO73h4yb5H1rmLjf6DXjMDnG2uX+cQvLbv/7iLDyxP0Cbz3PUHPdzxBdLdd7jPBMuW+dFl7uZX1xwiwVm7NN/IrkuLrbfUd47u8qhCXvlmeLe6kJ60w5Ptb1ntSw3O8xx3tKrsbP7T51pm9S8J5jdeMc84w9oH1a/dPD78ckOFz8XuJ12/cgr1vAbZMe05t7vMTUOYZnlry7hvpQxX6up7q1hTW/xrKeXhXTr/GQnGcZPfPJak9viOh+wT6fGUa5nm89PkLH3rjFe3l+WSsIKXDOPElb6axQunaTrvB+ALvMvYrbeRJGvtdRl1CV6NruuDvWIedudryzdLPL0g61WxHcgS+n2NjRMyV2cRwHy+VMOT7LE3gPOZ7n0EfMrq9CJsdFLWwfFxsTFzUyLja6gveQRPUTexIS8FNjYZ/I94uTOK5p2fMtfkF4R5C/+1MYTlY5BTkVwR2Rv8UuU8ditvAc3hyaQH0n1zxifob97XT49V1ojhz3X7nvxqSIOjRV6jv3eo1wpDxTznGzyznhSHnIE33pLNVxnfU7Ta89OrmmEra57qw1LteO8bB1db1tPf5E5/AsPd64h31L7e+tdauOP1+NNA/cZydI3VrCg8JtDoOzfjX3yDHi5zJG4NV0ewfRMD36bDRzIExfWoa4L7I6oHGrV/Fv6okl9aQ8l5YGYyb2a7juob1bXtW20bmwjj4bRzrn8hzG/BC3cuL8ZuZayjmJCzoTl7A5ksf3DZ7kHD3nQuR77LcH83dmcX5ObnZhDtlKHOw+EZOnb2DHMXnS1Ixxb9cdHaVM964grhoeR2FzqRz53SCgMN++2ncp7imm33KvHI/h+sWw/08Vh7+SrFm5ljnXu2JXauqBCbUCcjjzV4P5qu0AUi5/lrB4h9dyWqO7OTZrorfxHfna5O5rnFe8Brn7WtEVr5ntvvZ5xWuNXz0joH924WuzN17WdcxPMQMH1lg7c0pFa40f+ZrfR7omuvta3RWtxX7ka5+7r3Fe8Rre7muQV7xGu/sa4RWvGe++RnjFa+q7r6Fe0Vr7R75Wuvsa/0e+VnpFa/x/h9NmhJ/0ic6BWcgYx9/t/OZvec4XeYPrUcfaf9NXav6WdosDHtIUeAd3/H2z4+97HX+vcvzdXddW78/fJzr+Ps7xdwvH3/GOv/chK0PrVuh6H2Vav/C3/L7yBtfe/RpWhftgGvwG1oc+X3CN3G85Pg5+B9vC72EH+APsD3+EZ8CfYT78BZaof3m/hedBL7xQ9PYaz7KmAXzPZY3nWOw8sAasCuNhGqwJ68OmsDH0Q5lDBtvDWrAbTIY9YQo8GdaG42AdOBHWhbPgMXCehjcfpsFlsB68CqbDu2ADuBE2gpvV/ml4NNyh4byr+n1wlUfnuet8/zLYFlmh72INo4JrYh8LO8LmsB9sAUfAljAXtoJT4Sy4ALaFS2EHeAPsCG+HneHTsCt8HR4P34YnwC9hd/gN7AH3w14wELneMBoGjqvDvjAN9oOtYX+YAU+FPWAm7A0HwBFwIBwLT4ML4HB4IRwBr4Lj4d1wAnwIToSbVf+W6j+EQ+A3cCj0kF/DYAwcCevDUbAdHA0z4BR4CsyDp8OpcAScBvPhdFgEC+ACWAgvhsVwBSQ/5TqtC82hhuu1HNZCbtVy+D7X0ws/hTK/HCbBz7U=
*/