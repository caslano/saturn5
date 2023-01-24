/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_09172005_1127)
#define FUSION_CLEAR_09172005_1127

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector10.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct clear
        {
            typedef vector0<> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::clear<Sequence const>::type
    clear(Sequence const& /*seq*/)
    {
        return vector0<>();
    }
}}

#endif


/* clear.hpp
POW40G7o04okB1VcboDWPN/rbA+nbe5hIw2bu3iR3Nz0ne76G1qQ7L++vTPUcev17V0UYXtn8Pae/wRt7wzY3lnRxu76nmACkiZohvyJK39iRlKICpitcsIxCIU9VJRqKhSvEOOJroVcH2WYjIxjr8B4YgtToG1lZHrQHotvw1KcmWXdwHRhWHwg2T2kMMWbDHG8FGc8ZvwmfgR6YIpImN7Na0M/N4IgbsD8Q1obQ771Pi0awh3rBlY1cFaeqB4WTKohItf2Tm/cHoL5FDtf3T/kSBCY0NIdbt99gg28WDzw4K0XZQMlotbSScgD/P/vqOzAlNuOBxHpNKi3itah488YWWxkqC+K2PfmXsa+p+l958+x2kY1UWSwtADEIyCXcd9E2mzbzG1ak939LgplrB+SUKbDykQTiX6vfVe+XSne1A1zjqKJWNMKLH+AHrtW0Wc7VtBzMz/XcLrtXbZV4/RXVuFnL/LPJVyshp/Vq0gkVM6/t71Dz1IuX8LpE/l3If++ln/XivLqME68nLqYCXnqBVyiH3SgUe3NZXpwcid+xkG66rtMLJIWH230Y1Z0Dj8MO9Oo/nulJqtMIV+i4HgqAciV8pndTN50XEiycBh8Oi7fKtobPdQJWUeCUKh0r1uxcSqIoeHmumm4yGQfj3N/JcG55fkUPfYo3kAdysULWRSCPof4OGirfB5fmm2VL6C4cmJaifg2V96B
*/