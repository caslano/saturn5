// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<bool IsSame>
struct translate_int_type_impl;

//
// Template name: translate_char.
// Description: Translates a character or an end-of-file indicator from the 
//      int_type of one character traits type to the int_type of another.
//
template<typename SourceTr, typename TargetTr>
typename TargetTr::int_type 
translate_int_type(typename SourceTr::int_type c) 
{ 
    typedef translate_int_type_impl<is_same<SourceTr, TargetTr>::value> impl;
    return impl::template inner<SourceTr, TargetTr>::translate(c);
}

//----------------------------------------------------------------------------//

template<>
struct translate_int_type_impl<true> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c) { return c; }
    };
};

template<>
struct translate_int_type_impl<false> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c)
            { 
                return SourceTr::eq_int_type(SourceTr::eof()) ?
                           TargetTr::eof() :
                           TargetTr::to_int_type(SourceTr::to_char_type(c));
            }
    };
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

/* translate_int_type.hpp
5qM0fb/JpyvcaZiqmKqLwarb76RdiQ+w1CUufupyyJi74K7rBZjPcl+dCUMMy5wHNpnrcAHFcCM2b1uMC5wRZpkApkqcZL9wTrVu3WsSKz/Uc1GaQD5pZ6rz+i2jdzdf+dRnDIru2skLjErSl363B6It2jA+wz+7EL2yGwnG/fEijdBxNNipS5LUNSZEgtg1gZr4zIY4KBMdqpFt0KxrPlA6wlwb+W36ezl+6TRzzWA5xsL10IT7kobhyOBunAS7srqZPM5U5PKG3HJRbLj4K5F581WHn5uskmnBxo8Mi3+5Tlu/ZNp4pt1i0I49dMwz2tOTvcG7Z1tUa6DF/NyZTPy5u1HvHus4WP/WH93xIvD+5RPg6Y343XvfVnn7Hw/CwNKpljNHej+tzKCnLwDdtLNuOPL+V8C64oK2brFyJVUtgNFefT5+2Vm9QDsl4L4sqD+ePL8m7lpwDx+NcTyoTAiWnsDnx7eRmYBnqyQ0GurHZC+y1zETTzeuwd2FAOiUs83+svv+Yu6l0jqFHCsk51Up984lx/S3EDCRnb594iJhuVLab7ZpMBprrpYT9xcH5Xt2iyB8V9I63HGU2l8O7hJJtmM/NkRZiXz3nzmmeEtxLpPs5jn0qvTy7Q+oNL4aN756KHjl54J3bUd1fc9dPeXeHsnamsRQBb3EHLvoDd5akmhpKr24RFe2Ow8BmG4Db/pSh1uEaBAmUoJ3
*/