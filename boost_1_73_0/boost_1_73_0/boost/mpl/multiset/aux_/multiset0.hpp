
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
9G3Yvfc+zyz+9xQlhPyFRq4P0OQHsfa2wTuG5unARlh4R1RwYzfa3RD2Gc56iq3RThe68hPudLrQDPbRq/FVi4QhXk3wyygMQ/UbLNNpmnDwLgPQh3HKkwl04TF/Wv3+E8DvMM1/5q+8mc1FjdGzBXp53f8AUEsDBAoAAAAIAC1nSlK3fWKBqgEAAKECAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODQxVVQFAAG2SCRgZVLfa9swEH4X+H84WkrGhlHSdmwEYUg9bzWkc1Y7Y2XsQZUvRMSWMknuZsb+98my2zzsSafju+/HScyhdYJbTAiTaqf9ccD+lza1TUh+t9qQtEFuoMLfjnzMqvSWpNuyKu7usy/brKwIoyc8oyMFOSfnUKJ5QhNbWSNhBo9N7wE1dzwhj7ruIxKRN5B2poFa1qC0g85iDU5DIw8Ibi+trxRGJI4jAtDrzliwUgk02Ph5Rke2QCr2KA4JeQ2LyysIPuHVTfHh4fviB/x5N//7DJ9wjE6OgtW0kajcZFWEi4fYECAhsuVHP/B8BaZ4i+NyQHTW6RYM/uz8HqHWaNXMQVABoZWTquNOagWDuJ+l4zAwoduWq9qXA/+S0ovboqzyzfJiIN4U9xV9f72gEHfDXszS
*/