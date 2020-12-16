
#ifndef BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/set/aux_/erase_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::set_tag>
            ::apply<Set,typename Pos::type>
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
r1LM3omYvc3Z9qwr5fA8T/b+n+Vj++Xuv2orsVvfDOrAOTyflaVrOGa7Q8x21jt2DXJJ12YV/ll62lVd09JSUnPUVvb4F7P1YnZs1nAXeww1IOfnRmrHbNaqGPsGktjs0qevfXWgi5nO2TGgXszuezG73a/aTU3pntSjb1r2MBSf1iN35kyclf5ZuvZV2z3tMiVXbA2J2QpctZXjmjaM2bocs/XZvmvf/UxKjb122qVfen9fWlJKRk7f52XldEDlf5Zuuf8/2U/vFp+Ss3P4WbFfitkO/8fY/xl6Th9HWfYHuP5Z+tR/st89d+zXjtmPxuy3uWo/HkdyUmrXK1ej1/frvf53/e/63/W/63/X/67/Xf+7/nf97/rf9b/rf/+vf/ntP8Vj9+G1Xa2SUnolprlq//f34M/mue8WR7f+CY4W93TE89/01L5p3RL/+T/Tk+t27ZuUnFC3Qb0G9dzd6/ZLb+hucFf2Pxtwd5O66fap4MSEugn4vGvsnztsQhWtJST26xir8exDHdumpiand3ziafufDRrXa+Cu1/BO/JOuSSkdW6amZ7S/u0nHAfafZAukHhrwJXTNOZes2a7d0gb6MlKfaJFQD013653gcNVPsbX5PVJd9a+Utf9KTnbVT+rts9L3UA37P676qX0zmFpxVO3O1IDjSm7qWG4K2L8cjsjAMo489q8sdtOV71DlI3azMfcnZYmVNJY5sjixK48f7mBWCeVWliJ2mzFXp8LEasHu8LzE6hoLLeW6DY0FHipB7C74t+ZmYs2MeYU1hy/v3EjsEWPONeWI/QXlIkWIedGe1H0GdiXeDsb8ZQsR6wIbw1nnBMS2/gZiSdBgOmufYix4qjSxdPg3mHUZYCx8ktlQsKHMRsLuHPZ59JVnD05i42CjANt9xZjvpZLEpsC//KzLdGi1g/tLJmzEM5sF5uVczod/HYoSWwJfNnLd5YjtMNtdAyY534C6H3IcH8HnjbcS2+qwv5c5RztQLpnr7obPr7N/B5DzIPt3FHYncGxfoFz/YsS+NuY8ynF8Z8wVx8dH1Jh7EPtyEToHOb+/wr9x3P/+NBaNOIjlz4P8sn83Gotu42OwmDFvP9alBMpVZp3LGPMcYQ0qwkYH7s9VjYWlH9Q05tzEGtQx5nuJ7TYw5i7OfbeJscBs7rv3gtXnHHmMuWazfg/Dhhznj8PGKT4un4QGDVjntsb8ldiX54yFLnC5zsYi0/mY6Ya6+9iXntD0N463N/Rbxf0gDVrN5Rz1h38rmQ2B3d9uIjYCNgqxL3+DLlULEnsZusTnIRZAfhewf69B5yUc7zT4N5Nz+Q7KTeV+8B606svtzUPdzziXi+FfMvv3Pnz5mPvQarDDtxD7wFjwEtvdBLszWKstsLGL29sOrbx8HO1Ce1X4+N0Pn8uw3SMo9zXrEkG5aezLSWNhOdd+C1aP+9UP0K8J+3wBOa/A561fjPn68HH5hzH359zH8+W1vrGC+/gNYJ3Y56LG3DtZl+LGwnJcljbmWsH+VTDml2O1CmycKkCshrGAjM93GMuU9tzw5UP25U5jvs4c7z2wO5aPmQeMOd/mft/CWKg5l3sM7X3KPreG3RS2+zQ0CLIG7WG3DPvSCbqc5GOhqzHHSs5bD2NfrGKWbCy6nVkfYx6Jtx987slsMDT9isc/P+w+wGwU2lvAOo81Fvc4xzvRWPBJHksmo+4gZlPhcwU+ft+G9nX4mHnXWGQm150LrZby8bYIvjTnc9QyMNFgFdqT43c9dIlwv9qIOByc30+Qt6Fcd5sx73g+ZsKIN4Xj2AefpU8eRt/ty+WOQxfJ7wnkqAX7chrtLebYziLedzhHP4LtZ3YJTGI=
*/