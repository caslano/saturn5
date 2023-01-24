
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/this_count.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/return_count.hpp>

// PUBLIC //

// Validate params after they have been parsed.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits \
    ))

#endif // #include guard


/* validate.hpp
Fh1uSq675gRI3cy8FLT2KUzWXPUf0mEyIuwP8F03u7Ta5vhimAitaJpSUhNSkv0n0M+UlNTLLnv3P06rAwNvTqv+RImvoGbEhMyTo9ny4a560BfyaABU6JRQV5skSUhdHN0X54m+YSKI2SnqW79eQdtHMn5fIiuwSB2YkwgzGyQbHl1d/U53dr6Srk2AafPrtPPQwuJpMw4MLxZkjlptRp9c0mRvbW9V73qLhSAWF+Ffx3TnnZ6FE8+eF9OdN+3CmORaX1qZZkzEIFBewe3iejpezk+U4Sf4GyhSOc9WeCktvWL5I7dsb3qOSbMcJRpK4sMPAr9+CZrS4uRIfQlakCHydVwrwUaabROz/VqjpVYTt9+PeIhzm5RsY2fL59B0AkkHJuYP+tfWG+fPQQ3HH7O6csD5XV05TU3canZ2oJjTVAdHRDHMHXtEYxuXpmd3t2z7aY/u+7OLQjjb6ZD7/murZA5W1Ro+HYPVpUV3+k72g2ioy3f8xadL0HRLcGhocU5MTMzjo6daelklsDA2mSY0dLGN/m9Szb/WUZjOf5lTz09u9JV0/XYzDm2rLt2B3hdO3Per/vyThwIcX9VXw8mbRI2SRv4J6jsQEiyuzSvNr8vPr6//LCIishZXLTebvLuPdLoK/q5iePyW8n3gapAEEuKEhRzvSSZdKt7+gZPz2wZnwPF1c4Xc7eAcIiOxcVJI/WL/QU9h/8u7
*/