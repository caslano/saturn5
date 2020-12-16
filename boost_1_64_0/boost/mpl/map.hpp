
#ifndef BOOST_MPL_MAP_HPP_INCLUDED
#define BOOST_MPL_MAP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/map.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_MAP_HEADER \
    BOOST_PP_CAT(map, BOOST_MPL_LIMIT_MAP_SIZE).hpp \
    /**/
#else
#   define AUX778076_MAP_HEADER \
    BOOST_PP_CAT(map, BOOST_MPL_LIMIT_MAP_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/map/AUX778076_MAP_HEADER)
#   undef AUX778076_MAP_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/map.hpp>

#   define AUX778076_SEQUENCE_NAME map
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_MAP_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_MAP_HPP_INCLUDED

/* map.hpp
uyBripUjmRn6kMRCn7ByaPATWdw43V/oD5/IMmCoEa5UjEjXiJoAgU/Jf/Di5ch/RPMEuF7Lx3n/0Rz7Ey1vVPP2BwrIWsqfCfuvgPs+HJfdfnuxn/WFmRCyDTlOl/Hb9HVEbZ521ovwIM+y3LjgjSTLHZmkpUBoztlUqhiXnaujHWd/lYg5QGDIVwyOscDxWaIW9okRrcSZ1C82YfYzMg24P9UXrUdGkAZUfzGoxgPVYo1K8wlcXh7R4le4vHTs31MwH7AWT4L9FG7WhiZCAE3+IMKKWOUcYHiiIaVFXqwS77QJdpN3oU+VbnOAxeF+ELh21rumf0OCU6l/qxL0cJ9JxdXoKrNl+7x3oMHFPL0fU3C6KdhCpBqYLqT6GaxUwzJ7URYGyZCw/LTE0aQKNKmCm/RJDObOBjMf+1UfhkOiag6riC6M1uCCgd+lFWipckgykxdwhpIAYiDnlWhfUfLaS23PxdsJAScHk2CGsL6peiTQpBKsRXhG0ttQ72Kl7I5p9jgfmn1AV5+/ysfsz2Oauven7HQe+HtMD8YEp1EPVnj1wN+htx5bQxTnro6WpCZ6na231Nl6wGFpHGHaXyvh0BCjTweXx7dhiLHlRpHaCrx9VV573oswqcgUHxGwI7GrUvRJNDFm8z2Qcmg2H4/PlaB/ydH0Kz0TdZ5TTJaKwctINRjfdX+hX9/+IQReMFMcH2aOtLs8KGvsMsZgL/0Ya9PVg4+bHUgPuL0W7n+buNtrDI9WetzWRTx7rucWyZ9GnBcQF8uMTQleRzP2IsvbmPVjiXfo3Z8Ik9FlZu/w48AS2YsFk/0wOV0OPtFSg9CIzNimxLDl/MB7SY5Ddp96U5HdJTA3K85aTD7A34qIs8nFOfbYT5Rw/sQH6kvWRwrXKrJ7YV2BJY2+AY32mkZPoVbwCrLH6JPMSpibeBurnyvYhCefycJZcBOyoluChxT29OVd/tKIvrxHX/J+byV+3y5Q3XLVZx0DVJCmNYfGNBOThk2ARcrGLmKrtMysBvs50lFiJVAzb5BmXodmXrRXN/MtHqvh1DJtJQVrmmAC28XCKlZtsOrcdFI7AdNNbkwBg2kuL4EFnzKBfyboUZsHWGF349eP6ENDzIsZ2n2YJXl34hfAo3ZE1AZL00IO0hsn6COeWAYtTtInKxKrn8mx58pv13IOJB/Icv63f2g/KT1bFyv9e9azwTUVDfZDVWqww9e5FFzZWg9PJY6REtfrEtebEgOiJMXFtKV0md5SZoIuM0iVAXWrr9AWT37LbujICxfTRqMLh/JIrI38MGWgmSD7itYaXlrCWnzz6yotIGk+VisFCpvjDPOm7Mj952nmvfeTDdT57yGxFx50t0sT8Rz9Z3R8aM1QoRXuU2IxATFJqTBAo/4OIB2FDS66Kdv+J85lASHK2ktAOa6uYMZGkxOUmPA/vcEYMrUB8ApQ6UQWk1A0Q9d06paIy+F7zgEMRF3zV5xU+3k9wZzXu7uD64APH56ozukL0elkc05/uV5t5PpngP8lRfOTlfHsWefLn0XyZ4H8KZE/s+QPGymqwLjq+YGxn/yBdb9F1BkiWgX5z3DSZ17Yx+qT/wqc/FfAenKC7vWKlGK4ZspaIZL6S5wBC0Z66ICTf19ZncSqCvKX4eS/nE6nTRXtXxU+k5Lb5g3hmU8WA8a/V6rltao4ewEtnkW0eOYzXXe90XygSq+iJPgtCyeVXUSndeZElNLNpa6DtWVvM/5J8JciTQFX2tNKNWVJuCNRf4JfRJO3gBahtgicn2N/Dv11OgEV5C/xhFKZTYL2smccfRH3vMdt0lrtdRt4lq2mFmDBEhVIJU5tH/0RM4i5Ki17buE=
*/