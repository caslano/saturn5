// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for area
    \ingroup area
*/
template <typename Geometry, typename Strategy>
class AreaStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state template,
    typedef typename Strategy::template state<Geometry> state_type;

    // 2) must define result_type template,
    typedef typename Strategy::template result_type<Geometry>::type return_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy const* str = 0;
            state_type *st = 0;

            // 3) must implement a method apply with the following signature
            typename geometry::point_type<Geometry>::type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 4) must implement a static method result with the following signature
            return_type r = str->result(*st);

            boost::ignore_unused(r, str);
        }
    };

public :
    BOOST_CONCEPT_USAGE(AreaStrategy)
    {
        check_methods::apply();
    }

#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP

/* area_concept.hpp
8lwkHLrUqXCZmPQcUD3sL47hkc+Ev+Wph/GvYZzaJmSEv4XzaUh/QvyzYVsvlJHJttOvsW19rjJkGCsvrJMPjAjf7eTZ5n3Oi8/bokL0e+GyDnqhu8siB/JhXmGbL76k4DYPT8h36PzbYHb02LE637Zdm2TbrufSCtFzpvN09JlZ3vOwdXV0Thw/HsqeNjJsj9zn6qHM85zf4t+6GRk1I08dCp8fNj48Sc/Z/0wP952Ra4SRvoGaMDQzbUL+83X4tOXmOTaFZ58etkWfA41qHy+4H8Pzs++YXf5zkpZ/eDq//evQHb3GnJukzBfkK/NQv6xf9Jl83vEgQ7lOdFiIPciN1uMwfcTYoa4fwvPHRP1PHR6ucJI8M4vX+fLqaIpyusDf3r1MuRS4xkp87xFpo1j/qHiBHBG+A23OBZWU7byCZRt9Srzzz6ySHJvDsST59xuhrkgy57ls9kVGZN9sdnQY56yYusENjNWNZvOT5t8Twh3ZN//YfTE9ui9mb/fFiWnhNGGXyKkr05PsPxWjx8qhYzNzx2qq9h8Yqyn52EL//jGcdnaspuRjPhU2FtH/zthOycc6Knxsp+RjMhU25lPhYzJtrBKb/te7rnns5WfP3Dal4spKjUp/32Pnx4ja2bGdKlaNTf/12ft/qJVVr9LpB35X+5njf9pv18Zw6i2y+2Bg57Cj7yE6idAudPo+7MHa7Ml67M3m7MOj2Zed2I9b2VVkheWaxyvaZ3eP0PdzT7ZkL7ZmH3ZhP3Znf8bHZAn9HjA0p4qMyXK0dEuyA8uxIxN9hxcL65ckH0tCX+s3sT5vZmMuZVveyg68jfHlhf4I2CXJ8r4sYnncwob8ik2ZxfbcymP4DcPy3OsWXk7NQzkdxpZswdY8nF3Yit3Zmls5RCwPywvj2kb6Hr/PfPvxATbhgzyFq3g6H+UEruY0PsbZfIJXcE2edNJLFJ7OJyGdz9iEX/AUbgnpZHEC/x7S2crZ/Dak8x1D+Wg/X3h5XxPK+1o25EI25SK252IewxvylPfc31je/WF5K9mQD7ApH2J7Psxj+Ejeev4by3stLO91NuQbbMo32Z5v8xi+w7A8bdQLrw/nma8Gp7Elp/uvNS9gF85gd16UWF5oT87jkizvg5C/D3kwP2JDfsx2/JQduTmxvNA2nN2SLK9WqK+12YQHsjnrsiMP4nE8mIn9Myyvb5LlHRWWdzSbsAOb8xh2ZSf2YGfGj2eh/TVHJTmezQnrexkP4eVsxCvYgfN4OudzOK9kfMyA0J6as4RXZMyAW8Jyb+UhvC0s93Z24B0cyjs5jXdxBu9m2J9CO2nLSLI/PRWW/zQP4dqw/GfZgc9xKNfxAj7PxXyRN3E9t9K88XbQVG5e0TG40kP9OpNNOIHNmcmunMic43F6WM4+SY7HjcLxuDH3ZpNE+qHNMS9Okv78cDy+ks25gEN4Nc/nNUwcN/fK3U+W5qs3G8JYW29yP77FpnybnfkOu/PdxPqEdsBsLtbnG/Pr5D3ki6ewMU9lfH1CO14OED4XWZ/uoRx6szv7sDf78UT251auFKGNrra78eVU8u9lwkuf7tLnMLbncHZmCkczleM5ilM5mjN5BudyDFdwLO9jGt9iOj/kmSwl3QkszUwewEk8iJN5JM/msTyHnTmFYXs4MSfOs/IftkeSsc8aMZWtOJJH8Qx24Bhu5UwxJCyvcSiPWD2aKoqEsY0qsjhrsyRP4R4czT05meV4Ccvzz9yXt7MSH2IVPs3qfIU1uYf06rMMG1B+nEdCu1VuCutXgfNDfpqF/DRnbbZgHx7OgWzNwWzLsTyKGezIc3g8L2F3XspeXMDevJ59eDP783aexBU8nfc=
*/