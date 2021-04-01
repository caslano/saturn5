
#ifndef BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/has_size.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation - returns 'Sequence::size' if sequence has a 'size'
// member, and -1 otherwise; conrete sequences might override it by 
// specializing either the 'O1_size_impl' or the primary 'O1_size' template

#   if !BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    && !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))

namespace aux {
template< typename Sequence > struct O1_size_impl
    : Sequence::size
{
};
}

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type
    {
#else
    {
        typedef typename if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type type;

        BOOST_STATIC_CONSTANT(long, value =
              (if_<
                  aux::has_size<Sequence>
                , aux::O1_size_impl<Sequence>
                , long_<-1>
                >::type::value)
            );
#endif
    };
};

#   else // BOOST_MSVC

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : long_<-1>
        {
        };
};

#   endif

}}

#endif // BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

/* O1_size_impl.hpp
FOWObohLe6BE0oaqLfOjuBSD2tL5uNdWbZdnJ8dF5OZ28AQ+mRzDp+1yYvcGBtuVVvpg+xMyQgC+DV5XWXlgVyHWakOpeQdSm+g0+HQkTHm/b2VeqPpIvIwHpFMzG7CBdc60PG1nPvHTo/e8emm6cllkdjbGud5ZhGpfdlkMjI6QTcUBrKqwNlMBSXoIDzNDOKrm5B5JWi1EDwjqRyoxldWHLooETiMKlcHMVECZtylRlsrxaTVRxbuHr9rGIdJVIjSiYaXTwqJSXkxo6t/xDaTAP1RVnCsboyLqxZ23G+jDzzk3daEgCcXCiFY25p4Ez4nGrB2jLbirqAQ4VKlhAjwv2vua9blD86+lkUJnhN4nCN1luHM/cL/xbx5g6rA3ijXzuziSEchjqePEDWgfYWAmJl2IU7YTBYpP++6xZsDGki/gvgHVVASf5/GBz9EjySeK65exhdHtXrQJWrYxuCnDrZU0vgPsAhPbVoLU91L6og/TjrcnNVPgP1VJ+oH0eD7mRJYsAVxPJN7Hmb6fXOr/Jpap8fRp5DuD9g1s5E87YmWrzwlIm+DwNA==
*/