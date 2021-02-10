/*
 [auto_generated]
 boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp

 [begin_description]
 Base class for all steppers with an algebra and operations.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BASE_ALGEBRA_STEPPER_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BASE_ALGEBRA_STEPPER_BASE_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {

template< class Algebra , class Operations >
class algebra_stepper_base
{
public:

    typedef Algebra algebra_type;
    typedef Operations operations_type;

    algebra_stepper_base( const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra ) { }

    algebra_type& algebra()
    {
        return m_algebra;
    }

    const algebra_type& algebra() const
    {
        return m_algebra;
    }

protected:

    algebra_type m_algebra;
};


/******* DOXYGEN *******/

/**
 * \class algebra_stepper_base
 * \brief Base class for all steppers with algebra and operations.
 *
 * This class serves a base class for all steppers with algebra and operations. It holds the
 * algebra and provides access to the algebra.  The operations are not instantiated, since they are 
 * static classes inside the operations class.
 *
 * \tparam Algebra The type of the algebra. Must fulfill the Algebra Concept, at least partially to work
 * with the stepper.
 * \tparam Operations The type of the operations. Must fulfill the Operations Concept, at least partially 
 * to work with the stepper.
 */

    /**
     * \fn algebra_stepper_base::algebra_stepper_base( const algebra_type &algebra = algebra_type() )
     * \brief Constructs a algebra_stepper_base and creates the algebra. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra The algebra_stepper_base stores and uses a copy of algebra.
     */

    /**
     * \fn algebra_type& algebra_stepper_base::algebra()
     * \return A reference to the algebra which is held by this class.
     */

    /**
     * \fn const algebra_type& algebra_stepper_base::algebra() const
     * \return A const reference to the algebra which is held by this class.
     */

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_BASE_ALGEBRA_STEPPER_BASE_HPP_INCLUDED

/* algebra_stepper_base.hpp
kkmkNBjMc8dFdgJNLRth3oQndDAoSbGwbjFKGudqnaniAZDi6FjSSktyRHEgUKIozCFUMkHtwf7krYsmpj7Aj6ZmpzcBJUkMdIdzuJh3YcmNMCF8ulj8PL1awKfhbDacLK5heg7DybUj+3AxOaPUC3KmAe9KjYacaxBFmQtMGp9Pd0Wd74SM8ypB6Fo0lKpuZ2+rwCLBZbXy20JSxggTxBnX0L+ajXudPzvUBad0G6vEFZQ5bjeg74rB/63xEtdu+y1MrsZjv09hqqjnHY4ZyrWFfr20GAcSaeABq1wtec6EFDZw/Oz9eHoyHLPheNyDZ2+9zxGbfuiB1wSQlpoUp4GxlEodQvcLmh6kVMOY3Mhu77g20mipGmAxmi/YaDZjH4e/TGfsZHjmn3/2ihwPSfR0yM2mITtu1D5zDw6o2DP7UsO+zjhHLqsy+Df6or7H9uEEVzQQ1lRMtWaDbcsBByPkyk2JT2duzxU3BfAHV700FqzSm0HNErnFpZ2ROTWtz0bowz29XDBaQmdZC3wc99todjKdj0J4cRB6vrhk5xfj0ccRtQl1Q5Aruer5x/So3mVzasPxiNT36jKh0nuQE+r7VOnCUzeQbVxOMy5X6M/80JcbSjTy2iClVZ7TYLSZAc19R1qypNiR24Yq
*/