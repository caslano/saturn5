// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_TRAITS_DWA200347_HPP
# define ITERATOR_TRAITS_DWA200347_HPP

# include <boost/detail/workaround.hpp>

#include <iterator>

namespace boost {
namespace iterators {

// Macro for supporting old compilers, no longer needed but kept
// for backwards compatibility (it was documented).
#define BOOST_ITERATOR_CATEGORY iterator_category


template <class Iterator>
struct iterator_value
{
    typedef typename std::iterator_traits<Iterator>::value_type type;
};

template <class Iterator>
struct iterator_reference
{
    typedef typename std::iterator_traits<Iterator>::reference type;
};


template <class Iterator>
struct iterator_pointer
{
    typedef typename std::iterator_traits<Iterator>::pointer type;
};

template <class Iterator>
struct iterator_difference
{
    typedef typename std::iterator_traits<Iterator>::difference_type type;
};

template <class Iterator>
struct iterator_category
{
    typedef typename std::iterator_traits<Iterator>::iterator_category type;
};

} // namespace iterators

using iterators::iterator_value;
using iterators::iterator_reference;
using iterators::iterator_pointer;
using iterators::iterator_difference;
using iterators::iterator_category;

} // namespace boost

#endif // ITERATOR_TRAITS_DWA200347_HPP

/* iterator_traits.hpp
srZxtrKkX3sbZ8rDLau4nwnr6VAJV81zCUrjfrV2hTpurdj38Hgg/yOdg9L2qT1JpnrLwHOqtq/dKrZ9vMeVfEbfvkGDxbzSY2sb94doG4+eom0co+JDGv+AuaRJRntQIPYb3Wr4XnAD1if49lZR++p4n6+/J95pa7TRMj1dt8Wna08TeP+REtctns4oEXM90lHJh0piV5l2l4rf8xy2mbKHxw1id72Rp9lpk4dljaQ+lbC3i59w/V5yG/MUdkbbVZCbZ5T1AvET41jaYj3ntslKOcOYZpY7ZEG1y0MiUBejfO3yjFejykXVk0YZ4UK1yxUkvmS/fIgXuzJ+bXLsypBtr5abSPHT3K1syiSkETIpbS/XL6q2V64itsG9zlobnJVzyvmnlnZ5f0C7HNRWtwxsqyFznOf9tjwf4uQeIhtW+rfd+avsbfd2zvPeR325kfqy6D6LvszIOa2+fF3CLQmpLxGvXV9Sxx0X9zu1jtsHs1VfMi6rvqTu/UrcC3VcJ2G26kuJq+T6sui+kunLX9b468u3JVwi9WVLrS/rrVb23akvX9T68kfxP/2U+nLHGn99+TLCmPryTTHfe9b05ScS34tB+vJbsX+Q+rK+n770Pl+/s6IvT8h9bg7Sl4PXBuvL5+8L1pe/iN11p9SXlVf768vY1afXlxVWn15fblxt6kuWO/Xl/GjUxZgz05cLVgfry6Wrg/XlbatPry8LxU8zt7KWyf9tfTl0tb++vHSNv778CmbbmrUTzPwK3jm9WAHtHQdJXWfRl6OycrLGZ1p1ZRzYU8KcdF6wr4lhnKauLEgbbaypuULcj+MbaoxNPyK8VafpMYsfxb0F+jsJVp3I8LrORjKfzb3y+oufsmKXyHTPNeyqMC3jDbuqjD9D7CJLMK6h+hiyvvhfWhMZWuaQn2ehn7xnnV1WulRz5Hep64h7T/yzAGFn3G+RFYhKga1dZVnfJGG6um2sZ2cwzlD9QZb3U+KnsUVWGN7eH7TJhumfc0D4cmDou33ip05wG2oNrztj1vkrpv8J3v5yAQ7jyIaTbY6K9p8E3XoSifkZDg9DZ4XNTI5qENWjbHh02XI+udoC+4rU24F7dtz1gIqnOt35jmHozRXi3lTcU9iejB8j7hL3anEPEx3qS0thAtMy47uodJUSpK0kack/TVomiPs5IdNyvSUtcVV9aXlJ0hJWwrRcfpq09BH3eiHTcrUlLauYluiwGQ9GjZLElCgtjU+TllRxrx0yLa0saYlO1Gm52Z4W+70qneZeVSz3mqzvNcZ3q9PeKxH8SmT8UMh7fXd/8b3+9XEa6CGOvUSGGJOJtozJcKyGc6SoG2gfp+3h2bBPZHsc76vbbKs/ut+uXzOrO/IbxHHHgbhuR/iU9Rb9mpOhhvRs+tG+HnV9SH1o1Z/wb9eHNv1p9c+8sPU56N+q/+z6UvsPta76anGv7pRDjrLNwS8XhV08ft1G/HRymuBfef+j/GxNgt4rwZhrAuXIJjORIWQmOoTMxISQmTiLzJgysq2mI7/HICC1wDXgEvhfZJMRnDOdNTF033arhCl089wYm8wwTvv+U1XADeJ+rzsQq6ltMoTw9vc1lsdmcb/VXeJ8ZR/TNWXE4fsiojB15W7xEx8sY8H3x298Ztao4nW+X2yQ/lRIfVP5QZ7lxHXAkU5Obk56hrjfrXSfhC/vt7dvbbELU+mR/r83LN8BneL+qNTDRrCQcsYerHTb4xdmjHTKKnJ/4g4S9136PbK4zzcit6AgN9s8N+s98VtF3hfGQq/srOHt40TPmDNjS3SVGfOiwxNMPbrF1/85w/2uppVwT1vzXZTyTzuWKf1u02uRJa/53ko75iE=
*/