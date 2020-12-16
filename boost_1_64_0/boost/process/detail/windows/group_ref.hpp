// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_

#include <boost/winapi/process.hpp>
#include <boost/process/detail/config.hpp>
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/handler.hpp>

namespace boost { namespace process {

namespace detail { namespace windows {



struct group_ref : handler_base_ext, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    explicit group_ref(group_handle &g) :
                handle(g.handle())
    {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        //I can only enable this if the current process supports breakaways.
        if (in_group() && break_away_enabled(nullptr))
            exec.creation_flags  |= boost::winapi::CREATE_BREAKAWAY_FROM_JOB_;
    }


    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (!::boost::winapi::AssignProcessToJobObject(handle, exec.proc_info.hProcess))
            exec.set_error(::boost::process::detail::get_last_error(),
                           "AssignProcessToJobObject() failed.");

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_ref.hpp
T0pPSbDo/COMccq7leqZq66L7HYTzL/rtUr++ZL/FvlN9Z3tyjiOnZX5OKfr5n0U2gJGsJB4jXjdHKrOViXPImkDx1k3A/7gPbwF0/7+nJz17axLFtKK7j8L22+Q9bJY0vT6kvTLOt0oe8Yh5bJI0qXs5D7ALX1Nbi6nor9VuJXqnOGpzGQkpuJE/lEg853DuGLl4BGbkZnMSaiso8YMaXV5vnRD8pdxW19lXPxPXdep+mrUs9vSf5CbcyE9rPn9Xz3NgOlyPqu3mVDp7mA1PSPS6/qQ9HvWop676Hdf9fMU43sf9DDOtf1kuHqW+yx++vliU0lbSOoTgb7kWc9CnLqLe5uO+hJp/s1R8ec2uq44yjpUytqoK5Shqivu78fI+lX7ojpkcvzV9aC8sRYGV2Qpn5P1OyItg6+oOfZGvAKars53/xoi74nJwcF8vfW7DBPgdh0zPuN6zS7DqwOFUUf6zLRIDnfrmeF1HfGrKMNLRS6c9okZFunr7nxHDWue9+Q0l3kfJNMu4/6+yXPu9qduf8Oi87rbZ4aRPkKmU0Vfy82V/F4exewzGYbjnOQ5YXUdh68+v07Wz56aSDmEW7tT78dZWujj+0oZx8/WcJ7buexH9XXDRhm2AW+7eet9b7RMy67bRtX7VIrAfC7/gozfz8NX5zPeu9gj/eqq6bC1yHSqWyN5p8T9vto4b5stww4gXzjP2rpbrllquV8mPV3Zhetr1jclz3VrkO7P8Vlm3tjP56p10MHyhKz7L+RejPNaNM/lHsxGZajKs5j+8033ZKqq/b73H+z3ZR26XJc46mao3q6Mc4tsu0qngMznzmwHpMt2IHkD9Dh0/Za8Iebjhzo32SHLzLm6asPmmEt3pxnq3MXlOnlDlnNBWhnf6bf0jKScZHlyRmUmc3WcljjKfLVMFt1mBO/GZRR3T4dxqH25vl/rbl9APpd3q1y+b+BmH6CH0dcIxjfa3G7zOj91wuYYR6DR7qWcc7r/62K+DnIsb6ha3lJqXRa22VTOfF/NZf5lXep+ej5lPVxGCzO0z5f5tI6f2S9jyYMnk9e8c6brW0vHxvCOk5cjvcLhIX4pg7o+c9JnSkbVWtFLOB8p4Uh/c+7QXhvsF/788RvV78yfM+0N2r6W8Xzw4pOz68zcOPRUmb+uvlLzvoZMw8eRvn/cgd13rrx4ecyMSmXWz+zPuHtIeotrNWv0uTp+6uqOT4SfLzHjaZkn0rfvjzm3MqX82Tsv5bU7XmX9Je6reDvSPd5Irlz1qatNy10vFxj6/uDjbCu5jvQNHzf8bG1kuZN1hoza/Nu6Y2xHn3o60ltGJl6dMGBYbdvIYX7jf0w8wHFOxn978LKkHRE1mu177BPvj/a9V5uylvEvWTd/6/49T14fF7QxpLb3te60r2l1pIf5J3T+6tHzqfdXmzt9/JhVVzi+yfjXnn78vlfjVvk+67fXGnZ1+SZmX8ph5aI32z1jt91uM+ShVWnfPRTP/VYZ/6f+wZtjGzbc/ohn7aZPVmxfnmeKkv/8zMgFdXek3Zp4aemmSUsrreE4L/OZsS91ypWLNXYfeKltRJ3TTbZwL0jSJy9fcOj7nVFRE3f2Hp38/LLzjEfK0/NymRupPZMGHvet8XzGrIml2GfKdKOi3uzzw/7fw3sdHRfR6/WIXTwLk/l/slKtyA1l5qy7OeaDaV9Nv9SLo4bdkd7zgxU9vr2zpvMvq16Z5/tWtdf4zaekZ5ebfmXio/OfePb+fq8HNPQ5QxueMt1yW8fPvFUl5uOpo7usm/LRO3t5burhSH/r8bEx571eePOpFcEFe5fN2mGh3jnSxwbN3bbtyXJ99y3+0/sFtfo3Zr8=
*/