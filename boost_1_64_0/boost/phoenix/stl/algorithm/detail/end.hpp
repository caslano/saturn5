// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  end_(R& r)
  {
      return boost::end(r);
  }
}
}}

#endif

/* end.hpp
Sz80JVtnfjP19gOeXW/dj0fxb9nvlDYXa52ntLkB1nlKm+vpqT0GdPbUHgPaeGqPAS08tceAxp7aY0A9T+0xIMRTewzw89QeA6p5ao8BVTy1x4ASD+0x4LKH9hhw3kN7DDjtoT0GFHtojwFHPbTHgIMe2mPAHg/tMaDQQ3sM2OihPQas8dAeA1Z4aI8B+R7aY8ACD+0xINdDewzIlHmWY0CKTFuOAeNl2nIMiGNafQwYqEy3LXO8yiQf3bZPx2/dts8u59z+btkHznhZ94FjXtp94LCXdh9430u7D+zx0u4DO7y0+8AWL+0+8Bcv7T7wqpd2H1jlpd0Hlnlp94GnvbT7wCIv7T4w10u7D+R6afeBHC/tPpDupd0HJnlp94EJXtp9YKSXzuegl3Yf6Oml3Qc6eGn3gZZe2n2goZd2H6jlpd0HfL20+8AdXtp9oKSadh+4KPMs+8AZmbbsA18zrd4HjjCt3gcOMK27Dzh5XUr/uo7j61X613tcv451q65L6V83cv06kP51JtfvsXb1epL+9aFbdy+1q9erXL1u5+g63B9+pvkZcaO2PjZ7158Dm9+T/8f12AJH17ccXr90+TrWRdbf1E2+k8t3dCOJInO9mD8ytokPnsRoPIVd8Qz2w7M4HM/hWDyPBryAGXgRZ+ElnIu/4BN4BZfiVXwRS3A9Xsc3kID4HZ79EouwKu7DO/AQeuBnWA1PoDd+j9XxLPriT+iPVzAQ/8AgZB2VQtAHa2Eg1sZQrIvhGIZ3Yzi2xIZIWRjrxPJdj+0g9dXAVHdSX01M68WmGI3NsCtGYD9sicMxEsdiFBqwDWZgO5yFHXAudsInsAsuxW74IsbgeuyJW7E37sS++A72xwM4ED/GwXgch+I3GIuncAT+iHF4CUfiNRyNlSnTGPTEceiL4zEYJ2BdnIiNMAkjMBmjMQU74GQ0jyUm3xmwM8loN5bYMWlnx7EhfoHN8QRG4dfYHovRsr6CMtb3gazvoKzvEDbHwxiFn2B7PIKsj/qQ83vgnIf1sS3N9Sr3ebA+fBDrYC42wYdwIObJda5HcDzOwxRcgJm4EHNxES7AxZiPT+IKzMc1+AxuxCVYiM/hHlyGB3EFHsWVWIwv4GlcjefxZbyMr2KJZUw1yrABq+FG9MMCDME3sB5uwca4DVtgIbbBt7Az7sSe+DYOwCKMxT04CvfieHwPE3E/Sr2SseN6vVvqtRnWwebYBFvgQGyFcdgax2M0pmBbzMT2mIsdcQF2xnzsiiuwO67BHrgRe2Eh9sE92A8P4gA8ioOwGIfgaYzF83gPXsaRWIL3Sb2OxWp4P/phPIZgAtbDRGyMBmyBk7ANpmJnnII9cSoOwAyMxWk4CrNwPOZgIs7AZVVvfC3xVj9TzNRgwkgxpDTSYtJa0n7SGZLHJo6BpN6kJNI80mpSEekkqeobLF8xbknFuCW3sX9NxZglt/caqnrMkjhOmmaS1pD2ky6RAhnsqeJV8ap4VbwqXrfudZuv//O8gltz/X+t6tl/sfJRMJhUhTSQdNR0/f9Y5UrKs/94lJRxlunxWc4/+2+wPPvP8vySMConycDTG3gFKc//M8+LNz3ERZYNxBzeyyyb58wVSpzVJE4P0sggzgWOq+M0PebL9RjVzylpqPOcvhG8L9Ymn0zD1ITUdCq2XHlZ+ibslbyaSF6NSMep+wmSV58h5kfHqToBOP08Evu+CT8EWe/z98U28qwLqXOe30+9211jSKmije8L1ptvF9/E1IxyxVjaF+EmYzwnMd5NqiKxniDGIiVGefSdOsBKzj+ryb4eG/oSo9010Oyq2hi+DubP53YxUFHljUPqShOHuj0FyjPx4t14H44=
*/