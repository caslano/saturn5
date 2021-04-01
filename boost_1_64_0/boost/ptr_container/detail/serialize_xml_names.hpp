//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_XML_NAMES
#define BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_XML_NAMES

namespace boost
{
    namespace ptr_container_detail
    {
        inline const char* count()  { return "count"; }
        inline const char* item()   { return "item"; }
        inline const char* first()  { return "first"; }
        inline const char* second() { return "second"; }

        template<class T>
        inline T const& serialize_as_const(T const& r)
        {
            return r;
        }
    }
}
#endif


/* serialize_xml_names.hpp
0IlkETWoUnS9j9Ba4qpz1p6xQB42WC6ccrDuXN846BOotIf3gKKaR8050w3xeplPbFfb+WFWc6/urk5XUvqxteet0ZV548y365viNkHGTQ/Zlbf3xmsYLVpoSip8GuXOCe9DHFWCqKNbpy9pwb1TSiDo/PksJs7sTFB2NvsrdOW33dTarfyRzlJLpWFC1IQhSqnTqwd8tsfgIMd1ss0LZpw13R7FM1MmNo2A+VXJQAr67qosulJfFHzdEZADjGil+TXB5E6XlO4kaZefSqbh2UFekl0i8iVGAAAAAACBMweuMaKDP0RBB177P+5OW3zDZ1hPi9X6YZJLRH8So3fTiZvXBpB+dFwDOyJYv/Q8yoMA5ZQEmFE+Ah9i3LlScskfNKzKNRiELSKhMIA2MsLmoKQZkD9fMATTVmPKpK9AHUlxQeGhh1QIw84UaQROcmiiwym4semdWnkqeNW+2ltXfpABcocgonP2b3zfSyEbEgUqkuLvq4pEoVF7UcncsNkRkMFjwiXvqjuTdj/EAz3sMvuJEHzB0ntMArVVI0ImjR3SHWrvQlUG8w2rgQ==
*/