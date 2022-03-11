//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_DYNAMIC_IO_NEW_HPP
#define BOOST_GIL_IO_DYNAMIC_IO_NEW_HPP

#include <boost/gil/extension/dynamic_image/dynamic_image_all.hpp>

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/error.hpp>

#include <type_traits>

namespace boost { namespace gil {

namespace detail {

template <long N>
struct construct_matched_t
{
    template <typename Images,typename Pred>
    static bool apply(any_image<Images>& img, Pred pred)
    {
        if (pred.template apply<mp11::mp_at_c<Images, N-1>>())
        {
            using image_t = mp11::mp_at_c<Images, N-1>;
            image_t x;
            img = std::move(x);
            return true;
        }
        else
            return construct_matched_t<N-1>::apply(img, pred);
    }
};
template <>
struct construct_matched_t<0>
{
    template <typename Images,typename Pred>
    static bool apply(any_image<Images>&,Pred) { return false; }
};

// A function object that can be passed to apply_operation.
// Given a predicate IsSupported taking a view type and returning an boolean integral coonstant,
// calls the apply method of OpClass with the view if the given view IsSupported, or throws an exception otherwise
template <typename IsSupported, typename OpClass>
class dynamic_io_fnobj
{
private:
    OpClass* _op;

    template <typename View>
    void apply(View const& view, std::true_type) { _op->apply(view); }

    template <typename View, typename Info>
    void apply(View const& view, Info const & info, const std::true_type) { _op->apply(view, info); }

    template <typename View>
    void apply(View const& /* view */, std::false_type)
    {
        io_error("dynamic_io: unsupported view type for the given file format");
    }

    template <typename View, typename Info >
    void apply(View const& /* view */, Info const& /* info */, const std::false_type)
    {
        io_error("dynamic_io: unsupported view type for the given file format");
    }

public:
    dynamic_io_fnobj(OpClass* op) : _op(op) {}

    using result_type = void;

    template <typename View>
    void operator()(View const& view)
    {
        apply(view, typename IsSupported::template apply<View>::type());
    }

    template< typename View, typename Info >
    void operator()(View const& view, Info const& info)
    {
        apply(view, info, typename IsSupported::template apply<View>::type());
    }
};

} // namespace detail

/// \brief Within the any_image, constructs an image with the given dimensions
///        and a type that satisfies the given predicate
template <typename Images,typename Pred>
inline bool construct_matched(any_image<Images>& img, Pred pred)
{
    constexpr auto size = mp11::mp_size<Images>::value;
    return detail::construct_matched_t<size>::apply(img, pred);
}

} }  // namespace boost::gil

#endif

/* dynamic_io_new.hpp
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
*/