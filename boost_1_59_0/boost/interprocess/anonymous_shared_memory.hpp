//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/move/move.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstddef>

#if (!defined(BOOST_INTERPROCESS_WINDOWS))
#  include <fcntl.h>        //open, O_CREAT, O_*...
#  include <sys/mman.h>     //mmap
#  include <sys/stat.h>     //mode_t, S_IRWXG, S_IRWXO, S_IRWXU,
#else
#include <boost/interprocess/windows_shared_memory.hpp>
#endif


//!\file
//!Describes a function that creates anonymous shared memory that can be
//!shared between forked processes

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail{

   class raw_mapped_region_creator
   {
      public:
      static mapped_region
         create_posix_mapped_region(void *address, std::size_t size)
      {
         mapped_region region;
         region.m_base = address;
         region.m_size = size;
         return region;
      }
   };
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!A function that creates an anonymous shared memory segment of size "size".
//!If "address" is passed the function will try to map the segment in that address.
//!Otherwise the operating system will choose the mapping address.
//!The function returns a mapped_region holding that segment or throws
//!interprocess_exception if the function fails.
//static mapped_region
static mapped_region
anonymous_shared_memory(std::size_t size, void *address = 0)
#if (!defined(BOOST_INTERPROCESS_WINDOWS))
{
   int flags;
   int fd = -1;

   #if defined(MAP_ANONYMOUS) //Use MAP_ANONYMOUS
   flags = MAP_ANONYMOUS | MAP_SHARED;
   #elif !defined(MAP_ANONYMOUS) && defined(MAP_ANON) //use MAP_ANON
   flags = MAP_ANON | MAP_SHARED;
   #else // Use "/dev/zero"
   fd = open("/dev/zero", O_RDWR);
   flags = MAP_SHARED;
   if(fd == -1){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   #endif


   address = mmap( address
                  , size
                  , PROT_READ|PROT_WRITE
                  , flags
                  , fd
                  , 0);

   if(address == MAP_FAILED){
      if(fd != -1)
         close(fd);
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   if(fd != -1)
      close(fd);

   return ipcdetail::raw_mapped_region_creator::create_posix_mapped_region(address, size);
}
#else
{
   windows_shared_memory anonymous_mapping(create_only, (char*)0, read_write, size);
   return mapped_region(anonymous_mapping, read_write, 0, size, address);
}

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP

/* anonymous_shared_memory.hpp
9W9XUY/epw/LyAm01h8prsVY7JVIHTx2pqyNXvSCZORcf9rVJMBB0gOaX7EDcl8RGbMBQYVo3aYN+HhYEazf9jr6FDfaH0EBsIRmT6ZQEXqj8oVy//H1f66HYGr+sZJhic7oLZIpg3/mYocGCOFHqWvE9QWckPc/l2L6lSQIiTP+BBl8oVNtGK8lH/yWbXpy3guUsWTxun/BHBk1bZapYzGGFCNgxy/NpuDl+cvu/FAnKDAK5hol3Lb6v61VmIs7ripT3Ix0bjGMJxAlnWgeRNmRg6/U3JoBi3Qwej0dbBM/O0T9b6dGwm5OT2MdvMELB6mhYmT6p3RLZSbFvlLVGyqJdpJTeWB9vO9tkjIPBL9Fqf4Es8pVWR2atutBbwHCO754YP0yGbxT4pOA2fDUam25pDKl1K8/ztVTAhpqx4JanBSLLi74jh2oE4jolPDiDPq45lHRwbsAexSDe2rNyAMKmuKEjUlqbAFRaFYnEd70zzS7790iLogpeCLxsLHJpmHJ6QSf5IVAoZGb+pZSUViQg0yEgI50FKBdXWwHjuC/9nWHYbknFNi/psYwYXV+/Zo9ZAa23sbw3ytZ7dNXo2cyQRqHyC/Ww9oDsveXJ7ww1CBi+EWFSRaVSWoFOj8eHUsKnK4BjVIMBR2ymq6N5iRPErKJyEyiiKED6xSLC+1E8Q5jTMIFc2TvDDdhkJsgQWGsOJZi3ERHXhp8ca4SIuI4i1Y9xJA5N1klyjh3Itg8xAB0gq9m5Kp4wSNS3BS5K5d4ECB9KUD2kDPvHjvKPZKA55wHz8QLkZkgRI2Wp/5XRrmD49d+xjAjACw0AX3BG11Jp8fqVaGLtPcX4ypYUqlLJ64jaGA4D+giefmzql2HGiQF44VCSA9VCm1W5XKwV1RfnIMJXzIC7IlrYYVsbqPeJFYv9kHuLe6KU5WpjXYcWpVJuvWoWwTNq10cqZI0UzJEOs2r2eyMaeMpVpQEQoXdzJqjpYoGlNjB3QeTjgBJb7nPd6DlDFt+eRPrbSDwLDrLCCH+BuBieC+zLMe4ux2ASzoCPlLeBHR3BgdivPMcr/K0v4JAhgBZPhLfD2OfpnBjiESP2LSJVIMHMORz2X6TgSsXRwU5TTT4PZnyYFs04phZNjBb1uaXHbKjeoSUvyv2wQ4DKRbTyFWXUGjCAB9LJwc6pHNilovuf3xbntNXbs695U0oC6Dt8y4kEIx36yydTIl5lcjAC1v00SYgeAOkM25D3COEEbxeRImkINQqJWFXEdhHVdjXv7nSAtqLZHWkbKpK2Zbn/OoVOSeUQdZxmKBrro38684Noe4znE3wxEN/SwjYq7hio0IyI4EP/lLr68Lbsrw9eYPoMY7DRwBHrX+QEJ8hVtUi2YQFUYhWr1gTo1F9FQ9a9eNqf3RyilJ3toD5Y1GoHNDfoupkMGazz6Q54numO0x8Xb0EvLzP5t7jc2NjyfGblfgd/fLbTrF/KcbvzTaafnjNsstSObZgm/m6aLtSrZ2dZUSKu6xYOMwDr70714i92mh5qdZLaPgKDq/dg5VLKOr9qpgqDX+WmO3vR/fhE7oWX0wPmbHgAbo+cKnENn5w/eSMDAdb5ELfNJrlg3fjQug3fYYnFKCnYCXi02dj+8ngd03IrrgxPSCtO+sT+0GJoC05WdbAoZhm2pEFvwL97ORur5SohMI4QlXULiBC7zsKoPEL2JHnT7C212FlQGXptWeREEhRHIMsUdX7CbkjtBgoWcaC8JlTd3ZOl3YyFzBU91VERG257TnKX6U28aJ85YuLcepvh5UHZsVmgq10wcoRcK3Q5EzB6xGNK/SHAapEsDQHlYrUl5kxRNHx6nbGIkNVUGvoQPF8IkggFTzQ5RJgwSIFpMBIiqe/tTCtiKURbTk2MsHBIW/vMqtqGKiZcW6fomx7/ljN/B8B/G0WLi04/X77M0dK59oSA8dXQzSre1rTZh2f4EkMexTQJIRlFMjC5QduOcp9B57N4L2OAkoslLrPZIOmMBMDwqnXEQmv8huqPXysjLXB4l4k+q3yZAf5alstqxVDEkguClLCrL1gPFWhgYVAxOzxsdeI5ASv5pIMqmVESG8W8qaUhacTHLawt9OVDZ+s0YrM+waw5aCJgrwCtkK0GTS0NBna/vD7DnMZ2Zzpt3pv0luwVg8VCamjGBMGnlfLpoOdq0MPlLBcSIKGMU05AvfT1nNklGPjO4flSaFIfPHboTvvanibkcOswWlxZE9pZdSWuX2qi8P940WTebzdhLFjphFFCdL/WLgjhGelLyyuF5tMtcRNVcj/KbQPSYJzRw0UXXkl0laz6PDrPyuF2TzIh6EBlPouwAUx+zxZT6VtnE3DGtaTmAzzP323YFmFjzQRl20FTL1GDJlxVBHhDoXZlsQDmtZ+L1sG4GYMMiYUrxeDbloHUCMb93wTF3J5vgajBUaOgoEKG3z+7m/x/s3oHNguqKTYmSEge7NmCwIMRz0IVtCmDb9MzECoOPSwGo3U4WFmzX+VoF4mUXOYCJlaoM/Yjs/12GDHexZaUQBHnDNjIcYQU+NBTbRbmkcUHP8YOnNJ4FwQgeP25sge5OODOJ1vIKCh3evKbuTunSiQGuKXeyice3fWZq7nD/vdf5aRsxYzm4B1R9EvSQ/G5yy/gQVY1GNV2b+Y5rzvlO1OlkFVmx1CiYgqH89llkxmlvRnvs+IPGac78OKnKENhTVVNybvd19Q2s3zhBQ112PaYZRUcOuC2uZz0CpfwdJOYhfwdQjxMUPSgxHg5TohAV1dpgeLb+xX9rPGiffxfQ2B7OyfUesFmMBjg0CjL3cy2v+OX4bYYikmWPaJnULxFcQd6A9z50BCIN/bFebJ0cr53SzavF8kxn7BOXFIQmhi8UBVSc4ID0bor14712h7eCcP+ko9taIQvCkV0ZV9fA9f5jVOHp++qeXq5DVua2u3OnlJ297aacLe3Xxx9Jy0WfrT6mO3mtnRfFHWaZLcDLt/mQVN7eYh2dHWqjTXGtnaGiVjZqPPtZKaYLf7zopkfYHe2uwakdGqlaAAoC/6vaj6r7z5X0Zj4sGB6j8rmxmOVoH9BXC4v06ehe9ghJBa9EgjbhCiFB5Z/qbsQuq3qzGHq/27KzZjbTBM6dhpPfNeMnXDCpOF9Tt+L2WPw7FNJJmuOmUK5hcZT2iS6ycmcvjq+Dcc/XHFRtmZcHCI9aU5b5XjRbLCATTRYBwuRD2kAR/ek8G/ZpPlh756li1tyGhcYICFRCytfFWA9/Eb6NWSlYtlkM7xx5oyOjJraEOSL1IV071xlVFEOpcS3WzIJiXWgHvz558M4siTJMUbev+1qTuVq06ZUKYaGsbh7DZleOybCKlu2a0iUjVrsL0036tuKK8iunMfL9ImJEG6ANnd1njla7QF1EkkcOVyvpONBVecELN4tb9MklVwk9KOvhENBS9o82hnajms+X2KCNcsCQsn3EMCQqWc8WhnKTsmbH5RSbmiKWzS95NUt1BeOG5EKDWLYzhhwG296ddlm555e5+CfyKnBDKevBdfHeZJ/vHzKBsDZWsBO9AV/8OxKhl57dCAD8X0eBLyp9ubv6GrxiBax36VYBJhVlmuJ/YdeJjpdyjDL4pMcxlA65sxk8FhHkfCXIUdY2i69D9Zi3v8UP1+C9+UwmVjYsCAB5isMe3nrcvzhp0NFs0OeupS/H1bOCmy4peZ7aR02OQLc+M1OiCTh6YZLJreNylcH0q+FrDm1n6cWv1xvtJoNHLOgL4uq/1EtBDNFy0NmmrLb3NQ2YGzmIP9mmWHdTg0VBDhG06mxbVeJIxVno7se7cnMglzLR305ZtjhNjW+L+nMy91dKRJVl3olqylcf/RejgsIIzYinAIrD2xbIlgu6JPstRHhmDVz2QZDBkHJJsWpYKV53qdmjLt3/zJqw3EpUEKE3ZPFqdN1TCywHc311jpY7t1XeK5+UOCetsjxP8bhpLnxg81AdGua92l7by82/bJbIm5nMrZuZvreMPpmvd5qZJr4VKLhO3Zsk48inqw30QkN0QrYcKpJKKmRSTsnYPCQrkFU7iwpTbpXR4FjnVtE0JZwsCxwpz0slRhli9oaWvPtvk1p2L3FAR/Arkfh30j+uFyVoE83YfOdlcJj/YDR7a3XJzmeOFTNSntDPfRfulPl/9ysvM8K8mHUFOdNN3gXCvnDE3GHr14BMjoLGIELh1elj2G2pimNpExxn2ntPqR3bU0+OfymPGcUj3Doqt16QSA+jy8PoSW3j+w2Kefy8FtZYhqEqVPAMcasJZ8Ift1WRPlQpwIPM7/0f//bXztw+/r9Cfb1XDn/ECfyA1f3WYPwOLcnPkQAkjysCxwY3+XBMBin3xjA4hyMM2xE8AqA6B/Xz7HBmj+UZCHZoHQBLLxh84Rin3qxdKBABOgzYGkgA73V8yxmMGlgPmvk4W24v/tSvWP1s9bdVGWtH4+DJsALBNw9EdjBtocrwGMyg9eYI15BAL679GfkJyV4xyI/1q4vFFBG/0Mc1DNsR/gSw7mvzs+/37lE3TkHPs8/NXFgDz1zYI8ve6bJn0d9GW5nQ7bfktsIuJzyt0/ysxd708VJypVpRCZS3UnMYzbbslszcbG72BNoJOqfKVngdOVKLITaROeqPs/zv08Hur/ix9AKxVlSwpZKyHZUtmXqU9JEioh66RJKvs+Y8ZMQrJOZatsFZLEZN+GsU+IKWIwmLEOBjNjm2G2O31/v/u49/5zH/dxHw+v9/Jazut5nue8X+ccD/48Gn879EH87R9CzO+E0Kn636FyFRsPHj98cikmRPlqw+U6WE9oUFmrZa/JbtB6XuUDn6nP0tbnysNFS+tUqffKMhYylP6ExbF/y9/8Ch84o9YK1Z2Zyu8oQn4iLL8/cYUzE/OF6Xg0L3DBicoVjB/e9bSPma97MLf9Og3x6Sks2Pe83vuE0H1qfWsy8hn5HU7bwpDit4hzjNyspO+rUMmR5IONSMlq5aKp3fQmwmkdhK/5+rNgX5GE3fy/NVOKTR6fmTw5nyuadraPD6ZFHFT7K7z0FrZk7ZkbluxgJqFsFWLl6Lp+5aiTxcgsDlevXuV/6X09cLyn1aabOBGWBmzxZ60VlSml29KtpWqRdvVjM+7HJ+Yyy075zn89bjk8fncKWvE2tSH61FOjrciAqCxGV/BmdEWh6ovOJkCKu+e3ZcNjK6u1Gj/Yy78nP1krhlj8KV7vMdLJ/wm7cEo4b9X+pQVjZk4BdwUbmSke4vCnCBfqoMCYRz5UFxWHZs0WlHQ+cmk+myoUXnf1rrVcEqan5lFNb1rPtSLu2YA+L/vKAbNlRNdm/1lGSRscQb3adfOiV/XsF9nVkf8+dwdG0ot+iqqkIwiWLm0/bpW8C7O/WiD5JsBBv/1ipL11PJ4Dvu1+K2a2BzzXU1I4rz/nQrz3eKbkG3XyU+fQPaJaZflI5Lc+9lB5BtT9V8DBcVV9+YoQzygq7D7O/bKIwLigx3+RgVO7yUEKDOBW31WQLAqG03X67XbCWuV0lz20JxN6ewm/uPZNuzFL7eWaU50GRjDQofrXUlfK9dyWoOVjhNnflJXK3XPGl96E3/q9HR76KrN/3E3Hd8t1taRoOtznGy71iho5l7OdQeXh6xwx3y3DzVFPa37QIVDe1y7XniEzYpF9TF0S4FCK3CkPmExdfizrIs/i+DHDSVCT9s/PLpG67xInLtWyfyyEps+9E/xrMJHEOOAmHPWs5OXw83mXYKcSGUHZ7WFTruFqKYRBH7VrZas9Hn/YZKeFLxnHjXAb9I08isTEUs7Rf9QgFLM4d3mw9e0+zkaFjetu91iGY0NHZgRm8p719RZd3c3HccuQxfvnFocDkENwOmShYlRnm6Dm5ULBcgwAz9golHhQ8+eFpuuRsi5GciNynwAhut9RmGMjcufmJrlf0pycrgCVx/4UJjCeR8yx2zRaUa+ipr06PjMUlN2hY7/kujhPhSMpH+UXJc6+gk61G/mMYX82iYx9Hp1oTK7cr/Qx1741m1wGcZl6DvgYETo1ltk6/AOOHP9B41uLZBoLfcwo9TS7UrmNb4+UJ3PaKf9FvtK//rr2a20HXHJdL8F0P2Yb83CBKDjwSTvltfRHuSNm7oPdHllweSHK1r14Ubp7yyOG7BrVuwc5g3L5W7CFKqt9lmF3R81mRcHrtxr+z5TYXy0Q7fCNugMGo91deUwd3ZNR0cFI1Id1m7nsFs2tY3L2P6JeNM45OC9S99Bkac2YS3M2dcmXBKeUb1+cc+5pOrm0bH2Xt/3DXNBDbF7bI3z3mVTlCQdBL+B66slVafSYzW475W21/aDIeHjglV1X8MaMjyhbn/bfx8yA7NoPFtRrmy8MiZFd+gOtQ1fUnia/v5RyqO1AIeFjSjVLz4lhMLKht9j/qVzjM0bzqdQSmnSicOjjgtSmwODJ3XMxl/YmlrJp03uyikP/Vp1mE1TYtlaE1y/3G1iPv7oXUULNS8Ya/7RV/V4pkEM9HOA6eD25SsBNuing59ZhYpnnd61ZmMCsUXhKN2D9u1WL/Bj8GtiZZjoI/WmiTK6iOQmMo09u2Dp207/7pTYIco4nN6TPJVmNbxrfJQmxx1KqFY7t00uEOZXHicwZg52Zn/KWa9Rml290V6lWFtSdhFp3HxlHC6APfIsDXjh7UadSfrjKoZsn1OsivfMtuWEUfyqrce5kUvMh3kn3o83d+kO2HSd72efY58JcYgfQi8M1HyJDSGZ7bPgh58WHPhK20/WLrZDXwEcPXdrulTu/F76qA+/iMTkRGK8tyH7y6klRP/9nYaklUj8/XJk8W2e1XnvDRLYnU8ytePOkD9RmoeSYe8ALvJf2UJFdNT4lND60Lrrpr8ytsXKzHPJlORnXxuSx+fSqga0n1pP4otXX3lc2tCMvkso8NW1P2Tx/FlSGTVc8+3L7ugpu3KJBNWhK7Jkk/OLykX2K0Wt718Rt7l1vTo6Jehqw54L7XM0NgQvYiNPUoKM7d64fAT0T9Cu1x6uAoR9zz/RvtG6Qk3mic3EAswe9hNeYNdENmHuoo0rUo2w5pTerRYVDADWUCSTpt083p+y3AHHW2ORN+EAMJlZX5rVu6BmI99tiRLgLLzVB6XaLevshkuETKb8TJ7kXYIPIDXmYdE3GmMN6RjViY2WJ8jcRfeV3S3XVAXOPqn7XvVn6Uh7GcVGjz3xKv6cVmZdaGKnNXup22y0W2+j1LfDziEtR7o34rczNDF9J88Vvf3d8rine7D5YkmEcIGFXHD6H9Zv9+TjEYU5wZkhovbbU28K1ZThkCu780D1bPAK62PB2M9U976qd2676yN1m6uPuXHR/lh2g/FhRt0af5TXFtHtdKufMl7I29mzx9gZm0bI+Dq15QluGm9D6rnlXN+184ozL3ZiBq2XXIUydM/N61rLyAPepg+LNkXIAA9qfZUdobyT71GLgL9dau8ryWrU6UY+/nN0hJzLy5oGl0mixYt+I75HcXPtF2Pddd04H6+uOvUyHq9IfZFXzGvsJdkhPzEBp1rA3bfVN8S+dfD2XrpBAmrTCbh/OfACj82R1HIBnW/SbfGhfM+a5b+g9iXKmlEHshqrzR/Y/634GL+bULrzc
*/