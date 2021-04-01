//  abi_prefix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# define BOOST_CONFIG_ABI_PREFIX_HPP
#else
# error double inclusion of header boost/config/abi_prefix.hpp is an error
#endif

#include <boost/config.hpp>

// this must occur after all other includes and before any code appears:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif


/* abi_prefix.hpp
yvmx3jgVJ7hu0LsvcbDANoPRT98LaO7EocAdd9tcV0Tkn+WP7AFqQVJJKOkdyvspXlJVN89i4dyOyNKMCQPFHR/zr0/eA4hZ/FF/XNcfBHIRJet13dSc7iUwNIFcVthOoJo59g80Tbl4h0a5+tLUhk6H897ue+tHWcwS71n+daLp8xsmxTOM8F3IUUsdOMuuLobElcrOIycfzhdHBLO57YQkfdpvKEHSZmSXTVgvjqzPPBdYsxCL1cL6j+rgFWZKjUX/GoqbNFwthtoFAVOBKZaJj6HoHQObYkAv8O/BdxO9WAZZ3yqOuCHPIYSP5cuanuabwd2z1Tyv91jUZ0h6f8Qvugl/2TaS/MEzId8Zgv52MhRDBduS9qR2t2nw4zqzFaPr1Qkvrz63FwQWI+FyfTdJ1AWBO65KaAAl4+T0fQ/Ghx3Lzu1X59ZT6TZaII8mSLqXveR1asxfvZ/5yTzc08hQpBCI1on4zUX376GjQ0M29QzzSZ7s38WsEEmcys9V0PDh55lcCY3/7KVWCoha55HyQFiq+ECA8yTb1fPPVatYZFc1tSFK/SqD7Q==
*/