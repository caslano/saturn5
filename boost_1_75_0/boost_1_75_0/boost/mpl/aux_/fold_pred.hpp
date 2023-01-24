
#ifndef BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/same_as.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Last >
struct fold_pred
{
    template<
          typename State
        , typename Iterator
        >
    struct apply
        : not_same_as<Last>::template apply<Iterator>
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

/* fold_pred.hpp
fbiYFVtQG6q52RRIE/VAm/JQSncu15epWRBLZxOsHtliS1dO4SianIBLtdVd5GMkKiCzsfxoaSIgA0OdmRMuIbhXDRWdW6kcMbNc/UbaNCz67iWVzWPSf3DxmpW6zRI2VAsQXZ1PjQUzshegfxihbcqIpEDoQmzXT6JZ87Y0OkNvByU1czAWluDuKkCXcQMvIQr8V9lJV4rNPzWSRH1Uo0SJ70lvasGDZEynt2OAxtcQuQeH9rXvePjsLxEYijs2M3SvnoaWuB1w+7xlcgKoZSQXvRisVk8ScpKVw/GhQ+tvYYcFpx6QBwISqoWNJ/w2exmPHX9KmZb4AVx7LAthosAAKJbmtCsDwJuANoMgeh0pSMg6IDPTHb+jcIKP4FtkFyYF9z1iF4gDvz8dbd6n9DkxoLYZlydpQT+WKA42TZ/6Bcp9dbkdFUAwRVB6DDz5exQPgToTFAHf9/52a8WfxH0ixpgHKdbZiyR1VlPTSf9899jGzoz7mfR2Nhq0KotJ3/dph1kWdH6ZxBgwHoRa2l+w0a2c2o+TvcU15PtgVfeTiYbTIuvqMR0qz3fyVwFClozh/xF9XtYzLQYkL9ybHjtPqoiliOlp0ZXepY/PMQHsSI6ivB0sUmCOj+nsZqn/QMen/aKygGbmM5hpVj46WHotlkcj3Ss8219WD6t/pdjGtdr9dB7dKalj+BPCcisZ5h+KHwkQAWRjzP8A
*/