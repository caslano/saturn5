//  abi_sufffix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

// This header should be #included AFTER code that was preceded by a #include
// <boost/config/abi_prefix.hpp>.

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# error Header boost/config/abi_suffix.hpp must only be used after boost/config/abi_prefix.hpp
#else
# undef BOOST_CONFIG_ABI_PREFIX_HPP
#endif

// the suffix header occurs after all of our code:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif



/* abi_suffix.hpp
cwni6N3hl9b57907UFXbbewPQSMBd7v7PLf77Mpd2bD31S7L1eHgySs13xQvvG+dIsE/0kz9t0Oa3kH3QccV3p8BNYKd1106hGd53cHAeKU91iv9nKbPgFtpkvpnpJ1XqX7Elc6z95/w5lawy1LBYDKE8fHxL7APPx6Mjxw4JTWjFcSK1msqLh14lZuV30pyc+NK+toBqoBU7r2ASckkSF6oayIo4HPFMlpLmgORkFOZCbbGF1aDKikUrKIwCaOlH7xz4LpkWdnHueUtyJK3VQ4luaIgaEbZVRemIUIBLzACxs+ZVBizVYzXLsJTUFRsZB9GkyCV5ECuCKvIGuGIglKpRp6MRlkrKjzJKOeZHGXbVLil2jw41RLZbMgt8EaB4tBK6oC2d2DDc1boO6YIF5t2XTFZOjtaCFjnIy5A0qrqw6Ero7I7AoW4z5ajLaFB9kzpm+S11GjXJd/cM8S09oGKVtQIh2lBu5xj4h1o65wKY28SsUXps2xS/kTJdtxz4DWyAtuLwY9tWBPJpAMXfnIWLhK48OZzL0iWEL4FL1j28c794BS1wRBVAL1pBJXIQgDbNBWj+T3wr9rplpucwWQxn/nB2zCdhEEyDZJ0Ng3eJWfpaXgRzELvFF6APYaYNlrmP9lgV2ytdQBH
*/