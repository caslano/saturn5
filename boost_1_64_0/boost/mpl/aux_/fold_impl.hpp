
#ifndef BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

/* fold_impl.hpp
ZhV8Hp5KU55+yPssFOK6xEVDaHuN1/vh/cohCJxUlfXpgicKHz7PCjKJ2Psw8RXflVnSTU4p7CHbjF6UTn7cUBNcGxggqnfjCw017CjjvdoaXaW3qILYBSxcSF64yOKA43YT6qWNDUFh6NwlSZsZDdDxBNOTtHsOMnwb7S7sWE5fJ7mFew9X+EXYHmfiFkjqzc8VsG89EMywSVzv79MaQ/m3mL1gnwh0UTgUIF0Lq+ke/LoDFT6cJ2fLneC2cru7kRvH+DQ982lfaX/bFYhfvtfHdeQfZvtsayF7Unk4PACcHu2AvlD3Pv4uVuvZhdgSmWKVrhPf83hkWOZob7RTmCbr53BThT5UTFIzKQQJUDMgwtuvPVYA/hhBwnksktEDEs5N2Rnfxbpo/LCXrHmbXYmKXhasH/XErsRaF3LptEQK5f0zDtQVq5i7o3BXf7CTCn6kEQ3IGPDuGOF4I7sOy3OUng8RdxEOwJMoOoGz6AXzcfZbLu/U5SXR6AHqmRtOoIGf/0qr/W1w6/rjZ8dR/mYurzeA7C8Yb39TuT7Fey/sqBpxyhsCLRlopNn6Xaz6nbn+gv1iT9qbmIUmmjqv20RRQQhN1nPV+aCLULV5/xcZ0j/E+53lkTsZvLIo/14Zgc7GKkLtFYgY9wUecMBJznj3Po/Het158Lpzo/U5GmjBNFXIF+zAjZ+Dx0weHVacvn7j6LiNpQ9haZkgCowIn6BXjiq55WFVDXmCXVGzqLSqPQ04sc2W5bH8j94SXgMjkVgwpcE7F++BItq4/BxzxwMgvV7ljixnS/HoXuh1uP6LePzFXF9xCgCbuWolCsFfHAH8MvlQo/mdw/NT8JTPzXFYodFqETzBgWi/qHRfhtwhQJ2Kq0FpLtyaR/SAs/Rfegp+Ov13KVZl/0di8/qE47EFwmVYEzxQGtxikTXVPNalb+p+gKOVNcjFdi+4ao6XNqzPxz9SrT/TqaeWVylthF+ynRapOJQczcZY0gjRQVqXwspQSD3zvKqUsySTS2lj1PEeYbq4YZ+gpzpO9orik7i4d8H+eQRkbiCcRGlbxnuRApUKdtpPvg+FdfPcxrBBP8Ke0KkBkwXAyPRztF02UTqSiqnXVMxaSLWSAbKJ3a2LpUFRZUW1NXGGs2nzn+JvzunbOn9zWmbL/NOaY5rnn3aLo/0HW6j/Vp/W6198TCv+Sv9a02z7g1toH/zfOPof1rfl/n/laTn/wYwW5LffHhVN3wQp1jvJOxFLYcHLImJbvvlsFyX4fuqgOs6k7LCvRvJ+kiUltnUcguXOxvk/F/tu/19QgVUsiG5fgnNXL14MyRJDveoT+DNvNtHlUBw6g/YyEfQL5rpdYjweSocGF3fSSeAs7oYStkwwxJGBm01okHyC/tzi/p1ghJMQ+taI0B+o/p5YKbcartMarnGHS9KxQ3nELByhEQv/z/oWLBxAVEIBys3PkGKRYj+lnQPwzFJpRV0l4fAqhivnV0vzEE5Oa4VTx3E8UgxhVjgJk5mFkQq3P5tZYq5acbhVK4DtNCzAbz+UI62DZgzBo07gsFMtW+a68gkCNXlAjgSFp/CRzpJjtGWzzgfq8nSkItTHpGA4CWGGg0CSElYuBfM6WtR0K67wXFEIgyrBoD7bi0Gx1JrAN91pteHmNhrjOQidt8FjAcvBumk5mEn+zpBB4B1Oy8dIbEFxg+BszRvEX6if29mub7BQJWSOXVLy9VuwVxoooMfM0Wk+KnucU5QVVwr9uClB/BCv49B9aqZz1a6YG7rBlubitPCvVYJbJhgqwSMTzlUJPplwmkrIkAkjVMI4mZDJCdjZMqmLTBInUg5nB93/CNgFmKxjtw8A/Ok=
*/