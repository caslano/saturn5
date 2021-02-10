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
KRdTsQxToVDgnBjKugCYJ5jhdaXtBc83Qqg0XMhqpZxy7+r8vNAIUD0SClt0XRNlLSG7eiIjDxrCoQqrwaTSwuW3EqmaM4cM4oOsgcRypJVvlKogwmi01hJDSVShLT82kjxnVMKYc/nujdUadNq04dP+FXXqXyNV/jw1lSfQyugXjV9loA1Rc/0Ez/tvuj2r3el1O+1Cu8L6j8oBiklFdqVXimwqvotLbEohPcieFIYIfRMGZI4bJ9xzLXxaMfWNrJWVJnPcEOqhljukCYia/agWZltFw+1lwswG2UzpsJ94v2CapoZEqvv06uysM7B+6QyG3X7vOAes6w8BCHyYXwwzizurlcvy274CGlGDkWU46r/r9HKg4VyXQURxPcjnoJ1xBpoGHHdW8jnGnFqQN5TW3ph+kMwl1/uVOXtXlzKfmclwOu9VCuz6a9xjaTiPxjyo0b+0EOx1Rtf9wTurPehcPpqW8u+Dr5ReO0ottQMykEfT2pG1all40POCrtXqX1yed0YYJDuddqcNX76omUQZWLPXxi+9Ubd31anmxhct1eCxJjqrrJQqGzYkBaLUWDQc6faGaNndVrfTG2lvvd+b18hlYiCVKatPu+k29NYLGGQrRWX1p3I0qQcfpuHF5lZoozfoyzGmpWB1
*/