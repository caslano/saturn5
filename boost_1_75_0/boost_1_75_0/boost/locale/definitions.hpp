//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED
#define BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED

#include <boost/config.hpp>

// Support older ICU versions
#ifndef BOOST_SYMBOL_VISIBLE
# define BOOST_SYMBOL_VISIBLE
#endif

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#   ifdef BOOST_LOCALE_SOURCE
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_LOCALE_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_LOCALE_DECL
#   define BOOST_LOCALE_DECL
#endif

#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* definitions.hpp
be7a4LbIyfT1qlezU53h/0IfzJnKr98ms1/ykXU75hT31ZDe9/1seXaBR22/vTS/uDlPFTtkkP19XwMWPl5JMhvlhNvH712BCCt8s/LoZUzb6W1zOR9WXaKzb10u5ojSQZn28pCUSc4DFrUCNHdx27qjhQkUhH60RksDDP2VNrZFgXSE7RX+AecifDg8naJtZkWzac5oYW/tW0/Hn5WvSzsOzs/8TuVbe7XVewxGp1E5lp9+R2iX4n5vbfljqOK4TY3jkEcn/rqOI0YCZvsG9dRz6Ng20mn5c14rYjp0d37ROWwqWOpUZ3sR6Wmog+cwE9DVnSMMsfC6jKSh6Vsl/NQuI5BxHP4n35ShiPLSzapeSczNFffvZ5TSlWwXZ0/HMoOLRFioRbLHnA/CZNvU0cckXXWzbHIQ7uSu99y3pI7YYXerDrKjizDIeWaWbdp4tVFSov+zZDGvrzKpR86UNakMNVbLtfssV03Gq3AdbydpFvM6nz4G49dO+tWn7xwYQJplla0LHYHzq6CspWfs168sFAljGNxJczO6tyZUVO7nq6QJHqPrrpp8Xqhd9K6K6+LAcuBRhPFF38Oh2jbZhQnEN8Da9PggGGswNC0tjbBl7bDyQRbB/opMuOTjaOq8esfU2fPJHb4UqPdYPmZkLGRLYtwBfEPmd/J7x2KLBR3ikG9tOBMIWNgOhZ8fHPijjmY4iIxPIBfyB3Bg
*/