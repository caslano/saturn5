///////////////////////////////////////////////////////////////////////////////
/// \file rbegin.hpp
/// Proto callables for boost::rbegin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012

#include <boost/range/rbegin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rbegin()
    struct rbegin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_reverse_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_reverse_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::rbegin(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rbegin(rng);
        }
    };

}}}

#endif

/* rbegin.hpp
73IhUDcDE0mDX3ux+Ue7AEzBQdvCcOwuwtmObsTqCLwyNuXwuNuXP/5bH/c5Cysp6le0+jf70fwKN+LH6Nj7a0Ru1wvI1EOyih/i8JH2ZRFmfyTdXdLgYx+pP+bn1zClbd3+6nBlxQu8zTt9NJ9tJQsxGPk2y3bXF7z+peFD/jmj7dZ+n/6bv4P+Z4zZ6sfr3R6C1TebL13Q3bBAL9rQ2pg72wZ/xyZyGq1gPGicvdxCCxaAyW1zyHoRbgUxwJ/UVLoS0L0KPQTtLpoC07h53/NZ6UF6/yLJ6zCSinGZnH3U+DNCbTHWDw6zn429kwuwS3LFywHxBp8GuX+/FUYQ8K6vQL0FE6nE8rynh8Wvvy04kqvN83e5NwWpipBDcWV2o8S6ITH0c0/9RUQCu2p+0b+zKCXk/ugYEQn67cLklCuWaIvv17dBuWUtiPhjoLH2x/tW4xAfKNZQDBmFDqQuLzLw5i2NfNYOgQoDpbOE05It/Tn16sAFL9WaO92rdx9uQgXaOE+Gp6XC8jVF/vJeXOqA4COZFyBCrnssnvnGVPbdk6oIup0A+WVv6Zz9FqmqIPrpt0/PpBnPW2Ra0N52W5IkDf0WTo5HPFnCCG5rgzd/ekM9o6ztgHPWV1/rjlyD0diN07FK1Kzq17B9+U9u9hBzu1HWxMLfZuVLQhQ3tqM0RFOjCdUWFa9Se5Y1gLb4pFJCsNdkicWLRB87
*/