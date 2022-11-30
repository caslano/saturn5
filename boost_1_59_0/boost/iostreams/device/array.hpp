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
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
*/