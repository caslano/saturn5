// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/item.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Creates a item typelist.
    template <typename Spec, typename Arg, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_items = ::boost::mp11::mp_if<
        ::std::is_same<Arg,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
    >;
#else
    struct make_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Arg,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
        >
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_items.hpp
6v65hv+3utvBkHsAvuDUE3Tc66t7A/gq7u3ga7CzuneBm532B9+E58N/wtEaf5yGK4Lf4j5H7XPhbuw3qX0R3IN9tdrXwJ+wP6X2jfAX5/7SdN9X9w/gv537Te0/Qgv+DoMwKY6xANaBCbARTILNYTI8As6DbWEN2A3WhL1gLXgqTIX9NdwAmAZHqH0kbACnwEbwctgYzoJN4DzYHN4IW8D7YEu4BraC6+BhcAM8HL6o4bfAtvBdzec92B7uhJ1hQnzIvQrsDuurvQHsCY9W+zGwFzxH7YPhCXCi2ifBE+ENap8PT4Wr4OlwIzwDvgjPhC/D/nCrhn8fngU/hQPhV/Bs+JP6/wwHw7gE+nnYCM6DjeFQ2EntnWEWPFvtg+BwOBTmwSI4Ak6F+XAmLIDXwFHwdjgaLtP4d8OJ8E04Bb4LL4a74CXwXxrue3gl3AdnwtQqfGOHDeBs2BTO03E4xQ7vNUJGOr40wcTpOHwH47DDO2FjeA88Cr4JO8N/wi5wBeyj7v3U/RT4EBys7kPV/QK4Go5W9yJ1vwg+ASfA9XCW+s9R/7nwKTgPboR3qP896n8v3ARXwOfgevV/Wv2fga/Azer+trq/A9+A76n9e7guTveY6B6jeTrmrtQJnof0uWgVbAjXwhbwUdgeroe94K0ql9thX/i4c9/BJ+DZGm4ILMZ/rIYfr+GL4VPOfQafhv+Az8DH4bPwaQ33DHwO+2b4PNwGX4Db1X8HfB37H5p+0A65x8F/4l4XvgUbqnsj+AH2lnAbbAM/hEfBj2F3WAp7wk/gYOike77GHwp34F4Ad8KL4OdwgfovhN867Rkuxn6/uq+APzv9P9wL16n7Y/AX576Fv8KPNL9P1X87/B33vdDCXiNAPwlbwFR4OHTCtYGJsCusBk+HyfBCDTdSw+XDdFii9gmwHpwJF8Or1X0ObARvhY3hUnW/AzaFD8Dr4WqNtw7K9cCW8Dn1f0X9N6v/m7ANfBseAf8F20HnbJujYGfYCf4NdoZF8FZYAqW8sD2cr+43qfsi2APeBo+By+Fi+Kj6r4PHwfWwF3xD/beo/9uwD9yp7l+p+9fwFLgXngkz4kLu9eDZsJvau8Nz4EC1nw3PhRepfTwcCueq/RqYBe9T+/1wONyg9qdgHvxQ7R/BfPgZLIQ/wDEwQH89FlaB42ASHA9bwWJ4BCyB7eEUeDq8Hg6Ci+Fg6KQ/BE6D4+AVcIr6T1P/K+BMOAvOgrep+2I4G96r9uVwDnwAzoXPqvsmeC18Xe1vaDl2aD5fq/suuBAy/og9Hi6CjcQefh/UPSQwwed98Hl9v34FxsNXofR7mGEaL13HgzTMSo33O+Fs+AesCwPVyRfGwyNgAuwOq8CTYCI8BVaHZ6p9iNpHwCR4GUyGt8EacA2sCR+HKfBtWAt+A9PgDzAdJlOQurAOzIB61pHuydC5Aoz3rKMtet1vw+rwHdgQboWN4Huwidj17Dezb4I0NL04TFtNb6tzX8KPYA1YCrvDT7UeSs2+APLS+PUwWzT+2Bq0R1gMW8ES2BVOgCfDZfAUOBmeCy+G+fBSeBG8DE6El8Mr4BVwJpwOr9b4c+FV8DZ4NbwDXqPvwzfAh+B8uAbeCB+DN8EN8Hb4PFwCX4FL4WZ4F9yi6Zv2tp/5nM9V7l/AGvBLle8wS9fUw5M1XlXMII23S9vbd1pP/4KZcA9sD3+GPeFeeAL8DfaBv8KT1K7lY/177PvhDS3fZr0f3vTE26jx6vrEq1MzFC8dpjth4Pcw36y/Jg2NVw0zVOPtTFZ5QNGBAmvCr2Aj+DVsAnfDTLgLNoPfwDbwO3iU+ms5Wdscu5wpWs5aWs5U+L2G663x7lQ=
*/