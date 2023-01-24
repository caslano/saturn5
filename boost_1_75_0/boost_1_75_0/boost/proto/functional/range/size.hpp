///////////////////////////////////////////////////////////////////////////////
/// \file size.hpp
/// Proto callables for boost::size()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012

#include <boost/range/size.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::size()
    struct size
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_size<Rng>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_size<Rng>
        {};

        template<typename Rng>
        typename boost::range_size<Rng>::type operator()(Rng const &rng) const
        {
            return boost::size(rng);
        }
    };

}}}

#endif

/* size.hpp
ie0LVoYWZrV9wpMq4Kx1YhWrPrRDtkUXbQuklaFLa1XzzdUJdo6+LBUrNGiX4RZUUK/hqb8d11ZP3Mk1nP9GjGu4QHvDB+QYTt4mVfUelLOpllamZHvaxro0aMSbYh1e0uNC3AuPyzz4NYjULmOJ/0W5H7YJrCr/i7JPrB2BqMeH7iaVaRqG4PynK6z9Xb6jVnK+TXUS9Eki/Itm3HD974ZMU5PpNJxoZujwKk9FTkSfXKspg50X0S+xnK5f/iPds5/tdtzxH68qAtgP+YHZSYdVtIbVGrdQ/1N/Tn0Ia+wBo3sz5gNRlWpGke1XkNk0AM9eiOFzEq7pbKS0PcEm1+szvQZ7k6DXT8pf8Nq1BxhfiioUEsCsSZB+L55V0JUdK5vSgwO19itjPR4mF/N0dKuE+QR0dzOzStiXorIS6u0rv28ygLyOj40FF3y1/gBO8cFSXqllCFic6f1lceMLIZTcIJhdLbtLI5TQDkl7GYp/LuHWY/D6dm6mYZrdu7okjLMn6e3sk4ewm+zG27wvKyUo9fk/5OIASUNyJEe0CBLEy91bLziMYX/uwhiGn7DVryCgTUdCtqQm64n39zGIDLAMT0oeQD+6+yXYMSyqCRkPmJpCdATXwX4BivO/77Von5O1TCbMAZuQn454hZk0Q+vEfhdkCD0sLqTkFRykr5NdkGxiZDZg1pA3EHd6stdbtJ7x6I0kzmvGdlio
*/