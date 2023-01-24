
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: pp-list of result types (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard


/* decl_returns.hpp
hVrGuiuMU9fRgdltz7ChDphfXa70Gj3nCx18DZII2f1LZ7tPDdvG38pBkYBXvH2ByV0U7r7EL4OdbgaJfl3TY7Dc98LWo/tiuTDc+ZSS8yO/fI2WOBhMUD4E1q1yxfYM078uhr25CKL65ld1vt97jmg/fu33rdUFCTK5j/0U1jpt/pVE/eEff47KTqaspf7Pvkf0/7ZKM/vf5urOpk4ydi6mTmaGxqavwb7taTayN656zpBAKeevGP4YToH2Y16h9omjCXon6qOjSllsTA1DoqCW6u3PCqqUQm5txgCk9+E9b6hSNz8gYw5LTiiWTFJnVwhQAvbPVneo7yQVFXvBsIpyRX7kAITknAAYz01Fta/6TbXnueZ55w48zYCILYoGVI3T/K29E/mGt3XO+EO8+iJzXPbuWCJpS+ADtGrJpgllLy2+m8TOf9j5heOJlCJQ6QpIYdY9GTr5TTQ2kBz+BQHCe4B8K9gKY+CFEh1YgibFut+8wB+k5vkhvOAc5IpN+vu+88SHWGMSQEhA3f5QPAjpQXOeH7wQhicc5DxvPcAXwxMLgm2BfmAK0gEJgrxBb+OEhuEgKAfqIOs82JtOdE94CBLIb9o2s88DFcJtQTmMtYPghMjylgWxE17rrRbKIxuoPe9OdEx0TAyGpgX3+OnAJw7VguYAHsQICsuDwfkgPOqDhvJEAoThXigsuA4mP5JboA3j7SD+Ej3L
*/