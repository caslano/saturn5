
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_SYMBOL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_HPP_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/transform.hpp>

// PRIVATE //

// NOTE: INFIX is used to separate symbols concatenated together. Some of these
// symbols are user-defined so they can be anything. Because they can contain
// underscore `_` and/or start with capital letters, it is NOT safe for the
// INFIX to be the underscore `_` character because that could lead to library
// defined symbols containing double underscores `__` or a leading underscore
// (followed or not by a capital letter) in the global namespace. All these
// symbols are reserved by the C++ standard: (1) "each name that contains a
// double underscore (_ _) or begins with an underscore followed by an
// uppercase letter is reserved to the implementation" and (2) "each name that
// begins with an underscore is reserved to the implementation for use as a
// name in the global namespace".
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_INFIX_ X // `X` used as separator.
            
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_ boost_local_function_aux

#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_(s, unused, tokens) \
    BOOST_PP_CAT(tokens, BOOST_LOCAL_FUNCTION_AUX_SYMBOL_INFIX_)

// PUBLIC //

// Prefixes this library reserved symbol.
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL(seq) \
    BOOST_PP_SEQ_CAT(BOOST_PP_SEQ_TRANSFORM( \
            BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_, \
            ~, (BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_) seq ))

// Postfixes this library reserved symbol.
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX(seq) \
    BOOST_PP_SEQ_CAT(BOOST_PP_SEQ_TRANSFORM( \
            BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_, \
            ~, seq (BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_) ))

#endif // #include guard


/* symbol.hpp
goF2+ZHnUoxIT57RoAq67MmpsoijWcVo6Yj+AcfwFl6flJOfaoPni+HoArd+rQG/iTFNX2zF8dD3VpsOwoaz3nx+266QDzkr0CuzoyhSJRGlMAVkxFuhW9HcikzCe8uWhdzFsVwUInFZm34Glj6Urcz40PvIrubza3aF49JgWlmg0auZnIhiV0osUPko52CL9Dj3capHfyOWURKBbp7txpjSjiO8YxzUe40BD+Pc+nk0OD/DdJ0Ns+F/B09afvEMk3/GxjLQ2D5mKfZFSvIswakHVa+ynCfeTheHoJGvvEDWoEa3FwUHipHpbD+tN99yaNkfV5RiRPg8xjxTfcTI051of56q2mNDUz2/qsnMNI9nbmo2llev4KDeUn5Oc03KLxSi8udpGXpUqKWe8jFexxLfzXwwLbLh5kbzxDm22XxLgrHopxyKaZl6rD4kPza91ujYl597RkKLiuHJ2hkmiKPYcPXQWXRDBQLFvMTLrv+88qm60gM3Ugb96Eak7j/1bmvbrccUabkGRlGgVR9n3sGb4+NjWykqzkq/XURYvWyJf7MdSz/V7gWaVhwfm1jB/Ud5Jwgs7ChemFnF6HLs6GZhP+nd84Z0z01wLsfLYb6hX6GyUtfRPqIuME/v2oeHZuPhXVubhnCmmjq+
*/