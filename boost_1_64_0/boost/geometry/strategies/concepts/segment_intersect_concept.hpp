// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP


//NOT FINISHED!

#include <boost/concept_check.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for segment intersection
    \ingroup segment_intersection
*/
template <typename Strategy>
class SegmentIntersectStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define return_type
    typedef typename Strategy::return_type return_type;

    // 2) must define point_type (of segment points)
    //typedef typename Strategy::point_type point_type;

    // 3) must define segment_type 1 and 2 (of segment points)
    typedef typename Strategy::segment_type1 segment_type1;
    typedef typename Strategy::segment_type2 segment_type2;


    struct check_methods
    {
        static void apply()
        {
            Strategy const* str;

            return_type* rt;
            //point_type const* p;
            segment_type1 const* s1;
            segment_type2 const* s2;

            // 4) must implement a method apply
            //    having two segments
            *rt = str->apply(*s1, *s2);

        }
    };


public :
    BOOST_CONCEPT_USAGE(SegmentIntersectStrategy)
    {
        check_methods::apply();
    }
#endif
};



}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP

/* segment_intersect_concept.hpp
jgcqk+dZly+wC19kL65nf77GR7mBLUqoR2zLtzmY7zKF73MSN3IKN3MuP+N9/JzP8Au+wK/5GbP4K7dyj5L2Q7bkNvbhDzyZP/Fc/kLnYRVFfWJR3sDivIUl+DxL8mXuxb+zLMuXsn+xMSuyJfflQFbiaazKCazGmdyPl3N/XsUafIg1uZoH8U0eTPcERQ5hK9bn0WzA4WzEUWzCC9mMV7M5H+ZhfJIt+Cw78x88jv9kF9Yp7bqZh7Abm7I7j2QPnsCe7MtenMTenMI+PJd9eQNP5HIO4EqexHd4Mj/gKfyIp/KfHMKq9qehbMthbM9U9uJInsRRnMLRPJcXcgYv4rW8hEs5k7dyFrfG28GEttLqbPgeK3bc2hSOaxNKqq+cyIY8iy04mT15DgfwPC7iNC7jdK7n+XyDM/gBL+IXvIQ/cSbLFJUfNuGfeBjncBgv4wJezhd4BT/hPH7LP7OaPM9nTS5gI17NI3kNT+O1HMZFPJfX81Iu5p28gSt4I5/mTfyAN/Nr/o37xq5bWI23sSmXsR1v5xDewVQu53jezUW8h8u4gut5L1/jSm7hA/yJD7KW7fAQD+QjbMc1HMQneQHXchaf45+5jtfxef6NL/AuvsiH+BIf5hu03f0OOKeNtnNGuD5t6t9Tw3Z/K2z3jWzIT3kcN7M/P+Nkfs5pzOK1/Dtv4VY+z2/4Kv/BLdzGb/kDixWVNg/mz2zCX9meRWL3LSzGoSzONJbgn1mS17EUl7A0H2UZruFefI37sKN1K89erMAMVuS53JczWJmXsQqv4n68ndX5EPfn+6zBT1iLDZRbHbZiXZ7KehzGxryATXgrm/JZHsosHsbv2Jrh9/057bq19y74+/6qyqUGa/JQHsA2rMXTWZupbMCz2JAXsBFvZmPezkO5is34AZvzRx7GmtJtyfo8nI3Zms15FEM+c9pva4dYMJ8dQ73pGtI/nnN5AlewGx/iSSzps6dwX57KVhzEoziYJ3EIUzmUsziMcziCt3MkX+FobmAa7WNFOnVwjyCWig2ibEfrItLFZAeouSLlDYrlYp34UpTdoKxEd5EuZotlYp3YLEq/6RwjOokUUcSyN93h+uIx/77TZ0UN0/pztlgu1oqN4mdRY7k0O1qmKHuM+cUMy+nKIWKqWCu+FCWOVZ9EOzFZLBarxKtis9gmKnWSH9FVpIvZYolYIzaJb0WlzuYR7cR0MV8sFxvEz6L8cdIRHURvkS4WiKVincgS1bpY7puWwUFiupgrFovl4lXxrSjbVf0Q/cVYMVXMFyvERlHkeGmJTqK/mCpmiyVilXhVbBOVTpBn0VUMFNPFQrFSrO0o79wsinSTf9FYjBKzxTKxRrwqtolm3V13+0xXDhHTxWKxXKwV5XtIQ4wSk8VssUysEttE2Z6WIfqLFDFTLBNrxZdiTawe9JJf0UFMF3PFUrFSbBDbRI3e/i6GiHQxWywTa0SWqNHHNheNRTsxSGSKGWKBWCpWirXiS1Gir3IS9URL0V2kiOlivlgh1ossUaSfY4ToJEaJ2WKpWCc2i/L9raPoLYaITDFDLBQrxXqxUZQ+0XqKdqK3yBTzxQqxRqwXm0XZAdITrcUQMVUsESvEWrFBZInSJ8m/GCimitlisVgh1ohNovRA84hOYpSYL5aJ1WKjyBLlT5aeaCl6i6ligVgmskS1U+RFDBRjxXSxUCwTq8QmsU0d+ZnVTrUc0Un0FylitlgqVoq14h3xs6g0yLyikxgipoqFYoVYIzapGyXekn/RQQwRU8VCsVZ8Kyq9bRmiv5gs5osV4h3xs6jxjvIWKWKGWCJWiVfFt6LGu5YtMsVSsVGUfc/6irFisXhVfCuqvW8=
*/