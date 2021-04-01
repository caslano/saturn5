#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/template_arity_helper.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/template_arity_helper.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // template_arity_helper.hpp
    // Overloads of template_arity_helper, used by the template_arity\<\> class template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/template_arity_helper.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<
        template<BOOST_PP_ENUM_PARAMS(N, typename P)> class F
      , BOOST_PP_ENUM_PARAMS(N, typename T)
    >
    sized_type<BOOST_PP_INC(N)>::type
    template_arity_helper(F<BOOST_PP_ENUM_PARAMS(N, T)> **, mpl::int_<N> *);

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* template_arity_helper.hpp
vCSx0D2FtRNZQPzBE+4aSH/I13OQifOFm0oAbPFf7+6haJyIWp/q8RMWVDSFUMllxxmUesXqICmhb0FywHHhD4FphDAVdgqIw1sV1ZlDZa11Vz0cxTwLiD3uXbaNF6J3l5dt14HAW73nGatWg+2tN9Abk0lRcPc+4n2KdHw4Ijp0aWmxBN3EPEfVZztN7bhthRURzfXqeH+RBmQp2HhgqKGZitqcnu9D6dCDhYpRU8qP0GRuoSnSjyJEjZcshEZi/3xNrZ+Dr+buewmC0IFgLHb8W+JcphyG9TbbB58/Yu0rm9HiHIMr8ApORaCibVWljgv9rn3zhVeHRNANBWy7xZl/SeBEnT5KbPlrzP54UFV3iLG1G4LzzX5xmjAyIZDclXud5fpAvz4b+D2bbsurMxEDYSc8JuQ5LK1EmU9ZFbDyZ5dyVkIsy1NucfNSaGad7bj5k6WBt50898bS9o+ZxpLIN8cVx9qXaTW5u2Qt0bhJLyYt/5pcABo+0HBFKofrHitejaihe5XcuazejmpiECafQqws7I3s1N4+WDCeY476cmB+mcPLs0fZqw==
*/