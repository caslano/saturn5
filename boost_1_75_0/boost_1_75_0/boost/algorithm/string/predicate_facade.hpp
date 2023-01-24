//  Boost string_algo library predicate_facade.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_FACADE_HPP
#define BOOST_STRING_PREDICATE_FACADE_HPP

#include <boost/algorithm/string/config.hpp>

/*
 \file boost/algorith/string/predicate_facade.hpp
 This file contains predicate_facade definition. This template class is used
 to identify classification predicates, so they can be combined using
 composition operators.
*/

namespace boost {
    namespace algorithm {

//  predicate facade ------------------------------------------------------//

        //! Predicate facade
        /*!
            This class allows to recognize classification
            predicates, so that they can be combined using
            composition operators.
            Every classification predicate must be derived from this class.
        */
        template<typename Derived>
        struct predicate_facade {};

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CLASSIFICATION_DETAIL_HPP

/* predicate_facade.hpp
6T3Kd0Ec/ALMRmYTFXmma4npa6fm0p/NE6MMffgISDknXmoGvGxJnW14A/sZznnbOODdhQVKYu48l35LoH//qQuK+ioscFHyUY7Ztft4LtSCxuiPAcEjXoh1rs3yp9dJcMXardFYC26N/TR+h8rNiDkx42eGXHwfxRujwuk2gSI8sNdnSmvnLicmggTs3MDlzUtcQmyJmhGLktkPuxHv3JON+0s2aSa7BHz5lYoFxjevBI7Irk7Oq5VLTGvdT5zEfQiub7toXzcpFZpKEX6nEOh5vivmeFKZSj5XNy61wKi5+WPifPvukDEK5XF7wQeBP/dLm+x0zFAc0dGXfYL1C6klkDIdNbX9DGckYDsM9MeEYHbI5OBbzNRVEUwxHg70KX3J/IasYOBXAl3N+3nT/q31tjpaRheZzsRFtxbu5InrVFSHgNo2aazLw0uE7z09v/gPXrNR3+LjaWfSED3p00MU/0Bm6gru3jr57+Q/OrmHpAfREOhDipJvWejlaS0VKQsT+JUERj42MdK3SCC+nwzZ5Zuyi4q1VjD14pWKSDf1yFMfFDffDG5ivcidtiTveWInwLtK3PZL/KepAFtS/bVsoMQ2ghxC2ns/wnjbFAGySf/Re6hw/cq0+o4+Ytdq4Mm43Z1mLffFTH9Dg+LiALxF+VeL7+8XLbGAKC/mfpvvtdcnaVKvTCNfe5mHvYkJt1RZJFP/Guz4eiLH
*/