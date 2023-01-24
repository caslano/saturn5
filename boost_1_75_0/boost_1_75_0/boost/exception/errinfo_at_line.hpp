//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593
#define BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Use with parsing errors exceptions, for example in a XML file parser.
    typedef error_info<struct errinfo_at_line_,int> errinfo_at_line;
    }

#endif

/* errinfo_at_line.hpp
NslKtuzMGmWyaNryz/hQjfJDlD62Bd3NBQA4fB/iRX44DihiDAj1CTdtXFMs+UeaYtUiWOoAESzu08cyG9MUJy6SWDL4LtIUZ1/JWDICXy2/UmfzL2dYbP5MqEq0zXyzTaim2Fx8xJzbRqHJ6XRNU2zQ5fdGiKa4OZ1RhZRECelzaYoTz64pFr8Ik5s0sLHdM+pFCZced9LueaCfPO+Fr97VT9s9s9Kt3XOq/u6Z2zp09xx/QYDl4dYKLD/013ZPakOa4qshmuJ7/RksCBCl/iVb6l+q0hRTNU0x1J/ePjLOyK4aC/rXGMENpoi23+mFjLxj2P/J1PcQ/36RB/l/fsR9tp3vbYB7g+neyjxr78lzMgtRUYrcuFy5Q6sjwCoDWp8k2C1lfnUwvqxyhkEE/3qrGkDzP9I7C+hftaKTWOXiPkF3M4GfrqUbPjSM6NKYzQJSwzZUbJzalMo8PnWVRzQOwFJtcC2tiVkr9tSw1QEoLth3/eQ21GiyaLQMynkG7gE7jf8Mq5Z55okCMa/8TEpXttn8qHUwWF5T1JUPeECLR1a2NsStVstBrV424VFKAZTjyjyZTdUWi0B5E9SN6Pz6zMQEpPpVjydWo3E1nBlnCVig0Zfqnin2mMDS87KrIq95qZ2xQmZ1hxeC7jlAI6oiOzzfDg9IJIm/016ivxPkZzmdOFeEadrWjTtiC4UTtnuJMDvXbIvTK7uq
*/