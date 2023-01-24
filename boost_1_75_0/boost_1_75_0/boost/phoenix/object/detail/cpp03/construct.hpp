
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/construct.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                            \
    <boost/phoenix/object/detail/cpp03/construct.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::construct<detail::target<T>, BOOST_PHOENIX_A>::type const
    construct(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                construct<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* construct.hpp
cpYatebX37TB14Q2OU1sLRh248C0uXdEbJO1PmQdZG8PL1wFfLiZWYjTC+DDSdYhwKLrS0VtLC7cWVy4iQvB0HHDYRcRmtmX1qXhpk8Up80wrC0DuRm+YkiXcrMPsybdO5Q/GzfdtBm1NQ9RMzSKMeimmTY1Xc0GLxYjRtyiueWmYus9mRsncoy1xVlzzEbDrB30jUMQa+zDvc3NQ52dQG6GWFsA1nVFKY1dYA0EEGPWDXDpB/dllD/MGs0mbUS4W0TLATrHOqglhSVx7gEiiRJ1eu2FVVzlxI3bYbTaKR5oh9Fqp6LZp1TUNuUurXjp03fT6lDIroGsn0DWTi+CQHqG3LiPhUWYs0tOQgJg7Q/sOjGkgWhSd5Z1ZY6wNBObdpMo3+4c6/JmQQlgTauldJw1mzLJOoXT3tnEacNzP4aBwwNPMienzWiKpkbc1AoyxhJRcrKxuWimsWgWIr0FxtwjkVFa+bBpI9aPHfVNgCEHv3AIsLeD13y0sgxzdclJ7E7WIOXGSVo3sK4t7SprUWLGFIbOeBDg9ieJ4yF5ABM3GpfRTTuO6IRC04504/LkjqKZqGF25IQlS2ITDypJ8zMVY81aLUJsTs410NaVxPqFgWmYizNkbYcrKpZhLq45iYmQtZ1VQWJoQ0n3sa7oul1/NNYcuMWsm2Ha3gzWtJIadObRtHYYvboCcIeQRh1GrBgiBl9Ux5Ptxo24
*/