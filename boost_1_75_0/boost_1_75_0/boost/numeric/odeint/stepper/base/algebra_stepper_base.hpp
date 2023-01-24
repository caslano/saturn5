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
QQ95HztFwY2efbGK77OApb6ZrbKnuMOn3ofn8fHJ8aZVMDGViUH1s9bj3rBeF3ks9dBG++vCPReoz4O9cP7S/pQssrAWmeuhW90UJrJuw/kb8WkprJcIulb0vayHAmSte2n83v0VYJb2Y1S/mMdN7FwFaGC6HhYKy+qJ8+ZzuX/QleV+ei94hE0wg2nND2P+U6VbDHbTa71xxsfzsL5yJu+ExeSTp8+vkHfrFG/AI9uHK6293odnNqHDWE/vpJ9uWxVr/toYtW4ZeA743ZnuQBWeb9Uo0rIeATcJDuiyHqgS9TdOLGoXxjsXPKcKd1rswppVKFKMq/tBzMREc+xLoc/rmIZ6EEqUXZhZjO+hnzpdD107Z+WVntaZzrjxHCJfuvvrQHe4CPr10/dRy9vkiicHZfBnM0pwJsSlVfSwFw7RTNECKOGyHh2oTRRCXbLwrLxSGaa9kCcdoA0AT2EfdJ+u8V1u907nxbHeur87UzRMPzM9LHC9U/w0k32iM6gOV3Ssl7b0dBGfFtOuPK/I07E2q/Vsx6jSwjYx/2qn9fY62dT3URN2L0Mf63lKZE6LNlCp3J63u9H9NTpNZydasFshZWn9vI9Ce+fZ051v7XKmMnVBnwNvC1/DXEP0Lfar9ah75QF+D9PFePFG92OITPFkE7Cvq4A3CjM9XQ+NLVcoW725M0U2TZjPb30G2F/4j62s6rIe8Qb60Ht5
*/