/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP
#define BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/recursive_lw_mutex.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* simple locking policy based on native recursive mutexes */

namespace boost{

namespace flyweights{

struct simple_locking:locking_marker
{
  typedef detail::recursive_lightweight_mutex mutex_type;
  typedef mutex_type::scoped_lock             lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* simple_locking.hpp
POpsXGlCUg/bv07xm39U++9W1Ckjvi9T4h8ctdOfR/Csb5woo/gHlwfrz3pP3oUZk1uJnty4LfVkLkzD0sy8u3e9gMR2bzEXKIs7W99ElgATUkFs3kXWks+TuYP+sqgzv+9MGaGW4s1w/iYNtJYoojD3zwt4z8Bu8V0zZgLTVL7Pww6QRaeEb+NLOmPb6ySJOI66CKLhus9F16G4Oamx8haRoIRSxF5NxPxzjPkphl+ONphBFCLEaICQ5zZJjAlJ8FuM80KcLTGeekZoFiQqT6d34T4jaVZGVBbZ0bgC2yyKOnatCyuTr9aUOEG9Pbe1rOxHXLj0Grh8MyhxKjH4nosFJw9EcgNobSf8kvYqCf52p2EQt4L/ZKY1kImqhieyMnk9FKC4ivJdTRYcqc78TE40qZSQ7iXybC6lqWLeJqu9gEPOYZDa8WzWEvKMWu7ccOz26sikxF1/XilRtf9P5EEPOynr127NznjP51mbdKL1K/5Sm/7o2Rn9JZSbWR/qTsCXtjD44vS11v0J+5rRb5iwsY3ryyd6i201ToFw5Dc0QggL+kxjcn6S9nlFGZ1xyjfSB4vi4lMvkCz8qm0FYMc+wMSkuglWTJrbxsikWPJTjzYWdEtub4Ls4y0hWYQ5W9jB5HgYYXuHV/8KtJleKfgNayHpzdFNPspa88vKzCXBbefTZK6wtheNV3HXL5cCltZoqdZCGqfsu8hUC4SdWuNs7rYpHF8SH9R0hJgfl8Lv8PbWbyeMaa/exhY9tCXRu/TfZRXyjLx4P/6v/VQuLRsGBx6FXemmEyL67zrAT7++kL86QRuh4aVc8s6Hu2ik9Dz/Uzcel0R+5oYgK60PVyCI89z2ToN/1snnywshcXzKjWP30Prw4eGgwdaVHvUzSIc4gyw94uYXQCI20buDTmAKvIuqU7N0dmiCXS+vNsbPwThGLTvIPtWM9zs63uzPXQRcwX0OdKMaXYpko7KysD1TTTBXnfyXM5+v+7SPket+WQPZUUOrc+3Gqv/FxZn9A2UF74sL2vK+2Frvi0faVe6LDv0a+WY7Y12RzeY1F7LZpBZSNithfWszW4alA+aZIWeQyb5IFjJZUaZBUmjLSc6tJC7U429yuAyFNq73g/Eel4Hqo/HzwioLHZcsvNJ84jKJgevbcmGPGPfjp2UVsIrtb2LoJlGK8wos8gnAQkniuDyVgg5E4B+nLzwQ7s/HLQMC+1Rgk/3Ne22l/NTXRdbtshJJrBJJBLi2LWdbUvTcCSTK8jcvcO5kUxaxej/Gk/OkFDSLS0GLpG+f1mx744uTICu4Jr+ArHwj60vq1ppE0QKUkhCT9vpVKCUVXa6KUViUBFjNACY1UwGoINS/3XeVFHf7qMJscoAbhcuNYCFt/VF8LaCzFfFEwmwyCLMFaNFNwqyZ2FlsYF0lRecycccch3Qi+e00k7440SHAn8XePfK0iPLfPFmVRimtDXUlcbzm8zHVB6IfHbQRsrSn6sp5o29QHuZeSTy0JvO7BEYmWVL88jNZUtBRAZdWF7f6s0urZ/+p5P/qPOVWIw3xbDxJyRJzWbkeJKIJtdW9yUzDXJuGTyF78mHveJ2O5X8AOzl6902StU0u4fkYtrJ0B+t+uoDB01u1UlyApBCmGNr2Jui+tEIAyhyL4yoSMy79iE1fdWCVlkGluezX340MSGVXtfq5dUdVPZyKGc6Ac3KT54z7jbRGjPXMOJXVdt4iuTXLDxUeYOz4Uz8Za+FENYPvBWsTxjdb6Zs9WlHr0u7zxdasAfFFnUxiCAUN/jbEnku/KukrYPEvYsXK2aOJ1M/lygsjcGgnDNw6kzZJdD70Z4FgmEaLTiykVG3uzSc=
*/