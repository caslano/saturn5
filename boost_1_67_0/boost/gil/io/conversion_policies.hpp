//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_CONVERSION_POLICIES_HPP
#define BOOST_GIL_IO_CONVERSION_POLICIES_HPP

#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/error.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace boost{ namespace gil { namespace detail {

struct read_and_no_convert
{
public:
    using color_converter_type = void *;

    template <typename InIterator, typename OutIterator>
    void read(
        InIterator const& /*begin*/, InIterator const& /*end*/ , OutIterator /*out*/,
        typename std::enable_if
        <
            mp11::mp_not
            <
                pixels_are_compatible
                <
                    typename std::iterator_traits<InIterator>::value_type,
                    typename std::iterator_traits<OutIterator>::value_type
                >
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        io_error("Data cannot be copied because the pixels are incompatible.");
    }

    template <typename InIterator, typename OutIterator>
    void read(InIterator const& begin, InIterator const& end, OutIterator out,
        typename std::enable_if
        <
            pixels_are_compatible
            <
                typename std::iterator_traits<InIterator>::value_type,
                typename std::iterator_traits<OutIterator>::value_type
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        std::copy(begin, end, out);
    }
};

template<typename CC>
struct read_and_convert
{
public:
    using color_converter_type = default_color_converter;
    CC _cc;

    read_and_convert()
    {}

    read_and_convert( const color_converter_type& cc )
    : _cc( cc )
    {}

    template< typename InIterator
            , typename OutIterator
            >
    void read( const InIterator& begin
             , const InIterator& end
             , OutIterator       out
             )
    {
        using deref_t = color_convert_deref_fn<typename std::iterator_traits<InIterator>::reference
                                      , typename std::iterator_traits<OutIterator>::value_type //reference?
                                      , CC
                                      >;

        std::transform( begin
                      , end
                      , out
                      , deref_t( _cc )
                      );
    }
};

/// is_read_only metafunction
/// \brief Determines if reader type is read only ( no conversion ).
template< typename Conversion_Policy >
struct is_read_only : std::false_type {};

template<>
struct is_read_only<detail::read_and_no_convert> : std::true_type {};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* conversion_policies.hpp
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
*/