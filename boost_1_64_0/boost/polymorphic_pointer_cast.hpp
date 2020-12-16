//  boost polymorphic_pointer_cast.hpp header file  ----------------------------------------------//
//  (C) Copyright Boris Rasin and Antony Polukhin 2014-2019.
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/conversion for Documentation.

#ifndef BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP
#define BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP

# include <boost/config.hpp>
# include <boost/assert.hpp>
# include <boost/pointer_cast.hpp>
# include <boost/throw_exception.hpp>
# include <boost/utility/declval.hpp>
# ifdef BOOST_NO_CXX11_DECLTYPE
#   include <boost/typeof/typeof.hpp>
# endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost
{
//  See the documentation for descriptions of how to choose between
//  static_pointer_cast<>, dynamic_pointer_cast<>, polymorphic_pointer_cast<> and polymorphic_pointer_downcast<>

//  polymorphic_pointer_downcast  --------------------------------------------//

    //  BOOST_ASSERT() checked polymorphic downcast.  Crosscasts prohibited.
    //  Supports any type with static_pointer_cast/dynamic_pointer_cast functions:
    //  built-in pointers, std::shared_ptr, boost::shared_ptr, boost::intrusive_ptr, etc.

    //  WARNING: Because this cast uses BOOST_ASSERT(), it violates
    //  the One Definition Rule if used in multiple translation units
    //  where BOOST_DISABLE_ASSERTS, BOOST_ENABLE_ASSERT_HANDLER
    //  NDEBUG are defined inconsistently.

    //  Contributed by Boris Rasin

    namespace detail
    {
        template <typename Target, typename Source>
        struct dynamic_pointer_cast_result
        {
#ifdef BOOST_NO_CXX11_DECLTYPE
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, dynamic_pointer_cast<Target>(boost::declval<Source>()))
            typedef typename nested::type type;
#else
            typedef decltype(dynamic_pointer_cast<Target>(boost::declval<Source>())) type;
#endif
        };
    }

    template <typename Target, typename Source>
    inline typename detail::dynamic_pointer_cast_result<Target, Source>::type
    polymorphic_pointer_downcast (const Source& x)
    {
        BOOST_ASSERT(dynamic_pointer_cast<Target> (x) == x);
        return static_pointer_cast<Target> (x);
    }

    template <typename Target, typename Source>
    inline typename detail::dynamic_pointer_cast_result<Target, Source>::type
    polymorphic_pointer_cast (const Source& x)
    {
        typename detail::dynamic_pointer_cast_result<Target, Source>::type tmp
            = dynamic_pointer_cast<Target> (x);
        if ( !tmp ) boost::throw_exception( std::bad_cast() );

        return tmp;
    }

} // namespace boost

#endif  // BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP

/* polymorphic_pointer_cast.hpp
cmVhyGqAHhcU2z4T58hw4m4s3URvKwVxhksdnFZ5wAWEzIHtSmSFG7ja+9RWRe1C6iVwjRRxECP7pkxnCOmPTlU82FtUCvDIJjYOXNiocvvxyaAm42Xb7+vHoOAgPAc9sWC3eNPAXKTb6eu8DkNuKSaSgrCeda2CF+aP1nod3CZIzNfro5P5aUB1rm1rI+Hns4qMcwWJPYveTtyCs2+jgknfDsDtPpX41BQmqqbulKZU+t1IpyaeD/Rt+kM8Q0gm0Pwk0NVIlIt0bLaCzXqwT9BCgHBMeEG6td23JfJZsWcU3jArD6dJ9gC8BcFc1dLvKH7Cuc0NQ0WrVqOUKmcPkf2DDKVMzmrkcJ548Qh6navBP4sSCN4b/ZhDGUSMWlzRjatPUWLHsTBAWJY6kvZWyHukPTcRD8RMeu1sMZMmwiR0Iv8Zplg6/vFVHa6Xlfb+tEOsF7V+M1T5oC63VYVHRc4XtLfpyg7aw4zcfFBzqv6fKvighpPqeeTcMb1rGwpHtreLVQWLVkKVln+ZBAb7CdY1bqvjDngTiKERmel1vHyxOBQpk4VVa182TR0scKHx8EJMYmZCqLVsEnePMsN/D8K0HPTHSg+Ion20KvU0k87ZL4RSJz2snHmn7iewVoid4zSg5qHT9fhrpAQ7kK71h7EZEhWwKOm60D5HdWrhslagyxRQ31agfA1E38PYesK9NOQZAjnrR43DSFZoA9N4PjvUpj/sDBlvdofnvazgRF3B/ulSwVa9lV2REAJVuIPZSdUVq/8ZqdZ1Sro/5mRK91GJR/jeRBWPUPIIOFPBOJMw++xqBfOT1f/qj/ZCbZyd8D99xOWJE7sS0v0qGN1RYobFbNyzaA+GxT/k8YGPCB7ZeCKO1NrVEM5hlpumPcNOpk/YxStJ8IlIXUsgxd2yTHh4kGI53SrOvI8IXIp9g4wv7hnJARC0PEZsWhxs7oJ3M5Vv4bWRtc3xFbGxTuP3cYl+8CfQrufyhXYZSwcKgf/UfuLE5AY/AGN9F/I59McK3s5LSPfBCcDlP2tyXxjvc8LS/g7PxA3ytMzN138ZelIllb0rGlPlQ12kjchnaeWTA9abIRgRnJ3AJ8DG1G0S+zld4E4H5ZaFkjh0/jUextHs5lniL4ovTi9q7D30uGu7+BcPLGp0Dz372vQV6UVxqI9o5PEshmnmMeEjIXh0nT/OOb948YmNfRH1Qa6gb9jpzmx0e5Zken7VtDjT2LMJ1mb+3BMTkxHurt01F7sHDQnqIAxydlYgW4TfU/In44WJyvR35onUEIms+WvZszDwODkkp28CyYnpappSpnPZPI3MkxUyDz6RyLxQEH7P2UTmBPC/t2WCorenXCZITjprxo/JW9LfkRpfcJi2yfUoKKrPt54nAfZy7Hr82DOiUEIKfkvtoxedoKzst8/pREjBhL3vM5cqOaACtdP+NUoLa1pX07KaVtW0qKY1tVFobxuhGpfKG9bh6dD1j1f1A+ub0cWXj2c0QfhWOrl9NEF2fI6u3w7zh1VdM6Kwk9EC28U/npoSP9L+zmQ8tdOnsxVwaHfOUhHLsiBGwFxciG3NiMGOr6BXl/3wC8/bQqpH5ACT521r5ZzNxp4IGmcvmqdsDUoHy7e4PeUhW/FgOWSjKVV35ucP1pzsG+o5V563iMbgAfRfFFW3J3TjUf6grkEYQWV5WSdS+qxCdYn2tplsb5NsZuepphmIzv7OYK4l8L7s/eDEjQyqLFjHG6jDasLlCFcFmMFxTUUzBof7mLFxOSGaTdEoxD58CsZ01ODIvMHokJP0GuBsib4E7YxRauO0tWesKfA1xcK0IT1Bb6qrkeebgTKbUSX7Wj9SZdANKBs=
*/