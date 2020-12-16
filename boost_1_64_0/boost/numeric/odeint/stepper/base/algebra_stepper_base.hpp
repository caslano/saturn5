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
3Plwt5KumYPrD/cpXAsHN0zK+1C3uXGyLE856nuZTPeI416PTLdjkM3lwvVF1muOdBVwuXA/Orir5L3THPWdDvcY6XY50s2A+xyui4ObI+/9u+Pe+XB9jN/XbTnctXBdHdwaWb7nHNwmuGdIF+bgNsuyvOrgtrjI2wrXwA/9OdroEbjxcC0d6Xa45PuESx4vuOjvRamDdg7uVZkv7Qlnfz88cqD14xqFZcXpmad/Z6Ny40/5axs9ykvYzq3f6WvsY9ejhD3hMjN6ZJh7D8vryBxhy2STwBR5X3JESlLlC7ijEzkNDesZGtKzVx+uVP6CxMjCklJ2fU6pAOl5lb8iUaXfoz/9/TPynfSvrktKIRdTrU3e/vibEdH/slza/QtlSbWc2pDyXyra5Tcj3KVLuX9yuapFtVLbySLj4qNiExNjUsckRqWGx8ezXffFsJGJcdbW344USSMTosIjEx1MbFxq5PjY8NHREalRsRexq7fjWnx0BH9ZdCJ7LA5O6UCJnEU6XaYMT0lpZcFO75tvq/FP9Vi5C2RKZkG2pyCzpEdoamhKB7sUVczXm+y4aOYwtrfcMpGtFy8qCbE3RZQbTtqKSByfKFXpuoX86TpzOQY1RkaHx57e6z0qYkxCVKWao+LZpTI8ydTwmNjoiLjIKDORPJV7S8ZlwJ3aKT1VnkzwtKvckbiq7iM8KWb0iIhTBuLFjfYdHSIGpsQXF2YXp+W3G+HJY0fRrqjz/FP7oDp/K+BiTylbekYljRjHZu4pYT379gw9JSilLL/DnwuzJISGnL6L8oT0DO0T0rd3z5DK7w75LiSs9wBTiGUG5yyG6jAW+fH9B8bRAMYvYMYH3cAFIBmddOd4rvlM9hRQabntufL7TZ0C3H6/yb8OMVw94nHJ7Zdj++Z4mzsAl0S68cLmDsvx72vN5o7KdP1lum5nG3fyS1LKivI8Bbluv/cWppQ1iDWo8nrWvi01JBcGdxdctINLgvsA7qiDWyTT5Tm4VTJdpoPbLNOd5+C2S26Qg3tKcr0c3E64QH/iR83mXpfpJjrSvS+5ZAfXsLFVlgEOrlljK128g2shuWwH10be+42DG93Y0tXjjrJcLrkdjnRFUl5HyfU6W3tJP5uSmVqUlsGmNq7tNlJptzvI4zB6GYHcmpK7C64Z6+ehdW3uHsmdrGVz90kuyM/mHoAjlmUvQJt7VObxmSOPF+HiarNm4eBekfJ+62Rzb8p7Yx3p9ktuqoM7KLl/OLgjkhOOsnxr5UE8a3M6zzjTzHwd9/oFWve+7eDqnuJ0m2shuUWOPHrDLUfeHY57B8l0ZQ4uO9Aqy3GHTj0y3WuOPAplum2OMl8pufPr2Nx8ee/djjxultwRB7dElq+uI4+1Ut7jjjzulPfWdXCvwD1HuhYOeXtkupXONpLydnS0uQMyXZEj3SHJNXbk8ZnkvnWU7xfJhTjurdnE4p51cP6S+9lxb0AT2eYOe24j033suLenTPd9J0e7yXR1HO07uomlg3aOewtcuCVwP8B1kVzPqvXfdDbud/l9v/IAb38vsKJPyIDy3inlva2fQT4t7zue3Zjviw2owTz+QZ7lvaXzHiPPfHlPbfJuhI7TRAXr2d8c5lnqK4Z4LF8XgTzXaTaE9wp4LzAliedQ92B7e3hulMF72iN5fsL7uu3ppI1Yb7iG5wU9t7FOuBFfOIz18dHw+QbvXfJ86yBrvjzPn9WS2lzCM7ShPJ9g/SGOPvDCJtZZeU/iutG8G3g1z/WuYo2vnSbe4f2FSTrvtr/Lei/5Ne1AOVjfenA77wtk0YbLeIfyBPr/jDWrw6zfjsDeMdCEmqz3Y/gjeO/nzi9Yy+QdpcnfGuI=
*/