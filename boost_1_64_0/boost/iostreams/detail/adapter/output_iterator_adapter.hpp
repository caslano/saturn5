// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                      // copy.
#include <iosfwd>                         // streamsize.
#include <boost/iostreams/categories.hpp> // tags.
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename Ch, typename OutIt>
class output_iterator_adapter {
public:
    BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
    typedef Ch        char_type;
    typedef sink_tag  category;
    explicit output_iterator_adapter(OutIt out) : out_(out) { }
    std::streamsize write(const char_type* s, std::streamsize n) 
    { 
        std::copy(s, s + n, out_); 
        return n; 
    }
private:
    OutIt out_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED //-----//

/* output_iterator_adapter.hpp
baxhjtD3kGbhyT/KeXPl5olYk9MaUB3VThArDJ+s7vKFDSBNjbViUbJg49qCviYCu+5CRXgj5aVCg4aEhKz/lpcYJzPTnkEYVxLVRdOOyNteviXNao5vZupDzJlvmTCcR30A1krMPh6ju6fgR8vvX3LZX7o3jYNaPy2OKg14/fZbBxMfrYSxoYE15InfIy+wZONRbmMNU3xYx8HFrUJ98QFJfGoxD8cX4xJPcx9gem6PGCydRGIclQ6LEpfD4w2NUqxUEP1K1YX0ForNpAG15BQiyDg0vbLbRjnmH8HIyHPoEFbUpoyL8yUcwxq314AEL8hj1OAwp/RcgtOwUF1qPsNOv89xEp8tQV0eZxsDOcXwW+HU/D73Hg2qRBiiZxAH2VnwI3IVbHEyxOU4vUVvvkwEG9O/ZJdsZvbY/SAHX6cfN1TLTQa+GhXRf83DI+leuhQl2bKg2cH50OYSUz3LpNXnd91IM//NveN/X7VTQQA19uf3mpGzqqaYyvpfXL8B9LEFC0YYRQhmPqauL6jOEzKcGa5YI6WCqbhUtjmGVU47fMKg6vnkpF99Ew==
*/