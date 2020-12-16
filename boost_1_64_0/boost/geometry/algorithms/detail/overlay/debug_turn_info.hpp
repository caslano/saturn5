// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/visit_info.hpp>


namespace boost { namespace geometry
{

inline char method_char(detail::overlay::method_type const& method)
{
    using namespace detail::overlay;
    switch(method)
    {
        case method_none : return '-';
        case method_disjoint : return 'd';
        case method_crosses : return 'i';
        case method_touch : return 't';
        case method_touch_interior : return 'm';
        case method_collinear : return 'c';
        case method_equal : return 'e';
        case method_error : return '!';
        default : return '?';
    }
}

inline char operation_char(detail::overlay::operation_type const& operation)
{
    using namespace detail::overlay;
    switch(operation)
    {
        case operation_none : return '-';
        case operation_union : return 'u';
        case operation_intersection : return 'i';
        case operation_blocked : return 'x';
        case operation_continue : return 'c';
        case operation_opposite : return 'o';
        default : return '?';
    }
}

inline char visited_char(detail::overlay::visit_info const& v)
{
    if (v.rejected()) return 'R';
    if (v.started()) return 's';
    if (v.visited()) return 'v';
    if (v.none()) return '-';
    if (v.finished()) return 'f';
    return '?';
}



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP

/* debug_turn_info.hpp
EJMwGQ9hCqZiGh7GdDyCR/EYZmAmHscszMYczMUTeBLzMB8L8BQWYhEWYwmW4mk8g2exDMvxHP6Ae7ESz+MFvIhV+CNewmqswctYi3V4BX/CemzARryK1/A6NuENvIm3sBlvYwvewbvYivewDe/jA3yI7fgIH+PP+AQ78Cl24jPswm58jj34Al9iL/bhK+zHARzE1/gGh3AY3+I7fI8fcAQ/4iccxTEcxwmcxCmcxhn8jF9wFucQGOcIRCKEKKRCaqRBWqRDelyDDMiITMiMLMiKbMiOHMiJXMiNPMiLfMiPArgWBVEI0bgOhVEEMSiKYiiOEiiJUiiNMiiLWJRDeVRARVRCZVyPKrgBVXEjqqE6aqAmauEm1EYd1EU9xCEe9dEADdEIjdEETdEMqdLQMZ8vYTXW4GWsxTq8gj9hPTZgI17Fa3gdm/AG3sRb2Iy3sQXv4F1sxXvYhvfxAT7EdnyEj/FnfIId+BQ78Rl2YTc+xx58gS+xF/vwFfbjAA7ia3yDQziMb/EdvscPOIIf8ROO4hiO4wRO4hRO4wx+RnO0QEu0Qmu0QVu0Q3t0QEfcFcX24W7cg3txH+7HA3gQkzAZD2EKpmIaHsZ0PIJH8RhmYCY2YhZmYw7m4gk8iXmYjwV4CguxCIuxBEvxNJ7Bs1iG5XgOf8AKrMTzeAEvYhX+iJewGmvwMtZiHV7Bn7AeG/A4XsVreB2b8AbexFvYjLexBe/gXWzFe9iG9/EBPsR2fISP8Wd8gh34FDvxGXZhNz7HHnyBL7EX+/AV9uMADuJrfINDOIxv8R2+xw84gh/xE47iGI7jBE7iFE7jDH7GLziLcwjYnghEIoQopEJqpEFapEN6XIMMyIhMyIwsyIpsyI4cyIlcyI08yIt8yI8CuBYFUQjRuA6FUQQxKIpiKI4SKIlSKI0yKItYlEN5VEBFVEJlXI8quAFVcSOqoTpqoCZq4SbURh3URT3EIR710QAN0QiN0QRN0QzN0QIt0Qqt0QZt0Q7t0QEd0Qmd0QUJ6IpuSMTN6I4e6IleSEJv9EFfJKMf+mMABmIQBmMIhmIYhmMERuIWjMJojMFY3IrbMA63Yzwm4A7cibswEXfjHtwZRQcCY49rkAEZkQmZkQVZkQ3ZkQM5kQu5kQd5kQ/5UQDXoiAKIRrXoTCKIAZFUQypURwlUBKlUBplUBaxKIfyqICKqITKuB5VcAOq4kZUQ3XUQE3Uwk2ojTqoi3qIQzzqowEaohEaowmaohmaowVaohVaow3aoh3aowM6ohM6owsS0BXdkIib0R090BO9kITe6IO+SEY/9McADMQgDMYQDMUwDMcIjMQtGIXRGIOxuBW3YRxux3hMwB24E3dhIu7GPbgX9+F+PIAHMQmT8RCmYCqm4WFMxyN4FI9hBmbicczCbMzBXDyBJzEP87EAT2EhFmExlmApnsYzeBbLsBzP4Q9YgZV4Hi/gRazCH/ESVmMNXsZarMMr+BPWYwM24lW8htexCW/gTbyFzXgbW/AO3sVWvIdteB8f4ENsx0f4GH/GJ9iBT7ETn2EXduNz7MEX+BJ7sQ9fYT8O4CC+xjc4hMP4Ft/he/yAI/gRP+EojuE4TuAkTuE0zuBn/IKzOIcgwv8QiRCikAqpkQZpkQ7pcQ0yICMyITOyICuyITtyICdyITfyIC/yIT8K4FoURCFE4zoURhHEoCiKoThKoCRKoTTKoCxiUQ7lUQEVUQmVcT2q4AZUxY2ohuqogZqohZtQG3VQF/UQh3jURwM0RCM0RhM0RTM0Rwu0RCu0Rhu0RTu0Rwd0RCd0RhckoCu6IRE3ozt6oCd6IQm90Qd9kYx+6I8BGIhBGIwhGIphGI4=
*/