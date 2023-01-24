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
vYOwbLMbSQqasGRGmrCLYPypS4dvocpP1kfVcSqHy/7Xh/7ScrUxRqKovsdjqg77o0hN/fhGCB9ufUH1ZryxdMfN5ffZfWg/CAlT9Z2bEb3gPjoWfMScgHlUBwdIXfC9utv8bqf/VX70zKzhW9zPFv6/f/bB0H/mgy9Hk1+x6GcFny/GldVGKbAAthr2j9kfmjQ2nQN+jnQz/E8PsOECHx6yDAmuLrBV1Z8UwGfh2ABF/rSBMb3XMxUdsxYaCBuqC76B3HdNwyv+ln6h8eG/+uMjtXvzCd19Ub+l8X/hQ3+4oE2re+97cb3PD2jbN8Pq9IOvh2j1b7e3O3vtnNUZbo20RDvjufqJxu1NlzTP1i1Nra0ty6hsalvXskcXWvYuampvXVSksqmjsOiAvrrzB4vu67xkyfrO0qLrW8abb2takfp2ZiDdmi1SGU1frX+6dCDXuqxIpZS7WV+VXpM60rh3+faBSwrHi02l1uIyKpuGR4p7dKm4d0XTytYVRSqbVhVWEPSRH6y4b+ShFbcV9xRuG1ix+ttrBkZb1xapjI4S5PUD61rPL1L535S9fWBU1ZkwfubMzeXmcrlcxsswGcfxMg7TMR3TcTpmx2zMDrMxG7Mxb8xGNvLGdJKGbExjGtM0G7Mxv4RFNqWRjVlkI0U2sMgiixgoskiREgSriDSiWLTaEr+KrrrIitW2tO9zPmbm3pDY/v44d865
*/