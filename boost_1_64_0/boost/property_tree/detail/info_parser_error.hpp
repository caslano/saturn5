// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    class info_parser_error: public file_parser_error
    {
    public:
        info_parser_error(const std::string &message,
                          const std::string &filename,
                          unsigned long line) :
            file_parser_error(message, filename, line)
        {
        }
    };

} } }

#endif

/* info_parser_error.hpp
mhqlLGLb5NkGheLYy/C+Pp4uN5yJtwqSTQbdx4X+hYpgU/YGz/prST2VrIS1Uav9oPrXWv68VhPP09P6Ny7gr56jAfDfn7eXuiePSoTiJJYM0g0BmQ866+2U3cUFVekCWDBRjHlBrPBWmTNdAqAhel1xltbZGB4BVQIZXqK4jghyp0ilObJNs+sJiJ+4sawLKY9x42aHfmoPAKuOjLfJWEmR0Mq50NgrlfGfQSeQPROD6Z7eLaKMZUXdrTcWz0Gyxr7Q0HNnxCNxy3xYVhrvQJ7A7lksvFmiMaa19ITNdYFQKfPVfqQU/plDfnv92JYzskKURe/7DT63GiBQLWKhg83UdHiGel8LZ+J7jaEAS5cIsMDx96g9aXcZKaIsYmbSehoVvVtRhYNr0+Su3P4NuxYiirOsCFhYeYWFr/KHmDy0W7/kyA63VJFK8yZRDrUfe76qFSoaJtzXr2TzuRI3WatTsbwtr/qA6Ve227SYuGQ1+HgAvlupOw2ufoJ0Pq66f9y2oTtLF1xyfFXK/q7ihRfvboWdXRHew68w1CPSY9K1lOyP9PoNBvbMOA==
*/