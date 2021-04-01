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
3jUBi3g5BcMoVuvghInVu8mL/XiiJ0OoaWbEWmGto9Y0La5GCbVxwVF5mL5uNPh0cQLiTdoEqhDEqJfL6TCSqDg5D26qBr+Um/MaLcpA6SATFN9QohDFjtubIpLmzoNlM/i1nEVCSlM4KygOteOjj68KZw4ReSV4fZL3iKvYeZZX5JLWS3bs8XZv/k69uFkdVkgbkpeqzF8msMoFuj2zn4oWs9x0knpLtsao5EMDofehMufb+hxSLDWPnEs+LgmHe2EVVI8xvXhYaxS54LfuG1WDdpLyC1ke39dkV/zij8RmVSbKSDA0nCkxH0WmFNEeyjKXDvWLdxft+OadnWWLnb58OpWKO1OpROBaOJxjohCCHM1XljrpI1VWU1pSr44I6Wiyqmrt6O0ZAhc4owvSXC3NaYKhw9gay+5QUqyrUFQGTAKYC4GbisqVAexspTzL/zifNJ2fqD/hyITUfKwkZDUbhM75LCLONrSifUqE5YCHQIjiR+cLLkeT42NeQ8dcdcF/BatJerZsVn6GFDwWa/GN8muB5Nidh/ukkEZxDA4YiHo+nF367V2d/Q==
*/