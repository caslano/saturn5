#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
tmkZlR0V5S/uzsj+VIp82ZOiGK/lst23oN2WFiH3yn2X7rOYJFy5XMlugTn5x0D+YwrIf8bEUH70CJpEyDnBwGB/11Bnuqsl1+YVvs2jMTwTRDqpyOWxUlyZBZgrjBV6qYReUMA/88XKsZAixqEtoBPZwji26RBnPt4agw+o3IwPqI7xAVPgAxbBFiqFzMmQ144UHfaPnR5ZEOwi9v7Gh6Tl35Jq0GvdCQ0cn2GSiYVQ1cB4Z1cwrsXbsYHnvw5+5kR9r72a4aCh58eTGvKcvyzSZzi5phi5agrIVduAvS7IRbg0dkE2s9eVbEBcuol6Lej6QUODlmNqA+5nN/AaclqDPjvZJMsQVjPrhmC8d7dpYkhzhoATD/TTde7SwHt7neUhvELVQfZM6Sa1LxVZxqpwTOW5LvKD3Lxgt/hxtd1H2+ImUdkFz21vIQ1/vt+MR7spGfQaZ06DlGOeI5WLwfSpeFls7xnWb6B/b9c2VsanjW1b+F4NWG8C7toH+9EkB/+4zbcOWtB+rh3tPqnL22RsYH4Dl7f4b5XbmMUUGwP4xEt4nxn0aP6N8vg2C5455kdcHxkZ7Mf9ydd1GM7L0g/2yv1pian7poncN2pM31iO/rS96E8rTH9aacqsEu1RI/rT8ehPBwj4yhj4QZQ3t4ixppC9+G8c4FPG1JwAXg9tCOv6DKfVHrazYbv/Tzhq//twp3P0h3DLO7xTVl7m7y8E0Z2CDmXzfqawat5iuk/v2Rdp4pzPIYS6s3cluyiPcWDLBmeNwTk0hs66hnxnpwvz52zhCGELR0LHqM/roafBxkKlmATQHekfumO9TjB6HWgIv+0Q7dzZJJne26Snc0w23z+ucHd48GM7TwRDbPf6bBnKpcv9Dzgh3xtEvyrHt7XolzXfkY4h3JPUeskHYw7wVp+7a9JPj/fx+3Jh2j3Pl4vbUEp53o8iXRb0pntVXM5Upm9Ge1QG+ulNbQj9NuWHew1bk90dJ+yuiufB4ly8yRP295uJ8Xc8TuB2IxzdbidCv45vpBW9t8a4e92a3skN+jveXtSWgDNNkd4W/Dh64dkv9G/UUWPmA1+SfQHy1Kg+T28kY35xqPEXX2lwNE1MEZ6PKXoEF3wlgrMaNF+TzHfgc9iuyP71XbNJ9ltfJANwX4o5n/Q1NQYy/CWMN+cz34Drc1kfw53vC1Rd8edTv2lwlsXwc7FptwEhL/n5gvJeyvQJN17eb7O8oKflvZzlBTxe3u+puuLl/YHCiZf3hywvxlSWt2Yz7Xu1oF+Tp32vadDyHSDkqynQnj9RtOPlu17hxMt3o2i/TZtpv5uZHuHGy3Mrtx/oafluZ/kAj5fvZ6quePnuVDjx8v3ctN+XJzI/Ln3/zpyGHxJ9IP6Mwr2i3msq85yjN3OlCcZ/3W/6tfVvD3AdYYzxBM6SgFdXx+/yre2K3Nt0vvGhBj4b8XDM3OhhM4Y/qmwqXvbfs2x+7Vc+XtvAEwSPXXt/yO8NTo4/CjmejJHjSSPHUywH8R9vX880mDesFa6+2/Vcg45hcqKJYfI4xr8fYW5+20T0A7FWIVT66fX0X7UdYc7Pc+q/M9zvq7l89W5aA+NDJ4qeXVO9BPzShnj8pMF/pYHXMzVFrGdeE/OMUtMmb6jxJ34O/Fbcmg/+o2cH/slvjO/wGg5jpvR5tqz2ee9hnTRezI0/MOuk/4L+LXi7KZiK+Pgy5hDw3L3AEVO1TB9D+q1ylGc45tQ8x7Z2/Yo5uzQKZSlfndXZ1vD88am6XCnSlI9yGr4cPNTE8DDHtGM55B9n6hxj6qxAeoyp88yJw+t418hZiTommHXK+Kn6HOoEzAUnTGWchgbGkWuCiaA=
*/