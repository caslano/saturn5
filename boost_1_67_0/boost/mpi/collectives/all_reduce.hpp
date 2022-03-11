// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Reduce
#ifndef BOOST_MPI_ALL_REDUCE_HPP
#define BOOST_MPI_ALL_REDUCE_HPP

#include <vector>

#include <boost/mpi/inplace.hpp>

// All-reduce falls back to reduce() + broadcast() in some cases.
#include <boost/mpi/collectives/broadcast.hpp>
#include <boost/mpi/collectives/reduce.hpp>

namespace boost { namespace mpi {
namespace detail {
  /**********************************************************************
   * Simple reduction with MPI_Allreduce                                *
   **********************************************************************/
  // We are reducing for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Allreduce directly.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /*op*/, mpl::true_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }

  /**********************************************************************
   * User-defined reduction with MPI_Allreduce                          *
   **********************************************************************/
  // We are reducing at the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /* op */, mpl::false_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/
  // We are reducing at the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op op, mpl::false_ /*is_mpi_op*/,
                  mpl::false_ /*is_mpi_datatype*/)
  {
    if (in_values == MPI_IN_PLACE) {
      // if in_values matches the in place tag, then the output
      // buffer actually contains the input data.
      // But we can just go back to the out of place 
      // implementation in this case.
      // it's not clear how/if we can avoid the copy.
      std::vector<T> tmp_in( out_values, out_values + n);
      reduce(comm, &(tmp_in[0]), n, out_values, op, 0);
    } else {
      reduce(comm, in_values, n, out_values, op, 0);
    }
    broadcast(comm, out_values, n, 0);
  }
} // end namespace detail

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T* in_values, int n, T* out_values,
           Op op)
{
  detail::all_reduce_impl(comm, in_values, n, out_values, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T*> inout_values, int n, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), n, inout_values.buffer, op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T> inout_values, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), 1, &(inout_values.buffer), op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::all_reduce_impl(comm, &in_value, 1, &out_value, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
T all_reduce(const communicator& comm, const T& in_value, Op op)
{
  T result;
  ::boost::mpi::all_reduce(comm, in_value, result, op);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_REDUCE_HPP

/* all_reduce.hpp
ijQj1oP5Jx6FhNyUp8OMdpElvX4vQxh8GLkWPvt9DbgRfEt29fAC13z3wGDM6zP1SqR4+B8dZXos3d9wsR9bFK6fUAnSpDu2/mOAVcGDdtQhH9EdJ6oVtyXTZ0K5CPpANmrY91I62oMtk2L+seHGqo94SdwfCcJ92jv2d2Z+Zfc88DKQc23CYEcxYMqQMEoo4AMi5mXuX1Q93wj/5SIdV8od9ptCiTz07Ab/Gp8MPMHzKfP5gCnAj0npGE4frcNIqBT4R4HR35VDBwwshhDE5pZ4UaOSyPMHfyjvEQgbO798so9E3bqEbGFM1GNMKK37whw2qEexN/tM+73YX5JZtJP1dVfMfIR0HGO755kiyJeSBVvMawINJB4/DqQq3jvLw0rDRWNlhwuZQCIEppGtztdjWZl4yBiB4zAUdamwybt3AIzgFLNurX5FQoa1/Xt7+8Gdn16Fsvd/o47+hmGZWVhZVKr8tDwm06J3iuJ1a5XYd7umODiyWRaBrRWq74AcFaNA0lYIe+A4MWrYP7v75YevgcdOmudNRDvTZ55x5wc6k3LJBqyn/g0RQSLDvkxhJCHI+bWRXimE4Z22C/ifSvGkr7R+bAsYgkQB9vlQw02nNUaSCJVYohrEf9ktzCilius0zyQzzp+dzYK/LADDz19mMGaiUBZAZ/y2c4cKeODGOw0e04BLlFnTsfAkXva0m3RFLb7QVBkzoEnELJa1l37FxPF7F2h9E70ektHFq/x0NuRxGdVy9mandk4OEsvWCD/UAcjdl59k1GPGvQKyOvymtDpRTC55xcfEM3pJUsYpPi57sOVJL/yjYyep0m6ZI7lSQE3f21SCbjrj4xRDW4TqPTeJrQnV6Cl4x+paZnVKkTdfZ9TXuombIQyW4gsy9MmYpR/tj48G03/vvv6tXwZau70wXeRq5rt09yQDG/1Af0z82St5kkU/Nk9Na1lxuWflWPicg85r0csHoLbqJPz+YQYx6Fzpi9OiZchjT0RvjWY4VsPIahOjHaJALWV/hHh52oosbAu87WLEff/MlLqJTexwgCSd+IoMVq7OSeuOn1Grij//cFBgu974O77ncY4eRldbUjd8JCS5/7+gd5K62qZhy8IQw79PqaxIAqWCYewiqnmzjt+p2173g/RcFmaIPzPQYmOL0nHKJhvB9R+t6NskXo68HDPMyfmoNUviL2PBMJ/q7PP4uQC6XMdtjo6GjLhwvIzGHFv09G71N4V5bYva05Mq337vlS9LuSn8yFY3UhwtWkKMFAuKtdV1q8QFrZvUKHu+e2lK952Pk2XFwNbopek9jH8r/7lU6/fe5Z/LxnQN9SaMwKnRu0Mqg1PE1wcfZkaHeDBpxmQff4Ch3MNzqa/hQ6aXh0+9GO58wu9RqEi3nwYbFeir5ikslX3iQPIH/6Hfl9rsoloJ6KDj8Rkx0FY2Wro1fUOZELFqdvYojf4zx0CS5sbts4Wq3SR58p5/h7NVPreUIP1n+4MUAVWy0gdSa/mLPZTS3bSUTvqHw0Y03gvlNxav9aYLrRjGz4Itq4cjQPovUrDXtiANBg3bpRIF6EjTLJNUICPArUixdfdbmVlMbsMl6EGw2Nfjlmsz/DHdkKY7fvx0fKNGRGmemMuBdmSAadl8s1ovfbXkI+XfTYsCtrUfxPn7pelDIqJrnd+/eikvgRlW4p1evDFW5CXjZaWV46Cz+mvuWgebeUkFslzrb8jiQQTUv6gph+mq/W3iLxqqULra8++egf5sJCFOIZIwMWoUsrqWwfIaQ0Xd/UeY2kqlb5P5o5ZRwFWZ7EfCw978CxbcalNr1dPmTB2Z598zvioTH73wEfZVPF18DhOjsTjuS0zhBcOWD32pSWR3r9S8GO4HozH1lh69cFHHl1em/KVrPZikXwiJMUOvRq3x3nLfBInHCa+glMUhtU0jLFzMu+6YX9xA5+x2Wi7mDTeq1l5+SKymKneve+iyDjfzfMeTrZfyvU32tU1c/PxDlLjjhM/HYtdab+vJOQpKHx/L/9y4DRbt/euDogrBShgfXIV+IMpoPNLlbb+VIQ9gv64SNjQ/9+mvyXBidKHfl476ZQ/vpTc3mtgrqCqCiRD70VY9MKO+DOihqRFD6VktwcPg0Ipt4u4O2zOtJRZCXel3QZcHwRU78zj5zZBb4OCX95yub9mxT5d0rKxluD3CTPF3N7Fdb6X1XK/NGJ8fPFYLMvKv1uscgjz2POXvxic/DnppDL2V+Jt0+tKUtj3d33LISWxLmV0zr/S4v1fCw39ZWElsRPi3WkxCrCxlZ3FWcsrLoMXlXWWxzSoOP5R39FR5v33xx1RK1F/vqvjX4SOAlfL4JNxvWclHRclGLHID+p8Uf11fBL/4d33FcPtDotsON7iKyW5x+7pKYfvjlt9NTMnPBjsCiR9/IcsCn50juspjB/+FtIr9r4xwVxQXWbFZaS5tClaeHKJvC6ApZTq9Tl+qFTklZqsbDjrlquIUeK7fsUEv1SKkq5DUEOz2z4WZLlbyZozGa9vXNzXj/6LuNKWuiY8XdvVWo6E0LqSp8wed0d1H8lQhdqYqQN7L3xIqj4r8r4FP9F6dAMeKBM8CoIxaCmQVoVoNjMbjPdkxiQYII2RAwVFQZoYSnSWgXyCo0fq6YRmdVjqvtyRUtS8qX5QgHpfc/luZ/6cVdROzJ/g/CdW00g20xGsORVyT/ueQXWqVkFcAgID3u5DdtEqLjnRixScVBr+j5pA9YzrZRHWI1XJpciXfdyXLymbpGX/GgNvgz4H8BNatqsDGC9/GHhK/LZVBos9bu2B0uNgrhQ2+lt/4zl653SnzGnJKDZlC8bZJvQ+gFOomQwAwWkvgQt5OkBi2Vu4Piq8YHJC1TaeWswAALP/T046zfdnXll2ciAItvy/1dDKsloUBogMmFIp+Wf3Ioq+JiU5znO3IYPMcUEAkt+q+qnFy0O8Lx+KPsGr6C4DoCI3PyPcR2JE8yLo4j+m1znbKB/hBnDSZopW2YjfOFH4L7kOibsvy31H8Js83DU+5kU7WCPclxkmTYN04aFrqvRWDBLJToYIkLsKp6IjHTyZmquR/nBOmjJvjL9Mbo5YvK7xZatWZdRO1ZVZCFjztU3UwY4RsPOBd+RZW6OKC4EXweqYkVD47Dht+NWbQMHIPFGAf4V3qCr1/FMm8EzItdwUwhYmnOCAdpnqJaX+x8TsrIp0t5q/R7Giwsm/ZNWBX6I8W0e/2XkTuCZeprQ82Aa7vH6QeS69IiNpCb89coP8qmlE2rXPWH1rkVySDlU9OH+JeoP+Sypj90AqBwVe4C2X5hol9egUUCv0kipDbYljldWK574jm6pN9wCdD65Iqck76HgB9hruEXw/KP/khZqF2qDjq9zLoXdP6WuYuU01XSg18SfNYfCUxPG8ZMy+N62KE3AGfaHZDaq+drhp4V+jj3oVJ8qRfRrcjnz3dKafy6/0VQpIqHA+L/BjKDP5sUDVk+F1Qy2qvL0tSX3tGYXdNc4nKAEb7XLyt/Vg/6B3+ahrbZbeGhwnhot/nxZ9sGu9O2dtEfnzpvlM+EfLkY0MJ7Q/VHjX9ruHmX3US3+Sfht3NOT/b8XnS9iTNYVtDpe1Zz3X4xY8ZcQ21QKuhBfGvDb8hCb1S+iaRoPUfvyJLP7YV1lvoOfs947VFe3zi0EgvPBPf+qOz0PiHLsv/hH/bkg1nLv45oDhgrPl/ePRH6au8P8e/DUnwS5F0iTEVLyS8AasbPLvYgwF8IlgYFH6VE5glP2edrPylqaqaoICiAi5m/Kq+tbX1QE5weqtMr5P9OjDxseENv2/R8c7vd756/ZHriRd6+XNvcGtezPe8K9418+fjMklMqnXaCDS8YqVy4H8ocex2E9jrIAGVGKN2vopiABjzUf284KLVyVf/prcgv0KxmhNidH/eeT0nBSPYXo8LMxgx+j7oMvNRU081YZbBuDv+18fJ6yEM/2M4eQOa4lvglzRO90/l6YQnlh/z5/hghht5V9cjxb7bbrBzXoWdEAnf+eJHovBbvy03beIyAtU2bW5H8tueReh5mTZLm1oxsihg0/hgcnMf295bcu76qo3ysO6XfjzcJFPQf373Ionrf9dAqblQL3eH4N5E9ofPx77TUn6620Ar9uDh86RrwntR39UiKS29GgMbC/lrq+IZZVx/lyy6uprEy07XLta5KLCaNCvJQd8rWjRD1xNrkgOOtUgzAMnJ1067IpXPP1yjFUu/dh0fRn9xpKqfJ4iVlXI6AI9CYKPBo6FLJ3lYpIKJ265xtzwd+OgpdJpOLdEEmzD7zSR0upvKl7ENnIrc5t9idq+qB9dCCh6U643SnvPmkpmUWx9t9TGFTjY7FyLjGQYA4M+CQQrsAkvTqngrYS2aDhfVd5hLQVwtLDIP2llSTL+NXGIt08NNw5aDG2gWzx/vnAqeOcl1Owdr54Sr46Wcl1+S7rAvxIxOK4TLnRVmkKPFbC0kVnvjTu8JuhXCxSbQKg4ns+AnQbn6Rz6MUdxBrodB94JrfVZ7qD0McG/1j3zzovO6605T8n5meY/8dVEsg/nuC0FG4sNwZSAGa6147GzTd+rK+H97u6+8zWHxpq0xZ6fFbso8fwTlb2aHUviWCEwj1JGuIy3ztvbE0Hhg8n1wfnEwJCq/QH93/1fKV7QY3wP7cNC6i+rNZ9dzQ/HrPfNPrDkoHtzr3db+QSTUOJO/QXqsnZ5LuBJMKkNXdkOiAcJ2YxSjmJBvYHPEWDzdnBSmKG8F+0/a7yCz1T5ofeqgJMUG70ca/XQiSCxTCVyzQIvPnFw9fzkHeMP8e9S/aRLIZkdxH0CrZnkjQluX1efyi1lfR2g6DoJ+LZd/8atQk8vx+6YVRtaoXMVEIeVLORTrNssspE09Lcf0wkHvKt+OGdILe1RqUrlRtF3IQGBi6sjK2tw2ucM++GLxScS8NyWW7NvyOjo/tLIbtubwrcU8sxDXxodXeYbnREDf3k4f1ohIZpLQ2NJwn0IHnIiCOBPtkIlbwU0XnAgW0VFfAbdSQBwadbLAE3UQupSJhJoCEjhYF/gCWWaylr97xM8IdcDCR5Qur0cC+HFmOGMY6xqqEDiGDuyDJ0B1xCa4GLetX7gf0l6yscVwh9qSJai/TOZ9FRN+QP4ojo1wJquLt1Rmi/vzAX0ipmRNMTu85UuKx+/DyE4M3S4u5bSq8VPNa8cdOR2HK+bwWBLAzzVMjrhuQCDvrubFgPQqWb6nc01Hd2QxlZ2jxIOydy/bXIOPJOBEjRE+WADQ47a1OJgofiyZ/pE71OBQJwko7CvGF3TQkR76FSD4ZWyDdR/N1u08+jnHxmnlxHrV45vxVl66XoXuiyPz7L8ON/dtcdHAVfQz+tzgfsi06AP0M5EZIxwLVShVE+mbyrmRzExsxOLlrTmE+OGBUnLe2ljkjIC16sWZ4V8FdTeGyPGzT6rY1LDM0ZINMqz3fZgPp/2+Q54Wx1i+YgJQblpP+Qf6nrcAj8SAp1UKOQznXs4RtK0IT/8zxu8u7B8qAlutCfls6sBHPFMcpT5MJSZ27Ng9a7ZeOZLYWhcOAC9qxwzSTD+/s3KBvT0aybZ1YXIOXHvhbc79moa0rLJFRnTCRwX8tozC4nu/V1U4W3lthyXLSExrH1at/20TmVA4/m1KvpMbNnWQ/iauiXRhNJ73AbRtNE6OrGjdqRmMiSPBbMo7WfG5QWS2pt3AkZMBm0bvU+QH0JtKzXxBTuMuG7rbxrs891vMOrJirH1M18dNqyOmaFDRNjJyXlzsIyGvImsfmYZhzmSDQhXoVRZm5kd44dPWAWuRbYrg2ehf5O8m7IJA8j31cpPuKuMVtxDdOOiLGODaqNuxy/41OVlnaDsra8ujLYmO+WdB3h27ON6DIuR/BIaQFZlicaxGAVHQVAi3Az8CnyUANv25ARdg/ug0uL+3CE/burc1LP65PheKnHtVbTtS6cxxMe1y0Bz0iaTfhvyo07HLhbJ40ApAJEgUHosF5PPBD9sG1bnPiKPIbpXrwBeV0fm91ihdE1jHq1vG3G0Lu5dZzPmlcNilDF90wLDPqmksptYT4zZ9nWt+hpxlkBMwbGn8jCHSKX++gqZH+q5S46MlaOS5XMCJ63Bf6cuOxDusLX9sjPKRXCzB0sZmlSErblD1MmhUQmtVIJdM8NRZNehT8B2cJpUUVW6wPchKweWZFpXvvbZuOVwO/nbRUTzTaIlhmWxx25OEKnrgui5p7yA8AeEyingTd74XoKCmQnwePmxB7ZElnp/T0o/WPx7ztSBsBXqQHgvPqGCMUOvBhjH0rf6rLfmmoqDfqw+6MGdt/JvQfGqUzya+7f0Qua3bbBKjS5vGoLJb+ZNuusamvN0kOBa7P52vni1o4vSmZbq+9NOa+9gF6MtJDPeCX57/9FWTgE30IkVsqI8qihz/QoubmuGeRtTSt65U/rlZynuVIo0lFhTgw0HYfCbH/+DKC9gud16HI9H4ne+32lOuGyGgvBn70LhzuDbqqd/wS57gf+dwm+5l2tYuWKnt1kGgfCJ4zncqnm5AFaweIXdTRSio6yZIGyOJYUatoJtuWUF6LyAfvSs0Op5C2c76mnOmbi+SKqohpEHFwXjazY22txg8ipkIvFLX8f7OQAn8WARHyP1RcmA3jsHvwqr5UFNiB5do08tdFPIPjWZYPFDYHeeWGUGtEdfu4fC5YSkjj0/l6+4QCUIO+5lf9Vbfc0+dOI0o3OwW2+sKJG+2W7Buz3/0DIWBzsvRcaflsb7wDiRWdUTveaJtdQ/A9eb8BuX+tZrMBe/UZXwCS8s3+SVGPw+Yb/6D/SB+75Yn4Hysb8ADxXNINpfMzF82SQgHa6+2umCVmX2Wuy5bLoJJf8OXpqmlNhGCnKP2fP3GKfmQQpmrfCx3pqyqS2MNbKk3Bo8R394rcNq+dSpdx1RbLGTsFvq4W+IFUDSIdqRtmUA9VsuwpysXPHUo2D5/YkS0dgOtYs0FXdznLtlLTQwcd38MCXjHfRWwRr5+Xpydg3Vvcy2Deq729nWaMLpYRFTYzcurs2lJjsAfN5xgavM6T6opmggprRcKoPViDp44mS65xxn2Yy5RZjIZ6hHbYXRo6O3RQf6tVMOc3SOZNaJTx5d2pN9TfeAtRZ+dpdOvJlZkv6dO513pXucGQ89OcSXK8euTeRc0HRyR4tCnABTj6WrJiPnDNfBJxEZY67IMZem2NMpNZbi/Gc5xSL5l/KBtxiVH5lqun6lt5EYP1Vo5Rje358T9ZohxYTzYPE+XZukxmNmJZ0pwd0x0mNTmdueJ3u6gCSWAGlgz67TGSBxbm9E755K0c15jFJPLEI4SRw3tbjOevqomtnx/4E+E2Vztn58iIvrRVsJkrj9rj4zfWoQq3wEqwKB4jNBYusplE4Kqs2qJZOfqOgPkIl2kxjTcmQaa+deROzVCXwVCEot0WlBfn+9FyxufsMk7uXuQq7GK/HH2Hp/s47vkvG6i6V8k2lvMLITSr91EOlCeyYGDO0TV0qtckKpuXicRFh9HlZJ9LfL5ZgSg1ekW0g1ifFtKXenyyekltltVUrmkswwJkqDpMOo5AVhYdas1TjfX7TL6iE6iowhLaP4bemj1ycNjZf83/Vbf/9SZm0mjRIcvZ9t/sfLQLYkYDe6zSyph3atTqrEVlbboq8dRlmMj2mXCikbnboQOO10oIdzQJqw5imAVpyPpM7VeLuNF7WQOLegiSiQo2eloNzs8r/tnq6EmZB+vd9vzRtsX7TXF0x6zkTCirv2lemXPSiw4qTrkeyhga2Hw5tX52wHjelT7YL7JY2wdfLDzHA6mlivi1Jgz/l5K7zalPf/Dxj+MdoOsnjN1ffHiETq3A7QtIif2YPSDuJAp39gavduMDT9VKSXQuvLVWCx96fvK44haGuCaujI52zxM/N/ACQy8U39CKa5sjQmxCCZIXBFMEzbrm0ku2Y3ZngbjYHFxsZkfWz4y09EAaTPrGGg3YSq7uV0daMYWacRU9hRs5eRrfKcJZWtEl8bBekl82ZF9t0xoq6yLNxFPBHX87qj3kwXtlr8A3QXBIALdLh6t/JnToDUSubKBnB8K2Cs8m+8hkm29EzvkBEyTxybpSwdt4mmmH4JpI4yiK+TL1CJrH5pOYmrBH6vn8vl4Zh10Oa6WZ5p+A7jK94NMoSIWtG5IAESYRIuLB/Fv8XcIc7S0LMssz99t2bw7B3k04vagha7DjaDXsUt71KLznCEqR+YjavxkJJ42D4RxeKHsobD1Y/mrvo6FJoYRM/Xicsn5eczILPR17GpNaIEAjglzltdFEPDeGvd1l+12DmNKZ4qr7ETDuk7s6EOuZysFHHAEr9AuSYLPfHH+xyMaMIwlmvCox/83rfEkJR6K9jEG+HXaftWyb/RWQ9C0nTZesn2LylMJBBFiWuakHotm+OOejrTZkGgV/fKgb8MMv5igEX+9X0C/7EK5EZreW4/cDyzpL2rc1ntuEpYHc3pPeKmtOgXQMX2lGxqaz7SWLZiG6LbS6lqH7kU2CmSw4X54rOLVBSs94OkPE0OI8/8B7rTV2Djk+3rooQZtiqjcmNuYO36rIbmmf3eY3yujwymOoMvEtrYuRkKproqtAIDX6/2NE9PeDaS13gFbB75WH80DIbnuF7SR+ROQdMANsASJYtGngwT+YtgLpYRtOm3+Vda+XUXB+okEOJWX9VhUuZgikanscrjbLql+EGlbg8KlxMhWBURhUyMce8SUX/5hrfVWzcodY/XKJlLZcrfYOlrpmgo4X1VMDbIPttJ8JnYbaOx1MkZ7sx617EgVSNmGj2rRO53rcAE0Kn5drVWsEktIjhIfHxk8e3b6vlkF/kLCvDFAoaNBCazRYf2xwq56+scQx94PG5MVN+ITp8DnWgDX6tIrDmkxmaFd+mSj/9wJa2t4JdOMKpWWLRj3jLZ6VPfoI1sfz0jgOlmPQgo5FBM87lts84aVxV2pxo+mL9dmDFmPfDMUOiQE3oY0Ahs/oZRqwx6UJdyEn9l5E/MLWOcv5O1zYgdpBh5aQTvyPowcdOXVVyBsQBNniAwUsrRQ6TLZnFrzaC6s9XEC04XvKVQpaKnnOxMX/lLpYgr0xN/LUxy8TZ8nZ7a1qur+xQDFx7L3EufK1RI2/cE=
*/