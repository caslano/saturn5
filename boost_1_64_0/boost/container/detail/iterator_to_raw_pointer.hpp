//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ITERATOR_TO_RAW_POINTER_HPP
#define BOOST_CONTAINER_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/iterator_to_raw_pointer.hpp>

namespace boost {
namespace container {
namespace dtl {

using ::boost::movelib::iterator_to_raw_pointer;

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

/* iterator_to_raw_pointer.hpp
330EpiOrzmz444vu+J6+iUz/ba3rWNWWkpr3rQXTvSvue6H1WBUxCqYnc2K2/foBe5iRLIDZ9MWDDxbfM5Ppvq1nXauJ0q4OSd1gpvfF20uhnRs7VQ7LFqz9K7sZsDwyGTPzUEc7mGSm7ZNZmf5Rw5GnnCz8234UbDVGKrOi5XVY5sfi9Sy0xAYPf4PlCrb6nzZnYWYye2Yd7BdOgck+WcZd6vEuGaYkc2SmfFtLBlOTVWfmd2JOGiySLIDZygq5v8L0ZPi7FOqR5fSObQ9Lyi/ejwqt5tktnWFbyOyYHf8S8xm2W4hTTmy+HJYsWOrBpoNgaWToQ6HJ7lYusv6SiQzX0PWpH032LmhY/G7+87/nlQYFn4feYnJFbzXMfrAaLHmuUU/D5xJimTWi5xqRA35rAjOS7fjW99CCz7/siNTCcqkCHEMKbMlWtQYmlbKV5Mz2rpmQDlOS8bjlUl5vWBCZG7NfP8wpBQsjc2A250JUfVgEmYJZ7f2tasG0Qi5eed31sAQyF2aHNo97DUsU4t4d2P3vugg2+dz8ZrAMMmdmWWadGZZJ5sQs79GwGFguGY5nBdZwbuN1sDwyO2Yz3gRVg5mFuLp/5iTCJCtL2xvdbgBMRiZjuUjbu1WEKQWbeWaQHKYmc2dWZptuNUxD5shsuLRmKiycjK9Lg5FromCRZJ7M2pV7EgyLF3LpUmPxRJiOzIFZ84BzNjC9EOd4e70fzCjk6T7/wEFYGpmCWfXTHr1gmWQezIIdvpyB5QljTqw+LhQmWdtK1qwPFxM8rsNkZDVZXN9uE8fANGRBzCqOmfIFFk8WyOzsh3U/w1LIajPLSN+0DWYW7FMP1XJYsI3l9rL4WspEWKhgzsZFrWBhZLwPD56PXA6LEOyf/LfWsCgy3qPtXfrPg00g49t8l7VhobB4MnsW12tmx79hOmHMqHuNomF6sh+YuTbc1Q2WS8b7cMfp0kuYqrStFMLszcQjXWFRZH7MpvcrtQ2mI4v6dl75seD7D5sbVYLJbYvnK7SGrZtNgIWRofYCq9R3zxlce4eT4Xs2jemzKkPVbvYwya74uFRoW0fWz8ffKaMiCylVFNeErtkbVLzyNyxRVnwcLDQH/1EfYAYyB2aTq954Bkshs2d2fk9GBCyDzJnZ/aZpybBMMpz/CmzS8I7BsGwyG2YNBuR8heUIZvUqfD8sl0zG5gvOvHIe9pbMmsX16JLTDmYW6hsxe155mMye9mlmTxfaNIMpyfiaXeyatgimJlMyW3l28E5YGJk3s19nJX+BRZH5MnNW/P5fWAIZX+t3LbK3wZaT2bH6Vjbc3h+WJFith23SYAZhTMVfN2xgKUKe13euGgW7Qcb7sLTtuOuwTDJPFnd0Wd2KMDOZK7ODuneHYHIHWymA2T8xMzrBWpCVZvNV1WR5w9oJtuOBWxtYVzJe++T956Jgfch4DcM+9ZoPiySzZub7d94ZWBQZ384GHjkcBIslc2A2VeZZs8hGSDqyoG/XUhqr0dLDtt1ewoKci8cstFo275JgoWSor8BSn4Q1gIUJcROfD/CGRZA5MWuf6HoeFkUmZzar0bobsHgyD2bL9sxvAksks2W5zJjcxh+mJ7NhVjrr1g8wA5kLGzO/w89bYSlCnmWn19PAMsjs2Jiffp+QCjOR1WRxC3e1yIfJXCzj1k/eNxgmJ/NhcfVM/5kKCyLzZbZEPmcMLJxsb6EV9a/LGdknWJCrpWlTBr2AyeS2Ui02pnsZ/SCYhqweM5va56bC4slCmXXxj/oZlkFWn9mp2F/yYDI3OscxUwU8CYCFk1mzdYl8cjkb1pWM92+yV0CD4s98keE5Q1N6ptNvRrgSFu1ePGY=
*/