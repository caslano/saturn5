/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   save_result.hpp
 * \author Andrey Semashev
 * \date   19.01.2013
 *
 * This header contains function object adapter that saves the result of the adopted function to an external variable.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object wrapper for saving the adopted function object result
template< typename FunT, typename AssigneeT >
struct save_result_wrapper
{
    typedef void result_type;

    save_result_wrapper(FunT fun, AssigneeT& assignee) : m_fun(fun), m_assignee(assignee) {}

    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        m_assignee = m_fun(arg);
    }

private:
    FunT m_fun;
    AssigneeT& m_assignee;
};

template< typename FunT, typename AssigneeT >
BOOST_FORCEINLINE save_result_wrapper< FunT, AssigneeT > save_result(FunT const& fun, AssigneeT& assignee)
{
    return save_result_wrapper< FunT, AssigneeT >(fun, assignee);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_

/* save_result.hpp
vzfT/+0u852gvKuUuDhJy0WSfj/ZtA31p41pAP1vRgMz6PfUjn5PfanvR5vaANrUBnFvsItoAxtCG9hw2sDG0hY1U/L72Z7qBrYFZtGG1IW2wHP98qWXk6878/VgvvOYr0S95+J7t1KuB9eq/bfZHvPYHjfTL+we+oXNp1/YLWyfBfR7+wf9o+6kf95dwK7Au4EXAhcCxwOXAMU3DTiD5R6S9lPvnaRPpF6RkN6s1/2s12pgMv356tJ/rxlwHfAc+vH1oH/f+cBHWf5dLr4n4bukUrbhPHLcPmV7fQ1syj0jm3PPyHO5V2Q34A/s70Ps38P082qMBXQisAlwEvAg9Jcwfhbjr2b8NcBfoC+h/nbq7wAeg34R9fdQfy/3Dl0JdCH8MNANfIzptjDdk8BKwFe45+duYBRwH9AD/JjpP2f6L7gH6PfAWOBhYALwN6bDMSRdGDAZiLJFH0N9FWB1YBL1NahPA6YD61Bfn/oGwIbAJtQ3Fz1tuer5HzjFwZZ7Hfv/eo7HucAYhiczLHuwqudWPn+XltmDFceUclpxD9a2wERgO2AG8BzuvdrB5e3/jsBMYH+Xd3x3BrYx6gs06twF2IPhXgz3AZ4L7AvsDTSO3Qe4GtgXuBaYDXxUyvXWe7n5zCXPflLveMgdrHc+zx9riNR3PG38E4Fn0X+wPXAysCP9VDvRn/Bi+hPm0J+wgP6ERUw3DTiNfqXFwKuAlwLvBF4GXCLpuO6oZyVZN+zrziw//9gqwCv994JMD+y/OcjlzXcRsDrwYmAD4DAX56+6l5ZnBPs6vontsxlYCbiFfsyYE1LOVvoTb2O7PMX16WmuFy9o3v57kf6V2+nf+QzX9WfZjs8B85h+vKTnuFP3mrIm2cfdy2yX1+l3/Abr9TGwCXA/15036V/6FrAf4wcxfjDwHeBI4Lv0M91LP+H32G8fAG/lHrp3M/8K5l/J8AMMq/7cXk5/zmG9r2Z/XgM8Sg7D1tejtL2v/3/yGEZt/vO4DIdfj/rT+QyRb2AvTEgWZDjkMsgdkLWQ5yH7IIch0buitDqQDpBBu0I8h/+g/X9ywbhTt/8bdvzrMjR53or7Cz5vhZ6ryn+u4n7GJ1zTse78T67rf9aafrLr+cms5aFf6Bf6hX6hX+gX+oV+oV/oF/r9eb8/6fl/LB7gT5v/f/qdfvv/S9He/f/n+vn/b+ajxS/kZByFfJyE58aa/hx/yawlmHZ7Izg1d0q+o81Y8lrt/FMKxuT77PHJEv8U3m9fYLf9S/7yvwXwtsS31JLIp9ifCKXUyWerrydp9mtzDN4q5FmI4ogjbWGOUI0kvfBLGkn6D7UrDQs/5GnZeX2o1M2T4n2huyBOUPH7xdY/PAg7f7LYw2nH92s7q31f2kj40lIX6Bcme8N9GN6V6A3PYbh7Y294bpnwPoZHnGnl+O93m75uEt8W8k+UmV3L2teFRltLu5KDlJ87JQA/AHkr/q0H5Cm3f0dI/FlI61K8T2nveSlGe5+Ym6Ta26h/EutfkW8+nB3m7Aux3NdO3ukUtI8F/akri177zo0+J76McmdXk3KNEh33xOjLdrlR0n3qzkKp/SDjIZdCSiDLIDVdutYVcjEkX9e1q3ToIRsgWyEvQ5q4w7U2aKYwjcdFLbpqlbUBkEmQyyG3Q+6FPIp/E11dXJ8j33d6D1+/S97gefOS1s6bN7lVN6QY8brJjf9ewpmuPG2Lne8j5dm59ZY9oFO9fLZaXAvaS3mvuyZjDbgNcj+sNxtdbjvP3l5Xc2z25TpRIvEfus8hzykPUgS5CbIQkuIC0wgyEDJKd2mX69BDHoI8Dnkecpbbsm6ZvGCxBVY3yp+qVYNVvw0=
*/