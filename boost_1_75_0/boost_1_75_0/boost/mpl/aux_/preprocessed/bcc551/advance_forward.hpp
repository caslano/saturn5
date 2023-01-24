
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
oO3leESTc4fqNnm9qK0EuvaFbRhUPl14uOiX+nPy7epf6riRw4a+rI2MBOQs2+YZzc5z71GghHrGLvSWz7AqQjxPYIsLL+ER4GooBKbMYoX1cZFdZL9jvRtNJu9zvC0Wln2lb5poohAwHzdb++QvbsJ8JoTnX5byYeCdV6wVFRqtuIh50ToEr4/RDWdL1yCdxNUMEJq0wS05P1EwR+phhlzgWSeAo9h75ktt/D0vfpYFpCAdZi6uI0ZuX6Zh+RqrGHlk7cfzDDgKwchX2GzLUvdrDPoasOA8kOrhpjCVXEjGrRHLEbRaxthqpTX6wP3b3XbP5+txGyh1Lh/TGYV4wbfdKfkHLC9jgQGI7fjENCb7iLxKglLiJoJCATOyPW5AydjSBaehXde8/GhUmOdG97ugWTmzkG3bC7lBykd62ngKAToK9JlhCpyrONNzbuBbktOr/M/ukUjsIwqc1X+MRNo53eQEvnz2TI70fz1mGP7jTwrv32JJRwdLGxf7fw1D4npSQrREufT1CCei7Cbidu44koiX49gM9CdSKQVamggt1ofjKNoVomx36z1YVTtW1Cyt7FnK50licQNZo+bbvl42MC99tZZK5g4kzUz4EvglMExWXwGXPlbRsyklxH9mjnsi4Ly7U3+ssrn49kHh3hsMtDxfg3ituV6IHJz3XLYPAfwOx34C5mOasj4dThnis338NP82akHc+kMv
*/