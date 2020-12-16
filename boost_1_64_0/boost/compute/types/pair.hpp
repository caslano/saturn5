//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_PAIR_HPP
#define BOOST_COMPUTE_TYPES_PAIR_HPP

#include <string>
#include <utility>

#include <boost/compute/functional/get.hpp>
#include <boost/compute/type_traits/type_definition.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta_kernel operator for std::pair literals
template<class T1, class T2>
inline meta_kernel&
operator<<(meta_kernel &kernel, const std::pair<T1, T2> &x)
{
    kernel << "(" << type_name<std::pair<T1, T2> >() << ")"
           << "{" << kernel.make_lit(x.first) << ", "
                  << kernel.make_lit(x.second) << "}";

    return kernel;
}

// inject_type() specialization for std::pair
template<class T1, class T2>
struct inject_type_impl<std::pair<T1, T2> >
{
    void operator()(meta_kernel &kernel)
    {
        typedef std::pair<T1, T2> pair_type;

        kernel.inject_type<T1>();
        kernel.inject_type<T2>();

        kernel.add_type_declaration<pair_type>(type_definition<pair_type>());
    }
};

// get<N>() result type specialization for std::pair<>
template<class T1, class T2>
struct get_result_type<0, std::pair<T1, T2> >
{
    typedef T1 type;
};

template<class T1, class T2>
struct get_result_type<1, std::pair<T1, T2> >
{
    typedef T2 type;
};

// get<N>() specialization for std::pair<>
template<size_t N, class Arg, class T1, class T2>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_get<N, Arg, std::pair<T1, T2> > &expr)
{
    kernel.inject_type<std::pair<T1, T2> >();

    return kernel << expr.m_arg << (N == 0 ? ".first" : ".second");
}

} // end detail namespace

namespace detail {

// type_name() specialization for std::pair
template<class T1, class T2>
struct type_name_trait<std::pair<T1, T2> >
{
    static const char* value()
    {
        static std::string name =
            std::string("_pair_") +
            type_name<T1>() + "_" + type_name<T2>() +
            "_t";

        return name.c_str();
    }
};

// type_definition() specialization for std::pair
template<class T1, class T2>
struct type_definition_trait<std::pair<T1, T2> >
{
    static std::string value()
    {
        typedef std::pair<T1, T2> pair_type;

        std::stringstream declaration;
        declaration << "typedef struct {\n"
                    << "    " << type_name<T1>() << " first;\n"
                    << "    " << type_name<T2>() << " second;\n"
                    << "} " << type_name<pair_type>() << ";\n";

        return declaration.str();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_PAIR_HPP

/* pair.hpp
y/ldCxD/nnNdpGqjAsuqKd6Fwcq7n3NOIE4LGRgzwAFT5XwkSicjXtXWieBwGT1lZO8zBa8K2lpaFbx94IH/K8o0tFIoytWY99hRmf6qKFPeBMm1QW2pqxCwOuNe64eYy5SWxtmmrEsopIx7R8TlREjBrXcUc8Es3t+FuIo01FNdSwNpXn0KX9lbS8sh7f6FYgyBuJLUTHlvtBq/AGAZuLuFXS8ED8bXBRc1CxhDFHZdU/lGUjXmzuxCe0JcSmpOveZ1/s7k6aXQnhCPkdrVNH0GRrzHFn6p4DFbOWfyasUtH9pS0R68bERtGeLhkp1xr/WjYv7WOsGDo5iMkgvcOxZcKUPdSqUxF6cZzutHXEYaQVvBhQVuPHkgSzLYDIjHiarTuk6giAepxXm9WHCDDrW1RiMupBZzn1fktaZeMt1KzJ3fft+GuIp43zZCeYG5uJDhO1dwJffcea0wd37b/wbiCiKE061Tsy8xn25RBma+dleUFVeG19ZSxIW3Bt9FdK0f429VW9eiNhrqlq0crF6ka/EiDGR8G87GKPjW6IZqLcZ8yDbiG8TXxLfGmhDCwO+cVPpm4fQD/2LBF5ZVla3ghWrX6VPm8eGOesSXpPaqqZoA+X/k+gUVo+lyNoHxJeJyopR0nDqo7zlVRmBtA3EZabmWjRY15o7fqa8UNpm1yjLnMW8f2YS9XEVevRW2ajhKr91+SmY2O8f/J3g+uDG1aUU1UOXe3s4esPJ9yj/B9VMJ4VigOuv7HU4nFuIUKpOj+llCfEks8zQ0Qsz4sd8IbJzmgLiMhEpQrXld9DGACPGVBc+KQIWSBW8feOB3EI8TL721wZsxD/wdAb+DuIIIo9tK1H7UxwCrM+5HC7vc1rVoqBn3E+TI7ucLu77l3ttWzuE+toxduIy4lgTacEubZn4fA6xvwxzZT3HdNq7Vijd83M8A7myPYMFtDdWUuTF3f8w9ibiK1LVSlTV+LpfhthEQl5LGV9oZ9OGH9OZrmRcRj5FG0UgVYcQr+hnPK+ylb7aVLLcHeUTfMcQThHEnbMDfe1y0M+5Hi7IN1NhAGZ/HLfsZny/sasuEa0VhFyUZ8nq5KKM6VNIaH8r+Qvne/QnxOJHc2KYVvORBajObJ36GbbrkxKUtbI7f9XsiniRNa9pasLn9hLJuCOIqErSmvuYMc3EBQ7xJYbfVTRuoQXbLAoZzgBDXEBuqwJq6GX+rUbK34Ryggh9UdyXQXP5+xof+UZl2S4VxMhTf2sx4dpZCWU8+tFR4V34vy3r6EeJxUrfUNKqqEQ+3DbB57OfYZi1Fq6hFNvOcwjcP8apo01aaZt/oRzZuB45DmQ3f4NxFxG+Jto7Vtq2O4Gd9k2wvfJEGFnQjaws6GLdiY79bIYQ0IL+D+JS4uqpaHXjixxm17jwCnraLTGnnwO8gniC2rYz1Zjq/m+ZOVxNpJ94KujVe3865nljVhrr2DZjc2pjdEAPxSciejfa0U6GxcV5zL4bhpxnUdLNOt6oX90ECH3xOUce2bhRzAWzGTeb9DHBHO4Q1RJzW4Iy2ytCcR7eL+blr/aLgUBWMqYFzEDcNPHmhOA825yzr1ksrKwuU1af23xnoj/+i6M+rkBY30672tY3pGtyZxXjePrSeYqxnEJ8S0VSah7pGk7fLe7D5FfwS4gnSyiY0dOrTeJfUiyv7F6NvAubsPbv0i3J9XXPjlABuNwOclrGL+QLE48S7tvHW1DNe1wjQ/BPEXSKuJrx1tfbGZzZ713C4EV1qz8++c4VtFqioGlXN+AfdEYrZGQUE2lzODUQow0NT6Rk1/gXmuzPen4pyMpZ6761HxLR8cr6Yz/wl9gXcNc54lxk=
*/