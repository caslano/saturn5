//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GET_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GET_HPP

#include <cstddef>

#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/scalar_type.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta-function returning the result type for get<N>()
template<size_t N, class Arg>
struct get_result_type
{
    typedef typename scalar_type<Arg>::type type;
};

template<size_t N, class Arg, class T>
struct invoked_get
{
    typedef typename get_result_type<N, T>::type result_type;

    invoked_get(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// Returns the \c N'th element of an aggregate type (e.g. scalarN,
/// pair, tuple, etc.).
///
/// \see \ref field "field<T>"
template<size_t N>
struct get
{
    /// \internal_
    template<class> struct result;

    /// \internal_
    template<class F, class Arg>
    struct result<F(Arg)>
    {
        typedef typename detail::get_result_type<N, Arg>::type type;
    };

    template<class Arg>
    detail::invoked_get<
        N, Arg, typename boost::remove_cv<typename Arg::result_type>::type
    > operator()(const Arg &arg) const
    {
        typedef typename boost::remove_cv<typename Arg::result_type>::type T;

        return detail::invoked_get<N, Arg, T>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GET_HPP

/* get.hpp
D4CdeZdK/idnxqn7xyBrXei0lsapvh3oc/Nbqiu/rXH8woSRm6OzzenQWcjemMTgFgX5yW4n8XCzkX3KWgq3txt5/bt9e8WjLs1Wgd1BYsa3d1xhVC3CF8maFf6T+Z0EB9Gd6U4s2i3gVPV2b/7+pF8ywrGPkEuceq67yHujUwGbL+hS78JKW7TdtMUoOC6li7mxF3BaUop9nPzu+L7RcVPTWbDh7qExX9yCIH6HHunSUlSsJXY2wnfy2PQVoe6gxQT7ZW4XCc78GU/j/tq5V+BRVzWcVsd4AuaDV9AftCVj6+VjOxJr3sdjVTcSKLBZYPR9ZHVd/e6+EqMGEVj9fhIr1O+ydsDoN74wkKVZidEtF2lL9j3mm8fLYRt1XAQe6thBWZcCRmk6ENiWwihfwqD/n1JiVXjGY6PT48enxuh/NByP0Jgi772RRblP8NQ0t6QSPIJ1eYIXPP6JynbH6ZjnK404S7OptGhouPItjnRF+TaHcEP54Ft4CC84cAfu7v/hUqsihsr+4VySrC49RTG3Kt9lyZ42/Dfe+ZvP6VPtJXRWnsDDHI5zi9eCU871IU7faYzB0wZ3HQL84JTFqQAZ43vR76kAhMNmPUvh0zOjM3f1Jiu/fXYqwXH5gNNIpePy4vYSnKmTvipSLixOWaAdDObbsYMzS+63yQma+e6ihYZ96C0PAsNzWW45LCxqH2PvLMNzFUKZtmw6SlC4TDuWx0KyiP1Dy7ECkol7/pZrBYS4N8Da0HDTArIKG8/yjXDA7jxleTpmS3bG4tShAm8wTuD4xO0m9V5c7bTFXQYYa9HvXQYcD1DgZF5Pz6gBwzIc8TBg+B3oiKMHDMc8sjx9Z3g3SkcPGOx7JnmuTNBjT7ecaMDMBW494toBw/H7mmmuHTCrmC+G8fkK5ALWd3H7dInQgbzFOPUp2z3NHYtjP3sBsv18ySn3Wl2/r3TmyNWedVXjBYZn73dHuDOQ1jpr5dKS19sxb6Xfz4HXX2hxN8mjzjG+TunznthLk3g1XiBrL7McfQ7QeHmEFzTuyIB+IPLJHsQcmsaO3XMGhzBc1lMxR86HjUQaNh7RrOacGJ0ZjfYadk9FHHXWs5VIg7Lh32scExH65LTFKXUpx++x+Npcf2EF+IFN31cS6+n3GpyauxIfc+d/831DeO7chddGD1Y82jLC04lrsDNijmqz2RhX6+Stt0R4EK41cGQad5u809gJ1tuY606lOHr/azeZjt4LPmAORQu+G612T076zQ9ul4ckOC4rHpNJDmUlx6TgUNBgsmym0MCQsdMxR479rUQaYewjhunTmUO7xSfHYuN/AfonyWVbBnZDiqenJ46r8JAE19g0u49McPyNvkVpg9h8o4UC16X2jBSXbSDEBE7zrB20Gvit4Xye2ogf1gv5UL6d3rh9t4b+hqc4jpGc4Hq7COM61QfeNoL+4DznFhY6eRXfJqdjrk6hYwY8k3m0K1G9QTzo95aWzPjeZz0zT6GFFtyQo8dr5PnVM1Oc9d76As+Js+9PcKro54NC7fN+UPP8JhnfQfiIxsMGWcA3sWaqCkkDT+uG7Xcq3JeA/tnICui712lOv0fJZIzXnhVwt8/vq1rg/OyRBqdD7u4i3WISaWTPZg6dMfskuJ5bAt9YxTTRR7+8U+IhOD1Vg/LAfv3rwaFmoP0lEVu/+SGB8a1bHo/qt3SjbdDZcElwPbc5jd56hywClnWu5xvAoeteFFhhsFGtqaHzHw2cEhiQB1k5MqpECtjjj4k4PArl3PmcJC+0LfM+ZHlUwWqgdRZVXJ2I5+vpZBe8/QSP24PTyx5rec6W8lM2r2cTPCocz4GfsHiQAp6zm49nDik=
*/