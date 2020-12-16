#ifndef BOOST_MULTI_ARRAY_ALGORITHM_HPP
#define BOOST_MULTI_ARRAY_ALGORITHM_HPP

//
//
// Copyright (c) 1994
// Hewlett-Packard Company
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Hewlett-Packard Company makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
//
//
// Copyright (c) 1996-1998
// Silicon Graphics Computer Systems, Inc.
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Silicon Graphics makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
//

// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.


#include <iterator>

namespace boost {
namespace detail {
namespace multi_array {
//--------------------------------------------------
// copy_n (not part of the C++ standard)
#if 1

template <class InputIter, class Size, class OutputIter>
OutputIter copy_n(InputIter first, Size count,
                  OutputIter result) {
  for ( ; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}
#else // !1

template <class InputIter, class Size, class OutputIter>
OutputIter copy_n__(InputIter first, Size count,
                                       OutputIter result,
                                       std::input_iterator_tag) {
  for ( ; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}

template <class RAIter, class Size, class OutputIter>
inline OutputIter
copy_n__(RAIter first, Size count,
         OutputIter result,
         std::random_access_iterator_tag) {
  RAIter last = first + count;
  return std::copy(first, last, result);
}

template <class InputIter, class Size, class OutputIter>
inline OutputIter
copy_n__(InputIter first, Size count, OutputIter result) {
  typedef typename std::iterator_traits<InputIter>::iterator_category cat;
  return copy_n__(first, count, result, cat());
}

template <class InputIter, class Size, class OutputIter>
inline OutputIter
copy_n(InputIter first, Size count, OutputIter result) {
  return copy_n__(first, count, result);
}

#endif // 1
} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* algorithm.hpp
vVX0bnlmcKHfoUm2jjbHRuulP/jTCFvP9ZyozML8ju/3oPNqf9b0hZbIXQu0bbKcC4W2etSzGjpWfz8hUI+v5t51fV4kgriw7MTx/uc5M+hq4RiW3gDW9TiFcNPATaJgk4idWNz8wm9Bad3/F11nKOzMKr0odjfR2bKHcgonyPq5mhNg+mLhx5Ybx6lzp/r0M007cU3YHPxqZckd5hzq3mqc8RHOoRsE9XNPLRy1D5fOPLZx8O0GefUNvx+H8+jGctozcc3kNAfYxF0c24S7AoOqer2d7hwgbjVwMs+AvWYLx9U4V+qgewg5x9wLfqUFRxW0z2ac49V4eCC/b3uF84mBQRwvN3GKJN0Hfw+Dg5HQ0nnoni24kc4bJqeKKOG/3lHhfFJAOyd7LxNvxvPsvTnHjOf++5h4M54/ZxyKJ5XLvfdFfNOmkur7WaOtTFwryr3ytt+cNc+lXNb1HS7iMozz0pErox1tLbA3oebxdX4mQi9MXSu35VQjW/qGIo9npn341uCjH9XEHn5nqjctnF11+EkA+vM1ws9C3pfOqtJEJrt/ftcwcoxJTsKxbwY47pN3itzvPNtKn+XhdlraR/+KJq620ZO/v3mTt4eZazmJn93xBUO56i/q/nMz4SeeZSfZ//g21bN11NgO3sKeYfpsEWSB5dhx0q5QHY03349Ylvfh4Lc/gPz6+R9RJ+7MgCssliZm+3MLC/RmK+D7bxIusQlgIY75nQAuS3nuFK6HrZxWV/EMi6qrULbs+uEvqqvDHFftHp15GuG42ab91cBVm0XvnYwhzmNnfotuGRz+naG97CaHvjN0B1uTQ3vU6Q6xrcRZavPHLYY3/fHWbRw3/TE+znDyB93HLXGohWe0fFT7znbDPGlVDjob+FJK1T1i5w3vL3XDBPwGvqUCeum8IWJVOElq9fIyw2nKH8pPZff8H9AuvjUt9VJ8rlE4vu9yYAIOvJHMzj8SBu/RDMJdCsf3ZOT+Qmo7dsn4k53BPjbCuC06U8pwrnfvCGEUF3oHSGK1Pc0vj6CzlohrNgeUwdsjxEG7RBicrR9TOPmVZNMthEG8NPu1r54mxwSrk3KWBM9v6vZVnwd9Xu0FnBsQB2k4NIy4jrH8p7unTA729ugu+lETb5aRJ2JZgLjW2qmMHFfhk/vJ8APVvlX4eZCKO+WnjDOFo6B+f8xZxDAupE27d35EYRQ9auev/l7/bkSiiKzMzu/4s0Ht/Ngf+LpvUNqpFYTeHZ2/Wjgj23nlw+ffkL6am6iKP/n2LIXLZ5Qo/DKFQ/HR+H+l8F51T6XKI+mD1YnOUyb1Ak/4cYVP7ue4drfcXXW+KJJeFj+g4cqIzB8aMyic0kjYccIonYR9gmGQJpLDOqow8gOV60WJ1bZa6u74GOJkb1A+1fvchGN1IDk4N1mHa1WevV23VeF08AZnFvD1CXlChd7y2aZ4VF7JxicIY5MMhD9xnHAIBrjiEf4BwqlpYXF8+3aF99vjqN56npdzBujgE/BSOPqXsJIw/OhU4N3qzYYBRivCSKD3sBt4Ja90v3KA4/tkCBJ2ljDMdG5XDLC52f7aVB1lwocGOK7iQ6PO5Xca+GFD/16OwxUMiPO7Zx48bKrX7sAbJlxTr+0PJ1xXr70TRjhlB2F7RhBjSSdsgzDKqsGedcL0rNLOGI8auBGn1xFOWUXYDwijrKJ2ao9sp5aodNL3HHWjDK6F0JskdEcEYBjW/NZ+jDCqUPQd2vs7tKXiB42LFo8Zwnhf5XUUDhVdC/8EhWPDwvswDyE/GH0YwngcKM0MN/swDDP6MIgpe9q3nfowhLNGjvovhG/WfyHc6L/gvAdhrJGhOxt+y8dquVM=
*/