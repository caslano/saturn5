/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_10022005_1617)
#define FUSION_SIZE_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct size_impl;

    template <>
    struct size_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::size<Sequence> {};
    };
}}

#endif

/* size.hpp
XUP1XU84HSmKSOofvTw6gP075h319oj4oCcG243pDsW4KcKZMzk1q06W+h2wfqqNqWPuR8WEUBY/u1l6KLnToprqvLpJcnCN16zlFMQfjfEls96Ge19soF5SPF/rIGAaEl/Xwx0DYqAolKbcT4DyS4pzA4PisUEN+CkHtSp0KECC5ExBnVInJzXd+ZR7WmGvDg0xbkq/rG3oInlnjG13PmsIMQgbVqN/R+OSRIMKPTW9kWMnZx0nzUJOxXdC2E9hltq1V8MY9J4UDOKUQlGzeEVs8ffWCY/m3AkUTe6zyMlz5NPkxrllscEVW3PS1Vp31WoaAs51jo/mXcBDfenGa/SMlf9Yir5x9Sul5nDt3cr0ZZAyjp1YIijhY42P9+I7V2xU3+2Qelx6sbDTwGLSEcffvQ+1BraMk7OXg4TzEGtmQZu8FKcXec+OkKO8NYxrrwGhuCM6Gn1PX7nKsc7QNUaKPZyEsR5KOqCFS0PBs6dpsSTkH54hlRPrNTQsHpiSNnXwBLm+adI4wFwu4eGE8xixIyPQZxsqfCGeOJ4ZVFpyGOPtcpfg/bmOnw==
*/