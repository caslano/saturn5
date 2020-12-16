/*
   Copyright (c) T. Zachary Laine 2018.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALGORITHM_FIND_NOT_HPP
#define BOOST_ALGORITHM_FIND_NOT_HPP

#include <utility>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename InputIter, typename Sentinel, typename T>        
BOOST_CXX14_CONSTEXPR
InputIter find_not(InputIter first, Sentinel last, const T & x)
{
    for (; first != last; ++first) {
        if (*first != x)
            break;
    }
    return first;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_not(Range & r, const T & x)
{
    return ::boost::algorithm::find_not(boost::begin(r), boost::end(r), x);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FIND_NOT_HPP

/* find_not.hpp
DUKGH4AMtynR7SAMoUMKMiHKUyhRVyxS5NcUPOHCvbKeJeu32ejwrNrwnIlXLgLQmdRKTH7YXuI5lzKMfpiVviv6UZwMGcIpD8orvTlcITRIX5uFAJuJAMNzvtCPh/gfmoza+C+UAthMlalKwRta1Kd9SA2kfVrp1KLS/nhy80ujjnSi5Y2uScKT271ynI3ygqC8IChPmzMxFGsWj5FEIS6iqmSqjW0gSSXedXdciXqqhIyd9HXUDuHxE8Pjv6B99sWQwYNqIqVuUA2q8Tqo21+wXHVuCtWmhGIpMyeRv78/E33XEn1PM+lbja32VTrxV3o+/uqVV1RUvlf2wB+ppZPfGCS6I6tyXAyWHhPRXEwvivYK0iiVKfziVUBz/OZWmOiW46O/8ionK8shyoUoAUvCm4Al+ytvSGGVOjvxQZ55BLSVUvD/69GZCbvxfzv+N+D/avyvwf/3xiGM/2vwfyX+v4z/z+D/H/D/0XGZnfoD+P/vu/1anR8E8QZxUVoQBshD/FpUu9Gl1aKzta0+z5PVmNGiTV4oBPIitLwnqM7veb4e33159cKvmpJ92np/3jrFeasrEBnp8msXZ+Cj80K81XieX0FobGnrOG2dokWNtKv8easRodUoBct8nucbNCXDR5BP1lCqLElVzamqEZCXplRcs4qnP69Gu9ELZAW4R38rtOUBigwb/FjWI8MaJN3CKRoQMDLc7Mvbigi/s8YPNfMCDLVv/AWbC75RPM/XaBce4dM2AEO9H7sDYFgGDJvbwbAFNwMiznlzls+p9EJSsKLVSFfnJ8VBFAjp1rVpJl/eBu3CHI6rBrxSUIPytkq1sk0D+fJWQ1bJccu0rSiwM4pkqCUq2V2rkSrmNUjxXNrmvK15DT4nLjtZ5ytYq32jFGxRCpq5cqf7tJpW/dHQfuUKuXL5BO8MDET9lrVKV99+5c7iuCjSSeWsVG37Eam4E9GDxYizKlfdhcqh6+rRdUblvuLK+dr2wKb2KzeaK6cCHp0XpMp1refOP6Sem3g4em5Sl3tuKldusvTc5V3vuesOqeemHY6eK+9qzz0g+0XUb5Z03uwud94DtDo+lP57mlQ2D0MXPkDedbvaiw8sNir6wiIjlTNMMs8ud+cD5MPqUHr0adpyHoZOfYDuwO5yvz5lVvdxI5VzPikJdr13nznU3q36jr3r0x54CSikkzHjddrImLKQplpa2e/cxHXUwq9wxe+uo4dzraKtQulR+O5aVOqcVy81dip562kN586DpTVN4hopASBvhRb16dVK9F0vbr8hpOl1/vB5riCgsv9bhAX//33vv9byUUvfnqUoH+8UmcZLOHliLdFG2gTMErUSHJ8pWq8cz4J3ZD3oWfAnrAzF8D7va8O+N7Zm4RbPwvvZ8qkM//0Oz3PjXdgzpddhA4VwIiiUd+h4d/LfpDAEv4BOBhTvoRBH+6dVsG7Cp3I1gu96Lxe2T3jRorSx8yfIho/QQ0odbXRXliVqAK70Ow0IlwGRRBDlDJFc6U8pgfBusDpl9QDXqUplciC2IlZT6To19H4KRCwLz8ZusPENs3qvJhjV+94qVeo8PJVSIGUKQCV1So3nuYzcyiNyB6xTKo/kyhk1G4KaxQ8ulXCvHDnLhADM1NH/zmcV38fP8v+2gykTYrRUnIrDdM4BiZvnuTEszIB4y2d0hSKijDq8OeWBpgpYvUDWqvlorRFGX9QjPJD6Il9/0cF9kc8tbQkUuCvyqaFHJmqArSzBF5HoGBDcFQMZIhninK4de3X4w+FxODuzlf6YHCmMN8WPk6lBRjQaAs+k/sMs03C4wZns13ahlYpdamSWI6hdP1WFWPK5UWSliGhIuS8=
*/