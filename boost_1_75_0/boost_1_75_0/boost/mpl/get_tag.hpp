
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
+EEZeu4xk4/0mtMnsSU9D02H6lT4Bb9kGUucV/8WRTjjySDYArL7pILkguLTcHyynvbG0K+9yHpVum1xA9L70IMgc9hwUQQBghuBiWDhEdg53AzbOg0+7MY25w+ZMm/ILHdtWpR4yhUwPzkigXvmoIPToa4B6/wH3bvdSSAbnTslHDySy4ky1zkQ6SNK3Y7bdfM34fRr8e4JzzNimxiEkUGj3GTbYHLL+FcoF+W4SPdnbMjZEydgbQBKaHkvBHSe52QImD5kfDrNfDI4BrF7ygOd7npt/uyxQ2AyC36sn9NAJ6zH+4ZEhPX78z2O5oLj9sSPoW2fjVYMiT4Psdile8ij0nI8ydJmdsXUUKlap7Sk02bKsZdzHApcBDt0NsqNzJnn9THwvAtsJnCrJuc+SqDlx6Hyx1a3KKQQJz6wGdDoXh2m5QbWn1O753O4dnbkHy7ojZBPi474O6WkZPqNF7KGqMZ7tT0adR+QLbDPjpIWyF9lD1ZZ0uZ9aHBqgqWCTjtZQNXf+2bozcK59ChvLawoheGoCAsRhA+CNmn6ywg/Rm6cIluI0GJn+ZBhmoF/MfAp1MNNGt5kOBRzdqxHX3+gS7H443yt+TpyrGwQvKClC9AmmsXeG5NwO8IEZM1sQOnFhC/NzoqFtgfTdjFtsXdPfbuIt+z/PPatSRrsBCBf0cA0DjhlXOfIy+VsEsKPCEUUXGHOIXS5xbce
*/