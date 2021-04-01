// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
// Revisions:
// 10 May 2008 (added swap related forward declaration) Niels Dekker
//
#ifndef BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP

#include <boost/config.hpp>

namespace boost {

template<class T> class optional ;

// This forward is needed to refer to namespace scope swap from the member swap
template<class T> void swap ( optional<T>& , optional<T>& ) ;

template<class T> struct optional_swap_should_use_default_constructor ;

#ifndef BOOST_OPTIONAL_CONFIG_DONT_SPECIALIZE_OPTIONAL_REFS

template<class T> class optional<T&> ;

template<class T> void swap ( optional<T&>& , optional<T&>& ) BOOST_NOEXCEPT;

#endif

} // namespace boost

#endif


/* optional_fwd.hpp
o9od8zsW+oTM3CFodt9T7d5iHUSADpcy/jtgwi/e/w/x54bVwmsPLN46jeYPSVKUP7aCNKO24CCraRXOWYTovOdDvP0lq32Z9ukXvI3ie/E+0QMYqLN1+Kp8bQoL1PvppkakaS9+ESAPMOAiJYFMWQDKgTvd/MYwzA1ruFANIJti6JnNH5G0ZBOPWQK2U8QEM15fVJklhAzLpEsi+5YClJRZixyYdx1XoYiYT97W0GD8ezbfWQpsflDOjnm5xvU+Bd7QEcj1vpeCVezm9JWMDvhrLTVHGG7HHDeohoM8ULwATxcRwDWdUcOq4kV1QzF9OxGtwPA6QhmbPZSI5EBZ37pCRooucvTSCB0XZhjGhLAbwtl67OABnZozlIQHwIoPmQyqETpTC1kxz/3BTV7SREA4R6bymLIYbeU2kQ16LvRqqdBK41k0Ne6tdlF80Qhq+A7eSq95BfiAf+s42+klGHhpDmgZETnvRnrMJMcZj4Gm1grhQaqGgqfa8HAPPSRNRA1j1h2wQ09rCPwnVBP5nsRP8E6LLbA9mjobpsf+MgeQ0pmPpYlPdzSAog==
*/