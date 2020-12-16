// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename MultiGeometry, typename Predicate, typename Policy>
struct multi_modify_with_predicate
{
    static inline void apply(MultiGeometry& multi, Predicate const& predicate)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, predicate);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP

/* multi_modify_with_predicate.hpp
eZ9cu7klYW0r75Wj8NrWze0trTgvT+F17etN/Dqxh/pqosHyj49khk8AnVVuO114nNujFz4XPBCPkukwu0msqLNBnuv6KuRt+ouv1eLc7FTPhq9B2NvrwmhLZI/Ip4D9+4ZF2OLhN8Vt5d+d3ln4bUj0eItx/umbwuZcaXlcxuwtM+/vTpI20bOy+7agt9fSa2R6xgIdnzPfpWNLLSZ+493xbN77xoYyqb2wqeBh33BixAAJxrzs3dcYI5mAn+sUP/nqQO5tmlbkPmkDrmc7Ahx1buh70O2vCp39mvKdf0DhG+mLqL29PxS0x8yH+Aho3+S3LcyTbSp3n6TxkxCcjMrn5mw+wFH35ysa5tM0blM0tBxuD8bTp85fKDlqHu6m+FBbFa4nVs6/hJwXh6XTeg37dq+wb/eperqHwvejrmTZf0Xh0Dy0roOvg9m+zPDI+f1G2dNfU/gB+qQcfgt9ulfhHgrBfQj96EGRx+9lOpTpDyrdH4Uve0jNTT3M9QR5qLSPUljyr+MfE7R/oGg/TmFZHq1DT9ay38x7XkEr2zZA62lCkO0rDRxZb3+X+aMtrwhdk2htUasSDNBvRf9CrUU9i/r6lxz/qrh/C324W6xteHWirkC7oC7ox0ypczSmAje8n4n3RQeSo5kxn30Rht4fVZfNtzAk3+kq3xnId2YIrt5zdzRwZ0/E49io2foFHjnMPB4jeHxRSL5Fise5yLcYuPBPcbbL4Gt5TvPmIc18pMH+qrA1GqxV6jqf4S0EjVKV7y/yrMseizRlSBM6bzYpPZxSVFGnzv2Ab81vZR3ubEfeEaTLt86EtDz/WIO0tXVZHa4Q9XSclIGgs7gOtOTbg6BVjzRLCtR8kBzDiXmL52qD9+3+h8L6vt1pde6u/THsJZhF4XqPlmZdQ7B05hCswcLG7Dv2fH8jwZss3N01Ymki39Ue1kcBW0C4bSH7gxfV4R4frK+WU3iLN359uJrg2xyc/sGbDAQb9LBYDLyXEGwMMItJ8FW40+f4OunfxO3dKOqlBA3MM1dLqDqtSmfq/GWizk9A/Z0OX22J5cekkXtot4g9IVv5d6nzSXE/8lnRBL27MEL13oj55xNF2erz2wx7X7Pz5zs3tnf0mOuhcfUU/dzQSRd1dbf6919NG4+zqUNgGZzC8ThtW9d0ta9V44SlxKNlw06Z4Ra1/tHksH/cMjzSsGzkZ22xHOsukzaK4CehnSyvE32KijtZ2kfQ0Db8FOCulPYCuHovhry37hVId6pKZ+jLtTid7jSkW63KN12Vbw3wWlQZCA80xdoJcNcB196Pp+i3KfrtSHO6lJ+KWy/zBg3dv3QAd2MIn20K91XA7VI2Frjh8oaN7UHaTSFpi5TMddozkXaLqiudr66rs5DubJVO56nTvQbpzsmTn8HV6bYhXW+OMjbWYY+zSFuLMvYhbSw8T16f13n2I91AjnRF+HS6BNLtUH2bSKfSTPOGkGYYaeCbIg3w5f5w4I9p3QrRwyRwU5o2cDXtDPB3K/6BH8r/XqTZJ9rZf1m7Ejgrqyr+DYwDGtUbRmVEtBGG4TEMBMMSoiEzwyAgDBMDiks+Z3kwI7M8572BwZTQNHGN0hR3NBcyt8zUzIrMSkvLMtPUymwzM9cyM8vOvff/nXe+M9/3eE/i53O+e86555x77rn7tjgkvrHzp0Lin4b4p4v4JEfsz5I+4vh8utLsN9C8RnhbwOsMXceF1A+fAe1ZoXVVtP9/FvHOkWlU8XQaz0Wc83Q+II7OhwtAf6GiL2Jf9/0c86Kg3ybp0ScLu6PiC6C/WNWHRao+/CLoLgXdO8VyDRn9LF5DpgfVuzsC9w7OqTTtuRtQ2F4=
*/