/*==============================================================================
    Copyright (c) 2005-2008 Hartmut Kaiser
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUSION_AT_HPP
#define BOOST_PHOENIX_FUSION_AT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/type_traits/remove_reference.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(at_c)
  , (proto::terminal<proto::_>)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    template <typename Dummy>
    struct default_actions::when<rule::at_c, Dummy>
        : proto::call<
            proto::functional::at(
                evaluator(proto::_child_c<1>)
              , proto::_value(proto::_child_c<0>)
            )
        >
    {};

    template <int N, typename Tuple>
    inline
    typename expression::at_c<mpl::int_<N>, Tuple>::type const
    at_c(Tuple const& tuple)
    {
        return
            expression::
                at_c<mpl::int_<N>, Tuple>::
                    make(mpl::int_<N>(), tuple);
    }
}}

#endif

/* at.hpp
X/C/FoNFS6cx0JpUCWvyvR+y2g60U2cpPOEBhoirL2gG15SeZNQL0FrYQvRt/ZjoqxMLkQb6UlSe/HbXSClHHtWV6VUlxARhyOWKPHckbBw1BpKx8BCkT+U8ZtQRa1NKioQ+DrRjxR7DaWJJ+GMK+YHyQmvRzHz3Wwwa8l0Hg8EceQPQaRQJUseK4ZKaPVQHGxe+RC080J+WXs6WTLrjgDJbY2IrDmizSYfBMZMX44s4n+0ieB/G78yPzsbv/BTi95+6NOH3rcrEabaQiDCON4gdgm+7NMdxMQF9rMslcFnjbxkKtUcbFel9RC3HzHEklvJiNc5C/dYZBW4KukdxL0tRK1TPy5IErX5oBerJNG9xDxI5OnE/pSpR394gJi4lFZwWeSndsBn9dywYDIhZVFVnhRQzE57BSmSciLyRqof++AHXYXxnfaM429D6YACJTHYDTVyuPiaE5ncXTh3oIRqCCTWJ0TbkRb6m6bYcB8/MrdvU1duYw1RSPCLdu2lh6xkxHvGVQ/hqljIdtDTDtvOShfIcbbiImw9zdi1HiH8rgEkuAfan9zZE2fq+AXZUlmw4EwyyFJfs1HwnFR/wuecnSi6xMp/3DnOJGbrskLo0M7v3Bf3XtQDmJztFCiFLE+z0lFQDD2ftocYcOwPPLorHnM696xh5XFfb3wZl9rH7I232JRJ899BMOV5u04mHLypgv4XYgz7ch4t/9yjjy5FfSlY6s9lrLjohgeqi76UzaPmr7Z9qOCMMIZx7kjWcLuAENveCOyVriY9kaz8SPSVHmMYjTFoX+0kVjWOoimNRCEdvC1LpQpeXs+XIv0KaaLw+Xh9F5coPcpTJ/lVTTP1CmL6MY2oEHk/GneCbN/dObwaYJiPGIQUT0mzRNlGYj6JyvWXEyDz5dEcxoJTsZcrJlRZ3dgBXNdN0pKNCkzPS3x3FUHHz49Qm517p2ysQyoTQV7KO8+1rKRFe1KWLPc6oEj9cJf6Bjhrx1wGbKLhFYRd7OxXWfp2O81kC3P98LK+R3A/OkZypVOMMJ684HS2U4u0SZcA/atWsOcGD7r1JvrJVespaWiWlRu18vhVEuq9sHfOiriWnMM1dNTp+rZOqiqsEHZ1jiWZC28bZxX6dBlung12lwH4XA8HaRQWdQaoz2d5XY4dThbUrsG/FIGhQKU1pqVLa12H2ZddphL7QgpnLVSjZR7A+3zqWl1xrqArpzVbhxw6iqHtR1A5qv+l7JOu2kZF1JftdrThi9+eIGJ5QB/Rd7JnN1q1cQdIOSHy+fVz0FBDF/XQJgr6y5USpQp38eAuFLGvxOomy1Ai+7+PqzLBqqUsptaSUMql4Q+1l95UV67H201Ju9/kq9BjbaSn9vCUVAttqPcBAq8rBK1Rsd4i9ba716GZZtydJ1DrFTK1PFTQA9q5mOfSoAlsfTbBUIWNBF/u9GuyvdNLtUGCrGLaYlUdLL9conTmFnDO0nCt1OdOUnL+KVtQR+kVvFn0nz9FF5d0VWN/6llD9HW2o1xgxtrCOmBM8RB2kpFzHIvnJFiEZKmiWEdvbi2LbR5NoU2bqdthpK9kCP2lSzKHKKN5TRjFMkalooAq1SYVqyX3Y5DV7fBTnZej0MvIX9FZzkZoBnxdrpMTpONBTIWVFFILJvrLV3LxfxWrt7yuZo6/curhQ7y+bL6RpNbf/z+NC1V7WfPu3U9o/ikR4PuNLtqrbadbKkgOKSvQXS0IhL41H0D1/IY1TazScj+jon9VOU4SddGj3t2S0OQqNckysCNMYSS23khB7MxYGDwglawkVHogVfhQHaeJYa8luE0qjf314TH3rgDIG/v5KKl6MDIoKVTV/NSdZaOQ=
*/