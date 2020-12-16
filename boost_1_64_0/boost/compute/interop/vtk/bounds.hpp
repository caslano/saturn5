//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP
#define BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP

#include <vector>
#include <iterator>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/container/array.hpp>

namespace boost {
namespace compute {

/// Calculates the bounds for the points in the range [\p first, \p last) and
/// stores the result in \p bounds.
///
/// For example, this can be used to implement the GetBounds() method for a
/// vtkMapper subclass.
template<class PointIterator>
inline void vtk_compute_bounds(PointIterator first,
                               PointIterator last,
                               double bounds[6],
                               command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<PointIterator>::value_type T;

    const context &context = queue.get_context();

    // compute min and max point
    array<T, 2> extrema(context);
    reduce(first, last, extrema.begin() + 0, min<T>(), queue);
    reduce(first, last, extrema.begin() + 1, max<T>(), queue);

    // copy results to host buffer
    std::vector<T> buffer(2);
    copy_n(extrema.begin(), 2, buffer.begin(), queue);

    // copy to vtk-style bounds
    bounds[0] = buffer[0][0]; bounds[1] = buffer[1][0];
    bounds[2] = buffer[0][1]; bounds[3] = buffer[1][1];
    bounds[4] = buffer[0][2]; bounds[5] = buffer[1][2];
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP

/* bounds.hpp
kxXfeVoxHjq9Ms866MPQhy9t0rAu7VWXFgY5mZSOTEvMZQVzknqTANlEAub73ZiHqZgrCmbSSAu2l+/T1va4zPwgjgrrodw0lxspT5CZv6pYXYV/xfsM/x+7iJMojWpmmLhDHfFsaTep8N3XpaNJVUQ5v80jWMl+VewXP1QV7NckfvGX8qbYr4exXzEg/B7sCKin2a9T7FfAfo2zXzhT3EX21beoOpiiDGLb9RxLOqQclO17WS3nibB0U9+vWKjxRXoR7CDGZj0XcCzusNzSzYqgYtj5RQHlcejeRXPNJppt6D3fk2VenSJWfN/Mvz/UPxkHj1C/b+HfnZLayC7YXCm+b2Xf+b6z+baNfyNbz/Ikj4+6je3BfsZkDKefSJ1cxuK+IxszdSzu1SdPLa0QBd89fKeFVOBfRqWM8J0/kY7vFb5TvYjvq6ye+ff54dT0FBF5LFc+1+7n8/na/JTYixKU05wjdM9e89CmSwxJsVf8O627tMlfFV+nVuvvPB36RGYBS+fnZ6ZqWxD6fgMqN7VCMUmVRkcy25N/uyXtNMpM1dVeoPFyIzaPi/lYPUN8n9P4BDo1Uw8k0PZtYTSagpdAwh7w+5y2uKRSVbmv38rorAJAxV7u1dsYjTYoaC9xntnOv9O8ywmQNbKDfWfrDxYf5OPHowaN2o6C14N3bjfoq/P0SPXigrJPvVFNmxH5wN6Zf38SXZcMkGAh14/3Gu90ZGGWpv+9jmxtnn6sEYyrV6vyjse+HeQFrZz+Ir/u1Mfg61XsWFUGURr6pcWcD4C9t7xnVbGZxS5h4iBJ2BMIM/RsBpWpxuM+XOAx55V2kEalbbGy8OlySGx4JGECvl4GX5Y5kRsntsWqj/MJS2zBJ8tyVeUbDzI/S9zI4otuK29/M9JIksgrCq+yWLNukMYubc5KnMzxvKqwaCO2MDDv3/ar2NzKXSfPYr+yuDvCyvQMnKcVvfghlecYc0zN4sS1at11DR7C57DGQkcXxFVCFRVbj1haIx+dtaF4O6g+HjdnzHePsTcC1bcIaBwzf5kR/Zy4m41vOu5pr0ooGGuLgpmnm2pAGszbt2mY5TU6iy0tsXhihEHcmRYGgmBDtVPBsB2fsDlDTBCFLtwBpRBgqhvXGBE8Y22G2U1TXHg1Ps/VvQIj7O9qN6Lm/PCVm0o6P4aCb/lm4vvsgEQvPVkyIjbQzSV9bbmvPj+5v8H01eepW6uY7vocub2Jaad15o4NxqgvlPXAnQVGnPkg/y7iO7d5o35MQ1gyI4a8hqE1TskF4indVcXQex/i/QXIONSmm+kcvpuKIRUtEMq5S8Og80DGw+8OOuzeZfshbhMw3THsPnmPhs7rHBHsmjXz1D0bjNk/fqXQZFHpFbLh/FMGwDz1Xh2Y+UUNs+/ewMiakOH/gXmzwIg8cChfrVcajHefNobPpARCntsYvj0hCOzSLxw2MXLQNaNwSUn30H3beDYlq3n7bAeGLQ0q5swRHTPsKOP4URPTLuO+YyamXcY/tDAbl/HqmIlvl/GTx00Myojx+eoTNUZsOdHP/qZ8F/ygRfcTNLFoq/1i9gGCNuwfB/8ARh8HSPuBDd1M+6MPkjT032afZjEadI7Q+fyNf59eYF4r2DoxRS5pO2BDbjMMTVKSruixLjiM9ljWYLQDlnIwZwJ3KOzEYX3AvWfchUO6yNPbc4YT17Rsulf0WPtKojE91mmpYIFyEXvQZ7Ywuq79QGXSoZ2DjJGHmBjdhvfbbTp08Ufknu+iZp8SxXFY5mVgKbt7eITDX++i7pddJlVZRIWl7uvNmFeXLuo2gVXsO37sZFZf0xl3pVc1/tgKPNvx2WVpT5Oasb1G360=
*/