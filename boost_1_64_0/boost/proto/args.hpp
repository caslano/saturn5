///////////////////////////////////////////////////////////////////////////////
/// \file args.hpp
/// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
/// class templates.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARGS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARGS_HPP_EAN_04_01_2005

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/is_noncopyable.hpp>

#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_abstract.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits
        {
            typedef Expr value_type;
            typedef Expr &reference;
            typedef Expr const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits<Expr &>
        {
            typedef Expr value_type;
            typedef Expr &reference;
            typedef Expr &const_reference;
        };

        /// INTERNAL ONLY
        template<typename Expr>
        struct expr_traits<Expr const &>
        {
            typedef Expr value_type;
            typedef Expr const &reference;
            typedef Expr const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits
        {
            typedef T value_type;
            typedef T &reference;
            typedef T const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits<T &>
        {
            typedef typename mpl::if_c<is_noncopyable<T>::value, T &, T>::type value_type;
            typedef T &reference;
            typedef T &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T>
        struct term_traits<T const &>
        {
            typedef T value_type;
            typedef T const &reference;
            typedef T const &const_reference;
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T (&)[N]>
        {
            typedef T value_type[N];
            typedef T (&reference)[N];
            typedef T (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T const (&)[N]>
        {
            typedef T value_type[N];
            typedef T const (&reference)[N];
            typedef T const (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T[N]>
        {
            typedef T value_type[N];
            typedef T (&reference)[N];
            typedef T const (&const_reference)[N];
        };

        /// INTERNAL ONLY
        template<typename T, std::size_t N>
        struct term_traits<T const[N]>
        {
            typedef T value_type[N];
            typedef T const (&reference)[N];
            typedef T const (&const_reference)[N];
        };
    }

    namespace argsns_
    {
        // This is where term and all the different listN templates are defined
        #include <boost/proto/detail/args.hpp>
    }

}}

#endif


/* args.hpp
uiX4W/3ZWuf5rGBawgDCjk1sqXXkmeJ7ufWaPd2NkfARFzkRMPZfRUIxf/2bHiNzmvahbjewIm2JLPFV+C8ZfTBLle83lGej1bMlBdaurSWcvWGcFfzem9bZa5X8EovNQJ2TLFlwrHCD1roqu7VdwXonYGy14cpFn8OKMP6wD8hzntkZ7ctVAtqaVzgfNTjwSWhfy+m8ZXCuevsWcEwa4iqLsLzXOa/q2bqJvoeHmiwNzqIPFOxFUxVMLEAN2NhEBdvagPNaQRWsvEYFg02gIObMbPPaVb0x4eXqpO/MHeHyKJxBpRflLDOehz/4p/jHodqd5GvzsjlcSVHhYdI5KEf7b/zw813ImPxLt+J0jkTYzSMIrXQwsVB2gNimc7W4S46PsCrkgolhnDpzGFBeAKieKuPYdY2QW9+NEtfZ2rg/5BfL4LbWEJ5qX4kyfJ0IiyAuc+y/5Q0lCtMV59SQfb3UNPfez8NvVixZWGbdPOs6UhJRZbEHMRtDcp/pflL+rdUjdpxgJ0b0aDtP/jv/FipoHFyXyNU+90jL0i9IFBOlWdZxTEoMeQCu7mXhJ7u7hf/wDxbn8WRex6B0oLERUFOGVc499JTcJkJAaCWAfNSlQ3QlZh68BainGr/vWnKKZRarGaK2S8yx2m7N+E9+afUX8hSVYg/vY4UegrV12eyg5FqtE7gHX5Fs81xse+9o+528MkUiDAhQQjlM9SieMQ2dhJrAhwG2oaeIzlGLDvweeYkIJtgeHjQO9c7uPXN65NdcfUWFdSy2xSdCXFDXDbqu16wvVJ1VW6g8zPEFovP4O9ZzDGbwcCDY7nQOBwD4kqagXmtWz6zyNtgxMflvumPNVolxiRWxwuwGJJIpqCRyp0DniLCxDkwfIRME/1rDIqttSk7Px3zLC9xBi0HviJqltGareDn5Sbp0Wa6JO3FZRhg78j8G3RJO6bPzi9usRmRNkTGu6jeG4TiiaC1xWj6UJS76IiUUHPCDAV05xFI2xA/QVFYSZhpRBSlD62UWLcSuI/IcC7mP9mHNgT8ZDlDUgdZ1EN86vbMGtTgEMXRkRUvHl67builK4MyEA2lXx7uZZxu6v1EfrkOiNG93XES1QxGjrNSTkDK0U62XleGJimLWab2OycHoCDM56ea4DezwQqRbl26heAfc95WXcVrgKo6jUdUac9TymRchZq+P3hfOFeG/aOjsi47a8Z9+6GGVSbNGm4zmpwaJ0z0ji1NHbR1UBliqoFp6DTKYfXWLGDXS8cxH7fj9AOcs7RL+Wx/nsAuV9VVtjKB8huZ0xdydPWuVh10cxVE3in3Hl53L7VjqC1etO4/hZVH3bgHZzUoEcW80zV+S2sr+aKz8Zm69jtOE5sryDiZXHFF7tG97XbLI7ZyKE6ifyf382aO1u/tduLBc5GOc3cb+Ed1M84klAqIOMjL8y1r/FnGJeN8YA0ZlFJVdrBnVz3vubPdzkOVIk551aSMCS1CS0dMI7VD9vJeX9VAHrMVdD77kUXyxdx8ohz3eGJCnHjK5Cojqfj5659o5DZYbDJ47miYkEdJ7xvb9n9b5bzitoI3ztTRAyD/WLihOc+ZR31bSXsRpqXY+z2pn4ZSIaA/Lbve/byeMHBxQoJ2a5ictmiVsNax3cVmOpIlhQE2XzinrbUnTFCT1WdPfQZPLaIgkT243jugOgaUWVSub3Ey7b3wXKwYea38HZychluTKZvhviImKoo6m3SdAk/sWfCSZ9wvITPmfaU1u3JefFWmddZbTDOAy6GAuhK7/v47zeau9gg6eAsAW4/8ZZ70fBk0+T5EINMyRL2E3eT6D6BnIMhStbugm6Q1ox9r9uAJZ3GN4GOY=
*/