// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP
# define BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP
# include <boost/preprocessor/seq/for_each_i.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/cat.hpp>
#endif // BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP

// BOOST_concept(SomeName, (p1)(p2)...(pN))
//
// Expands to "template <class p1, class p2, ...class pN> struct SomeName"
//
// Also defines an equivalent SomeNameConcept for backward compatibility.
// Maybe in the next release we can kill off the "Concept" suffix for good.
# define BOOST_concept(name, params)                                            \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct name; /* forward declaration */                                      \
                                                                                \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct BOOST_PP_CAT(name,Concept)                                           \
      : name< BOOST_PP_SEQ_ENUM(params) >                                       \
    {                                                                           \
    };                                                                          \
                                                                                \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct name                                                                
    
// Helper for BOOST_concept, above.
# define BOOST_CONCEPT_typename(r, ignored, index, t) \
    BOOST_PP_COMMA_IF(index) typename t


/* concept_def.hpp
gvLALWIILzp8jgxNkui+dOJGzlfXLmumRHHKpfPhnxAKMe9KnBZibnT0Gwf4Pa/w91FDs53uXDgcBNF0spE7PMiXpmKf6BpZ8f2HPn/ByF4CbMGpqkHArgdLDW3r08pnQgjIYLl3SoMrLNiivyN+oY2PGttj893LYfEfXOrTqHf6ffC2vP+LWZ1u+SOH17IX/H+1dPxokIS7qVH9ewx96cSJm8vTfhKITCwE4vQz5lFpEgNWMvM7fjVUHzkzxnv5ZIbCP3bv8DCami9w/qjPKsDFk7M5560sQj4wGq0KK1s3G8ro+ZCUYoLdNbaNYjcuf8TBfTHzDurLDQNvt2hLjm8pigD8IrAVLnJxtSvLN94B369nZ+enRjMEnU/WM04CEAUVcjblD7pNP0u0Qutv4sL8Oz4jwRCv/evMZrd4fG9XOFJ0RuqGP9Y/epW+7vEQ3OM7LKDDodLYcn92WLxbiIRK6ZOhjLgWb+Zo+6RHZYfokKqHwDJtFjd6SD1bquPEbuJmpPnhaRNNoLsqdPcoJ1ULc/sv4Igf2yuWmxmQkpKZbTaV5a6Yl6C+OA==
*/