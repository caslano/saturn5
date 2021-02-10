///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_EXTRACT_EXPONENT_HPP
#define BOOST_MATH_EXTRACT_EXPONENT_HPP

#include <boost/multiprecision/number.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend, int cat>
struct extract_exponent_type
{
   typedef int type;
};
template <class Backend>
struct extract_exponent_type<Backend, number_kind_floating_point>
{
   typedef typename Backend::exponent_type type;
};

}}} // namespace boost::multiprecision::backends

#endif

/* extract_exponent_type.hpp
AsbqxyLlzmQy8vhRQIojEe5ZlB8ZuoKuSFwkR0vhbzSc7YNh0WWYN3m7ZBebX6uLzdldbN5VF8GS/DpdhIZndRFe31UXv07/ZnVuAfR/J/Pcbh8p+36rOFMXZ9Hjipl+EnzSz6UEYGkRXUz3iVsxm9W8NPax9k+t/Vb3t1yDI70OkZeFlX94WP5h4/3vBXb6Gf6eMvxTeVyo4C1i6SPWMDvSDFPOvRhM0bNHmR8xZLLxewE7Vig2ljSB6FrkW9MEa+8ddls7/JL3XLoY6yr9CjW987nycLz9NjtzrYgYk2QNHsvYMfLDXMkFOauRtLjc+kILLQWHF8N1D3TSgcXoNbuYnoNQjdECi9KyILwCMxmY40wxgrA+jNA/IPwihpNgEab9vYvZEqZjJiKnUiKVyQBqRyic+tyr1HdAmmbl+sxkKxdrywp31tXu5PNF4DC2d7jL2q/Y8Zufjhn76vgsA+cOvaIdzAWo1gKUxCCYUFg9Bc+2+fcN+lGrid12EgzxnZ7z1FxcYKJgGvbdJDENFfAGiUSpfYgodvy+5DcqRtv8ZjF5dou/F1E0+nsATa60FXEQmRdI3lM+BFlABtZoBeBR8t6bXD5N4dnqyGNj7Kks8yy/zDOFSKqMcTKMClHEkFkIH6EnFxdBRgW8
*/