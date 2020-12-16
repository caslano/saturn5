// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#endif
#else
#include <boost/mpl/always.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    struct always_true_predicate
    {
        template <typename ...>
        struct apply
        {
            typedef ::boost::mpl::true_ type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename ...>
        using fn = ::boost::mp11::mp_true;
#endif
    };
#else
    typedef ::boost::mpl::always< ::boost::mpl::true_> always_true_predicate;
#endif  // BOOST_NO_CXX11_VARIADIC_TEMPLATES
}}} // namespace boost::parameter::aux

#endif  // include guard


/* always_true_predicate.hpp
9IRaXkLgKFgXxkMfOBvWh4thA3gLDIB3wMYwT0sD3ifh1sn2etneAAPhJtl+AgbD5yW9fdAPHpDtt6Ab/Jts6+3iZefnRVup33ZyPrU3XserCTdc7FZHQC1cJNTtGl52fj59Jufh53J+fGFo9wUvO7+/+0TCfQobwhOGcKXVpHdcwn0k6f3DEK6smnB/lXIpkv7tCeN15mXn9hfN5HrcXK7HYYb7EMsrzu9DYiWfk6WfmAEDYDxsAhMM8zphEs94k35tnhznQrnuzIeNZbsjXAT7wsVwAFwCx8ClMBougw77xXxJ5yUT+8WTtezX8W9hD/gd7A1/hKPhP+FY+D2cCc/BbHge3gZ/gBvEv+N8zi11/rw6RJ4ftpZ+v408N2wPm8N2sINs6+1C4gswqacttcR+CTaCRVCv31Ln7X6vXEffgHXgPuhYX3ZGwlF3V6wvqyt2Wz5i71Jf7F0aiJ3LZtgJ+sJw6AdvEPcJsDFMh4HQBpvCm2EwXAFD4EMwFD4NH4PPSfjtMAyWwpbwEGwFy2FreBK2gWdgW3gRtoNebpQn9Ic9YFvYE3aFfWB/2BcOgf1gFOwPY+F1MAkOgFb4F5gHr4dFcCAsgRFavuBguB8OgWVwGDwOh8NTcASshJHQQpmOhD5wFPSDo2EIjIJt4Bh4LRwHe8FoeB28AQ6D4+E4OAFOhjEwDk6Bm+BUuAVOh8VwBjwME+D7MBGegCnwGzgL+tBQZsMAmA7DoA32g/PgJLgAxsGFcAFcDPPgMrgO3gwL4HL4BLwFPgdXwh3wNrgX3gk/hXfDC/A+6EG7ux/6wnUwGG6APeDDsA/cDPvCAng9fBRyzVHtZbrsP2thP7Lus7fnEjkP1DucHXYnnvbrVCBUdiewBwyCfWAneB0MgYNgKBwq7pGwGZwOW8Jk2ArOhW3gEtgO3g87wAck3EOyXSzbun3lm9JvmNxvNZTxWxPomN/NFf+7TOZ3fxL7hJ9hY3gRasf1C+yj+ZXjsshxucnx1IKjZf84WFuex9eF6reioA36wBWwgTx/94UPS7jHZHuHbDv6Det+uS6a9BuzxZ5gDqwP02ETmCH2BVZDPMXVxGOTeOZJPPMlnhyJZxHUx8v7nffTyySeFVDN50u4XM3/AXu4EyZ2HaO97PMNE6CWXoyMzybCB+B0uBnGwa0wHu6ESXA3TIavwlQZB6XB9+AcWA6n6OMhdND59f0Vub6XyvX9VajbqR90/jy/sYf9+h4I68MmMAgGGdflHHRuR/m1pHta7Ci/MYzPcyXcIJPxeYik21zGDWFQy19L2AK2lfvLdjACtjfkp+Kgc7syX5lP9xO7Mn/jfPpbzvvVZyRcMWwEn5VwO7W8SbgJblfOi/eXdQIDZH3A9WJfNxC2ghGwh1YGcp8xDN4Ih8M4OAImwWSYDEfBbDgaLoQ3wA1wCqxHQtNgIJyuxQvjYT+YAMfAJBgNk6Fu/39InleZ3M9UyPzZJ7A2PAGbwpMwFH4Gr5HtVrKdAj+HjvFW9NvO14vsk/Uib0I1jyPrRQ7IepGDsl7kLVkvUibrRd6G6l3ZcK64O+azKyS9cpP57E7SrrrDbrAf7Af7w8FwIBwBI+EyOBLeA6NhPhwLH4bj4Pvirl8//uZ8nckIme+MlHUmI6E+7j1sD5dkMu79Su7PvoHqfQgwHJ6Ff4HfQ618KuF0+AOcAc/DRNnW1ykcdl7PX0o9fyX1fFrq+Rup52/hNbLdSrZT4HdQP44ye/zZJsdxQZ6T/QLVezJl3UgtWb/sB4dpYXztx9MAztG8wSzZ7+gXiyUdN5N+8aBcb/4G9fFymfP7mmCplxCxNw6F+nWkmnDNJVyYhGthmL+2HHE=
*/