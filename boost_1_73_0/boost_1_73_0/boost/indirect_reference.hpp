#ifndef INDIRECT_REFERENCE_DWA200415_HPP
# define INDIRECT_REFERENCE_DWA200415_HPP

//
// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// typename indirect_reference<P>::type provides the type of *p.
//
// http://www.boost.org/libs/iterator/doc/pointee.html
//

# include <boost/detail/is_incrementable.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/pointee.hpp>

namespace boost {

namespace detail
{
  template <class P>
  struct smart_ptr_reference
  {
      typedef typename boost::pointee<P>::type& type;
  };
}

template <class P>
struct indirect_reference
  : mpl::eval_if<
        detail::is_incrementable<P>
      , iterator_reference<P>
      , detail::smart_ptr_reference<P>
    >
{
};

} // namespace boost

#endif // INDIRECT_REFERENCE_DWA200415_HPP

/* indirect_reference.hpp
8WAma1FkV/ArnacZv+diyNKrCWxzfq2zQ3jZgnb9jcGKdeYbq+wQ/7V5YD76rc0L8MwTPWv9nc4L7S0N7pLndG5i0tUfOyyE2BNlb5jZ9/cFdXq2CpVdSzR7/MGgZQM4H4yrLhfNx38suImeycKO5dI2BfvMP2m0aNvelFHtXC2PiQ52E3/WmOGsitB98hedGK3ceqMLuS1q+ledG8wfG/WevzlEcf3AauDvOi2g5zdi/sNlBrkn0V3yT5c5EK0=
*/