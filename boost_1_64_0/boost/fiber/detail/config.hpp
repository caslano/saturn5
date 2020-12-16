
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONFIG_H
#define BOOST_FIBERS_DETAIL_CONFIG_H

#include <cstddef>

#include <boost/config.hpp>
#include <boost/predef.h> 
#include <boost/detail/workaround.hpp>

#ifdef BOOST_FIBERS_DECL
# undef BOOST_FIBERS_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FIBERS_DYN_LINK) ) && ! defined(BOOST_FIBERS_STATIC_LINK)
# if defined(BOOST_FIBERS_SOURCE)
#  define BOOST_FIBERS_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_FIBERS_BUILD_DLL
# else
#  define BOOST_FIBERS_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_FIBERS_DECL)
# define BOOST_FIBERS_DECL
#endif

#if ! defined(BOOST_FIBERS_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_FIBERS_NO_LIB)
# define BOOST_LIB_NAME boost_fiber
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_FIBERS_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#if BOOST_OS_LINUX || BOOST_OS_WINDOWS
# define BOOST_FIBERS_HAS_FUTEX
#endif

#if (!defined(BOOST_FIBERS_HAS_FUTEX) && \
    (defined(BOOST_FIBERS_SPINLOCK_TTAS_FUTEX) || defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX)))
# error "futex not supported on this platform"
#endif

#if !defined(BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)
# define BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD 16
#endif

#if !defined(BOOST_FIBERS_RETRY_THRESHOLD)
# define BOOST_FIBERS_RETRY_THRESHOLD 64
#endif

#if !defined(BOOST_FIBERS_SPIN_BEFORE_SLEEP0)
# define BOOST_FIBERS_SPIN_BEFORE_SLEEP0 32
#endif

#if !defined(BOOST_FIBERS_SPIN_BEFORE_YIELD)
# define BOOST_FIBERS_SPIN_BEFORE_YIELD 64
#endif

#endif // BOOST_FIBERS_DETAIL_CONFIG_H

/* config.hpp
0/xp6fIuiV0QlOWv9Eyi3C6c++7lyEJSxqTnKi8Weq7q+NRz/66fTp8VCv+vv/X2Qlas8pYW2tpNezTpOl9yF5SCLccuUEqXo2IX2Az+TyMuU9S1J8uNF370V/rVPYD1q4t8i3y5T7WQN7Oa7lsk5VroJqV7tC8pXXzH9CI3K11Mwqwi8mbEu7EA/APso1BUhB1npcBTAJ9myyuyL0xCnoi0PvPEFagzWmLfBvWaQAnoBW1JpGvRAS+mkOYWVzWPgf94Ub6slFTExASlIsYQCl6Yv0yWuCjBtPMpJDeHh+UC2ypSJl1LWZmsZGXyYQ4ssBVCcxRqnm+EjcPX43wDicFsaqoYdKwTKUtOPJaJQ/HGbwHKZBcKxJh1Qxt/BxXSNntsJxmHUhrjWIotA3QRYjub575iCxTUnBtaIi+fubu/cMQ8tfcnxL5OEKX7IqulXczF4x4zuwn7wxahFNVYxoZ5SYiGNIl/4bxUfIturldzbsES6sgA2Zd0RydV82nONfcVNfew1lysFGiIlBhnhFCJ/Q45HXazPeRex/YQm1Id+4hECJndd6h0O5fDm+Cl8PfIp6X2rnSLK/DyEsnqdSavMkAjmbohtlpHQcYSnI8QFYgLBSnC9IAPr1eCsqOtuZDxIWWMRZ1/YGtnKJKPM1pU/5A7NBFy8RXS0ea2oOYEKwFCvZubWTseRhWiMifSQaqE6GxELJpchP4b9hS5hxurzIfxloPjTVwatZ0GwWmTafJtGQR/OH1HnVIc0TORonwUjrA4oZgbXfku8t2HfP9okheujEW8uwnvGyWI9yYr3ltOx3D4Hhqq60qU9bnsUkzeS8k/k8lhoy8kY7OxEpebzNK+wcIsZbn/r83SMftZLx36/XkqSBNAd6k3dr0aIyvOSqNp/Zth/Qe2InTd650RuoMTNMNjoGyz8aPer2NXtRXjTzGpPXO4UIi9Hv8eeLdzQXZWC4Kxl+eGHTyXvl5HLhdRZvyirq4x6/uxi06eISym0+5hdU1byGL/+aowXP/9M6yG9nMFwS6eZZp9tLsOh8ZEHBrFse9fnKbuaQsmMRbe9MsYe/cSrrRAl0foaibSxR8WdC0Z3deJtkYNEo1KhUblq3RaiO4lLoylpoYId4kO93OnKtzLAbcxNsl6bNQDV2WoSyP+eIk64fRgIpUqpNc75WuRpWmP97QeyUPdK/Qpb/P5SzHZ9wmHt5MHoLuoJSTt/OVExNpisvMWInb78KAmzZrQH1Cf+XNHTsE/CZFp+CcxYx4eRsXHpEj3WjxqmS+DAQXk3fE0J2T89CJyhmrx0ybWG3rjwn2cT3DRKc5lerSUZS52LvNqK1lGED+BiH98AhI/3Ur83h8B8TgVE9cxw51zS+BZXCUSw7bmu+3yfEep29Ihs2hB5rGzsSfOEHVNo7r6i7rmWeu6DevqYUIhzuongMfQn5FWVBfTXRh0iAiakpdFzwj2M/oDlvQb1aRPLCMt6OXCfJyWP1rKOGEToAm/jw9SFtWF/QJpbAf+aWfX64fF6HGh7qBZq7hDkeNWfOX/i71IBGg82Q3Kr6uWFjhXIegD7zNbk2FFTDJSEH1X3rgXprGkDuDucalh9B3seaMRsfEOwXTP6+PSY1fQL4Y4DXqTJ27K+H4/nf5fJ/S/367/Zyj9X8T6X+aUUwL6yfTjbxEZgbrtNl15g0fpyseGKCFPPSqVG72OoVc6XVGjdOWs7o66ch/pyl+NIV15wX6CLyLdSLoyzGeUSVd+Q0P4ljGsK8fzEH65IwzhV2kit9VF/iqqXXckE/8kRobjH0+kS7QEtdN6qZ2qWDvh0DhnAH1LNTrFucyhdFnmYucy29JkGdHsZnQ=
*/