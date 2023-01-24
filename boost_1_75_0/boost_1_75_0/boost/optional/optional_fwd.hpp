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
DP5wGsTh99hhE7/deviaNR0DQR9/34yzLXjNr3RHE2ob6PjiWaCKSa8Rae/kYeUb/P2I+qeKe7xGhv29VWJivAFifzLMXhTmDp6Lh5oPEW6Vjlj4W1+qNLEGWEeZOg7eEwtRK6C7eTVfY2LcoiWnxEvpbXXBFYnj3BSJf2miNg2F/KIFZa/fDdiscMWfn73xW1K6k9EH9Mv/ObbAUPlBq/7hNffH3Uy7lomid3o3oIz3d4LirEK+G30eXB/Z/hzlHGqtdVM0/jxEvM7Gup//TkPh69HnI28++hZVUiZbzoENpF48O7j/q14x0l94QbLog7GBoa+jPYNziCMz5LPM77pSt3csjMYmnGXjpzuJ4o6rVXs7Nn/z8Immb/qsqpr3pTnet72Yfeh139ZUgmF4k+keX+wbVZmbb5hIO7/WR/Mrlw6tpdnT+ublha/frLVlYEihTLOT/xgj2bdvm/HuZD8IHSw+XSd+0y5H6XY5cG+P6fCX8M0HOXMmlbfpyXQnf+2cU/W3a+38v4DuPPIoJKH2kXjPjx4PX5zo7m8gTTOzjSvZ9pnsP0ToITs8pSzqKk5JMiL+55+d30zPDwPEbPhSiauV9oCAhDMVTVYXPeYHjmWlKinvix8qRqwxd2esPyPQ0Z0GdjV1XIV81WZMaHVbWa386cU+LnmgZ5rUiRN+GPOzrKshw7ibkxkqFxWahZdZB8gqX7/bxLMH
*/