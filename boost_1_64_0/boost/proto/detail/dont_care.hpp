///////////////////////////////////////////////////////////////////////////////
/// \file dont_care.hpp
/// Definintion of dont_care, a dummy parameter
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007
#define BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        struct dont_care
        {
            BOOST_FORCEINLINE dont_care(...);
        };
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* dont_care.hpp
6HnTterCIcb26cCcKgwzWUVH6+xkdibMJwS3a/2q3O6dmFY5p4+n86ky754S6GtmSUz0VQo8l+KWGYDiraytBOjFSnUtCmyaOSqhRBQVQnReWyPXiCjjYRmy+lh5obnZqnR6/YQ0z9hZm2SGZDLWi7O7dqHHZGBLSyRJTC7r7BaG4LaUwCJp0qSJmNMKVSCv1RzYYoaKsbNrfblCJjvSe/D6IZGjrwtBNQOsv2CVVO5yPeI/zIHxLPCzAm83vd/P71dRCISmr1Tp6hSWaXTKWqtjRj914az8ZHlGe7bZFF4zKPq9vgeH+VvrXc5ePnFi7RSl4qO3Via8Pnr/EJOAeZgTPbf+6mPE+vYuupzGVyxmRt0IYtiYttqID9yXB79K21rq4Pkia2VpvvVrYjpWEqrwB90blp3IOBKquWVRP87owhPKBJ+286ZHCY4Om80wyaEdYAg3qNlKAgCy8DOtZKyzEg5nZ/rOPXvOVGeVDlsYm31+ci0E+TKwH3gVDT01pNtJNaRxfFLhSDjUV6LipJwGXqnv+eTLFosSV1KmiV7cUV491b8dCPAxng==
*/