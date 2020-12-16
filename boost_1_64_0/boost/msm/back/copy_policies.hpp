// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_COPY_POLICIES_H
#define BOOST_MSM_BACK_COPY_POLICIES_H

#include <boost/noncopyable.hpp>

namespace boost { namespace msm { namespace back
{
    // deactivates copy
    struct NoCopy : ::boost::noncopyable
    {
    };
    
    // allows deep copy
    struct DeepCopy
    {
    };
} } }//boost::msm::back


#endif //BOOST_MSM_BACK_COPY_POLICIES_H

/* copy_policies.hpp
8BWHr+vIr4PIq+g/dz/+dA22QY4LlRl7LrbPeqbMWFXe/QsVsUdqrFIB/yOPhX+DrzxBjXIx8QobDsj3QL+FrphnZAz87kOskGvl9+h3u/HYIn1dj189h6z+jg7OxvcPJf8WkNUDjPEM9oxNVmZxL30Xb8VHWBcFb6FGQY7l2xmvwA8xLLY9NrIeG2esCj4jWDOFq8hhE3a9E3Ho8gG81zySOIW8xrMvgT0WRozhnBedcq38AOMTo0N/+QZxlLoTfOgn8HgevJ+Pvu9s5Kwd3yZe5Q7j51Lm2EPsmU5+Wco8Tscvtqa+Yh0d2MjcG+n3eOZwBzw9hnyRc4i/PVDlb4QEdsNvqPXCbyJX9tyDO7D/QH4q83vsPHi+azTvIBD3P0RXJxFbi6OQF76IHYiV8HgJ+utGFz+gPj2PvomD5e+S+ziHyS/AlmScgM8C19PUtxW+wz3M+Ws4yX354cRtbIs5hfg7aDPlO6kfC74bkzgBrfBHbBZfCHyXePzGSNaSxBViWXEXcshT5GNiVnWnMdT/2NSj8Pgc80bOFXlWwbXQicxj+HjWNFy/nfXqxeiT/eUQOUVIe12GDsZhk0H0Qt6pPokf/pixEtSnZfLog/DxKGu4qqCkZt73M8YgdLd5EGtr6q8CsePkscidHCn3Ze5ELqwXxMdcYx86PZK88gzroveQQWU0+1qsd/GjIs+MVOmv/G3s/iz0QgwvvT8cedAne1XifWrQF+X7PyNZB2Kzf0duJfYeDsEm5fqvBdn+lVr6v0PRGTnuGuzx2+iC3Bahfs4nscN7sYnkONbdzIGasvQk9jWG+FHChlL4ejLA/jTr3MdZq17F/j1xOMR8KsitUCFfTafe7WStQLxME3tDn5Nvy2NEbhvmX6LGx77zGWQ7Cz+6kTXN2/SLf4T3oDbCHyojiT8l5r7tBOSPvlcSKxaNQEfwUiROnwWP7HuWrsY+O5HXHOTxCv3xu2BeQeZTIp6UPyD/gc2PIq7RT2Bv5CHXn9hN4Er6+T4y4Bkh8Qz2wHszVc6fI78n7kSGkd+xL7lWwW4EtlA6fxw2zTy/gFdytyCeV/ZDxi9sx/4Pnycy9z2xnV9TNw3E35+ixluGLJ4j7t9GvXU9ttKGDDchZ+ZY/gxfrqKbAmsFfKF8GrzLsf84GHvHpsAVyMu5HOOuH0VOYx1wGTHjJWxlf/Iha5bwlfjLI9RdbxNnBDodPYpxeC5qDXK5mxgDPn0nsfML9HkKY9BH6UFi1q3EaGRXYv8lx30l8kL4CWICa9TIsci175kobHyrrbAl7O84YsBA+BbgacPQcr3EUeqK3Abi/vAxvOPBPO5ibfAz7AD7FGHy4IvwJd9lCQ0Diw/jPyVkU9yKsdkzKn8PHeP3kePR/VzWBC+jt7u2Ebkz4H8uY2aQ38HY91PkvzdoP0HWxOMYc8k1YUNTsT1iuxi8DXkXHX7Cum4j+l0Hbxchy+JA9kDk33RDltwblvsX+GV5NOe91NcBbDa2YRT8w/uv0TW1fvV5ZNw4gTkT8/dlz0+O/0/45ffQx8hoZ+TF3zgIsw6rvkysfRW/vpfYeB59HYP/Hontv8P64ULu2XUgMqY2wTYFNl9cjC29h+0hh6qUx6vYCpgwMa7EuUJFvqs+ApqstyYyB97BDuB7eZ4Z/lK+jz8ImXbiy2djS9cy3iP8fh/+3kIevQ79DyS2byKmbc+c9uH+q/A/6royZzH5o8nFT8EL302e+y4x9z75PBVzvpgxB5LPB7KXM4SarAG9fLOB/RbWtfLcsgl9IoMwOSWcpv5JMua52IaMr9BKcu1NXVP+9zD8F7n9DV/l+zHEMuR7e4A4xbwmso/AWIGzR+A=
*/