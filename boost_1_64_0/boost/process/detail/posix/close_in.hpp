// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP


#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/used_handles.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct close_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::close(STDIN_FILENO) == -1)
            e.set_error(::boost::process::detail::get_last_error(), "close() failed");
    }

    int get_used_handles() {return STDIN_FILENO;}

};

}}}}

#endif

/* close_in.hpp
Pkc9Gu+dNmfE1GfvybimxdS6tfNaTK1bO0HM/j6NPcTs79PYQcz+Po2VxOzv05hPzP4+jenE7O/TGELM/j6N3lpM3Y8wLabuR21i9vWBrxDT1/+NmZa2/o/PYJr6vzzT/lr9ny+x0+o9Gdr3KnHx3XlX5FW/U0X8mP29+TJ+Ik1cG6vkkq187fP4P1XvqISLesQ1KyZO6xqzPPjm6sXrJ8TectQ7Ouodn7/ecZ5Z/haTvx2TMYQ0lbgi58vIihUwGwahH1bFN7AaxmN1fBsb4kZsjFuxKR7G5ngMW+CX2BLPYyhexdZ4HdviY2yHf2AHdGXjOmIm7ITe2Bl9sCu+guH4KnbHUhiBZbAHVseeWBOjsAH2xkbYF1tiPwzF/hiGMdgZY3EQVsOxOBgn4Bs4BWvjCvwA1+IOfA934vu4C5PwQ/wcd+MV/Ahv4x68g8H4B9ZDM8e+PjrhMMyBw/FVfBODcRS2w9Fy3o1xGIPxOAQn4mKcjLtxCh7A6fgJzsAvMQHP4Uy8iuvwJ1yP93ADWj9f76EFt6EnJmIOfBvL4XysjAuxCi7CmrgEm+I72BJXYCiuxJ64CvvK8uNk+fG45znnC0k6qNXbnuX/KQcd/VAd9beO+ltH/e3fs/72kq4O1/2Qow7X8XA8HA/Hw/FwPBwPx8PxcDwcj7SPf2P7f/eBQS+m7/8mg/Z/Yvbt/8Ts2/+JGbb/Ezdu/xdxJ/v2fBl3luXoYy62MnTLe9v3H5Dx7Hb9B3LLuI+Ih7asVbehtYG+VhOxjBuvGbfZ99e12RdxV8RjmSvX49IHvJIyTrbZ8y4Y30ugjf/kGy/ahY3uI6AcozZ5bRy+bGLZyUb3FbCs4X0Fog/8mt+fPi0klo12NZor0I9nS8Trd12mmbM62dqIt08WbcuizCRfWxusHIubMjMT32TXjr9ClPMLffHP29+fILblBMtFiDylXI3a53PLclpPIg9jGudl74JIbZQsYr0bWN66nLdYbmD32KExcV1itGNUcKJ1OWeRN9kobzNtbHIvkbexyLvzd+M+Ab7yfcsk8oYrFSm7mSx/Jcukd39ECq81EPvZwNWon4C4P4I8TUSeuq5GfQTyy/em5AQx3qc5TinM+BB1GKvgmjLWnEkdc3WpeH2ipbAyhvppL8Y6X2cS92hQfl1RfhPXdPsWkEfX5twtsosY1Fwdc7mCWL6Ta19Kv2hhNEqna8pW51YmX/G6bd2TeHW9ckJJEus9TZnxYjl312eOf6w2hlgucUxLiO1IYhmj/gu+WEqUFeH6xCWbOBf35xXbGqToxqP9SpQVahpGz+NvlXwsa39soszWbTvCesqK8rq62vV9UN/rOuK878JnPKtSj+Qt4ray/C1sosVa1gXKqhov1ktZ6rkcx5kj9ukgr9vfr3KJWKBYpr1Y5oDcF951df7HAeLcT+Ks92GM/dnivfAhnlssN9i1rbObMpDk4eKseFJKOn0kxPqusb4QsVxN1/T6WWzXn8dsC6+mmRPzO7E99dT3bYw41m04LvbnAMdYHvf94hhGGvatKCr387hY7kuWyUr/+Pzc35OVu3S8TevMWZUkknXbNott0/pNiJNI7ttZXgsT+xagO/5x/WP6BInX7/P6aOvrHKX0+keIe4jIN1HkcxPl/OwpPwuKor4n1cU+l+OT78P74aEem/4ifkU9FivFPsUzIvJtcyVTB68mhv0stER/CmEBHxT9JbTnMaQBMl7M27hfRpKBWv8MWabWH0OUt1/2yXiKsbp7mwby/zjSINJga5w0hNTbK3Vc06Hi/1r+bPx/GLHhpBGkkaQ3SaPkcqNJY9S+Hlo/j7E4jmTYd0TeSxXmZNgHRHxcMys=
*/