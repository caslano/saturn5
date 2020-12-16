
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

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

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
6ONA0hgGrkdGjqME06BG8ggeWCJoeoVuIdw0z4XkHLgfxiM8AiS2zc1FNahk6ZfmsuSFuQOTFCzPkEm7hIEJKitUlQFabGVXFpLLG0XiwIdiE7iESu5PpwY6kaK2zYMLNS5Qz6UgyPVzENLlUxCnm59nma03uz1eL/3b7PJ43VS9rvQj+rlNMk0RY4N3/O/+TP93Wrvb7nw6/WbsgIvzeNUU1r482au9FNRfjijhQ3ixxBzhuQbLm+Nm/+9LrfspluKRWzM+GTuO5aqBAjd03LYrYf9gZZ8+Akzhizj6ymO3qucqetS/ojAFN3iUb5+rnqvoERdMVnbyDVH0KWLsZKPRQXpcHK3z4ToS/krwC26U3RHDn6f0XCUxwRoKli/a75kgbPC5aypDC1n0W0h/xwHJ/LBafTdSZsn+Ysmit2h/Eaqmcc9ajaukKCqQv8qjPrxR6IwqlKhCepNXog6dQWO9/X4ycm8IZFUFRjYEPVXBg9mPhUaI88EZ3VWhA9mPBQ9gn5HA93X5KrcObQrNMhukN7/2+WOBfpJw6e+Ok0yNEX+OxD+eoSaHrG0ZXsOnzHn/Hy3OTU8SLELEUjTxxsnVspLL2ADCm64TWZGMDQM9h8yv6ONc4n/ZjPZpvAXxmoLUShGCLoAlBwafUk+1r3aG70uinKmcKiFCKRszhJYMtB3R2zbQj9oxjUyaA1sqVOi0f3/w0Pm99HXkF0YmAt82g5CgI77bBh443EJw/urh/xPQ7cnf5V4LJ21a/KHZkhk+UwIfGadtCeA9fJpSMRONp/55ncRlamWI02ihgHXFxELtl3pculaEuFgk1A+exy7WHtHj0rSFiOuNhPrA00vX9ahMdEdCPWBGHv5leoLx2klI0BUJ7QCzk+hKHiMT+xdwXHsk1Almp5CDpB6Xof0eca2RUBt4Ti7UpkvcGSMjt7rKd7soMz8GpjkSaqGv0t7WQbrhr1OXP+eKBBsjoSb60C19gPyRk7VHCEemnJwlhdoTRKYHEjmhpGiNMFMze2Gha5p6bB+WPM3Tuunj1qd2RELNkQCxHlKs42BdHwk1VPM32xuI9WXgp+WEBpU26xW/BsVviPnFmd8QtpMxxa8f/DZFQluqA5vow8bEbxz49eaE+kTLFKH4bVH8Ysyvn/nFIgGqo27Frwf8avEp51r6rDPxe+xi5teVE9ohlUARit9Gxa+b+fUwv+5IgL5b2a74dYJfVSRUQ19lp+8OE79rwK81J9SmKqdK8atR/NqZXyfza48EOmnhAn7spwN+ZfRV8epAGX1h/JFTtBPBbygnFJeWShFTM2PgVzH12H5ZgjK/JPNLyOZI8RtkfnI7Wx0+gitf+wdNvJ+Yz7xjOaF+ac0SrbOPMkhJ0FjCIEvQaOdJbworCX2QsAYSSuS+NEgoEQnLIKE7J9QjzR/RhoQSi4ReltDHEnrpNevqYJeSsAMSwgRVX2UPQ8JqkfDqPJbQnhPqlI6CaEPCaouELpawgyV0RQLU2VqVhDZIWAEJRZCwAhKKRMJGSGjOCbVIV0K0IaHIIqGVJbSxhNZIoE3NLViN0/B2/BMZao8zZAnYuZte2lbPWLSkUw/gAdGT1ooUsTRSuArA8iST2iRb5nxZuhBy2uqy8RhPrdTGg5i22nhMoH4sPA5zeD36O8Ifz0eNeP/xIuv6FavX6HJ8W3vPdFkP1i2XVWMTrSf1IHysvGmJtlWeKQ4LNYT9Ix1LLgpTnHQOWq8eU7lcFpg99G65ziDUAwHMWHtEYMSMwnroswCCkWsrsVjPlm/u84wuxJP8N3P9CcwHac6VNAMvMEfFXfu4cFZh2vgUnEHjJimT80TiTLlFmuenKc7E0Qg=
*/