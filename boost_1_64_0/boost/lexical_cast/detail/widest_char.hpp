// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP
#define BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif


#include <boost/type_traits/conditional.hpp>

namespace boost { namespace detail {

    template <typename TargetChar, typename SourceChar>
    struct widest_char {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            (sizeof(TargetChar) > sizeof(SourceChar))
            , TargetChar
            , SourceChar
        >::type type;
    };

}} // namespace boost::detail

#endif // BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP


/* widest_char.hpp
49YgY6woqRsjZgtLY6wosT5G1G0wxnbNNMaNMfoxpvrqxogZxtIYU33Wx4i6DcboivAY/fOdp61+D1dykb09XMmaZy8uzD6r9yC2nb5/qSVm//BjZ+27lKp5dmIi0Mc1QfqYWddHfBWs9TFT08f2Eejj1Pb6PlbW9XH/dIt6rNT08d+EpvfxryB9rK7rI75u1vpYremjOwJ6TO6o31OYUWR/T2FGkfU9hRlF1vcUZmi+i53DHLudPYUjqKMJe+p15C1RdIRvhOXfwBLrevKWWNeTV/OMtG1BPXk76fUkfIqe8MRb1ZPwWdeT8FnXk9D8HokW0NN2HE+NoN9Ec+9FTTjAhfPzxt50d/vDXxpy5O2n7/jgusJZkfOD0Ptx7Dw/iJ3l7xBJv4ZUQXuctuQKdd2ZfgMGL+De0kJlvTo7RLub2O5mtrtFaecN0W4l2z3Edg+rOc1DtHuX7d5ju/eVdstCtPuG7bay3bdsV+m3B2kLr+Dv8Rq268t4lIPA+3Pdewj9Ng5kPMexPD6W696ncp07l7ns5zMXUBlzAS1nbvrH6dew3vhsrotPZk6hTPB/6GfSmTl8EsBPY+7zk8GH89jUN8eRqBl/L44/iXuAk9U9vSXB213Mdpewneq/keoL3u55tnuB7dYre46T2c94tlP3HHdhu3ilfmpJ8PrFrF+i1M8MUX8e65cq9StD1H+E9R9V6leHqP846z+h6CmD4+2l0dM+rN+Ne6a7q/ezJHi7C9huEdtdqLQTvuDt1rHdM2z3LHM8JVfGWPOhQL1M0CxQGSj2yUB/Ct0e7dD+E5+A1m2JbtRvIgdUjf/Lwekf0cA3ogf4GBD9IfS+EPX8IBr3fyg7JLjPwzhQKD+HZfV9G4L6NGR8HS19Gnwg+jHQh8H0XQjwWwjts0B/BdNXoQxUvjm61kfB5l5ovR9CfR8ET32/A/ocNPQ1qARNoH9BNehGPEOrQRtBW0HRz8eIZFAaaAIoG1QKWgJaDloHehe0DRT9AuJGvuD4ITjFKU5xilOc4pSmlRZZ/y/O8+bm5zR5/78/BmCOXOevFTp8VKoZA3CrEgNwYJD19Ngicx3ZFGA3BmDHIDEAa7z21wFrvNbXj1C3AV73SxPxumDrRyuDxACs8NpbP6rQ9PmnMPus3oOqIDEAK7328fpKr3V8tdJrHV+t1Iz95zDHbhdfjWQMQD2+GhxH1e9bCo6vfiDx1ZXXL3m5eN49G06NH9Z2/fKikyOHr0Yqf9Gujsfq99vtfJwWc3JQHDON+M1I4pijwNmO86Eej+vNdn2Ix/Vlu4Gck4LhWYls11Xdv+QNji/1YP2e4CCJO+Yo+3PSXnBiAO4O+3MiFQNwY1qbFt+bYwf7as17cjLxXfKAykDXOjiYU5ziFKc0qbSI/V8wx+OJoP//QGn/G0Kl6S9t/++6C9OHPDmI7b/M67f90U52qnFbTLU5twfKpd1fFobdX2bD7i/z2stpa8fOb+DHTzs/26adn92EPqo6vjEqsD/0MQvDrvfasOu9Nux6bxPGujPt+NYWX6Z9ugvnf+l755Vd1yf926dT4d2vnbT5pMjZ/a0tvkyk7Hi79npLxJGR/khe2vGaOB/70U5OpR0/XPV/UtsFs6/ZrpfqpxWiXRzbdWa7Lqqfia5doP3PdvsExPRf6djzjj2/E+Ns7C62/AZ8j6pB20Ft1zu2vFOc4hSntHRpEfs/P2f6iAja/9v+Nux/Q2id/b9N2Z/fI9j+fMX+R+NG7TfVLsWBfs9oGLZ/qg3bP1Wzhvxrt8Zxi3CwANia+n16hfawANRv6KcQZp/Ve7AhyJq/CAMbEDawAWEDGxCa+7U9zLHvSlhBpDCBgyQ=
*/