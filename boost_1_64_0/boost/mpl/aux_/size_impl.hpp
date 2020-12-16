
#ifndef BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'size_impl' or the primary 'size' template

template< typename Tag >
struct size_impl
{
    template< typename Sequence > struct apply
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
        : distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
#else
    {
        typedef typename distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, size_impl)

}}

#endif // BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
JQiPdMXT4/6y1mA7Pmk3yIGXuuGyXwWLe59gfmO52D5yM21GK0rnISuhusNQ3mJn/OqQJcYM94DKQxcO0bbC8JhRYvSMycwxniCrxwRC400pyrY7seeb+1Qs2YJsnS9i0e7ZMNe1Fdu6a+CTVmv5uHY/4mJHYaj+G64aYkPFM+9QqnCLg499JJ2WSOWBFdDYMUPk6/5At346dM3fwNERF9niTwEyzbtLg64veXLNQ/p1WIuYNeHcYuzFdk2zsNwuEYdfbWdLhU00TOxJ86ODGbTxsHRWuAaFhLGwK3uOA3Nvi/ZJlnhvN5QPk604LNNcHFykR7+ot6j5tQ0Ls85x54Qy5s1QEQMeDWTMzdd8EfCDL19mMPNKNf+mHOMdo87Yl3pBZi5s2mnTzrJbq1sIf+rBuU1uPz3ASnTucwWilZvs+UgJHz63gHHPQuxoXSInDE/ExLezhe/1q5C33EVyQwqdj1ySTs08edZpKie52XDy6CBZr28Jt+8bZH3kIg4yzpdmiz4j6kwcHWp7Y4WOAC9e5+qz7eVJ8yCs+/Ydc6eOwsjJa7nuznL4NT+H0tpCbOqjL2P6D0BimLcwOLGC/me/YOpjZSp0zRYDvjzFLK1nwmCeF3PUe8qkr3cQ2m+9+HonAnO1LnPMrFPU0dSQm9ePZXW0JoflxuFuZx8atH8I9Tc9xH8r98Gn00U8OLobZSHWOFtxltc/PKeb9gUO7bSDXa/NocGQeHlQ7xdOeZZi+v0W6DZusczrHMTzf0fKQuHIsOWSr2K7o+zvU2HWug8eqfxA0JMhWHYsH95mBfCyfiH7dspgvZsJ03eqMaOHIWfOUcPkP658OzCHN4sfslAlEW5bXIRuhSlkmwd0uzqKfrca5fQlw/DxwjVxaZw385PjOdjrPAPs4hEWa8SoNs0Z+X4uw7YvkBafBtB54HB6xn3FwbESSrua8stSG1l3ZDvGnLOSaQHZbD+yL7IcBjLCJY0Hkc0IuZJv555gYPEvdFB9g41Wa+XNroo0fP0QBkXj8YlxaFagiNdGr2TKmx90NnkkatObsZdjnKjQ38FrFSUwHWzBFW0OI83xILpXuGKB/X/InhPKRJtlaLA+Jnp8quCBTrOleZtbiNTWkhkH6lheZCdSIs8j92Q0fph/xp4vzcWYl+a4uXKKWFP3mJYp0bDtGcPpE/vIDpVe3LOskwzU2MKzKmY8kDsCj07mIt//HfqnKPOAhTNNTGO42zyUep4RrAqNZsGsXvJm20K4uTrJgyqReJtRgt1fBvFYSic5QaMX2412kt1NspE28re42Po7Etz3c5rtVgaVPhdXTwbxY6sFMPA2Z/GHRvh57kA/tQC52eALtswMxaaK/ew6ORMtfg5jxqvvosPtcn6/vwhLVt5H9BcbdFI8xxhRjZz9Flj9q5AGr0Mw4lproamvCFvLFjQ6ksHANfqcvKsdC+elyPAuE1D85p9c7XmeoSOGyFdp6oyhuYgKr8W/YHsYT/mAIXdK2euMIWMK1zJfs5QdfqeLZkruPHz7N4/kudNDZtFmZHOcS3EX88MaaakUg2bb47mmeSVqnwuoafag7nEbmEXUi0ars8jpo8Dpy/fwznFVUW5ixYDBoXJL8ziMSU1B13+rYL/AXvwpmYn5jjnUDjSDmqUvjht957eUljx7gxSWm2TZ9Qq4/6tkmKYX/vSwFgZQQ8DcaNF5dm++fGqJFU4bYO50kq03XITqFWX5b3s9n3YdIqdWgb/njafbm524rEjRKi4fDzdnC/tn97DpmQteR5Sii06yzFr+FLqrd8nnab6Yb2QlfI58g/Loi9QflcojLtf59mEadVvsYYpbEX9khqPH0EMsX6M=
*/