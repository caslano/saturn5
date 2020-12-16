// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::reversed_range<Geometry> >
#else
struct tag<boost::range_detail::reverse_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


/* reversed.hpp
1H1hVJY9+DlOarinoAOe1nT7Wp/nG02vMwHPcVX9k3cHHfocIfI3r+av1c+OuLu7l9XdPHU3PzDd7uFumbpbru5eDXCXrO6iQ7ibqu6mafmYHuAu/R7unlV3M9XdcwHuMtWdO4S7vuqun9b//gHuVqg7bwh3q9XdGuiBrwe4y1J3uUK426Du3tT69Za6m4nap+5y81+aHRrtprrr4vT1/4/BovBJmAL7wnkwDS5UebHKm+AAuA0OhrvhMHgMpsOvYE94C6ZAu130JT4NUcVGER8Z+/niEwYTzZcdsRcPW8IysBUsD9vC+oYb9acb7jLVn0R9LqPetoFyws/hK9cjoNwNBGvBlfBhlRvCsbCJ6jdXuQ2cANurfieVu8HJ8AnV76lyKsyA/VV/kMrpcBocqfpjVZ4EZ8CnVX+ayjPhc3C26r+g8jw4By5U/VdUXgFfgJtgJtyi5ttV3q3y+/AleAjOh9+o/lmVz8MV8GfVvwbXooqN8aXvdM2nGLhU8+k97BncC4vD92EZeAaWhQfggypXhodhDZUT4VFYR+W68BPYQOWG8F+wmcqPwC9ga5XbwG9gO5Wt8YnGt4bEN7h/8zh95SE3TIAJsDAsBEvDWFhB5cowWsvZPlT0WJ+/f6u/+eEW9fc27a687w8LQzvxSYIdYEvYUePZF3aGDeEw2BxmwBbweZgKX1J7i6AXroF54A5YAO5Xe0fU3ifQCb+DYfASDIe/wwh4Xe1dgzdRyeN8zzFM64sR38v6HG/puCELPgzfgZ3gFviEjnd76fi2n47Dn9Jx+Az4FXxe7b2k9hbB9+E6eAhmqfm7ar4L/gseU/efq/lJNf8WfgP/gmdgHuL8LSwAv4MFoWHvAXgFllC5rMqVVLbK8wTf878Zojyfc/jKx0+wCnQ5feX1AnJtlZPgJeRGKjeDvyK3Urkd/DdyJ5W7wuvI3VXuBW8h91V5ALyNPBQ6kdNFX8fFRkQn+uJ7SvOropH/2r510H67M6wNCUvi1Q220PFqK+3X28MBMBUOhOlwMJwMR8DZcBRcDMfA5TqO36Dj9S1wCtyl/ege9Xe/9ovHtF/8HM6CJ9X8DFwI/4Cr4C2zf+MZ1kAnNOy54SIYDV+FBeAKWFjNi8N3YDW4BdaE78J6cCtsqPaawZ1QvskLO8D3YGc1fwyehP3hKTgbnobPq7mR7m4H9WSyL92fcfjSvb6vnstfLa0ndWFdWA820Pl5M9gIttHxcgfVl29xwzTYHA5R/ZGwNXwNttF60h5uVPMtsB3cpfr7VP8Q7AI/hY/Cn2AavKjmv8EnoZG+PWEUTNP6Y5jnh71gcZgCy6n5g2peA/aGdVW/ueq3hYPgo3AwfBIOgb3VPA2OgKPgSDgRjoIZaj4DjocvwQlwMZwIl6v5apgBN8ApMEv1t8Jn4X44G56GmfCMmp+DL8NLcB68qvo34EL4D1wEHQ6fvhu+AvPDejBB9YvB1bCEyjoe5wF0nBdiPF5Cx10loYzHdLxXOmBekanuG0s+BY/HyRNxXxHWgZVgfVhVy1UV2Ehls5+7qv41CtHPndf4/ARj4H+gtF9aXsO0fbfDhipfg8VQyVP0vjTUETt2YD71t4XTby/9Pu1l3qe9rPu0d/w+7V29T3vRU+9ur2WAvar3aS85wN7ZbPZa2wLS7z7tZd7DXkqAvaz7tHf8Pu1dvU970dPuz17V+7CXYbS7aq+zS9fNZZyu9wN7fesSs+ADcA6sCefCZvAF2BdmwpHwRTgaRuWyZUyF85AXwPlwO1wIP4KL4Mdq7wf4CvIvcCn8DS6DRru5HBaBr8Ly8DVYHa6CteFqmAQ3wcdhFhwEN8NR8F04EW6F8+F78F0=
*/