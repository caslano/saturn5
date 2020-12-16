/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for vexcl
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// specialization for vexcl vector
template< typename T >
struct algebra_dispatcher< vex::vector< T > >
{
    typedef vector_space_algebra algebra_type;
};

// specialization for vexcl multivector
template< typename T , size_t N >
struct algebra_dispatcher< vex::multivector< T , N > >
{
    typedef vector_space_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

/* vexcl_algebra_dispatcher.hpp
mZBrh/1mb6oAGD1fKkVZdbhInSsfOUHODI/C36WwvIwv/8IJooka35fo1hkHTj8IpU4n+nr4bk5OLHSg316/S63FdlXnEfrNPONDLN9olk/uEPMt8fHhueNexH/Y4eXs7Z5OZvd9M3u+pghxBV6iu1ONkcUThjdGHkH+e7h0vck4HIM6/tTbXcq//2lQ8ENmffO8OltdAvxL3jq33zGXdyXHKHneEF239UKtWwKTM5FB24tc7wwjva/Dscam9ka40syNyhCn6XZNMx5xrDPSc9+H3wfxnOvQP6jYO/Ch7y77ARtZtmHYoXsPUJeN9mRlr5og30lu4rp4LX7dEe//1kyQedwNxDSoNTfSO3uuVfq4yfKiPuoM5gbFB38H9wGUbGspG/NVeQay1ZtyEB/61jaB2GnAcl6v3xsAXyMr5/XTlazXU05bngaxEcdzgvERN5P1f32x8cNJnh8tMb5sRdeQKY8eoeuPsS8ATeqaaT4OmugI/m2VjMdxj0XnOdfQrQ/YeczrE2VuzKF8QVlPLw34CU/6t52gcKZedDmajf5s3ocY+jmGfihl+0GxjD8oQ2RaxIf3z0VGaztiN5BxBfUJutSp4mvnRKs0X9JL1NuhJSx7C/luB4a+3Whvkm6e8at5pMm7wejjKEO/ydDXGrrdvzuG+vzrmLBdxRBveR2neD0Tod9WRd8e0TbaQffnp9ep9yfWIU7Pi9cjrOdCHQjr9mN9hW4QOtJK3QDn6F2GX0OJttP8Z596hS/aV26+m0ydH8Z2S3tGOw34pLT+idF8+kEnnmH2b3zb4T32V9LXSD+9BVi9Vzubb03PKwvPLz4NHPsUyQu2daLIBt5Cn0fdnUT+tzO8SudH+9Xpe4w9nJLbt7FvMOdVFW7//fPXyalGXpQz7LMWdC1/3f7kK2dMYbMRe8LS74Me7W/2K7Tdp5XtftXY7lnG1s4WeUEjT9VfnUs89Obwn9pP8H7cH8y7vV8XOUEP+D1MzMMcS79pdGT9RJ8vPEDnvpkp64WGh30v4duGfr2hXyxjINtcMFefOU7eC57DuWZgi739afXeIt76h6ONWGtnr+fiUHeYv7bCX1R7vG+rl/0edtkE/T3Mveq0ugUP6S+LYQmeWcTkRofOcZ5ebN4Np+yIz/FheYbBXkUs4nOwTxnstcQiPgd7qsF+n1jE52BvN9gfSBslVmzMpt1m0v6IabeZtBMi8j3NpL2VaU8zaW9SfQPDpNu+gN+a9wm3xTuVfX6hQn9rAy/a+N0cs1BHoX7up4jX+NOJv5f4Mwz+PoM/g/j7iX/K4H9u8E8R/wviTzX4Xxn8qcQ/SPztBr/D4G8n/iHiUach/CMGD7rD/4b4bYb/Ywa/jfwfJ36CwT9p8BOIf4r40wz+mTAedPp6MGOg/bb5O0U/PYL+vKKfEUF/QdGfiqC/pOinRtBfVvTbI+ivmPmypf9J0bdFpH/V9JeW/hdFPy2C/gbokd/rh93nYZ7HMUvPOX5QEd5Xesi8535D3ncoVy6Zv3pGQ2x148LmpsZs9jmxvCf59gQZO9+ZIHtb/zTr138hjF9IB/+mzb1LLP4GP/n7HTMW/5fp/+PGCMTUBrgRtWEc6KF+bVfiCoibNkC5TXldOdnH0Q+1zDvknn+BN6pWymr8Tbiy7g66Ho8Leb50pJOJe0i1uevAPZkONMdnLxeWb0GWXuTCkh7xIZ2XmPSWXopw9D51cmNbChppjWevwUmM7CHuzTIsHtjXTticHLc8NPId5/iKX8IyV15kzTlGbZkfxsdOP4r7W2dVuDw7GOvixte6uPg67kMH88redEeiz/mlwBx9ZHntUO4+z/NmUZb64vDdiX1c+s0=
*/