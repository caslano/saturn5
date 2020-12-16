/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   static_type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains implementation of a compile-time type dispatcher.
 */

#ifndef BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_

#include <cstddef>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_index.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/core/addressof.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/once_block.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Ordering predicate for type dispatching map
struct dispatching_map_order
{
    typedef bool result_type;
    typedef std::pair< typeindex::type_index, void* > first_argument_type, second_argument_type;
    result_type operator() (first_argument_type const& left, second_argument_type const& right) const
    {
        return (left.first < right.first);
    }
};

//! Dispatching map filler
template< typename VisitorT >
struct dispatching_map_initializer
{
    template< typename IteratorT >
    static BOOST_FORCEINLINE void init(IteratorT*, IteratorT*, std::pair< typeindex::type_index, void* >*)
    {
    }

    template< typename BeginIteratorT, typename EndIteratorT >
    static BOOST_FORCEINLINE void init(BeginIteratorT*, EndIteratorT* end, std::pair< typeindex::type_index, void* >* p)
    {
        typedef typename mpl::deref< BeginIteratorT >::type type;
        do_init(static_cast< type* >(0), p);

        typedef typename mpl::next< BeginIteratorT >::type next_iterator_type;
        init(static_cast< next_iterator_type* >(0), end, p + 1);
    }

private:
    template< typename T >
    static BOOST_FORCEINLINE void do_init(T*, std::pair< typeindex::type_index, void* >* p)
    {
        p->first = typeindex::type_id< T >();

        typedef void (*trampoline_t)(void*, T const&);
        BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
        union
        {
            void* as_pvoid;
            trampoline_t as_trampoline;
        }
        caster;
        caster.as_trampoline = (trampoline_t)&type_dispatcher::callback_base::trampoline< VisitorT, T >;
        p->second = caster.as_pvoid;
    }
};

//! A base class for a dispatcher that supports a sequence of types
class type_sequence_dispatcher_base :
    public type_dispatcher
{
private:
    //! Dispatching map element type
    typedef std::pair< typeindex::type_index, void* > dispatching_map_element_type;

private:
    //! Dispatching map
    const dispatching_map_element_type* m_dispatching_map_begin;
    //! Dispatching map size
    std::size_t m_dispatching_map_size;
    //! Pointer to the receiver function
    void* m_visitor;

protected:
    //! Initializing constructor
    type_sequence_dispatcher_base(const dispatching_map_element_type* disp_map, std::size_t disp_map_size, void* visitor) BOOST_NOEXCEPT :
        type_dispatcher(&type_sequence_dispatcher_base::get_callback),
        m_dispatching_map_begin(disp_map),
        m_dispatching_map_size(disp_map_size),
        m_visitor(visitor)
    {
    }

private:
    //! The get_callback method implementation
    static callback_base get_callback(type_dispatcher* p, typeindex::type_index type)
    {
        type_sequence_dispatcher_base* const self = static_cast< type_sequence_dispatcher_base* >(p);
        const dispatching_map_element_type* begin = self->m_dispatching_map_begin;
        const dispatching_map_element_type* end = begin + self->m_dispatching_map_size;
        const dispatching_map_element_type* it = std::lower_bound
        (
            begin,
            end,
            dispatching_map_element_type(type, (void*)0),
            dispatching_map_order()
        );

        if (it != end && it->first == type)
            return callback_base(self->m_visitor, it->second);
        else
            return callback_base();
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher_base(type_sequence_dispatcher_base const&))
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher_base& operator= (type_sequence_dispatcher_base const&))
};

//! A dispatcher that supports a sequence of types
template< typename TypeSequenceT >
class type_sequence_dispatcher :
    public type_sequence_dispatcher_base
{
public:
    //! Type sequence of the supported types
    typedef TypeSequenceT supported_types;

private:
    //! The dispatching map
    typedef array<
        std::pair< typeindex::type_index, void* >,
        mpl::size< supported_types >::value
    > dispatching_map;

public:
    /*!
     * Constructor. Initializes the dispatcher internals.
     */
    template< typename VisitorT >
    explicit type_sequence_dispatcher(VisitorT& visitor) :
        type_sequence_dispatcher_base(get_dispatching_map< VisitorT >().data(), dispatching_map::static_size, (void*)boost::addressof(visitor))
    {
    }

private:
    //! The method returns the dispatching map instance
    template< typename VisitorT >
    static dispatching_map const& get_dispatching_map()
    {
        static const dispatching_map* pinstance = NULL;

        BOOST_LOG_ONCE_BLOCK()
        {
            static dispatching_map instance;
            typename dispatching_map::value_type* p = &*instance.begin();

            typedef typename mpl::begin< supported_types >::type begin_iterator_type;
            typedef typename mpl::end< supported_types >::type end_iterator_type;
            typedef dispatching_map_initializer< VisitorT > initializer;
            initializer::init(static_cast< begin_iterator_type* >(0), static_cast< end_iterator_type* >(0), p);

            std::sort(instance.begin(), instance.end(), dispatching_map_order());

            pinstance = &instance;
        }

        return *pinstance;
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher(type_sequence_dispatcher const&))
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher& operator= (type_sequence_dispatcher const&))
};

//! A base class for a single-type dispatcher
class single_type_dispatcher_base :
    public type_dispatcher
{
private:
    //! The type to match against
    typeindex::type_index m_type;
    //! A callback for the supported type
    callback_base m_callback;

protected:
    //! Initializing constructor
    single_type_dispatcher_base(typeindex::type_index type, callback_base const& cb) BOOST_NOEXCEPT :
        type_dispatcher(&single_type_dispatcher_base::get_callback),
        m_type(type),
        m_callback(cb)
    {
    }

private:
    //! The get_callback method implementation
    static callback_base get_callback(type_dispatcher* p, typeindex::type_index type)
    {
        single_type_dispatcher_base* const self = static_cast< single_type_dispatcher_base* >(p);
        if (type == self->m_type)
            return self->m_callback;
        else
            return callback_base();
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(single_type_dispatcher_base(single_type_dispatcher_base const&))
    BOOST_DELETED_FUNCTION(single_type_dispatcher_base& operator= (single_type_dispatcher_base const&))
};

//! A simple dispatcher that only supports one type
template< typename T >
class single_type_dispatcher :
    public single_type_dispatcher_base
{
private:
    typedef void (*trampoline_t)(void*, T const&);

public:
    //! Constructor
    template< typename VisitorT >
    explicit single_type_dispatcher(VisitorT& visitor) BOOST_NOEXCEPT :
        single_type_dispatcher_base(typeindex::type_id< T >(), callback_base((void*)boost::addressof(visitor), (trampoline_t)&callback_base::trampoline< VisitorT, T >))
    {
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(single_type_dispatcher(single_type_dispatcher const&))
    BOOST_DELETED_FUNCTION(single_type_dispatcher& operator= (single_type_dispatcher const&))
};

} // namespace aux

/*!
 * \brief A static type dispatcher class
 *
 * The type dispatcher can be used to pass objects of arbitrary types from one
 * component to another. With regard to the library, the type dispatcher
 * can be used to extract attribute values.
 *
 * Static type dispatchers allow to specify one or several supported types at compile
 * time.
 */
template< typename T >
class static_type_dispatcher
#ifndef BOOST_LOG_DOXYGEN_PASS
    :
    public mpl::if_<
        mpl::is_sequence< T >,
        boost::log::aux::type_sequence_dispatcher< T >,
        boost::log::aux::single_type_dispatcher< T >
    >::type
#endif
{
private:
    //! Base type
    typedef typename mpl::if_<
        mpl::is_sequence< T >,
        boost::log::aux::type_sequence_dispatcher< T >,
        boost::log::aux::single_type_dispatcher< T >
    >::type base_type;

public:
    /*!
     * Constructor. Initializes the dispatcher internals.
     *
     * The \a receiver object is not copied inside the dispatcher, but references to
     * it may be kept by the dispatcher after construction. The receiver object must remain
     * valid until the dispatcher is destroyed.
     *
     * \param receiver Unary function object that will be called on a dispatched value. The receiver
     *                 must be callable with an argument of any of the supported types of the dispatcher.
     */
    template< typename ReceiverT >
    explicit static_type_dispatcher(ReceiverT& receiver) :
        base_type(receiver)
    {
    }

    //  Copying and assignment prohibited
    BOOST_DELETED_FUNCTION(static_type_dispatcher(static_type_dispatcher const&))
    BOOST_DELETED_FUNCTION(static_type_dispatcher& operator= (static_type_dispatcher const&))
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_

/* static_type_dispatcher.hpp
rq7M7zMj8vtOnzXyk9R5d120ovaOLcuve3b/OjTO0+Xr0LSTzsRh0qFp7+pa6HvcT9dC6xfM36EwA3aBmbADxD/fqPo+1Pf0bp2ht1jjHS9wnyB8VboIr+usvMb47wmbwMGwGRwGD4Gn6Lz9EZKfKflZ8F3pzvxOugnvSZfiQ+lQ/AnO0/n+82EL/N0Pc+DDCmeNzvt/HH6i8/w/1X7Wn8EtcDfcAffAPyoeH8v/J/AL5d9X8Gv4d5hBmr+G2TDinjSa+4Pgd8htL0iu28NU2AtWgf1gGhwCq8KRMB2eAzPhBFgNzoLV4TxYBy6FTeCDus8qWB++DBvArYrH67KPxHei953D86byTjedFX1fSZfkJOnGDIWZ0nmpJp2ZJtKZ6ShdmR7SlekrHZkT5F71S98W/vWru+pXD9Wv3qpfvRTf2W7/HRbKfzW1reZP8e0N68A+sL50i9pLt6izdIuOhv3gAOlCHStdqZHSlRorXalJ2selQO7c52u20tHG5/k6QunoC1vDIxX/QvUfffeT0f4r7r4/adq/Jx2eA+tKd6i+5A3hWOn2jJMuz3jpIuVqn5c8xXdXQP0c9Qt3a93Eu3ouJ0l3aqqeywLlUyHsD4ukuzZD+8HPVH7MgoXSGSqRztB06Qxdon197pFO0Eo4R8/ZVXCjdIFekS7QG9IFehv+Cr4H58FPpBv0F1iq5+s6GEnMfBiG18NUuACmw5tgU7hQz9nNsDVcBHvAxfBIeBscAJfCwfAOOBreCcfCZXAqvFf7zN8Hb4Ar4c3wfngHfAAuh6vgCvgIfAauhW/AZ+Fv4a1wl64/gQ/Cf+g6FIzqslWBT8I6cBNsCJ+COcGou7bwPHiYrjvDfNhN1zOCzn73qN8ezjBdqQVD0DfCbMaUpzfV88So7tRsuBCzNmK43g5dXaqBJyXrUxUiK8W4elU7TvLXrVo4dP/6VR1Pxg8cCnfBBdBv/59dJ8d0rcYPK1/fKnwK4cN2cC4cCktP+Wn0r7YPJ78x4aO436ncDzMHswLj6mVtPhU3mH78ffgI/qY84vW0No1I1tVyTovqa9WHXTF+elvbT9uH7hYTA1NGBg9Ih2vg6cHYXvop7CWEOQczG7MEswmzA+OkosuVWqnHVfmr/FX+Kn+Vvx/3+3nm/xkG/Qnm/5to/n98wvx/4tz/F3YGwL73ABj6eNzc/wHM++9v/X/HaLg/aM6/4+MVn/Pv+HjF5/w7Pv7zzvl761U14P51iG9iMTLnv/Vh5ZH/fL83P/0Hc/dxaDChnuwcamcHvsgKmkaBwwIXBulb0YmvHurBmOzRxFXhcpd+AfpojD9/ECjy8kH2vvnbXmOzH5j9h6Fj+bosxtzK/TIY4T028K1zfjDkBEMhp08oxWmicV73foczjjyQew4NFCfcU278dQWUxq/XYM+XyAV8JVfXuO18k430K0vC89Ud8OZevjC/7Z0sXLvj9J8+GpF18dEvSAzv7bhx884aN99l9u+FjiIHR7A39a0wlTH550lzH+YQzsN8i+keSk3SM+jt6m1YGL+lpFKcXEwpObOU9H3D33cGmjptg5nOhGCKMz94jvM5bBeq4jTUWPXFlp6x5H5WoF3gTeYAWiXqHegeCy2NrZzsJH/fB/CDO0/voLMTN3fZ6hGbb/DKo8SuV7HqM8ebazjFZGG5ccPuRA4wV6Px7ahsOTMLd8XFb5I3L9jD7HN07YaRFh+vTk7cGvluZp/hleGKNYqn6mpbi9PXtNtNTVaLq37mZiD37+HF9WWT/Yk1u8vk1713+0AKI1rVY3EdWxSXL69b+Nne2H+aXR9N2EHCCXp585HJQ1ZetbywL0Xr5GVnDxodJzLi31A=
*/