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
    template <typename ...Images,typename Pred>
    static bool apply(any_image<Images...>& img, Pred pred)
    {
        if (pred.template apply<mp11::mp_at_c<any_image<Images...>, N-1>>())
        {
            using image_t = mp11::mp_at_c<any_image<Images...>, N-1>;
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
    template <typename ...Images,typename Pred>
    static bool apply(any_image<Images...>&,Pred) { return false; }
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
template <typename ...Images,typename Pred>
inline bool construct_matched(any_image<Images...>& img, Pred pred)
{
    constexpr auto size = mp11::mp_size<any_image<Images...>>::value;
    return detail::construct_matched_t<size>::apply(img, pred);
}

} }  // namespace boost::gil

#endif

/* dynamic_io_new.hpp
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
*/