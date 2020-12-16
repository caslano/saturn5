
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/size.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), 1), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR \
    , /* else do nothing (keeping previous error, if any) */ \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_specify_more_than_one_return_type BOOST_PP_EMPTY)

#endif // #include guard


/* return_count.hpp
j5wjec/6ZJK5Fr5P+nP4QcGweIThHRJK42Df5+I5LcnrxWIovAZxBiEd75v4XQXdleIZK1v6vndaSEeWhYbPk+xQtxcrdbuzturG3uEchkcQd+xBIc5PlclhyN83bzzbKtv9U+tzxJd18SGhK+Jq/Uxd5T3bPY8B+YBNyIfCY8D5ECbOR74bbCWX227rW9DNd7aVIYYrm/MVm98I8Q9rtdeqTRfl4vx+rejKe1w3/YO8IQx5s3N6mAeVk9Y/I9xnTyF+aUSfhULGHbBHXp7hzn+lik+eiOA/6vI+0bn/Stey/57Q+A95oP+sbdxSjf/uh65f5z/BrXTnK7/VJvRfdc0m9bsJLX3C8/oKdBu1ea2ubaisDxguy7bRzK9svyv09zCbXe930S62eWwHKyxlsigz3M7noNektbO28mja+IzIdxUK3oHvqNTJZ0P9a9B1mLdhs3NFFHYiH7AJ+VDqJM6HMJzPVqZz+obb+gJ0m7W24t2vvrpylss6iDTU/mx9mVr0+A4Wha26Mm1hmarPYxVZ4Xa+mwPdg2xcvAq8XAcq7ZxU/XuJzLfk4mnto55y33Zvn8qv3NDKw7PU2fx+4fa9jLhL9PaV+AP1rmxcEnYfQkx9nZW6HX1AXbMzTX0e4fksz9b9w219CfFbbbaKiVWG4crO1ijsbLXaiSPrxs42jZ1v5yA8zE7cFlza2WbL+5ooOKFq3tW6lzcgPJ/LoNtuzyeaSnByxfiE7G90cX7VJyMH6sveKLCdyz+zocqlT4wC92Vv6sq+UBf570rZ9x+k5w77CrrOHfYVuOcO+wrWPXe4K2u86jme0XOKB0zxIDx72f4l1zy/skf91C2Ov2P4D1dFzx2OliP8T3GB9Rzq6LnAeq70v48jrOdiO3GHu8YRXgzBJsZQpsSFxqc/U35/qPx+Vfm9Uvndpvz+XPn9Hn/fid/Lld8fKb/fV36/rfx+l3zkcZBP+fsyyDv8PcxjfsOJnA1gkobHOAKHDfJFE4Fbq+uMMl6KJt62jLcdsCdweyVeM+NtoIm3C+PtSr7pbuo3oxivhybeTow3CpgE3FnhgS5hvHEaHmgL+a138nx3ke98N3AoeZRbA+8FjgTeD9wLuJjp58qxbeRB8+2mzT0h/vGWwF7AEcBg+lsBBwO3Bm4P3MZDvqyH45YcYzb55YgntoOZzynAQeSFb0be+ATgoeRjlwAFtxfoJ2/6aPKmFwDLgU3ACuA1wErymI8gj7kKeB95uI8CjwQ+A6wDPg+sBb7C/feA9cBPgbOAP5A3G488Hwf0ARvxvw/wZOAQ4CnAYcBTgSOAc4E7AecB9wCeAcwDzgceDDwTWAicDqwG1gCnA48Hngo0ebnZ+F2az/pF/w2GpNN/j9N/z5D3+wJ5tv3h/4Hkc28CfInl/howh/s7cH8M8A3WgzeBBwHfAk4Fvg2sA34ArAd+SB75R8BjgZ8BzwZ+DjwP+C3wKmA7efLfA2+n3iPUexy4Cvgk8AfgG8Cf6PefgZ8DfwF+BfSyHm0MDDohC5gE7AfsCYSdvC44VgLcSXNdXMHr6UpgKrAZuBH307ifCbwKuAXwauCOwGtYDqXm+ANgDNPvCSlg+tfzursB2BN4E/nbNwPTud+H+/2AtwA3Bd5KvvltSruQz/P007QLg2FvEIcAs4CbAM38NTLeSE3+9mD+xgFTgHszf/swf3nAjYG5wC2BE4BbAScCt+dx8zytPE+R5jxn8zznArOB55GHfj4wh+FjgRcCxwMvAuYDLyYv/RLJ32YfKZ8Tp8RZ+dt3Knr5ih7yY9G7TOWNO+vh/qHwxl2et9GlXpNLvWaXei0aPR3/fYlLvVaXem0u9dpd6hk=
*/