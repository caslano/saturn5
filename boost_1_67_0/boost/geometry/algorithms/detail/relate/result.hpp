// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP

#include <cstddef>
#include <cstring>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

enum field { interior = 0, boundary = 1, exterior = 2 };

// TODO: IF THE RESULT IS UPDATED WITH THE MAX POSSIBLE VALUE FOR SOME PAIR OF GEOEMTRIES
// THE VALUE ALREADY STORED MUSN'T BE CHECKED
// update() calls chould be replaced with set() in those cases
// but for safety reasons (STATIC_ASSERT) we should check if parameter D is valid and set() doesn't do that
// so some additional function could be added, e.g. set_dim()

// --------------- MATRIX ----------------

// matrix

template <std::size_t Height, std::size_t Width = Height>
class matrix
{
public:
    typedef char value_type;
    typedef std::size_t size_type;
    typedef const char * const_iterator;
    typedef const_iterator iterator;

    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;
    
    inline matrix()
    {
        ::memset(m_array, 'F', static_size);
    }

    template <field F1, field F2>
    inline char get() const
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        return m_array[index];
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        m_array[index] = V;
    }

    inline char operator[](std::size_t index) const
    {
        BOOST_GEOMETRY_ASSERT(index < static_size);
        return m_array[index];
    }

    inline const_iterator begin() const
    {
        return m_array;
    }

    inline const_iterator end() const
    {
        return m_array + static_size;
    }

    inline static std::size_t size()
    {
        return static_size;
    }
    
    inline const char * data() const
    {
        return m_array;
    }

    inline std::string str() const
    {
        return std::string(m_array, static_size);
    }

private:
    char m_array[static_size];
};

// matrix_handler

template <typename Matrix>
class matrix_handler
{
public:
    typedef Matrix result_type;

    static const bool interrupt = false;

    matrix_handler()
    {}

    result_type const& result() const
    {
        return m_matrix;
    }

    result_type const& matrix() const
    {
        return m_matrix;
    }

    result_type & matrix()
    {
        return m_matrix;
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');

        char const c = m_matrix.template get<F1, F2>();
        return D > c || c > '9';
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        static const bool in_bounds = F1 < Matrix::static_height
                                   && F2 < Matrix::static_width;
        typedef boost::integral_constant<bool, in_bounds> in_bounds_t;
        set_dispatch<F1, F2, V>(in_bounds_t());
    }

    template <field F1, field F2, char D>
    inline void update()
    {
        static const bool in_bounds = F1 < Matrix::static_height
                                   && F2 < Matrix::static_width;
        typedef boost::integral_constant<bool, in_bounds> in_bounds_t;
        update_dispatch<F1, F2, D>(in_bounds_t());
    }

private:
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<bool, true>)
    {
        static const std::size_t index = F1 * Matrix::static_width + F2;
        BOOST_STATIC_ASSERT(index < Matrix::static_size);
        BOOST_STATIC_ASSERT(('0' <= V && V <= '9') || V == 'T' || V == 'F');
        m_matrix.template set<F1, F2, V>();
    }
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<bool, false>)
    {}

    template <field F1, field F2, char D>
    inline void update_dispatch(integral_constant<bool, true>)
    {
        static const std::size_t index = F1 * Matrix::static_width + F2;
        BOOST_STATIC_ASSERT(index < Matrix::static_size);
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');
        char const c = m_matrix.template get<F1, F2>();
        if ( D > c || c > '9')
            m_matrix.template set<F1, F2, D>();
    }
    template <field F1, field F2, char D>
    inline void update_dispatch(integral_constant<bool, false>)
    {}

    Matrix m_matrix;
};

// --------------- RUN-TIME MASK ----------------

// run-time mask

template <std::size_t Height, std::size_t Width = Height>
class mask
{
public:
    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;

    inline mask(const char * s)
    {
        char * it = m_array;
        char * const last = m_array + static_size;
        for ( ; it != last && *s != '\0' ; ++it, ++s )
        {
            char c = *s;
            check_char(c);
            *it = c;
        }
        if ( it != last )
        {
            ::memset(it, '*', last - it);
        }
    }

    inline mask(const char * s, std::size_t count)
    {
        if ( count > static_size )
        {
            count = static_size;
        }
        if ( count > 0 )
        {
            std::for_each(s, s + count, check_char);
            ::memcpy(m_array, s, count);
        }
        if ( count < static_size )
        {
            ::memset(m_array + count, '*', static_size - count);
        }
    }

    template <field F1, field F2>
    inline char get() const
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        return m_array[index];
    }

private:
    static inline void check_char(char c)
    {
        bool const is_valid = c == '*' || c == 'T' || c == 'F'
                         || ( c >= '0' && c <= '9' );
        if ( !is_valid )
        {
            BOOST_THROW_EXCEPTION(geometry::invalid_input_exception());
        }
    }

    char m_array[static_size];
};

// interrupt()

template <typename Mask, bool InterruptEnabled>
struct interrupt_dispatch
{
    template <field F1, field F2, char V>
    static inline bool apply(Mask const&)
    {
        return false;
    }
};

template <typename Mask>
struct interrupt_dispatch<Mask, true>
{
    template <field F1, field F2, char V>
    static inline bool apply(Mask const& mask)
    {
        char m = mask.template get<F1, F2>();
        return check_element<V>(m);
    }

    template <char V>
    static inline bool check_element(char m)
    {
        if ( BOOST_GEOMETRY_CONDITION(V >= '0' && V <= '9') )
        {
            return m == 'F' || ( m < V && m >= '0' && m <= '9' );
        }
        else if ( BOOST_GEOMETRY_CONDITION(V == 'T') )
        {
            return m == 'F';
        }
        return false;
    }
};

template <typename Masks, int I = 0, int N = boost::tuples::length<Masks>::value>
struct interrupt_dispatch_tuple
{
    template <field F1, field F2, char V>
    static inline bool apply(Masks const& masks)
    {
        typedef typename boost::tuples::element<I, Masks>::type mask_type;
        mask_type const& mask = boost::get<I>(masks);
        return interrupt_dispatch<mask_type, true>::template apply<F1, F2, V>(mask)
            && interrupt_dispatch_tuple<Masks, I+1>::template apply<F1, F2, V>(masks);
    }
};

template <typename Masks, int N>
struct interrupt_dispatch_tuple<Masks, N, N>
{
    template <field F1, field F2, char V>
    static inline bool apply(Masks const& )
    {
        return true;
    }
};

//template <typename T0, typename T1, typename T2, typename T3, typename T4,
//          typename T5, typename T6, typename T7, typename T8, typename T9>
//struct interrupt_dispatch<boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, true>
//{
//    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> mask_type;

//    template <field F1, field F2, char V>
//    static inline bool apply(mask_type const& mask)
//    {
//        return interrupt_dispatch_tuple<mask_type>::template apply<F1, F2, V>(mask);
//    }
//};

template <typename Head, typename Tail>
struct interrupt_dispatch<boost::tuples::cons<Head, Tail>, true>
{
    typedef boost::tuples::cons<Head, Tail> mask_type;

    template <field F1, field F2, char V>
    static inline bool apply(mask_type const& mask)
    {
        return interrupt_dispatch_tuple<mask_type>::template apply<F1, F2, V>(mask);
    }
};

template <field F1, field F2, char V, bool InterruptEnabled, typename Mask>
inline bool interrupt(Mask const& mask)
{
    return interrupt_dispatch<Mask, InterruptEnabled>
                ::template apply<F1, F2, V>(mask);
}

// may_update()

template <typename Mask>
struct may_update_dispatch
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Mask const& mask, Matrix const& matrix)
    {
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');

        char const m = mask.template get<F1, F2>();
        
        if ( m == 'F' )
        {
            return true;
        }
        else if ( m == 'T' )
        {
            char const c = matrix.template get<F1, F2>();
            return c == 'F'; // if it's T or between 0 and 9, the result will be the same
        }
        else if ( m >= '0' && m <= '9' )
        {
            char const c = matrix.template get<F1, F2>();
            return D > c || c > '9';
        }

        return false;
    }
};

template <typename Masks, int I = 0, int N = boost::tuples::length<Masks>::value>
struct may_update_dispatch_tuple
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Masks const& masks, Matrix const& matrix)
    {
        typedef typename boost::tuples::element<I, Masks>::type mask_type;
        mask_type const& mask = boost::get<I>(masks);
        return may_update_dispatch<mask_type>::template apply<F1, F2, D>(mask, matrix)
            || may_update_dispatch_tuple<Masks, I+1>::template apply<F1, F2, D>(masks, matrix);
    }
};

template <typename Masks, int N>
struct may_update_dispatch_tuple<Masks, N, N>
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Masks const& , Matrix const& )
    {
        return false;
    }
};

//template <typename T0, typename T1, typename T2, typename T3, typename T4,
//          typename T5, typename T6, typename T7, typename T8, typename T9>
//struct may_update_dispatch< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> mask_type;

//    template <field F1, field F2, char D, typename Matrix>
//    static inline bool apply(mask_type const& mask, Matrix const& matrix)
//    {
//        return may_update_dispatch_tuple<mask_type>::template apply<F1, F2, D>(mask, matrix);
//    }
//};

template <typename Head, typename Tail>
struct may_update_dispatch< boost::tuples::cons<Head, Tail> >
{
    typedef boost::tuples::cons<Head, Tail> mask_type;

    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(mask_type const& mask, Matrix const& matrix)
    {
        return may_update_dispatch_tuple<mask_type>::template apply<F1, F2, D>(mask, matrix);
    }
};

template <field F1, field F2, char D, typename Mask, typename Matrix>
inline bool may_update(Mask const& mask, Matrix const& matrix)
{
    return may_update_dispatch<Mask>
                ::template apply<F1, F2, D>(mask, matrix);
}

// check_matrix()

template <typename Mask>
struct check_dispatch
{
    template <typename Matrix>
    static inline bool apply(Mask const& mask, Matrix const& matrix)
    {
        return per_one<interior, interior>(mask, matrix)
            && per_one<interior, boundary>(mask, matrix)
            && per_one<interior, exterior>(mask, matrix)
            && per_one<boundary, interior>(mask, matrix)
            && per_one<boundary, boundary>(mask, matrix)
            && per_one<boundary, exterior>(mask, matrix)
            && per_one<exterior, interior>(mask, matrix)
            && per_one<exterior, boundary>(mask, matrix)
            && per_one<exterior, exterior>(mask, matrix);
    }

    template <field F1, field F2, typename Matrix>
    static inline bool per_one(Mask const& mask, Matrix const& matrix)
    {
        const char mask_el = mask.template get<F1, F2>();
        const char el = matrix.template get<F1, F2>();

        if ( mask_el == 'F' )
        {
            return el == 'F';
        }
        else if ( mask_el == 'T' )
        {
            return el == 'T' || ( el >= '0' && el <= '9' );
        }
        else if ( mask_el >= '0' && mask_el <= '9' )
        {
            return el == mask_el;
        }

        return true;
    }
};

template <typename Masks, int I = 0, int N = boost::tuples::length<Masks>::value>
struct check_dispatch_tuple
{
    template <typename Matrix>
    static inline bool apply(Masks const& masks, Matrix const& matrix)
    {
        typedef typename boost::tuples::element<I, Masks>::type mask_type;
        mask_type const& mask = boost::get<I>(masks);
        return check_dispatch<mask_type>::apply(mask, matrix)
            || check_dispatch_tuple<Masks, I+1>::apply(masks, matrix);
    }
};

template <typename Masks, int N>
struct check_dispatch_tuple<Masks, N, N>
{
    template <typename Matrix>
    static inline bool apply(Masks const&, Matrix const&)
    {
        return false;
    }
};

//template <typename T0, typename T1, typename T2, typename T3, typename T4,
//          typename T5, typename T6, typename T7, typename T8, typename T9>
//struct check_dispatch< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> mask_type;

//    template <typename Matrix>
//    static inline bool apply(mask_type const& mask, Matrix const& matrix)
//    {
//        return check_dispatch_tuple<mask_type>::apply(mask, matrix);
//    }
//};

template <typename Head, typename Tail>
struct check_dispatch< boost::tuples::cons<Head, Tail> >
{
    typedef boost::tuples::cons<Head, Tail> mask_type;

    template <typename Matrix>
    static inline bool apply(mask_type const& mask, Matrix const& matrix)
    {
        return check_dispatch_tuple<mask_type>::apply(mask, matrix);
    }
};

template <typename Mask, typename Matrix>
inline bool check_matrix(Mask const& mask, Matrix const& matrix)
{
    return check_dispatch<Mask>::apply(mask, matrix);
}

// matrix_width

template <typename MatrixOrMask>
struct matrix_width
{
    static const std::size_t value = MatrixOrMask::static_width;
};

template <typename Tuple,
          int I = 0,
          int N = boost::tuples::length<Tuple>::value>
struct matrix_width_tuple
{
    static const std::size_t
        current = matrix_width<typename boost::tuples::element<I, Tuple>::type>::value;
    static const std::size_t
        next = matrix_width_tuple<Tuple, I+1>::value;

    static const std::size_t
        value = current > next ? current : next;
};

template <typename Tuple, int N>
struct matrix_width_tuple<Tuple, N, N>
{
    static const std::size_t value = 0;
};

template <typename Head, typename Tail>
struct matrix_width< boost::tuples::cons<Head, Tail> >
{
    static const std::size_t
        value = matrix_width_tuple< boost::tuples::cons<Head, Tail> >::value;
};

// mask_handler

template <typename Mask, bool Interrupt>
class mask_handler
    : private matrix_handler
        <
            relate::matrix<matrix_width<Mask>::value>
        >
{
    typedef matrix_handler
        <
            relate::matrix<matrix_width<Mask>::value>
        > base_t;

public:
    typedef bool result_type;

    bool interrupt;

    inline explicit mask_handler(Mask const& m)
        : interrupt(false)
        , m_mask(m)
    {}

    result_type result() const
    {
        return !interrupt
            && check_matrix(m_mask, base_t::matrix());
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        return detail::relate::may_update<F1, F2, D>(
                    m_mask, base_t::matrix()
               );
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        if ( relate::interrupt<F1, F2, V, Interrupt>(m_mask) )
        {
            interrupt = true;
        }
        else
        {
            base_t::template set<F1, F2, V>();
        }
    }

    template <field F1, field F2, char V>
    inline void update()
    {
        if ( relate::interrupt<F1, F2, V, Interrupt>(m_mask) )
        {
            interrupt = true;
        }
        else
        {
            base_t::template update<F1, F2, V>();
        }
    }

private:
    Mask const& m_mask;
};

// --------------- FALSE MASK ----------------

struct false_mask {};

// --------------- COMPILE-TIME MASK ----------------

// static_check_characters
template
<
    typename Seq,
    typename First = typename boost::mpl::begin<Seq>::type,
    typename Last = typename boost::mpl::end<Seq>::type
>
struct static_check_characters
    : static_check_characters
        <
            Seq,
            typename boost::mpl::next<First>::type
        >
{
    typedef typename boost::mpl::deref<First>::type type;
    static const char value = type::value;
    static const bool is_valid = (value >= '0' && value <= '9')
                               || value == 'T' || value == 'F' || value == '*';
    BOOST_MPL_ASSERT_MSG((is_valid),
                         INVALID_STATIC_MASK_CHARACTER,
                         (type));
};

template <typename Seq, typename Last>
struct static_check_characters<Seq, Last, Last>
{};

// static_mask

template
<
    typename Seq,
    std::size_t Height,
    std::size_t Width = Height
>
struct static_mask
{
    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;

    BOOST_STATIC_ASSERT(
        std::size_t(boost::mpl::size<Seq>::type::value) == static_size);
    
    template <detail::relate::field F1, detail::relate::field F2>
    struct static_get
    {
        BOOST_STATIC_ASSERT(std::size_t(F1) < static_height);
        BOOST_STATIC_ASSERT(std::size_t(F2) < static_width);

        static const char value
            = boost::mpl::at_c<Seq, F1 * static_width + F2>::type::value;
    };

private:
    // check static_mask characters
    enum { mask_check = sizeof(static_check_characters<Seq>) };
};

// static_should_handle_element

template <typename StaticMask, field F1, field F2, bool IsSequence>
struct static_should_handle_element_dispatch
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;
    static const bool value = mask_el == 'F'
                           || mask_el == 'T'
                           || ( mask_el >= '0' && mask_el <= '9' );
};

template <typename First, typename Last, field F1, field F2>
struct static_should_handle_element_sequence
{
    typedef typename boost::mpl::deref<First>::type StaticMask;

    static const bool value
        = static_should_handle_element_dispatch
            <
                StaticMask,
                F1, F2,
                boost::mpl::is_sequence<StaticMask>::value
            >::value
       || static_should_handle_element_sequence
            <
                typename boost::mpl::next<First>::type,
                Last,
                F1, F2
            >::value;
};

template <typename Last, field F1, field F2>
struct static_should_handle_element_sequence<Last, Last, F1, F2>
{
    static const bool value = false;
};

template <typename StaticMask, field F1, field F2>
struct static_should_handle_element_dispatch<StaticMask, F1, F2, true>
{
    static const bool value
        = static_should_handle_element_sequence
            <
                typename boost::mpl::begin<StaticMask>::type,
                typename boost::mpl::end<StaticMask>::type,
                F1, F2
            >::value;
};

template <typename StaticMask, field F1, field F2>
struct static_should_handle_element
{
    static const bool value
        = static_should_handle_element_dispatch
            <
                StaticMask,
                F1, F2,
                boost::mpl::is_sequence<StaticMask>::value
            >::value;
};

// static_interrupt

template <typename StaticMask, char V, field F1, field F2, bool InterruptEnabled, bool IsSequence>
struct static_interrupt_dispatch
{
    static const bool value = false;
};

template <typename StaticMask, char V, field F1, field F2, bool IsSequence>
struct static_interrupt_dispatch<StaticMask, V, F1, F2, true, IsSequence>
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;

    static const bool value
        = ( V >= '0' && V <= '9' ) ? 
          ( mask_el == 'F' || ( mask_el < V && mask_el >= '0' && mask_el <= '9' ) ) :
          ( ( V == 'T' ) ? mask_el == 'F' : false );
};

template <typename First, typename Last, char V, field F1, field F2>
struct static_interrupt_sequence
{
    typedef typename boost::mpl::deref<First>::type StaticMask;

    static const bool value
        = static_interrupt_dispatch
            <
                StaticMask,
                V, F1, F2,
                true,
                boost::mpl::is_sequence<StaticMask>::value
            >::value
       && static_interrupt_sequence
            <
                typename boost::mpl::next<First>::type,
                Last,
                V, F1, F2
            >::value;
};

template <typename Last, char V, field F1, field F2>
struct static_interrupt_sequence<Last, Last, V, F1, F2>
{
    static const bool value = true;
};

template <typename StaticMask, char V, field F1, field F2>
struct static_interrupt_dispatch<StaticMask, V, F1, F2, true, true>
{
    static const bool value
        = static_interrupt_sequence
            <
                typename boost::mpl::begin<StaticMask>::type,
                typename boost::mpl::end<StaticMask>::type,
                V, F1, F2
            >::value;
};

template <typename StaticMask, char V, field F1, field F2, bool EnableInterrupt>
struct static_interrupt
{
    static const bool value
        = static_interrupt_dispatch
            <
                StaticMask,
                V, F1, F2,
                EnableInterrupt,
                boost::mpl::is_sequence<StaticMask>::value
            >::value;
};

// static_may_update

template <typename StaticMask, char D, field F1, field F2, bool IsSequence>
struct static_may_update_dispatch
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;
    static const int version
                        = mask_el == 'F' ? 0
                        : mask_el == 'T' ? 1
                        : mask_el >= '0' && mask_el <= '9' ? 2
                        : 3;

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return apply_dispatch(matrix, integral_constant<int, version>());
    }

    // mask_el == 'F'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& , integral_constant<int, 0>)
    {
        return true;
    }
    // mask_el == 'T'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& matrix, integral_constant<int, 1>)
    {
        char const c = matrix.template get<F1, F2>();
        return c == 'F'; // if it's T or between 0 and 9, the result will be the same
    }
    // mask_el >= '0' && mask_el <= '9'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& matrix, integral_constant<int, 2>)
    {
        char const c = matrix.template get<F1, F2>();
        return D > c || c > '9';
    }
    // else
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const&, integral_constant<int, 3>)
    {
        return false;
    }
};

template <typename First, typename Last, char D, field F1, field F2>
struct static_may_update_sequence
{
    typedef typename boost::mpl::deref<First>::type StaticMask;

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_dispatch
                <
                    StaticMask,
                    D, F1, F2,
                    boost::mpl::is_sequence<StaticMask>::value
                >::apply(matrix)
            || static_may_update_sequence
                <
                    typename boost::mpl::next<First>::type,
                    Last,
                    D, F1, F2
                >::apply(matrix);
    }
};

template <typename Last, char D, field F1, field F2>
struct static_may_update_sequence<Last, Last, D, F1, F2>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& /*matrix*/)
    {
        return false;
    }
};

template <typename StaticMask, char D, field F1, field F2>
struct static_may_update_dispatch<StaticMask, D, F1, F2, true>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_sequence
                <
                    typename boost::mpl::begin<StaticMask>::type,
                    typename boost::mpl::end<StaticMask>::type,
                    D, F1, F2
                >::apply(matrix);
    }
};

template <typename StaticMask, char D, field F1, field F2>
struct static_may_update
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_dispatch
                <
                    StaticMask,
                    D, F1, F2,
                    boost::mpl::is_sequence<StaticMask>::value
                >::apply(matrix);
    }
};

// static_check_matrix

template <typename StaticMask, bool IsSequence>
struct static_check_dispatch
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return per_one<interior, interior>::apply(matrix)
            && per_one<interior, boundary>::apply(matrix)
            && per_one<interior, exterior>::apply(matrix)
            && per_one<boundary, interior>::apply(matrix)
            && per_one<boundary, boundary>::apply(matrix)
            && per_one<boundary, exterior>::apply(matrix)
            && per_one<exterior, interior>::apply(matrix)
            && per_one<exterior, boundary>::apply(matrix)
            && per_one<exterior, exterior>::apply(matrix);
    }
    
    template <field F1, field F2>
    struct per_one
    {
        static const char mask_el = StaticMask::template static_get<F1, F2>::value;
        static const int version
                            = mask_el == 'F' ? 0
                            : mask_el == 'T' ? 1
                            : mask_el >= '0' && mask_el <= '9' ? 2
                            : 3;

        template <typename Matrix>
        static inline bool apply(Matrix const& matrix)
        {
            const char el = matrix.template get<F1, F2>();
            return apply_dispatch(el, integral_constant<int, version>());
        }

        // mask_el == 'F'
        static inline bool apply_dispatch(char el, integral_constant<int, 0>)
        {
            return el == 'F';
        }
        // mask_el == 'T'
        static inline bool apply_dispatch(char el, integral_constant<int, 1>)
        {
            return el == 'T' || ( el >= '0' && el <= '9' );
        }
        // mask_el >= '0' && mask_el <= '9'
        static inline bool apply_dispatch(char el, integral_constant<int, 2>)
        {
            return el == mask_el;
        }
        // else
        static inline bool apply_dispatch(char /*el*/, integral_constant<int, 3>)
        {
            return true;
        }
    };
};

template <typename First, typename Last>
struct static_check_sequence
{
    typedef typename boost::mpl::deref<First>::type StaticMask;

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_dispatch
                <
                    StaticMask,
                    boost::mpl::is_sequence<StaticMask>::value
                >::apply(matrix)
            || static_check_sequence
                <
                    typename boost::mpl::next<First>::type,
                    Last
                >::apply(matrix);
    }
};

template <typename Last>
struct static_check_sequence<Last, Last>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& /*matrix*/)
    {
        return false;
    }
};

template <typename StaticMask>
struct static_check_dispatch<StaticMask, true>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_sequence
                <
                    typename boost::mpl::begin<StaticMask>::type,
                    typename boost::mpl::end<StaticMask>::type
                >::apply(matrix);
    }
};

template <typename StaticMask>
struct static_check_matrix
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_dispatch
                <
                    StaticMask,
                    boost::mpl::is_sequence<StaticMask>::value
                >::apply(matrix);
    }
};

// static_mask_handler

template <typename StaticMask, bool Interrupt>
class static_mask_handler
    : private matrix_handler< matrix<3> >
{
    typedef matrix_handler< relate::matrix<3> > base_type;

public:
    typedef bool result_type;

    bool interrupt;

    inline static_mask_handler()
        : interrupt(false)
    {}

    inline explicit static_mask_handler(StaticMask const& /*dummy*/)
        : interrupt(false)
    {}

    result_type result() const
    {
        return (!Interrupt || !interrupt)
            && static_check_matrix<StaticMask>::apply(base_type::matrix());
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        return static_may_update<StaticMask, D, F1, F2>::
                    apply(base_type::matrix());
    }

    template <field F1, field F2>
    static inline bool expects()
    {
        return static_should_handle_element<StaticMask, F1, F2>::value;
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        static const bool interrupt_c = static_interrupt<StaticMask, V, F1, F2, Interrupt>::value;
        static const bool should_handle = static_should_handle_element<StaticMask, F1, F2>::value;
        static const int version = interrupt_c ? 0
                                 : should_handle ? 1
                                 : 2;

        set_dispatch<F1, F2, V>(integral_constant<int, version>());
    }

    template <field F1, field F2, char V>
    inline void update()
    {
        static const bool interrupt_c = static_interrupt<StaticMask, V, F1, F2, Interrupt>::value;
        static const bool should_handle = static_should_handle_element<StaticMask, F1, F2>::value;
        static const int version = interrupt_c ? 0
                                 : should_handle ? 1
                                 : 2;

        update_dispatch<F1, F2, V>(integral_constant<int, version>());
    }

private:
    // Interrupt && interrupt
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 0>)
    {
        interrupt = true;
    }
    // else should_handle
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 1>)
    {
        base_type::template set<F1, F2, V>();
    }
    // else
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 2>)
    {}

    // Interrupt && interrupt
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 0>)
    {
        interrupt = true;
    }
    // else should_handle
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 1>)
    {
        base_type::template update<F1, F2, V>();
    }
    // else
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 2>)
    {}
};

// --------------- UTIL FUNCTIONS ----------------

// set

template <field F1, field F2, char V, typename Result>
inline void set(Result & res)
{
    res.template set<F1, F2, V>();
}

template <field F1, field F2, char V, bool Transpose>
struct set_dispatch
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        res.template set<F1, F2, V>();
    }
};

template <field F1, field F2, char V>
struct set_dispatch<F1, F2, V, true>
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        res.template set<F2, F1, V>();
    }
};

template <field F1, field F2, char V, bool Transpose, typename Result>
inline void set(Result & res)
{
    set_dispatch<F1, F2, V, Transpose>::apply(res);
}

// update

template <field F1, field F2, char D, typename Result>
inline void update(Result & res)
{
    res.template update<F1, F2, D>();
}

template <field F1, field F2, char D, bool Transpose>
struct update_result_dispatch
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        update<F1, F2, D>(res);
    }
};

template <field F1, field F2, char D>
struct update_result_dispatch<F1, F2, D, true>
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        update<F2, F1, D>(res);
    }
};

template <field F1, field F2, char D, bool Transpose, typename Result>
inline void update(Result & res)
{
    update_result_dispatch<F1, F2, D, Transpose>::apply(res);
}

// may_update

template <field F1, field F2, char D, typename Result>
inline bool may_update(Result const& res)
{
    return res.template may_update<F1, F2, D>();
}

template <field F1, field F2, char D, bool Transpose>
struct may_update_result_dispatch
{
    template <typename Result>
    static inline bool apply(Result const& res)
    {
        return may_update<F1, F2, D>(res);
    }
};

template <field F1, field F2, char D>
struct may_update_result_dispatch<F1, F2, D, true>
{
    template <typename Result>
    static inline bool apply(Result const& res)
    {
        return may_update<F2, F1, D>(res);
    }
};

template <field F1, field F2, char D, bool Transpose, typename Result>
inline bool may_update(Result const& res)
{
    return may_update_result_dispatch<F1, F2, D, Transpose>::apply(res);
}

// result_dimension

template <typename Geometry>
struct result_dimension
{
    BOOST_STATIC_ASSERT(geometry::dimension<Geometry>::value >= 0);
    static const char value
        = ( geometry::dimension<Geometry>::value <= 9 ) ?
            ( '0' + geometry::dimension<Geometry>::value ) :
              'T';
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP

/* result.hpp
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
*/