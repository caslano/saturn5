//  Boost string_algo library concept.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONCEPT_HPP
#define BOOST_STRING_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

/*! \file 
    Defines concepts used in string_algo library
*/

namespace boost {
    namespace algorithm {

        //! Finder concept
        /*!
            Defines the Finder concept. Finder is a functor which selects
            an arbitrary part of a string. Search is performed on
            the range specified by starting and ending iterators.

            Result of the find operation must be convertible to iterator_range.
        */
        template<typename FinderT, typename IteratorT>
        struct FinderConcept
        {
        private:
            typedef iterator_range<IteratorT> range;
        public:
            void constraints()
            {
                // Operation
                r=(*pF)(i,i);
            }
        private:
            range r;
            IteratorT i;
            FinderT* pF;    
        }; // Finder_concept

        
        //! Formatter concept
        /*!
            Defines the Formatter concept. Formatter is a functor, which
            takes a result from a finder operation and transforms it
            in a specific way.

            Result must be a container supported by container_traits, 
            or a reference to it.
        */
        template<typename FormatterT, typename FinderT, typename IteratorT>
        struct FormatterConcept
        {
        public:
            void constraints()
            {
                // Operation
                ::boost::begin((*pFo)( (*pF)(i,i) ));
                ::boost::end((*pFo)( (*pF)(i,i) ));
            }
        private:
            IteratorT i;
            FinderT* pF;
            FormatterT *pFo;
        }; // FormatterConcept;

    } // namespace algorithm
} // namespace boost




#endif  // BOOST_STRING_CONCEPT_HPP

/* concept.hpp
G7OPfmEktquCl09lWQjzk3Lyb74bfsr3/82m9LtWI0v6vUa//SazsPgAhf5IJXsAstvxEg9yiHQML1XN0WoaFzz7NFsbxtatx6Zg+xBm66YLWzdGvbWG2TrWMWPGCg66okRSvZs/nxd7MDjpxLOPo6Sa+huOeVKPquk1rnemGxcRE7wLtyAvsdAscqUmpWaIlTIMYZCe5CYtz3fM8VHnsnDQ1w7tulC36zJ7u8arVmuE7/ppLbcPTKW4vd1rq2hoxIqiqaKXHueKWqOit/ZJRd3tFd2s3nxRKrqbKyoZRN/nrWUT7DTRTibBmkhCWbcFFVhqbmrXW6WhwG+TID27AEuLJdfcQFUfP40ir4HR5B7o0TV4VPnevkYbbJfuZjnxp9pg+/fYa5/tv3LytZmbzEsXBjQtKKEt8NUjX4+rDi9Y4u1btY/VXepZ3AQopYF46ZCtPPBlsYwiKA/LjYttUB4NdcduhrpAK6fOghgSP+uDGS8nyAP09F3mrXID51TiSlmZ/pe9T6Xx/X+jHopAhvEdRgEMaMpB9Y11pckZj31ZhxblVtVuKfdimIGlknssmNOW5LHToU3PFkZE5tKt8NjfLbScPV2BK0hJTRqb9+/Vw3owp4G2gZ/k5KGIxVCU1KDOz9pJ67isbwjjdrYbSDsrd5RI4zFiA48HRdvEgEBqyT4ODvgaqDorTfFrzhx+ninBG0VecN1yfHVl7MKA+GpQj44BQ0lzDmbNQ3OLbWgsx12LdlsD3BCkCMtE/fwoj261AsZ9PobdhRx18D5AFscgTXx5v/CHD0+4/GO9eTXJ28uSBle/t1XOKmt7QPa1n9bGsQ+YUMXTFCYUm2203mCLKiGWPJV++y0tjhUoakvRW+bJ8nI9fbJkHDbyViAPjoCMCRNhrg2qdg1UEIyMufDvRe+pWYuNrGkQFHjzM1Zk4oJVsJzFJYMfNZaTBnG6KwMOnL35sxcWkKMkvlW5Mjbig11k5e0tiHICCt8HuTI2raO5YQ23vMUS4Shjaz4ZGeMxNCULZ8zwLIqL9KTW09stFLsL+4cY5+8Hit17rKq5mo+EBzCn5FhnBigyzWz3BTz/XynXm1pA46WTOeNFZDKzQyNNck41bzEPP0V6rk9LK1O259a/MIJzmfBk0Ddovr9IExKzQ1xV8dUv8CNOFv4GAzBEVlNf3UW5rnv2oZnsX90tEd577eSzGD3wCl0sNamlqvts6FH2Y+3ow0uULe8+oX7s5wIpu6nx7dEwgnxFQ6YRZNQmG2Sahrx6u0DeBUh6UE5QK+/jvlpWu9bOw2iw8e5DUuJKpKPRCL2k4tGf9K6lrrs7cqt9K7yGbzGrNoDutKTqBsG4YWG6sYtdjxCv0QBFvMbshYRpn0Ni/2yTc/U2EHgYxLqNv/PaYB2RFICIvyit532NIOPTlc/VewtDzb4Tz380TcyRU9f/9mdq8/Sm6DN+3UeydD8LMFRd8CZcZgCVKRiKJaLtSwowaWx+zC+Ogx/1wDitAWGlzJ3PySCch0xr9huYsx/7tuSehIYEzzuNw9QsCn+pOi9Dx/VEfhRlDm8TrCwmxtctwVI9SDPzJW4zzMW4jZ8op/4bFgFzoeWZAOn0IK+yRihcky0UUDjL+JVKb8B6KZlLsQyAhoonQkDJ5CTT+LtquZxNQpicZAo5Wf0e46pN6nvbNhGer0oup6gPQMShy8BekWIt8OceDeb09RKZBbklDkdviXQkJVL53quFh6Lvs4ELaJI1mlVr+Gc13aq71oiQLJOsn7MOE1vTaCuzNSrq/5rxZ/xnP0+CBfq9YYM4X2L+iGZMvcBv6jPMACPWccEQ6tbdNFP9eJeUrD8TqXs5+bs=
*/