
#ifndef BOOST_MPL_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_POP_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/pop_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_front
    : pop_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_front)

}}

#endif // BOOST_MPL_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
hlr5Dv3LynL857+sw2TvOLE/5U+WrPVNmlwcvg4EMQN5G2sqzN2sp+RACIHNAuCMAORaSuDbtPNrIKnVxhtnaxvXiE8bt95FqWBGQCsKY4WoD+lfPcvklgQ2sX59NdA5Up+muv3HJlL7lxIS5Ub8+qS4R/3DfUPPkSgPnxKOsP5/mRp73COmHdEwsLwJX35oGhrzU8eBJAq3J8cfFW6a/n5qpWPEMyOBD4gfcNLob69NYPm3x2YvoKND+eEEibYU/FjrbZf7Hnpjpnkf1ob57ZVucFl+bCS9fciKTz4093P4lUJob2COaCXKhGr5aa3wxvuj5bbFIwRFOYLef4nwuOGobjqFvmLQPXZfrTavYLHrp55txeEmzFs4NBIMV+Kw7nGOIgOTQKhBNRmer9qrN9srFqw/5CgU8WLaym521gXzY+cRnGLauzjgHFWRT5cPf5oKYaIJodkBCFlLZ4R+pkrBqc/LV2EYlUISCG3VQMYqINkmkPXYkc0Xo/NZ51pB7HlPAYYosmmylzrqCu4l1wjGBaR9WKHN+UQinKWM043Hr1Ue/oaF3aH91CYs4ctnqGS/upiB9JEqnSD1N/sTIQvsfH0jxehjK/KvLGmsSRrbXaGzcCqG3UF9G28vdu2NM5ShbEQMZSViHoieX4z98Oj4nA85CeZA1f9wEK/WerXdEkhcCrMPsSIyYKVjkD5VWpZfdQYdormCBtWkavC9RBBrcyzLoNdxmfo85c3qh8y+xcH9DWx19KsEkZWMTHoV7DQ9KTJ6tT43qB3fOrb9RWIKzoFx/qIyuS3yTzWeMNPfdp6pTu05Yjb9yP5s8RRFrmr5Mru4M/kyF/5vxif713w0y/K1Z9wQiLWLHz+e0VEX9pogdUhO+6D/TlO3PjZQXCOWOre4LKmzgaXOBclSpwBSh13haJETXsr8P1IY72yXJW8iFyXJmycgb2ZPMVtcr6dGhT9vU3bOC+2Y6k9Q/LYtEXaSgwZqVANDzAa2koBBeKLeRDGai5Cf63G6t55Qrt5CEmY92aOVi2SYh8p/vVgq10Eari+m7hoky/LJBm26vdzPzXI3OsF1ruD6vE1T25e9x77vCKcZgtMKhdNDZvELNFhxR4mqz9UF14ZnoQZHlDJyrjTF10Y4PB0Qvt6UXQA1yQT1ttiNmZ4O17Ljw3K48Tx/ouVQcQscojYozm0A57Jvy1JyU3k6Wm8A5250lTWYzLuRnEeSy7RdRDtiW6H9TsW2T2i23diRbTcS21ptBRsgPRoEHqw3eWvwOXjTbCBHjH/QOXVlq3Xx6qrVbNgYFvrdq+h3zUXS6X9kiYhcUiROIUsr8qn0/A5TrMgs/RKkpcjaZ8jX3bQU0czeHL+vk/3ia9MzFemPqXTaia4St5KRgOn8UnAXB5aVtnIVcMYq9S8ut9IvFchr4QPPmPVbdZh1eniJjG0IiN96IRAHd4rD90eZvHC9i3JwIvvbcwAYfZo9xlRRHhXHZi9fkXFsltb/wrzLEW/TIaEDs/Ed9Mpnna6107BV7KVLNIPMRX4b9Ig35cq4GKJWN+eOCraRpfTgUGEBjdjnw4toxH5copY6sBo8E3msCm0hu8mxok6KpsaK6dlSdSyq3qOqxm6Bk44WNmMBGs/KXkPYQVjok1jYNb9xQdKZVg9TR4y5iZVxwhS+QDAoi5PEk2Ozd6COe4/3SrODvVTPy2IdgjGChI9P1Mfj+eFx0v3bw4vZ/80FinJvM+WuRB7MC3LG2sjG8m+CSTbUmyT1muu5lkM0pYR16jfuE/ZD5bvoIo8Qlw+Uo9hzMr7cU+DrOKlXYDFfGvRWnqYPs9yiPH33V4pV+4WvFTRCQOOl89EO8yg=
*/