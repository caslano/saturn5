// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct null_out : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    file_descriptor sink {"NUL", file_descriptor::write}; //works because it gets destroyed AFTER launch.

    ::boost::winapi::HANDLE_ get_used_handles() const { return sink.handle(); }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void null_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
              boost::winapi::HANDLE_FLAG_INHERIT_,
              boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = sink.handle();
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

template<>
template<typename WindowsExecutor>
void null_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
              boost::winapi::HANDLE_FLAG_INHERIT_,
              boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdError = sink.handle();
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

template<>
template<typename WindowsExecutor>
void null_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(sink.handle(),
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = sink.handle();
    e.startup_info.hStdError  = sink.handle();
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;

}

}}}}

#endif

/* null_out.hpp
pTrnbqT5W9v6e/v4W/lwBp9pK/Y3xTJMLsNsD3L/bkSYyrORPHvDyOOXc8XfVlrne1vlK9z/f0GeL4mviH3EZPp/rbr3q+vhgD84V3o5yPhdaCm1Le6X/fpovR0elG7qsOv5kVE31XWxuh9a0zmR0k4YL+eBoXKMcm5vmZkjMrJjs5KHpcVnj8hMLLwuvk/OO3SyXv87ZDi318OM0/X3jVn6ufBO6ef9h+9jFJ4jMn2WyZi++X2Lefc7B5hLWIlXiOORlLtapsyUrNik7OyM2CGDpR6uCpFtN3u0+3vmDGdst+87n5mnur++0Xn1fsli2i9dlH5PMJ8eMq4EuZHmmB3jmuuo5HnB4sl/u6ppHg5Q+SzGO4BdpPzL6m3VW7rbkGKTYYLvU8MkGMe7mzLuYWwldrmmqVmTuavFsd1Rf72i/L1ZANf6G6TyLSSfLZh8nlad5w2XPPnk8XDk8c2ZotsIUHkKp3dWTy/zH07P/341rhJ9LHpcLnmiyHPQMS6fdhbX3+qXo9vTUfp0HyLPYUK8i9+kFh7nHPUiVOqFcZxj/ZMm67/IM8W82s4RVHRCHupdWY6LwVLnGAnvo2XHDslOSR8Wm8IbDrHSIISsq7Sy/7D+MQ7XZwkZ8dlJxnlGtvQPZa9rd1Mn9fB6X3ckjHoWZvnDba2wHJg/VQ4u9+hlPlzKoa5zBH3ViPoQ8xk+t2g5jEzMTB46JpbnVvHZjgP5XZUD43B5/t22tZSiqY2XOZKnO9+3qeGmLNyPw7kURnnOkzydLWUYh5vjOONwPe6npas5cXufzX1+markDzHlDzHnZ33Z6D4Wxv6L+OZfXGdFn5WrOdXHB52u5oh08z0rY9kkPcScroYwH08a1nPOTAU1UxHEEyzYRef6T0jk99zpY2KNF6Qtxj7gBMvH7+nlPWrbfBK8dDZ9fLki4/H9w3Iwn1MmPaC+cyTp/I6ReI95CgiReaLRHg4FPFSIzVbnSvq6lWsr0z63juTPclc31bis5vNRt/VP5zOuR/S5Tz3pl6F/Zz+G8fxKnFLxOnFCp5nS7+K5e5F3KPRyUS+Mc4iiz52jnANXccL1C9Mpx/atyowLQMe9CLlv4+ben7syUsO6v0e3RfrZjfcM7qKuy7mA630hdf2xNsS4/2JerlvFLNe+osvFhfLdL5dzWOvdznuXP5r3gmLm/WB99/POCMzzzsq9+3ln2GLXSaXQf2qd/OFyBYS6X65uDZwjCFYjCiKakzfKuVxyIzD9b9SdeXwURRaAZ3JASAIkIRcQINw3hvvGgBxRrnDIDSEkgQQChIRTUMJpgIgoyCEoUTlUZAHRFVdURBRUVEBEVMSAqLCCsBEBFWG/eVNT09P0SNjdfzY/Ht901avqquq6q7o6KWdyasaE2+YJx32auO8j163V9UjTff2aOh3WQuxITWQgBTFR3ZedH2SE1LTpqk7oEOUwTx3FpS6z94turFXa4o9nu/uNnA90+30hrrLquF+Eup+xf1ujuVN5NeKv+rnV6O/lOsPt2J+bmpU0RfUX2YMZJuHO4lKPh526q4n7BGOYMTfPvY1xjBn0+G+T2E8Q+yth6pw1w/jvH2IfZLln/hmxy6IH6i/u+7jc57jn5NaKznTbJBWGZySlpmRnGMZ6H4pOFT3ftlOu+9NeN9J9JNxwIJV7bH1OdGozzomwdCf758kPy5qxo9TRp7RXlv3zA73vnxf9V9Dv5tAv2fSWMaKr/T6J/QBk4B30PR3PLEI/M2OZUs+DfH0xwr0v2NgGr27h9HAxEoHMVOUpNlLyR3pyjrMwJU1LzpjMkrdrTPdGrPMst6wpk7PTUpz1xVl1ppqvOgcvPXlCqrGv1F4=
*/