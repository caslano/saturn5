//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONFIG_HPP_INCLUDED
#define BOOST_LOCALE_CONFIG_HPP_INCLUDED

#include <boost/locale/definitions.hpp>

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOCALE_NO_LIB) && !defined(BOOST_LOCALE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_locale
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled


#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* config.hpp
E13HqAj7J/mCA38mUrKgvO6Ti3y467H0KY4IOfApwAwzAYURLL7Riaj74f9lwAqeapgpMR/sHu0nWAG8IeROYHbh/oE24FNWQPYefLdHODmtGz0z1fu40Zv4lBKRYANPdo4BecCmg7l4ATJPTmNuC8xDkDG7ryzWhmPeCBMhXQ0cHQ93PfxFSizwBONTPbxpvzZoAvky6nP37HXgIDst+B/mFbzFLmuPCd0y+N23jUdFpTBjV9rC4M1x4GJYtOQ7aWEkTAItlOY+8CFQl6mO7Y4xeMnT2Fe5oVqbFrqP3WMJtgNxrC5bB3eTfUDpmFHYkzyeP2NoHVeHuLCay8T5iS+qGI0lEVJHmeGwPDJ8JJrBS15J3f/MafAn6zkGWrAF+oSm9wpo3VOejLzrAWUJ8tQZwjkK9exK+j3+DWOySpZKnVpptORaPyjhg9+65wEc9ZGjIJOW/L2bPO3tCIHi+HMpY7GFxTgBc3IhUXDQ89IZwyWhfNR6mZU5uN/331upDRRYHY4mg45QRfMJfHnirI+PErXEahI4RqP1IBcMI9JfVq38NVqRykP5ag==
*/