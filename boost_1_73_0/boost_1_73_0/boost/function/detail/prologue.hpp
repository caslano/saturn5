// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_PROLOGUE_HPP
#define BOOST_FUNCTION_PROLOGUE_HPP
#  include <cassert>
#  include <algorithm>
#  include <boost/config/no_tr1/functional.hpp> // unary_function, binary_function
#  include <boost/throw_exception.hpp>
#  include <boost/config.hpp>
#  include <boost/function/function_base.hpp>
#  include <boost/mem_fn.hpp>
#  include <boost/type_traits/is_integral.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/inc.hpp>
#  include <boost/type_traits/is_void.hpp>
#endif // BOOST_FUNCTION_PROLOGUE_HPP

/* prologue.hpp
0XQQ/LdOumFFlzBbLuZ+EMWhP7sKT2J7iWdvYfTmFOyqZoUW9whGBduo7sOpdXJivcID9RRTIvaxoFL1Gb8oKYGo4SV49lfHeAp6fYyNVWNQ8B3StaUy56mADOttzaCq+d0eSIN0lJIlRKFqzHDl+UHohsYfrEyKJqVwppJoVZl/NHS8hOP5YW5j9QaOctRLgbJ5Ii8TCl7ewIbJLRE/Jh90wAsnnC3cIHJ9zwgINoW0Vu1IEcyd1t0UKhmoulBWpEcx1ZNEFUNPXjuww9I6CsZi0g1fS8wzhFigR5eXxd4QTVXxWokvK8iN0DDrzFVVqtLiczt0Z+ss6FPVIYQayrrEIqYVlrbjdXqQmDkA+RKGduA+RsHzY3wBh75ItfGrv+d7zmPvkj+uK1Q0Ym0kkQ0pdJqg8jT0tHe5wg7HRZt1QVQ/g4X/fbUMnUVwfTF+O8FwnSitrp2f7eU8MobE3B+UqE0RKfJn/jw0bLWE8MT5bn8N5o5hlZnRqkl39K9ftMZKJscoHZaN1eEE/jHgsRTVwYME8WLCqN+v9I7gzFMr4dsRAqH79Ag3+c+Gin6PorwGsjiaPh9E84JhBE9+iBOMozh9r6j8tN1rmGFEWurF/0ggB73S6ntRAoNBG9L/f9CA1qj5dnH3JR9g
*/