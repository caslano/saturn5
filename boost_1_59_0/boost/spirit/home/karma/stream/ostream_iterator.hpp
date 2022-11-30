//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_OSTREAM_ITERATOR_MAY_26_2007_1016PM)
#define BOOST_SPIRIT_KARMA_OSTREAM_ITERATOR_MAY_26_2007_1016PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma 
{
    ///////////////////////////////////////////////////////////////////////////
    //  We need our own implementation of an ostream_iterator just to be able
    //  to access the wrapped ostream, which is necessary for the 
    //  stream_generator, where we must generate the output using the original
    //  ostream to retain possibly registered facets.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename Elem = char
      , typename Traits = std::char_traits<Elem> >
    class ostream_iterator 
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef Elem char_type;
        typedef Traits traits_type;
        typedef std::basic_ostream<Elem, Traits> ostream_type;
        typedef ostream_iterator<T, Elem, Traits> self_type;

        ostream_iterator(ostream_type& os_, Elem const* delim_ = 0)
          : os(&os_), delim(delim_) {}

        self_type& operator= (T const& val)
        {
            *os << val;
            if (0 != delim)
                *os << delim;
            return *this;
        }

        self_type& operator*() { return *this; }
        self_type& operator++() { return *this; }
        self_type operator++(int) { return *this; }

        // expose underlying stream
        ostream_type& get_ostream() { return *os; }
        ostream_type const& get_ostream() const { return *os; }

        // expose good bit of underlying stream object
        bool good() const { return get_ostream().good(); }

    protected:
        ostream_type *os;
        Elem const* delim;
    };

}}}

#endif

/* ostream_iterator.hpp
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
*/