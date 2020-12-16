//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for all of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see any_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool all_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if_not(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
WL0ha+xo/6H9XiXeo+vv+B1NVMY4OsPhsAsshF5YCjNgJewBr4LZqgPrBR+AveFDMAcehGfBX8FB8GV4DnwVDobHYH/4NhwA34N5ug/TEKOD1udY+wvya9NBj0SuIxwNO8Exqqsfq7rucXAuHA/nuJu3f1IsfVQD3uyTdIo9koYPbP6+SCGdVfS+R9fCfXjd58hpjyPd38jsbRS1n5HsZTTYcf8i1X3Z9yt6FYoOTPcmSh1y0j2JdD+i8H2I7DqzhjC92aahp95rSPcZ0j2GIvYUctxPyGkvodh7B21zXO8oam8gsy/QAt0PaBu+spa1kGrjurW4i7u4i7u4+2S5D+v7f0V9w+JqvwKgFb7/qzy8C/IdquPj4s5W+4re+H3+M1mh79DSsjK//ePi6vKSFbVljdXl4WvmNsP2O9xOf62uK/+mO3Cto/CY3z49cL2y2pKGJXXlamtp7B1Z176xXL95VRZdg1d1DUslfI97jtXE+/wqF3Icd1nte4iOQGxKN9jSqyldUa7fyCa9yRKeS/hqCd/v9iBPHnGUfcmKUnaElm/jbRypE5nDIuMJyWCwF0i3mnSWi8zT7nbG5rDKzLX8upwb726yipHnWFh+7detqC5dWi8ynTmyXuLd7Vabdly5r6HOtp+BXqumSmy01b5xq8S7zR1mt7nK0vOZ8Kfdxa5dw5oXnf/01S5iC1pTEbY3+1WS3sOR94/FZqCMdsB1IvOYXDNL7NCr6xvC9mrfKOcPuP3rAuQSbkjg+4xWkprQmJqYlJqw8fcAedU/sBe5eJk74dE4O4jzT3+cDhu2aZvkjF3mG8hUe5DpeOUPzX7gKtOXcDLhFZyvwdfq/u9/5vwk1Rn9Gh97vW/7nJUNxm5T2qscu9YckzYnNsfbAs8Zx0y7EtnBxrZf6lRsjTt3U5ubzoHwfhO2z8/snhi9x/qgDP7pGdxj/fwLZ04umVc4fW5gA3htK3nR+6sT5/T3gM9z2AP+nRj5ewvZ7Oj82TaB17YTlUfimT3g07wx94BH5vT3gOeaUXvAp8kxcx1b+R9Jir6/4f5+Ldb9SfNwLH+N4w233S5rMvMtQudNe2/BfZn6iZpTJdew3VNTjH37f0Bgkd4TrVd/EEoqmE9WX6n19Sb9BftnlIXdk8bxBvspk/cp6af+/QjmnXTJp6Rrn/Ok81mPJKBLVb7qV9JE5VOmvTnlUeUz5PxOaVPa5wXnvMr5TG1fKk/uvIHfFZxcqr58SUNVbU1o/s/NIpdi2X4HdH7xe3JudsIZCWeF9bUraCGh+NlnBubcm36U9oKu28zFvV/SmJVwDv9ez++g5Jffk7d7+Y8PMvuW3Cty9yX4+9u11O3LycH+dnFqYt/UxCuPsAyLQ3+7U+PsTeV3zT+/bcOelEGs25LQlrltCSkp7VNyU3JYy6UoZWDKJKa+eTiX1D4hnT8782e6JykvwZvUJqF30sBUd/+UtnIcMWKfkZ7QVYL82S+hC9JtMlPdJKlx3YkinpnUJyEhaYI/SkIv1oxJIa0OqR0xzmtuHx71PqF67i5SvmMSPFreEyS8jt+2i91R7wzEGRwWJ7hPxngJb3RPwVLxX1atK3DcZeT6c+59t9dyeqf4D3tnAh9VcQbw93ZzkgWSAAk34Qo3hBuUI9w3BARERAKEQFIDBAgILVZAtFixRms9KlWqVPFqo+LRVitaqniWolZqPVDRUqE24oUWbf/77bez+3bfg4Ta9teWhcl/Z94355uZNzvfvJltjnTEjSnMuKGdyHT17/P1UbdwHId99a19zrGGvutxiVxv7VtsTbCyxM0jXc4xh3nnrb/INvHf5puk45BI3XIbhwxwGYdk6pjobAk=
*/