// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <string>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    typedef Char value_type;
    typedef std::basic_string<value_type> string_type;
    start_dir_init(const string_type &s) : s_(s) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor&) const
    {
        ::chdir(s_.c_str());
    }
    const string_type & str() const {return s_;}
private:
    string_type s_;
};

}}}}

#endif

/* start_dir.hpp
PhvOH2JB7WKIs8vjnjfylnqV4iniR+t5GwNQ72jcjsFTThdYj3qTDs0z910T1NERSOGgoaCsbs5tl22lbsdtTKbGZ42glyK49S+mPtQyZ6PpB3fEQBwG71CnUKZQMYL4t9+9mfrluR4QhHUf/GIahfLvaH379aVFLoU3yqfReyeKQd8g41z81y9p3+FcOgyHLkaLa574YML2ujG3GZyxPuHivORCtQr6tS8ajvg5btL9RHeJ5YzZzH5K9Yvx4Ity7sYLY1TCBC9CL2p8jW6iy9YKtT1HlDTCNHyl4nqFpwr+hGm1ot20MGr+emnbx7PxJGpFRp7EkZpsar5Y1r9NUSNkH/iSFAdxsyOPq62g+yVi1kVF7nPpLc5X7QRNTPmt3GJmt3opNjHf2EUDtLvMbk/Tk7lvd+YsDQVi972n5W0Pla0laTpIlDfezhKSWWdkKjLe/uZbt4qzYoqvTcNeQL2S5Lf/BS9J5rH6ATrlDU3nC6bVs3xP+0OMXamvOPdTGXPRt5YPjsVGm/RLtLOdYTw2bHyslmRKFuPqywOUSxy0AuQvo0XheZIXFWaM7nLGXWZFHMV/WRyqV87/jGPzQVMyPe9DPPSnY1HeWVgK5ZT1HhyT3qGHWoKjMlodGisB0k01Z1anfj2G8OaxaCV1fpfWWC+9ux70RyxfyDKG2eHcjF40edryzCL8u/misiRkSdbDmIB3c3ssm+d8
*/