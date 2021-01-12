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
OnPKykoLcsvLQvP/JyR/48R/fcwBMY/1d+Zru8F1uckSZl2njvYDwXwM9SV5olcnVeviHLn+buAep53/Vf9BU6eSJeyb/X6+sBnSM+QqNp3Bpp3QemaZ+I9x1I3GW93oPVIkrBhp05sbaT+0yDHl9Yceofa531P2PXTP0r5Y7kNAATI70CChA+ug4xK6st4ZE5VQy0UgJiYxKj0mkBhVN3iWaX0S7Qw/ixFLXyL5OV7rTXNN
*/