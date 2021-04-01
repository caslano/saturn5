/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
t9Nhcu2VZHTdUYWalhttdRXgYZy3Yo/yNBqXvKsvqaPwShZFFn4f7F0H8x2G6zf/MhAnMidyzQdUVVpbrjM10WT4UYvdx5zUEzfesqUFuzKTGMbwuUMi5uKXSxEdVGxkUc7KG0dzNurDwuMfwhMmLViAWehFBTLnRa3MLADzkeFMmnc7s05b3d/LH4jAvRqR7mpqNgIOs8FHikCf+qjI5wgh2o1MefZiP5zQtOcGgOiveZhEc0amFZ4gjaj0ft54ZdrAL1Hpwz5XcWcs2+6ErY5w3FGkBFcfVIhGoTIOz76Npr2muDNjGJNgNFqlO33fdUgozTTml3R8uBSfKg5FEQMYs1D1djJ41K7cgvxP4uBO6P4woqvOxgkmFQScw3ZHS4LLusD+GOvfB596tEZU7dSWUT+kRUO14pvmvlR09TyxSrmp9AvwHVOL2dF/261tLXdfLVoDZpSEPZE+8dC0fKdCzP7SIl4zlNx3ubqsNW7RlgXRnl0vO2W26SsSBpb+UuuN+z+Sm9IUlMjoRTcYdwpvyFJEqT7nvukp31abFAvzk2wa9cAbK5NiIw==
*/