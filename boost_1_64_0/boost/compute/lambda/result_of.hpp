//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP

#include <boost/mpl/vector.hpp>
#include <boost/proto/proto.hpp>

#include <boost/compute/type_traits/common_type.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// meta-function returning the result type of a lambda expression
template<class Expr,
         class Args = void,
         class Tags = typename proto::tag_of<Expr>::type>
struct result_of
{
};

// terminals
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::terminal>
{
    typedef typename proto::result_of::value<Expr>::type type;
};

// binary operators
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(tag) \
    template<class Expr, class Args> \
    struct result_of<Expr, Args, tag> \
    { \
        typedef typename proto::result_of::child_c<Expr, 0>::type left; \
        typedef typename proto::result_of::child_c<Expr, 1>::type right; \
        \
        typedef typename boost::common_type< \
            typename ::boost::compute::lambda::result_of< \
                         left, \
                         Args, \
                         typename proto::tag_of<left>::type>::type, \
            typename ::boost::compute::lambda::result_of< \
                         right, \
                         Args, \
                         typename proto::tag_of<right>::type>::type \
         >::type type; \
    };

BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::plus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::minus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::multiplies)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::divides)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::modulus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_or)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_xor)

// comparision operators
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(tag) \
    template<class Expr, class Args> \
    struct result_of<Expr, Args, tag> \
    { \
        typedef bool type; \
    };

BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::less)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::greater)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::less_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::greater_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::not_equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::logical_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::logical_or)

// assignment operator
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::assign>
{
    typedef typename proto::result_of::child_c<Expr, 0>::type left;
    typedef typename proto::result_of::child_c<Expr, 1>::type right;

    typedef typename ::boost::compute::lambda::result_of<
        right, Args, typename proto::tag_of<right>::type
    >::type type;
};

// functions
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::function>
{
    typedef typename proto::result_of::child_c<Expr, 0>::type func_expr;
    typedef typename proto::result_of::value<func_expr>::type func;

    typedef typename func::template lambda_result<Expr, Args>::type type;
};

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP

/* result_of.hpp
etQ+otxE2m8G3SFlcJbwWMomMWVALBIs+/ZewhexgjdJxavSMb5++7Vmfd/T19RB3mCfT68AdRbniZKWbebLQp4f9u/3gn6qYxG1edEwN7VsJmhXhNOVU7BBHvN4Y8VkE8WqSiTrG2iySuvu0V3l6o8bctbbKpaPBbElW8Ujk8Rgd9vIXl9zldAZradYcbUrecffEv6EpVXVRqUea+N5NtlFhwf5ffe6duwQ/oq1slRZnqdD/uFDRMOPMffLaVnaxEVSqZK5z+GSfijm28QnsNU4PryhTkx0o1qC0bb+jRP9l13Ow+/jn6ncJMlExbkCu306t73V8W0grsej6fc8jfNUKlH2uYAvTaZmkiIp8Gz8zbuvXzxD69xF8+7LLKb0YZihZ0/W9E3Q/Ydh2N/9Q//5UP8uzADxMKzu2vZwejepF8WobsQt55jDfbJ3N/fB4d4bPjV4X7EAHP2Q+nHcDwLj7WNtQZD3gDsPMfAm8n147hLi7P1Y55qEvfXVuwLnfzRBv3Z30I3W4pCHnL/38OjOcc63sYh7DeluP4cy0vsSjO098l7hfkO6bfC0r8f3KQYjgHuv+4/Qd5zF8dwa6bszDxhiba+smfz33lsX4MY+/n39f/XAIc51AcraehAwU2sXs1IBw57+wEM0LrDduD09zge/NZhbsN3sPxS4UdsN/CYfZnDz/Zq+DfrQttM+HLRRH0HQnND7dfkPLc18lzx/9PUF8m2JecWVqFKGsYGHy/Ct5UNoTqCsTdo6yxj1gaX+PPuURxZSVY1s2Wwfa/wsjPMK5XmXz9OwotU1LFLueLTHC1i8ODs+T6WrlEvRZoJ5FqAwDo7296RxcGoVNyI3X1ljxA7im/hYnrG2zUWSNy2baZrzvBj6bMD3i9YvS9q0aKKCeSrYsUzxJpr2Q50KHqsmYjhJmu6zXODRihHEVMwTkYm84zFOKZCDvFKOBzEi2si8UUg102irkFfK56uZEFw2eR4x31e6861AbE+fp9Q6lMRRW6ds78LU9SHdQ6VB3ZJCFFmZNGx7ZxZuebXTW1q387RubWycLbS++7duXd0Qz5DyqDZLIlFV2DpZ5xPH0+nQHT7PclpUMmpqcAR6PcNi/tQqT6oyY9THlvJ8hvIkMo1LlWSQ4BwtaEwon6dhVZXGSqYVeLiJjBjMn+uUJxZ5Fau6YsSyH/DcoP3VKC5S2Sokxnoj9LPnuUn1szEODXHBex4vtg90+mGEJ+ei5Qlv+rp5cxs+jT5Pa+JitbWUBeu3u2cG+/Un+TycszyVdVE1PpOzPNI4HSzg0x1XZHXWsvDBiuPr5sJZn69klcxEzcuuK+BK2cer8PENS2IueVYg55k7iQTrL+XJ4pqnKq07HuKDiVgVjgexD3melnWTs+AxjeXy1tMP+HzPzvOEpzLPmNllZK5aZ7q2f4a23aQhi5LYYn2VXoWPLsVzKXLVioaZ46Z1oQnG8vfBmPA0TuNYZm69Dpc08N0M2h7LStb6G8mC73uoo4cfTnQ0bnlVcKs6zqUr6/1uEUfZ5ylZEYlIr4eKdVuqyK2FiKPs41fqomh4VkaY1gM/weUZHt/6Ukb6G+ItT2Ev+HGnHk51rY6qOuUFI+9j3NkD90lEXsSapm1UXSZ2cXciBU7XXu4Dn6/VfReLMmoYNQIGeR/f4fM8u4iiMk7Tgs1e8Tnd6bDvJlhRyrSO4oi5V3sU+xEf+xwuZJS3bWOwWC8wHlfp+OVNEYvUtBtv12Z4+EGTstsoK+KiUsxk8tQf8yDuStCXufFzicuSBQ/rur7s8tYdv4/hozuyLm+dwXxIY645DHZGDuDn2ts54jDYIAODcm50GHztAUI577qvw+A=
*/