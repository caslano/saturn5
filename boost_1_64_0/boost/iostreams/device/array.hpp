// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ARRAY_HPP_INCLUDED
#define BOOST_IOSTREAMS_ARRAY_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>         // BOOST_MSVC, make sure size_t is in std.
#include <boost/detail/workaround.hpp>
#include <cstddef>                  // std::size_t.
#include <utility>                  // pair.
#include <boost/iostreams/categories.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Mode, typename Ch>
class array_adapter {
public:
    typedef Ch                                 char_type;
    typedef std::pair<char_type*, char_type*>  pair_type;
    struct category
        : public Mode,
          public device_tag,
          public direct_tag
        { };
    array_adapter(char_type* begin, char_type* end);
    array_adapter(char_type* begin, std::size_t length);
    array_adapter(const char_type* begin, const char_type* end);
    array_adapter(const char_type* begin, std::size_t length);
    template<int N>
    array_adapter(char_type (&ar)[N])
        : begin_(ar), end_(ar + N) 
        { }
    pair_type input_sequence();
    pair_type output_sequence();
private:
    char_type* begin_;
    char_type* end_;
};

} // End namespace detail.

#define BOOST_IOSTREAMS_ARRAY(name, mode) \
    template<typename Ch> \
    struct BOOST_PP_CAT(basic_, name) : detail::array_adapter<mode, Ch> { \
    private: \
        typedef detail::array_adapter<mode, Ch>  base_type; \
    public: \
        typedef typename base_type::char_type    char_type; \
        typedef typename base_type::category     category; \
        BOOST_PP_CAT(basic_, name)(char_type* begin, char_type* end) \
            : base_type(begin, end) { } \
        BOOST_PP_CAT(basic_, name)(char_type* begin, std::size_t length) \
            : base_type(begin, length) { } \
        BOOST_PP_CAT(basic_, name)(const char_type* begin, const char_type* end) \
            : base_type(begin, end) { } \
        BOOST_PP_CAT(basic_, name)(const char_type* begin, std::size_t length) \
            : base_type(begin, length) { } \
        template<int N> \
        BOOST_PP_CAT(basic_, name)(Ch (&ar)[N]) \
            : base_type(ar) { } \
    }; \
    typedef BOOST_PP_CAT(basic_, name)<char>     name; \
    typedef BOOST_PP_CAT(basic_, name)<wchar_t>  BOOST_PP_CAT(w, name); \
    /**/
BOOST_IOSTREAMS_ARRAY(array_source, input_seekable)
BOOST_IOSTREAMS_ARRAY(array_sink, output_seekable)
BOOST_IOSTREAMS_ARRAY(array, seekable)
#undef BOOST_IOSTREAMS_ARRAY


//------------------Implementation of array_adapter---------------------------//

namespace detail {

template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (char_type* begin, char_type* end) 
    : begin_(begin), end_(end) 
    { }

template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (char_type* begin, std::size_t length) 
    : begin_(begin), end_(begin + length) 
    { }

template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (const char_type* begin, const char_type* end) 
    : begin_(const_cast<char_type*>(begin)),  // Treated as read-only.
      end_(const_cast<char_type*>(end))       // Treated as read-only.
{ BOOST_STATIC_ASSERT((!is_convertible<Mode, output>::value)); }

template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (const char_type* begin, std::size_t length) 
    : begin_(const_cast<char_type*>(begin)),       // Treated as read-only.
      end_(const_cast<char_type*>(begin) + length) // Treated as read-only.
{ BOOST_STATIC_ASSERT((!is_convertible<Mode, output>::value)); }

template<typename Mode, typename Ch>
typename array_adapter<Mode, Ch>::pair_type
array_adapter<Mode, Ch>::input_sequence()
{ BOOST_STATIC_ASSERT((is_convertible<Mode, input>::value));
  return pair_type(begin_, end_); }

template<typename Mode, typename Ch>
typename array_adapter<Mode, Ch>::pair_type
array_adapter<Mode, Ch>::output_sequence()
{ BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
  return pair_type(begin_, end_); }

} // End namespace detail.

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_ARRAY_HPP_INCLUDED

/* array.hpp
siz529iZv9fw92akkL93wqPoHYAh354+1zf590zi78VIyM+njr+3IiF/n73XN/n8nLw+3O9nPW0v5O+RbNvp/zNpI/VHNpGugyFfoK0bw/2BGli2C74FP2RZwg3U1y4TmnyD8m9o8g/aam+fbbfkJ7QLnS3kqUPvEHwLcfoOpd5IXUgfQG/ujU0+RIX2crj5xuh9ifbdGNmfaOPT9Hl45MaW/YqybmryLZrL39uofx3cgfS5GF3o9DdqpP4hn6PGm8x+R4cow+R7dILlb7H8Q8pI3hT0QxoJbV+k1F3xVv6moE9SDdyEhHyT6u00PARNPkp9vkQ9YBY8wLJFcA1yhL+3QqffUj3pbfAwtC7BjnAf6YybqQvpHOj0ZaohHfJnaiS9i7T/5/gSIXORMmQjshM5gBxF/C+yHpmLrEC2vBjz/4n9ovslIBX/5uf/6gbN6mVXKgcAyzplH4CGdMoIfe+4g6V+jXFc68HX4YBMzlfHqXsHedMX5hcsLaouLy5YXVpVvkx/L6tfprp/qp+nd4ezxtt5/u7rYP3W11fubV6nylkXN4SznXmczV3gO9NnusfA9vQ9hj3d1f2k0qqaan2Pt06tfz7OdM/BmXdO3+D9JeOzQ5fuEEu9c3RF0fJqa6DcW71Drf9C3Has+wdfovWxL87qFzfHdE/XXWd+xWVF5RW6rGxlj5S4Dla2b5avl1WAVZ72pav71B9+/PHH08+013fx7bXSVRlzqbsl96kGhp61qTKqfUOJYH2Rs8gkX2erlHqpe9as+Y5a/4LVhSu8rpR7knI3qXrtj+uq7zVXlULKFJ8Ntf6euDhrFOfrU63BvgoOKx3VPdDi4F0wygru02dUHf3O+9b6fvnv1La/YuVwtzFN6nOdWvYX9ulQawJ16qFtU1tRU1VbXVNaomPsN6p63Bz3EVFoi32DfKHnk+tUGTso41LyO8vd70uwNgX19LIH6cvLHN/DqybYvalP9lM6YzjP9rNMt6GinPD/0uomvdulLanYWbVd27ajNZb743vs/U1H/bn6hp4/Kd6fkNS5U+ehSQnxaZ1nJCX5E4cldfLHreNaUj+feTE9KD20XavLl1cwCPmF+sA9ygbfi9vu26vacMsAtb/KSxzj6halk0WPzAjdr1f1SeFwtTSV+iStLQvdbzvZIzg+H+/VdE8vjW2dYFtBez3nO4+b/Vf6eus+9rhaPoOe9X3rOez0W2uRNcXXUT+fOKjWp5IO7ou0CaTZu679wJIVwWcFUr8c6vduCvXzra2yH0D4BvuTbbsYn0FInjLyvGnn6bT2xlCb3nLpbELnPVunw9pr9X1Gl0691lmX69ZJE53DofolrDvfn5RkiV5YnU6i976t13HdT0M6J1xlDUti/rP3Red1D/rju+myRncP6n2KNKutoWlBv6L3ewb5Ev3jWf6+MjWYHs76z/P3SHia6I6AX4GH0N2k9IIyTL636G/lucvxM5ueu/Qg/ZdxKr2swF4iOn0mBHV4kKLvx9pzfC/meOf9WMYyy9TcrO+lM+eqe+nO5zJDkF4ytzZ7F508o33Cx3bhY3AE20k5Sx9vGJiX15ZW14SOOKo/D1fHG9Y43tExVeWp8PXzjbXyfCnm9/6cZT6uGI4j6IYfR1ZVlZqOI+gajyPax6FSrT/d18sXhw7LSO06W/mqmY4lujz3nN1X5oBr1fpOvolWb+4NZVv7rYC2wyWq3Ar8JTqxdLDMG5Smlu9mtG8LO76kydgersq9x/dpjinViK33qnrmuLy0wjEHXab05vsGc7RQ86NuT0fz/CbH7e+pfG9av7Di7Xar45NrrtbHmseVbnfTPK11/GqbGZa7DnMYX91lfP0=
*/