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