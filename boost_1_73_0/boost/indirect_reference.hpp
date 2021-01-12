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
bqstF6x7BYJA+iPTQdv76D0IUDfaTbb10QLRV1AhHsC8QF24UXxoAONm2KBJxIT1HTJzZDXY6bUPsfh6KRxqhEbT+19Yq0MWqm0Xk/Lr7rkICcB7GqVbRWnHJaQbVeQTx59YZTF30I0XrbzanvOQhGFXMFaDx3tAduPpWXgynp7BG4gX4h4tRM/TczjvRs4rupqjOqbt9f2My66IoFLkOfbRwhcA8hq+nArUrQPCKE5VCFk2
*/