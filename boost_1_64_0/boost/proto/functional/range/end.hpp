///////////////////////////////////////////////////////////////////////////////
/// \file end.hpp
/// Proto callables for boost::end()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012

#include <boost/range/end.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::end()
    struct end
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::end(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::end(rng);
        }
    };

}}}

#endif

/* end.hpp
Z3fF5OqFHiwd/XfIihqE7CK+0VqbmKTanPZwf+29NPPkfhBV4WSiruw+zeiYb1ii1v4058+B4V4wOFyCzjtFPncBfXljreQGBYcqfXBCMMygvvjPzFJLTR6ains1HeKmKNyKCQU4Yvf7rL5toKHpsxEFA5efKLeVEBvix4u86WUD0gzLZCh4mCrM557ldKLPyAygtz5AUY4g+4g3/rW5ho685tCeuVAyBlL9j/CLONrj7XMgYrBP5kP3ulGV1iPnyDB+uK5sT3yKmT8vg6UdykQGaF5yEXdaOVF3F6Xad3L6QH3G2CZYH9PqD620AjhRDtygCy7HO9xrdX8gOndvDpWVGf5Qge4JiKBHN4azLIzAew0fRGrTZwSuRTWtttqQ79uR1cIwjwMDDHvzO6ydESt29MRXdZNZD30Q1R4WBhKLnXlbCq4PUoXQ8ZftSI0OAhXnWx/FlDVZCA6Tiu3C/qvUg1arw5SxJI88nI0exJ5W524H8+aQPnByVsPy6rDjV0No4vyqb9fdlMJ0dv+DlmWOgOpMvJiru28/8en8kl4YbvMGn6tyRJGivg==
*/