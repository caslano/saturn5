#ifndef BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP
#define BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// transform_width.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// iterator which takes elements of x bits and returns elements of y bits.
// used to change streams of 8 bit characters into streams of 6 bit characters.
// and vice-versa for implementing base64 encodeing/decoding. Be very careful
// when using and end iterator.  end is only reliable detected when the input
// stream length is some common multiple of x and y.  E.G. Base64 6 bit
// character and 8 bit bytes. Lowest common multiple is 24 => 4 6 bit characters
// or 3 8 bit characters

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include <algorithm> // std::min

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<
    class Base,
    int BitsOut,
    int BitsIn,
    class CharType = typename boost::iterator_value<Base>::type // output character
>
class transform_width :
    public boost::iterator_adaptor<
        transform_width<Base, BitsOut, BitsIn, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        transform_width<Base, BitsOut, BitsIn, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    > super_t;

    typedef transform_width<Base, BitsOut, BitsIn, CharType> this_t;
    typedef typename iterator_value<Base>::type base_value_type;

    void fill();

    CharType dereference() const {
        if(!m_buffer_out_full)
            const_cast<this_t *>(this)->fill();
        return m_buffer_out;
    }

    bool equal_impl(const this_t & rhs){
        if(BitsIn < BitsOut) // discard any left over bits
            return this->base_reference() == rhs.base_reference();
        else{
            // BitsIn > BitsOut  // zero fill
            if(this->base_reference() == rhs.base_reference()){
                m_end_of_sequence = true;
                return 0 == m_remaining_bits;
            }
            return false;
        }
    }

    // standard iterator interface
    bool equal(const this_t & rhs) const {
        return const_cast<this_t *>(this)->equal_impl(rhs);
    }

    void increment(){
        m_buffer_out_full = false;
    }

    bool m_buffer_out_full;
    CharType m_buffer_out;

    // last read element from input
    base_value_type m_buffer_in;

    // number of bits to left in the input buffer.
    unsigned int m_remaining_bits;

    // flag to indicate we've reached end of data.
    bool m_end_of_sequence;

public:
    // make composible buy using templated constructor
    template<class T>
    transform_width(T start) :
        super_t(Base(static_cast< T >(start))),
        m_buffer_out_full(false),
        m_buffer_out(0),
        // To disable GCC warning, but not truly necessary
	    //(m_buffer_in will be initialized later before being
	    //used because m_remaining_bits == 0)
        m_buffer_in(0),
        m_remaining_bits(0),
        m_end_of_sequence(false)
    {}
    // intel 7.1 doesn't like default copy constructor
    transform_width(const transform_width & rhs) :
        super_t(rhs.base_reference()),
        m_buffer_out_full(rhs.m_buffer_out_full),
        m_buffer_out(rhs.m_buffer_out),
        m_buffer_in(rhs.m_buffer_in),
        m_remaining_bits(rhs.m_remaining_bits),
        m_end_of_sequence(false)
    {}
};

template<
    class Base,
    int BitsOut,
    int BitsIn,
    class CharType
>
void transform_width<Base, BitsOut, BitsIn, CharType>::fill() {
    unsigned int missing_bits = BitsOut;
    m_buffer_out = 0;
    do{
        if(0 == m_remaining_bits){
            if(m_end_of_sequence){
                m_buffer_in = 0;
                m_remaining_bits = missing_bits;
            }
            else{
                m_buffer_in = * this->base_reference()++;
                m_remaining_bits = BitsIn;
            }
        }

        // append these bits to the next output
        // up to the size of the output
        unsigned int i = (std::min)(missing_bits, m_remaining_bits);
        // shift interesting bits to least significant position
        base_value_type j = m_buffer_in >> (m_remaining_bits - i);
        // and mask off the un interesting higher bits
        // note presumption of twos complement notation
        j &= (1 << i) - 1;
        // append then interesting bits to the output value
        m_buffer_out <<= i;
        m_buffer_out |= j;

        // and update counters
        missing_bits -= i;
        m_remaining_bits -= i;
    }while(0 < missing_bits);
    m_buffer_out_full = true;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP

/* transform_width.hpp
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
*/