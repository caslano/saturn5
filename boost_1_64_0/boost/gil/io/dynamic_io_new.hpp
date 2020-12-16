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
G62QCrZ/jVDG9+VIr016etQ20G32R9OjUuHRN3CAhm4zzxulpaHbKelHVKUJb+TBKuU+JDimMUjIaUOINEMo2pksAJnvIL+79H8ORTrnmVrAvnk+hlzt/yFlcQH9GmwojzUQ6e+kT+zxSTRWvDlDpmq1ZPOB6vxlzL92m5X41XtLm95iJY2eBlKGkuaQxNb4gd6MfhyjD0QzXKMZVzKaLxHGmqksmIt3OUIakV9vSCFoQ7WwaI8nN55ruBcth1VXI5ESMGntp54wrzwsnAANjw0lDWg6aYiCJfeEiJQQCwO8rFHuP+Vbkh3MeHIjyfsW34NHoZBD21y/hvDxD977LK9ZEcnxIXbz5Wvq808pkz/nWPfw7TLPNXRXwu3LisMv6fDbhDEFtnmSHpHEddM+fyt+zKtKaqekH7mNNB9ZyI8ibGY4zyI8qzmqtUQb/fIG0qwq4xF9FQXCVcDPEkjHI2aQQ2z2oTyHslgSUHgAViltxQ5fIzwi9MDCUF+rgNqZavWFs22xNuTGCLbDE+yKlvcSDbajWLAL9XReoh11bRSG6a4pmri4RBf3K6gEDrGjrdV8BC09/8H0qPaQseH5og9//HLuw09QbJ5jG2fM6S6v5PvT09bZ7OVlEccVsqYnvykbMTN4AkmQNYAYWrpgMwtflXA3Ej0HBzpR52q5nv/YU431HXJikVhGnMOPGYuvm1QXD2h0vsSHH53t8Tu7EgDY6FJX4bz8B7jDHtPEgXCNMacnst4y/Pq97227D64e3MtwH8NtgdsP9z3cBbg/4ZpBTyTcc3Aj4NLgZsItgPsUbgvcQbizcJfhbsD5LYNuuNpwzeEi4NrDJcE9DzcEbgzcP+AccAvg1sF9CpcDdxDuNNxFuL/grsL5Lve21YF7CW4k3HuLkA78zodbAbcabh/cZrjjcGfhfoW7AddihbetL9wMuDfhFsJ9ArfiQ6Qfv2vxmwd3Be4gnn+BuwtX5QOkHy4Ozg63BO4TuD1w38DdgiuLMNXgGsK1houDexZuGNxEuCy4/2o/eiDKcx47DxakJr2u2qqqufZTAWzNQXovbZ4DzXO9NPRKGCIlV8pu71P6dAW/5fGCkDa2p46UcVSjtBBewbfR7eIQr8Sg+43mOdEc8ho4gpxZ/+/OOBZPf3Oxf9X0I/XZKccSHTxxkoi+slVCRIfg5MfMHL5gmT68V/gN6fsd83zFQP8SGHpdvbXo6j7D3i2YeQvh/H+e4rchoPkK4vlPxznaN0hwdA5IcLSvKmNnEJC7Z0J18PxQPbnGPiC3DBcx8kMTdF1z9BucKfrQzhwaEx3xDcyoejQY5rqn+ccTerSRBsG5HYK11/ThT7Gj9Z76i+6xcQmNXR5o4z5D8tYc9xkSGiwjswvqbeQq4TZF3vqk3nw8sXIz19WbDS/M/jK31ptB3x+81pHzjDeRQLCxY6XGgAmQGM1ozj53B2tzh9/zFaBsO4xKv0OnGatrJPdxvD2X/TALp0Z61E+Uk5FnfZCheN5YFJ22qMD3wDQ/1ubA93N42cjE5q/Ra8Vs/rY/JDZ/kyAgA1W1+RsUKsfA4vRAxi4MsGLCw+xVubBcyvQvJrx5kekfgpt/1JGk1iCeIXJPfBeUl7kCcnT6IZfzxQA1d6qqcmUtufwTtBNMv+ut63qm0+M8ttayGtKFkam9HY/RhHO3LxzJxMZFG4Fl7lmbeYhEfv8D/yGO3aqDrz07NP78Lk3451rAzExJCooowu8g6HhKe6IYDNAL4ND+9W2dd47RDfZ6SDnUMjdmKfzOLH83mvPE2mLsPwW6ZBSniM5VQEVWH+O8U1U9DVXmzENFevpQT4y/YjWTagaDIkBWTGJdaMg=
*/