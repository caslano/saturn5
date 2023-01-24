//=======================================================================
// Copyright 2002 Indiana University.
// Copyright 2009 Trustees of Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP
#define BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

#include <boost/operators.hpp>

namespace boost
{

namespace detail
{

    // Iterator for a component index linked list.  The contents of
    // each array element represent the next index in the list.  A
    // special value (the maximum index + 1) is used to terminate a
    // list.
    template < typename IndexRandomAccessIterator >
    class component_index_iterator
    : boost::forward_iterator_helper<
          component_index_iterator< IndexRandomAccessIterator >,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::value_type,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::difference_type,
          typename std::iterator_traits< IndexRandomAccessIterator >::pointer,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::reference >
    {

    private:
        typedef component_index_iterator< IndexRandomAccessIterator > self;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::value_type value_type;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::difference_type reference;
        typedef
            typename std::iterator_traits< IndexRandomAccessIterator >::pointer
                pointer;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::reference difference_type;

        // Constructor for "begin" iterator
        component_index_iterator(
            IndexRandomAccessIterator index_iterator, value_type begin_index)
        : m_index_iterator(index_iterator), m_current_index(begin_index)
        {
        }

        // Constructor for "end" iterator (end_index should be the linked
        // list terminator).
        component_index_iterator(value_type end_index)
        : m_current_index(end_index)
        {
        }

        inline value_type operator*() const { return (m_current_index); }

        self& operator++()
        {
            // Move to the next element in the linked list
            m_current_index = m_index_iterator[m_current_index];
            return (*this);
        }

        bool operator==(const self& other_iterator) const
        {
            return (m_current_index == *other_iterator);
        }

    protected:
        IndexRandomAccessIterator m_index_iterator;
        value_type m_current_index;

    }; // class component_index_iterator

} // namespace detail

} // namespace detail

#endif // BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

/* incremental_components.hpp
s3ZiLnOsztIr1TwcPrWWIp+fr8FgPxVIpQl57WAetK1HKmyXHK24ZhSG6F/Yub8kRpfFLwPDArRnRDudxgbAPT6Lp9/QHYfHxYmql7VZx8NROD+uhqNWMckIxYRPMNP8zg2qYMiaMMfMNpV8PCb8848i6Rz/AfScmHHZaGxHzainpf0y/q1VGxM+f04VDKoKxjIuGFejxJGy2ApIkPO0wa5IRqsiGRfpA6OE0OTICRp9Q6RgtNPqC9ogtoG2t0UGFwpbGcDt9I1R2iB2NN0XkdFCZ7SiYHixTf959AtRMNgcCPAABOPZ0SHBoKpgUEENuvWcZ2FsEAzKBIOqgnE84GyWHO30WWi+9t77mGC000+fUAVjIQpGlR8NQKJqACg3ADhOPweWA81AK33HppiBilFoBtpZr8rMAM3jFgaNwW6F5dvhTYiGK5iSXlTNQjto2IHRA81CG737w0ju//uFSKZazitaFh+RUU/L+mX84pyW+x+cHcD94o4PFbMwFbmPEv4fM1j/l0QqW4mZnrLhzG2IAvTdO9EpC6E038riQopk0H+M6i8X6z6IlIvmDyPlwnFOCe5kRmSMpr/+MFIuks4pBuMiPTdSNRgaudiacD25+Ph/VIPxA3KxFRCp9SxQ5OIo+EbYMUytfQHlonQbl4vKweXipFTZhqKRNgcngUgrXWLlnquYcgj3kKRVtplr/oCS0AdUAYMwO7Tu
*/