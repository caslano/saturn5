//
// detail/scheduler_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP
#define BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/system/error_code.hpp>
#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/op_queue.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class scheduler;

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class scheduler_operation BOOST_ASIO_INHERIT_TRACKED_HANDLER
{
public:
  typedef scheduler_operation operation_type;

  void complete(void* owner, const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    func_(owner, this, ec, bytes_transferred);
  }

  void destroy()
  {
    func_(0, this, boost::system::error_code(), 0);
  }

protected:
  typedef void (*func_type)(void*,
      scheduler_operation*,
      const boost::system::error_code&, std::size_t);

  scheduler_operation(func_type func)
    : next_(0),
      func_(func),
      task_result_(0)
  {
  }

  // Prevents deletion through this type.
  ~scheduler_operation()
  {
  }

private:
  friend class op_queue_access;
  scheduler_operation* next_;
  func_type func_;
protected:
  friend class scheduler;
  unsigned int task_result_; // Passed into bytes transferred.
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP

/* scheduler_operation.hpp
Dut2eAbwFp/ocSmH8i5ZrjPkRMihJ3263/uCcsiXahwW+QXyAcAHHK2sflt+zsllP8T4nPJzD3xX1u6A7WlPUXILMEPJLWEt12cCs5XcEtbybr+wbj/9me5cVX78ThW/0wo4id95n+3xg5BO90chne6jwH6qnwVOVf0scDHwM9bLIeuOTrnLVOLtrPpPxvtYSI+/T5B/fsl2/SvKhU8DrwE+w/b7LPAu4HPk498CnwA+H9Ly2AvAj5XsDlR99X5gJvCPwPOBrwALgQdCup5fA14C/JOSN4EHgT8Dvg5UfPR2SPer7wAPAA8B/wR8Q30H+K7Jf37eySh3R+p8zlb8B1R/9X4tb64BFsjeWp2fS/1ajrjMr+XL9cDnVD/g1/3RFcC/y3xG9zdXAocCvwMcAbwaOAZ4DbAIuMWvx4nrgGuAe4BXAn/t13LkXuA9wN9wfrHPr/P3O+ArwBf8On8vAt8DvuTXcuTvgSdVeQJVPf4BmAD8IzAJ+ApwHPDPwFzgX4CFwEPABuAbwEuAb6p0AN8G3gR8B7gL+J7KN/BD4OvAj4EfAY8BvwD+DegLYPwDhoEHgPHAV4Htga8BuwD/BMwAHgT2An6u2hPwBLAK+A+/lhu3AW8A3gS8F/gD4JvAW1R5A3+ovgu8Fdg6CL0aMBl4GzANeDuwO3AncADwPuBY4C7gLODPgPnA3cAS4MPAeuCjwPXAx4HXAZ9Q6QDeqeofeBfwDmCbAOoB+CXsfjXAwt4K6AO2AwaAnYCtgGnAtgF7vlbIe706e8zXPg7q+drfgrrdfsp5f5D942dBLT9+DlyoxumgHj//DtxCuu+rdTHY1Vjxr6CWI78Evqc+wHmZT/p7TR8PDHD8DLK9HDbM+7Twx34hTclTTGdhUMuFxcCzgSXAUmApsAK4FFinZMuglm+XBbVcVQZ8ROkTgL8ElgMPACuArwMrg3p+VgVMBa4I6vlYTVCPR7XAfJ/oumT8Xgm8AbgK+ENgA/DHwNXAu4BrgL8CrgX+DrgeeAh4OfBt4Lcp7yBNvIMJeWR+1T6Ee5jfG3xIjxpXfXqc3+7T4/qtPj0f2eHTcuUdwOvUuAq8QY2/Pi2H/9yn0/UYEDTGr4B98Y3fAAcBnwMOU+0MeCHwfWCZam/Ai4HPq/kUEGmX9vgm8Fnx1+nfa/DeHJlDS/plveJxpr8upOdTqyinrA5pvlpDPcCl7NcbqQdYR3ltA3C56u+ASo6/HLhO6WOAG1X/B/w28ErgViUrUo75bkj3l1cBf6r0TsA9Sq4Cvgy8Fqj0etcDfeqdao4HN5D/MAbw7hDUHeV7xW95lO9vDurx+CdB3V/fFtTlfztwsyp/8j90jdJP30M+uzeo9QD3kc9+Sj57IKj7693A5UpuAVYDHw5qufBR4PWq/oB7gY8HtR7oCeCrwF+Qr/YA/wZ8EvgZ8ClgGtL+NPAM4DPABcBfKz5W9Q8sVPUPLAa+BLwW+FpQ1/NB4BOq3oF/BL4e1PP23wf1fH2/+o7q51V7DKCfB2YB3wIOA74b1PP0w8A84PvAc4AfkO+XGbxTQvVB5Hu1r3Ax+eZKtvOrqLe6Oqj1cNeodKv6BHb3oR6B41Q9BmUcF/cqxLUNuAZ4Y9CUA3lenGflI+XApICWqzsCe8o+ZP391IDmy84BXd99gEpfmw5sAHYNaL1QN+B3lZwV0P1hz4Aev3sBfyDhOF+3zgBDRmG+hyq+In9tCev+9ybgBOUe1nrDW4CzVfsH5in+C+v+bgewRvXfwMtV/GH9vTvDmg/vBu5WfBjWcv29wJeA9wHfBP4UqPrcB4BtfBifwpovdwNVe34wrOXyh4CDFf8BRyq+A85SeQHOU3w=
*/