//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>

#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct iterator_traits : public std::iterator_traits<Iterator>
{
    static const bool is_contiguous = is_contiguous_iterator<Iterator>::value;
    static const bool is_on_device = is_device_iterator<Iterator>::value;
    static const bool is_on_host = !is_on_device;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
YEppnbSMI/02jZMALQPTy4unWvamrBq2QIpr1X7cOk51hrW/lIvoNcaBANRhC/GT6TadyK3/qCu3Gr3+WqQJxT6VVWDckVb2k98XLI//TVjXtD6OBqiIzyeKokcIjyEh7pfDxkXVf3JCb7JPkXF+DkVCOhaGuZwBOi3/yd56RKJSNJp6Hr0G4g5AQFP6qqf2368I3FYBI7Dev/srp2FJVpojMc8MfMHKE1JSGOmk/aT0UUEOp9ARQlQ4sBixzV+Al3yKebW2HYgpMuL3erExyK5QVUEc9q/Xd+CxT0mxTSWTDskhevhihnD5xZjr3P5FtiHSFjKoQ+4BI6hSIUtoGGcqjcdJRG8BEFzJy6qki7iwTYFkj+759zB+hjlmLQs93dmZ7Fy1DZWTnYwq/h3KDwWZa6lsPBoxhALT4LfY5KB2JrAiWS2NkVWGcsc94v+J42d83gKMGwNC/lXx06NFUkxyF/UquhdF8tB21gnXfhDceZ77TsgS3fvlombaL8MfuoYBudDx+kSSW1IiF/vEFvEbhQg551FWQch8nkOnhgFM8xBKsKdlounmZg==
*/