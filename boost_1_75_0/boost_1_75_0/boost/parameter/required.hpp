// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_REQUIRED_HPP
#define BOOST_PARAMETER_REQUIRED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - all keyword tags wrapped in required<...> must have a matching
    //     actual argument
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct required
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_required
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_required< ::boost::parameter::required<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* required.hpp
pcxe0lXWWEVbEHZkBS5O2zAJG/wIIIIB47yPb9CLDvYFWDskLLk3difWPD2V2DnkvHpokxEa2m1VtURC2Vxk8dcHwOqTe+CMd4ffFlZlhgKb3gdpWmjXtzQFYS3ZMgDBj+6N1Y0Sj9J2c8mSFzrxOyxVElZEWZemQutC3GBQzWairyrNiiF0PTGF2e3cQdxbJKfONIndDZuK+eyDTkmlN+RTlE6AVwXg0oNMp2ePA2uiD6Jg+n70mQZ7trd88HVpAY++p+lNLW2ZaridcenIyKZ96lvw/d0tmuNUJWCxunpxHaSi1bcySd7Of8dDIIsfBhXsMjnIotSoD8ysTxPFupmtUFt6KFERqZ932jUot6NKPGBN2/FO4jwwRx1pYymWAcblZMs4bQQyKC3ZeH9Xc2udRE7e3DsEuVD5Jhg4fvo8MR+1BEG7B3X1VvkICsCtGXJQZPom3+2MmR5cRyjLPaXNxlFGm0Rvywq62GAVeiddNJOSc5HMO36bgrM8pE/C/VLa+9qfWmZZRwUZE6rrMM7wOvXLkapp3aawcThHhcX3UA2qzs944vmb+fjxahiUm0RYwRyb6H4dIXkvtoLZeuoo+I0bVZ3uYYumHUBA9xhvC9epr1eJDNggSMLIVDQ3fYm8Tc1Jv7jMhRH7+J2TO916DGlCJ5nXxWuNdjyBGezUo6iE2+mgVDPiGF5KqFy+zB/ncNYv+a8o1qqO
*/