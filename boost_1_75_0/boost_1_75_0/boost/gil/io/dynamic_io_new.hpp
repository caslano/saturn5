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
TPzUwphXe2tgR+S42IXFg4VD6yFa5I5PL5dsYeGH/W8yiZ0EnVYrWlpzxNO2iJpashcbOSxt+5DJNiKwPNWgX6qZQ0aw8PVBdK5ZrDPbOZodO9gJC90+5LapZjZK5Ozjq/ne5vchq20EWuMI+vyvHyRGExZe9xQWnuAIC6/y/qHKMzp4Ku+d2aJm1Nqs37J1Kk89uXJc9wQWzrHsV1/foyIH2HqZlFafpiwHCGHhaXbF5xshp9xe9hA/TceJP2Be/qCDhatq+XLOok2T6+n7prPZMORgNldnMNuJT8LpQeU+Otejb58ZzOZ4e0PpEtCfbpmlnP2sDWJM4zd52pWBYkyTfo8/s+EFZjPmF6RBo0iSXszKHy9G4e+I/P25NJwBC9++MEtAZOjM5MWcSTQDf6FGzp/I1VDrXjjMygDKnrh90Ot5witboSekAy6QWjydY02OJyk/7YJv67o4bj9qbLEUcZ7Wb5V938+jDwufrdSNAJaFF3mRHrrkncqTBWEXdBilF+V/Dw2PkEtmmWQ/PgEbiNLTFkSx6lrIYhBgtoWSLDbFlbWbMYNagH3+ApvYp0NydMQRyAX0pLJK57X4ht452rRsHyi4LPTJQ068RrDVtqmJ/1qBjzdhkFWj8JFQWBPJ44dFMoL2Ty/CHOkSLzlrSY9CmV8i6DDLr61yVlJz8+yIHUjLrwaFsQfX5KVn5tnV2dtfjYqTDmn1
*/