/// @file
// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_MAKE_DEFAULT_HPP
#define BOOST_MAKE_DEFAULT_HPP

namespace boost
{
    /// @details A considerable number of libraries require an instance of a class
    /// provided (storage created and initialized). For example,
    /// @code
    ///    Type result;
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// In generic code that results in the Default Constructibility requirement imposed
    /// on every type 'Type' to be used with the respective code. Inevitably, that requirement
    /// a) either excludes all the classes that for various reasons do not meet that requirement or
    /// b) imposes certain (not necessarily desirable) design/implementation onto respective classes.
    ///
    /// Deployment of boost::make_default() eliminates the Default Constructibility requirement with
    /// @code
    ///    Type result = boost::make_default<Type>();
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// Classes with no default constructor can now be included via a boost::make_default() specialization:
    /// @code
    /// namespace boost
    /// {
    ///     template<> inline Type make_default<Type>() { return Type(parameters); }
    /// }
    /// @endcode

    template<typename T> T make_default() { return T(); }
}

#endif // BOOST_MAKE_DEFAULT_HPP

/* make_default.hpp
qcd21K9P0uznC0DH7BZh7ACse/XSxwQEUXAZyQEKdE6nQ9r2Jtve+hQwUzS9eOsFhk05gMlzEl5ozhg3gwnbqUOGtwvRfNiaT9qDuUwTwWWWjUG+Md1s+7z28YiLCF7hey5g2ZoYNT4KKQLu6pEU8NqWEArr43NCjIkY08I8pM+yxSr8tyV604BbbwM3ppNxO7BAZqghBTOkDqHzHclC0qLfx6ZnG+T1llilGP/C+Xfq4PxiNISk2VD8gORt1z67WPUNwljOd3Hevx2QEFko72AqXqB4F+qDILZRL81/qu/8YrwhWj1uE0wmFt4JGbtQGaIud6IyLG87Z9p19U9oKUV4n+8YtUIxQNVJFSViKTRhNSGhULD1pud8qeljt+cIAUUThXImNQnSAv3TpYvdQFQF5iVqrQl428hjYRCR0CGKbBTwULrE+IrzV2zt2+xydyac/vV4ixaNpZpk+pCxMwQEqJwEA4TVT/jERPcOopFMG69r6vkhzDdQGmFjXZi1ez6KkBRMw8JEPuETnUUAU8EIwgBj6qRiVAWwSEh0cuVVWH05pN5SFkbtRDdAmbVizyI2kTdDkWXoiRC1A+FwQ11+Q/vBmxrr4Y2QitgdO6KH+JguevjbYLw+ZrbRZWi+QgvV8mfEvB3heUJm+A67PKQ634zwidxSZkX2uFd/8E+MiHtYhBMxNuybxVhMWfN4cbPYU/XGMt24vVw3FmkBt29RO/588mCl21fRjD9X1OLP1U/hz43fxp+5j+jGK+JgwJsCH+5LANzJz8nPyc/Jz8nPyc/Jz8nPyU+3+3upI8wVwoE1Mbm4Ifbb2xHovsa14bkjt/516AIuUljj/2HTA6t/fuvvxFLFNSWdj71z95E7J+GXR1tz6OL3zJ745pXfx68ibY1tXHIj7TWWZYtfvkSgNn6VJiKx8atMy3oflm73/yqwzgeVhVC3sRjtC1KKUXIcJRELME58ceT6jjO1i5LWd2S1CqfnD9bviuUm1stY3Sy/2r+jRpO2vdG6GRlZn/o+bvQkvwuHW2uasCiaRLC+pRTSxK4dCwNi295QyeSFWNnyjdu4smXqQqyy4OZRsVvTl7WUO6x4fixvEatb8kXpD9XMWMoXHtp/vI9rW4DX6eS1epi1ouXum+0VLZpaywUtXixoEacJ+BwSyvPwfZzDsT5Y/H4eQLCUaS/kn0seChZfHts8/1QHx+Juz6DXIqOwBGHEW/w3UnGPvMJzkUK/6kUVLgN5XFRRQBfKRRUe/Bt/UcVo+i0uqijCv0nVi7A7QcVYe02MxnHPD8aINTHTcwN1lutjVgy1NuFY+DxrJ2i8aS2OOWwujpkpjk7D6pVSc3HMn24Vi2NKcTYNK+JJc5TbMHWhvTJmn7kyZmf1wcvlypiYVsJY8NgKJBFBqfCUXLkQd5gxEnJZTDUzds5eeILXxPS4HuYgJXKHy14PI08UG3TNh010yIEsd5mRSDa2Yt8Zrm6JhHB0heeDRx4c5RDrWrj2wT0Sy2aI3p+JYS8Gso9Rvvj5OH8+x4cAiPQSBPH7Yd5+WngGgvj/gPj/hDkxYoZKzQLXPm69brcPwVBepTHZ5/bc4Kk0bhiHtS+A4YLSgHOyN2BMw/dmzd+IxREt+fPcy5vdns2B6quKHasOURlVGtOKA6vaqXtAIxRYdYhKSWlg8b9NDpSDgVVHqIyCGPvnB4w/olry1a3RJg8yq53nvosLKJa/yOxd9J0FlZfxfU9BwHhR3RLdUKDgBBamjPC1PRj382BRJBynoBEElfboRhz2tpmMBeCACCqvYJv3gPG2epROQqMpumWIiuKKjJAa6VqQPIh6K0B6FxIH6QFH4vFBo0lZBxk=
*/