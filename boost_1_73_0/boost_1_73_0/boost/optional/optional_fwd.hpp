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
KE6zo7NZ8nY0eZPMjt8duUr8itR3d3Z2Op1BqClcUMoMqIzk51zqSzIgPKuE3g+XchvXSyk3M9A11Pj17AS8qFaoW22EWqJXk8nR4SyZTsYXjm3g8rpjrq2tBw2OCsVct5wzAICFDwDg+jApSWnrcOZSp5+ILUARKittdaolOBmickTQCmQEEQhErLgFz4ynUYE6sSV3GJdoNRioUg/v7k9S1NKKRKiFTirOsqjruj7odISyPuwozVlFvfPTcbfzpUN0iBX1ODPX9IIm5+PxsBG+o57HuiF2GOAUJDvrba0U0m23hVmaRPKFXaOYJXAMFCAwFnMicVEkFtxQy6jr5Uup50wiaGEjZ5S8GU9fjsbJaDwOCi68cOxWQdYmCqFfBumgR0vt2jDX6A4Sb4wNt2iCN499YNOTWfLX0enL6dlRTLvjtbUpeYoWEkJdYog+goBXTK6WmzDv1bvJho27kALLsiTH0JE8JBLTJklwKhoOu+Q65epX1Y6youArJl3BQVkmh/5wkTnXeLm23xFdVsLyOzJ+lfIyyKQGYR2qBtte0PbeXpD7jrKrRdYKvTREjdGI4Io25KcNEbqNEptrtFqrdbcddtSeikX0pDXohI/hHGF/GroOOOJ7yjrx61fJP0en0+hpyKs7vCv1
*/