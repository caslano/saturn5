/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains definition of generic type dispatcher interfaces.
 */

#ifndef BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/static_assert.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A type dispatcher interface
 *
 * All type dispatchers support this interface. It is used to acquire the
 * visitor interface for the requested type.
 */
class type_dispatcher
{
public:

#ifndef BOOST_LOG_DOXYGEN_PASS

    //! The base class for type dispatcher callbacks
    class callback_base
    {
    protected:
        void* m_pVisitor;
        void* m_pTrampoline;

    public:
        explicit callback_base(void* visitor = 0, void* tramp = 0) BOOST_NOEXCEPT :
            m_pVisitor(visitor),
            m_pTrampoline(tramp)
        {
        }
        template< typename ValueT >
        explicit callback_base(void* visitor, void (*tramp)(void*, ValueT const&)) BOOST_NOEXCEPT :
            m_pVisitor(visitor)
        {
            typedef void (*trampoline_t)(void*, ValueT const&);
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_trampoline = tramp;
            m_pTrampoline = caster.as_pvoid;
        }

        template< typename VisitorT, typename T >
        static void trampoline(void* visitor, T const& value)
        {
            (*static_cast< VisitorT* >(visitor))(value);
        }
    };

    //! An interface to the callback for the concrete type visitor
    template< typename T >
    class callback :
        private callback_base
    {
    private:
        //! Type of the trampoline method
        typedef void (*trampoline_t)(void*, T const&);

    public:
        //! The type, which the visitor is able to consume
        typedef T supported_type;

    public:
        callback() BOOST_NOEXCEPT : callback_base()
        {
        }
        explicit callback(callback_base const& base) BOOST_NOEXCEPT : callback_base(base)
        {
        }

        void operator() (T const& value) const
        {
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_pvoid = this->m_pTrampoline;
            (caster.as_trampoline)(this->m_pVisitor, value);
        }

        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        bool operator! () const BOOST_NOEXCEPT { return (this->m_pVisitor == 0); }
    };

#else // BOOST_LOG_DOXYGEN_PASS

    /*!
     * This interface is used by type dispatchers to consume the dispatched value.
     */
    template< typename T >
    class callback
    {
    public:
        /*!
         * The operator invokes the visitor-specific logic with the given value
         *
         * \param value The dispatched value
         */
        void operator() (T const& value) const;

        /*!
         * The operator checks if the visitor is attached to a receiver
         */
        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        /*!
         * The operator checks if the visitor is not attached to a receiver
         */
        bool operator! () const BOOST_NOEXCEPT;
    };

#endif // BOOST_LOG_DOXYGEN_PASS

protected:
    //! Pointer to the callback acquisition method
    typedef callback_base (*get_callback_impl_type)(type_dispatcher*, typeindex::type_index);

private:
    //! Pointer to the callback acquisition method
    get_callback_impl_type m_get_callback_impl;

protected:
    /*!
     * Initializing constructor
     */
    explicit type_dispatcher(get_callback_impl_type get_callback_impl) BOOST_NOEXCEPT : m_get_callback_impl(get_callback_impl)
    {
    }

    // Destructor and copying can only be called from the derived classes
    BOOST_DEFAULTED_FUNCTION(~type_dispatcher(), {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher(type_dispatcher const& that), : m_get_callback_impl(that.m_get_callback_impl) {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher& operator= (type_dispatcher const& that), { m_get_callback_impl = that.m_get_callback_impl; return *this; })

public:
    /*!
     * The method requests a callback for the value of type \c T
     *
     * \return The type-specific callback or an empty value, if the type is not supported
     */
    template< typename T >
    callback< T > get_callback()
    {
        return callback< T >((this->m_get_callback_impl)(this, typeindex::type_id< T >()));
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

/* type_dispatcher.hpp
z0ssjy51rqM23oyJ3b+A+8fmXlIt3PRAJqNEUwlntTNUdZxcNLubnBChZOvZj4V9JdJazjDautpxOiOLMVB/S4fkAPRIXF0Sb352H7okQx9L1CXJeSymS/LRo65eR1fvnM2zPFkXT2+kVUzmndu5Z42nc+L5nReTdXJlV61J1kM5Y03ymZ+HrUnWTWkek3V2ZWHJpK9i+igLHvnX6qMknGlRVftzS0/hLPdMi3V6j5Sre6J5MHM3sjzdE4VDbfPawLHe/PJTZneC5petvsgc6Pxy4j4l7kTXXqvzNtZt8/Slq5Umf70Ur52/zdwtwm+JX5oIx19XJVvtyRNm/7wziVg94j9PTxi+OizefO8ys/+dM5sncQsm0hZmev72Mp471AtPcr93jbcXzgqz3+5cQApewJS3j8NUe59wvrLtl6OzMszveupaCuOaLbx5x4dN/mpcWHlTxkxwvHbta7NvRw6kWNtWXe3YJpOHuLY06frZxLZd8dlidsO8uPS2+A0gFpnotaQo3m6YU5GeEa8H570jXjL7s3SWset+Bm7PUv2zNkl7UVSkPfrhOkLReqoB/0j+6tm7X8/e1rVWTyukH5Rnz1C2Xz0lnH3XiZ1mv5i5Be6GaUI+pGrPmFi7XnF9sf3tI/OJpTdZX2ho9Lk8IF0h/OxTV2g49r66QvIb32f/8ifUFXLTukyhMWcWnSMKRNug3auU1vL0hFSuhQ9FdbcynOPVB8HeZCmBQ5x3/PJEYfvvLZMN/2b2WYFIW/0I5jlMRiAgXRX5J8adnB1euJL76RR5z2Rbi9drzkU80/Mwvvt6rfLVTVGfBFoYi3DbmjfCUfQzwl7/7EmzO9x71nPt+mTye4jcBJw1Jgt5eiLN7HpHUt13921JMftvnWWE8iC1cT33NL05L6zGTgryuDbJa9+7mP1cp5g4Xowb93221eQdvP5hR7u+klhd7Bu29DXi2h1Ywb1NIn2HaPhUvjHTip39tkkVO+vnm1qO/S4P2D3pbZrOFRM8qrf++lZeHetg7gYHcvi2a485EjMgkOJXXwnTV8fKewbeNvvD8dvW7znGv68OlbenTnOzPzPQOcDcBGYI5lSMX/1UWOXuWXOi1d+DyKt0/IW9ZzLV5NP4Bh+m9x65YWG9R7lfwDxhN+99Wd/kUwOqk0l6VF3M/rjAwXwDtsH0xvQLpCbUweZ65k42t82wDTnbMA55nI5phPHVA6rgey1Sr8Y+WLF6VbPyDKNydYF2mS5QVrjmL4/9zfXv/LF7t0c/mtWnUheowvvmDH28fJ2fVtItaC2dnzZxOhkd5c/3jBzpMlwjnYzrpZNxrXQaeJQ1ZmPjaeb/FMwyjUdSbczfHu2Tsxd2lc5MH/glPFq6M8dLd2Yo/BYOg9/rTPqLud8Z8HLp/oThZJgCL5X9VbK/BqbDebA2nA8vhLfCi+BDcv+Y3K+DteATsD7cCBvC52Ej+I50lN6XjtJX8GD4D+kU1Y18jEL8WLhNYSTc5rAVbAnbStenDewCD5WuTzt4NGwPB8JOcBDsDIfCLnA47A7Phj3gubAn/CXsBS+Fh8Pr4RFwBewLV8IjI+mF/eCzELe2n8pl8D3FcxfsDz+DA+D38HjYgDI8AebAwbArHAr7wovhqcGo/9PgcDgGjoCT4GlwFhwJL5f7a+T+V/BMuBCeDe+A4+H9MBc+DPPgc3Ai3Aonwe1wMnwHToGfwSJYNRQt13owEn4DOB0OhDPhIHgxHCp7nbGk72zi4HPG0rHSJToeVtU+SZnSdaqus5tqSkeqKRwiHZwT4VHSmRoonamTpCt1lvxzf3S89P2pb+7dOhvzG93/RuKZDm+BWXAxbAhvhR3hEtg=
*/