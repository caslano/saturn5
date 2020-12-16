/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP
#define BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/proto/operators.hpp> // Included to solve #5715

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <typename A0, typename A1>
        struct sequence
            : expr<proto::tag::comma, A0, A1>
        {};
    }

    namespace rule
    {
        struct sequence
            : expression::sequence<
                meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::comma, Dummy>
        : enable_rule<rule::sequence, Dummy>
    {};

}}

#endif

/* sequence.hpp
nWPYtYHsjIQbBcBRQGZ/NLCYv5MVdscCTxbvSzc1inugTSHgeOA64NHAC4ETgNcCJwK/weZJ4HeBxwKfApYBdwGPA+4GTgL+FXg88EPgZCDbKz4FOAp4AvA44InACuBU5gdwGpDN29OBK4AnATuAM4BJYDnwHGAFcDNwJnArsFIR8XhcoWcKwD9R3EcDH6B4XE/x+DLF4waKx43AicCbgdPFc5lN84FfB3qBO4DLgbcCPwe8DbgW+A0gu57dDrwYeAfwGuA3gV8F3gm8C3gXxetuite3KF7fpnjdC3wTeB+vB6sPPatgbUL1KOBxFOlHLlGPJ6kf/dhllNtO5cbalHuByr0IZHHZJZV7vB9791K5+8je/VK53f2Ue5DKPUTlviuVU2ryl7uLyt1N5b4llSuryV+/Z6ncc1S/nVK5Jf2Ue5TK/YDKPS6Pr5r842s29ac51J/mUn+aR+NrPo2vahpfC2h8LaTxdTKNr0U0vk6h8bWY+sup1F+WUH9xU3+pofHlofHlpfHlo/FVS+OrjsZXPY0vP42vpTS+ltH4aqDx1UjjK0Djq4nGVzP1yyUuuv/l98UiHlNY/el5YivkRgBXAhl9FXAGsA24GLgG2Aw8ndkV8+SmLDACPB8YZfaAqiLmu07g7cAu4HeA3cAngDHg88Azga8A1wLfAsaBHwF7mB/w6RwWR/h4HvDFAfiPxRF4AWsn+H8R8CTgxcBy4KXAU4GbgX7g5UAVuAW4HngFiwtwK/MPeCXwbuBVwMeAVzM7wGuArwO/CDwA3AZ8H3itFkdFu3dnc5yIYxHvRyJto/54LfBI4JeA44HX0fXiepehZ3s/eq4gPVtJz5Wk5yrSc7WkZ3c/er5Oem4hPTtIz62k5zZJT9nS/Hq+QnpuJD03kZ6bSc9XSc9U1s9Izy4ad5PYdYj62d9o3P2dxt1eRYzbfcCZwP1s+gS+o4jr6QHqd++x9gR+QPP3P1i7Aj8EXs36NPAWMb433QP8BHgf8FPg00AX/PspcADw18AC4DvAQiA7R4W8qRQ4yCXG4WBWL+BQ4EzgMJcYh8NdYvyNAHYBjwBmgcXAPmAJ8HLgSHb9B44BPg0cC9wJPAr4InA8xesyhe7Fgb+luB8BPIfi/lsal68AJwB/B2Tx/D1d714F1rA+AFwD/AMwDnwNuBH4OvBy4BvA6/nzexGHPwFfAr4F/CXwL9S/NynavTXmImo/Zj+rXRcUMa9/D1gGfITNR+L6vel04BPATnZdA34J+JQi1j3PUHs8S/Pjc2T/JzQvPg9k9/a7yA/FRffFrE3Jj4n8/kmk+S4RF5Th8VgArGTzs0tc/092iXlriUtc993ACLDGJa7zHlqfeV2i3/iAt/M6i/j4XcK/pS4xLy0DMmcagW42zwI9bH5l+oHLgZ8HtgDPA7YCrwQGmV7gSuADwFXAx4FtwKeAq4FvAdcADwBPA34AbKf+cY+i3Qdjrqc4jOTrGpEmUhyOAR4NPJbGYxnFY5JLjJ/jXaKdJgMvAk4BbgaeyPwQ43bTM8DpwNfZHAAcwNZvwEJgOY2LCmA5sBK4AFgF9AFnucT1aTb5fbtC97a8zYTfpXy9JlKI/D4DOA7Y6RLX1y5gN7AbmASuBV4CjLN4AnuAXwSmgEzXOpe4vqSBPwBmXOI6kwU+CewF/h7YB/wTcD3wbeBZwL3As4HsXvlhTDo/R/4YeUYN/EK+CvlJ5L3IUz24FiNHkTchb0O+B/lJ5DeQ2YV8HPIc5HavWHzuQP4+8ivI7yKP8iFuyG3IWeQtyNuR70HeibwbmS0ApiJ7kduRz0G+Efku5J3Iu5HfRR5Vh76P3IDcjXwV8gPIzyC/gfwu8qg=
*/