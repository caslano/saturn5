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
BeySiZwt0R0zkBlT6OfdblyVOZ6km6hYd+NtKLzMrL461RzZrNgGVGHAKKg0d4H2u7BSiUhpxBDhZFEtc6Ezd0cLHcqkq0rQPM8bODQVXNdH4BA00XJpJxTIXhgatJKavK0ztdrbiGFtgNKqlOgOw4L7EoWBd6GSCS/tfhuIrZcmyjbkd6Rsxz0BJZEVtPoBjIIWLJkW2oUPo/DUPw/hQ38260/COfhvoD+ZN3hno8lrrA2BXkvgV0XJNbIoQayKXPBkz/kPVbrjhacwOJ+NR5M3fjQYzkJ6gUfQOnoIAS+wsI+etKCViyVlHp56jx97PZygbxFnehNdcCNkqijRWE8aIYNTmPTfDZ3buItDwO02uOE4gJiXRqQiZpjyOGNCWttgPvGnwShwfhIyzquEwwl5q0sve+lY3Fjh/C0SbVqCgwyrIsfiuEXAdf5D/JjBCnuXBbXM6FQHB5ZY0Tm23F4Pg8FsNA1H/sSZMkwSg0IJaah8UDFw/9sg922dokDv57mNAJar5lYY1hxfHLYlYDLSm8oTQpfVClsJVWQu5CesLtSK0bDGUgGLzZaqqiN6I5qOJY3q0LpaCXlhe0PGElikIwqKPw2vY9J+1FmkU+CSpJ6gdHjdaEr+V8W1gTXTzoolvO4UDceSF6pE
*/