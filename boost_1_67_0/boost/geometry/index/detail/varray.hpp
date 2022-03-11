// Boost.Container varray
//
// Copyright (c) 2012-2015 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2013 Andrew Hundt.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_HPP

// TODO - REMOVE/CHANGE
#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

#include <boost/config.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/swap.hpp>
#include <boost/integer.hpp>

#include <boost/mpl/assert.hpp>

#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>

// TODO - use std::reverse_iterator and std::iterator_traits
// instead Boost.Iterator to remove dependency?
// or boost/detail/iterator.hpp ?
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/iterator_concepts.hpp>

#include <boost/geometry/index/detail/assert.hpp>
#include <boost/geometry/index/detail/exception.hpp>

#include <boost/geometry/index/detail/varray_detail.hpp>

#include <boost/concept_check.hpp>

/*!
\defgroup varray_non_member varray non-member functions
*/

namespace boost { namespace geometry { namespace index { namespace detail {
    
namespace varray_detail {

template <typename Value, std::size_t Capacity>
struct varray_traits
{
    typedef Value value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Value * pointer;
    typedef const Value * const_pointer;
    typedef Value & reference;
    typedef const Value & const_reference;

    typedef boost::false_type use_memop_in_swap_and_move;
    typedef boost::false_type use_optimized_swap;
    typedef boost::false_type disable_trivial_init;
};

template <typename Varray>
struct checker
{
    typedef typename Varray::size_type size_type;
    typedef typename Varray::const_iterator const_iterator;

    static inline void check_capacity(Varray const& v, size_type s)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(s <= v.capacity(), "size too big");

        ::boost::ignore_unused(v, s);
    }

    static inline void throw_out_of_bounds(Varray const& v, size_type i)
    {
        if ( v.size() <= i )
            throw_out_of_range("index out of bounds");

        ::boost::ignore_unused(v, i);
    }

    static inline void check_index(Varray const& v, size_type i)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(i < v.size(), "index out of bounds");

        ::boost::ignore_unused(v, i);
    }

    static inline void check_not_empty(Varray const& v)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(!v.empty(), "the container is empty");
        
        ::boost::ignore_unused(v);
    }

    static inline void check_iterator_end_neq(Varray const& v, const_iterator position)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(v.begin() <= position && position < v.end(), "iterator out of bounds");

        ::boost::ignore_unused(v, position);
    }

    static inline void check_iterator_end_eq(Varray const& v, const_iterator position)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(v.begin() <= position && position <= v.end(), "iterator out of bounds");

        ::boost::ignore_unused(v, position);
    }
};

} // namespace varray_detail

/*!
\brief A variable-size array container with fixed capacity.

varray is a sequence container like boost::container::vector with contiguous storage that can
change in size, along with the static allocation, low overhead, and fixed capacity of boost::array.

A varray is a sequence that supports random access to elements, constant time insertion and
removal of elements at the end, and linear time insertion and removal of elements at the beginning or 
in the middle. The number of elements in a varray may vary dynamically up to a fixed capacity
because elements are stored within the object itself similarly to an array. However, objects are 
initialized as they are inserted into varray unlike C arrays or std::array which must construct
all elements on instantiation. The behavior of varray enables the use of statically allocated
elements in cases with complex object lifetime requirements that would otherwise not be trivially 
possible.

\par Error Handling
 Insertion beyond the capacity and out of bounds errors result in undefined behavior unless
 otherwise specified. In this respect if size() == capacity(), then varray::push_back()
 behaves like std::vector pop_front() if size() == empty(). The reason for this difference
 is because unlike vectors, varray does not perform allocation.

\par Advanced Usage
 Error handling behavior can be modified to more closely match std::vector exception behavior
 when exceeding bounds by providing an alternate Strategy and varray_traits instantiation.

\tparam Value    The type of element that will be stored.
\tparam Capacity The maximum number of elements varray can store, fixed at compile time.
\tparam Strategy Defines the public typedefs and error handlers,
        implements StaticVectorStrategy and has some similarities
        to an Allocator.
*/
template <typename Value, std::size_t Capacity>
class varray
{
    typedef varray_detail::varray_traits<Value, Capacity> vt;
    typedef varray_detail::checker<varray> errh;

    BOOST_MPL_ASSERT_MSG(
        ( boost::is_unsigned<typename vt::size_type>::value &&
          sizeof(typename boost::uint_value_t<Capacity>::least) <= sizeof(typename vt::size_type) ),
        SIZE_TYPE_IS_TOO_SMALL_FOR_SPECIFIED_CAPACITY,
        (varray)
    );

    typedef boost::aligned_storage<
        sizeof(Value[Capacity]),
        boost::alignment_of<Value[Capacity]>::value
    > aligned_storage_type;

    template <typename V, std::size_t C>
    friend class varray;

    BOOST_COPYABLE_AND_MOVABLE(varray)

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
public:
    template <std::size_t C>
    varray & operator=(varray<Value, C> & sv)
    {
        typedef varray<Value, C> other;
        this->operator=(static_cast<const ::boost::rv<other> &>(const_cast<const other &>(sv)));
        return *this;
    }
#endif

public:
    //! @brief The type of elements stored in the container.
    typedef typename vt::value_type value_type;
    //! @brief The unsigned integral type used by the container.
    typedef typename vt::size_type size_type;
    //! @brief The pointers difference type.
    typedef typename vt::difference_type difference_type;
    //! @brief The pointer type.
    typedef typename vt::pointer pointer;
    //! @brief The const pointer type.
    typedef typename vt::const_pointer const_pointer;
    //! @brief The value reference type.
    typedef typename vt::reference reference;
    //! @brief The value const reference type.
    typedef typename vt::const_reference const_reference;

    //! @brief The iterator type.
    typedef pointer iterator;
    //! @brief The const iterator type.
    typedef const_pointer const_iterator;
    //! @brief The reverse iterator type.
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    //! @brief The const reverse iterator.
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    //! @brief Constructs an empty varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    varray()
        : m_size(0)
    {}

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Constructs a varray containing count default constructed Values.
    //!
    //! @param count    The number of values which will be contained in the container.
    //!
    //! @par Throws
    //!   If Value's default constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    explicit varray(size_type count)
        : m_size(0)
    {
        this->resize(count);                                                        // may throw
    }

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Constructs a varray containing count copies of value.
    //!
    //! @param count    The number of copies of a values that will be contained in the container.
    //! @param value    The value which will be used to copy construct values.
    //!
    //! @par Throws
    //!   If Value's copy constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    varray(size_type count, value_type const& value)
        : m_size(0)
    {
        this->resize(count, value);                                                 // may throw
    }

    //! @pre
    //!  @li <tt>distance(first, last) <= capacity()</tt>
    //!  @li Iterator must meet the \c ForwardTraversalIterator concept.
    //!
    //! @brief Constructs a varray containing copy of a range <tt>[first, last)</tt>.
    //!
    //! @param first    The iterator to the first element in range.
    //! @param last     The iterator to the one after the last element in range.
    //!
    //! @par Throws
    //!   If Value's constructor taking a dereferenced Iterator throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    varray(Iterator first, Iterator last)
        : m_size(0)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator
        
        this->assign(first, last);                                                    // may throw
    }

    //! @brief Constructs a copy of other varray.
    //!
    //! @param other    The varray which content will be copied to this one.
    //!
    //! @par Throws
    //!   If Value's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    varray(varray const& other)
        : m_size(other.size())
    {
        namespace sv = varray_detail;
        sv::uninitialized_copy(other.begin(), other.end(), this->begin());          // may throw
    }

    //! @pre <tt>other.size() <= capacity()</tt>.
    //!
    //! @brief Constructs a copy of other varray.
    //!
    //! @param other    The varray which content will be copied to this one.
    //!
    //! @par Throws
    //!   If Value's copy constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C>
    varray(varray<value_type, C> const& other)
        : m_size(other.size())
    {
        errh::check_capacity(*this, other.size());                                  // may throw
        
        namespace sv = varray_detail;
        sv::uninitialized_copy(other.begin(), other.end(), this->begin());          // may throw
    }

    //! @brief Copy assigns Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be copied to this one.
    //!
    //! @par Throws
    //!   If Value's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //! Linear O(N).
    varray & operator=(BOOST_COPY_ASSIGN_REF(varray) other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Copy assigns Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be copied to this one.
    //!
    //! @par Throws
    //!   If Value's copy constructor or copy assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C>
    varray & operator=(BOOST_COPY_ASSIGN_REF_2_TEMPL_ARGS(varray, value_type, C) other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    //! @brief Move constructor. Moves Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor throws.
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor throws.
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move is \c false_type - default.
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    varray(BOOST_RV_REF(varray) other)
    {
        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Move constructor. Moves Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor throws.
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor throws.
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move is false_type - default.
    //! @endinternal
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C>
    varray(BOOST_RV_REF_2_TEMPL_ARGS(varray, value_type, C) other)
        : m_size(other.m_size)
    {
        errh::check_capacity(*this, other.size());                                  // may throw

        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    //! @brief Move assignment. Moves Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor or move assignment throws.
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor or copy assignment throws.
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move is \c false_type - default.
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    varray & operator=(BOOST_RV_REF(varray) other)
    {
        if ( &other == this )
            return *this;

        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_assign_dispatch(other, use_memop_in_swap_and_move());

        return *this;
    }

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Move assignment. Moves Values stored in the other varray to this one.
    //!
    //! @param other    The varray which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor or move assignment throws.
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor or copy assignment throws.
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move is \c false_type - default.
    //! @endinternal
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C>
    varray & operator=(BOOST_RV_REF_2_TEMPL_ARGS(varray, value_type, C) other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw

        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_assign_dispatch(other, use_memop_in_swap_and_move());

        return *this;
    }

    //! @brief Destructor. Destroys Values stored in this container.
    //!
    //! @par Throws
    //!   Nothing
    //!
    //! @par Complexity
    //!   Linear O(N).
    ~varray()
    {
        namespace sv = varray_detail;
        sv::destroy(this->begin(), this->end());
    }

    //! @brief Swaps contents of the other varray and this one.
    //!
    //! @param other    The varray which content will be swapped with this one's content.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor or move assignment throws,
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor or copy assignment throws,
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move and \c use_optimized_swap are \c false_type - default.
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    void swap(varray & other)
    {
        typedef typename
        vt::use_optimized_swap use_optimized_swap;

        this->swap_dispatch(other, use_optimized_swap());
    }

    //! @pre <tt>other.size() <= capacity() && size() <= other.capacity()</tt>
    //!
    //! @brief Swaps contents of the other varray and this one.
    //!
    //! @param other    The varray which content will be swapped with this one's content.
    //!
    //! @par Throws
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c true and Value's move constructor or move assignment throws,
    //!   @li If \c boost::has_nothrow_move<Value>::value is \c false and Value's copy constructor or copy assignment throws,
    //! @internal
    //!   @li It throws only if \c use_memop_in_swap_and_move and \c use_optimized_swap are \c false_type - default.
    //! @endinternal
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C>
    void swap(varray<value_type, C> & other)
    {
        errh::check_capacity(*this, other.size());
        errh::check_capacity(other, this->size());

        typedef typename
        vt::use_optimized_swap use_optimized_swap;

        this->swap_dispatch(other, use_optimized_swap()); 
    }

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Inserts or erases elements at the end such that
    //!   the size becomes count. New elements are default constructed.
    //!
    //! @param count    The number of elements which will be stored in the container.
    //!
    //! @par Throws
    //!   If Value's default constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    void resize(size_type count)
    {
        namespace sv = varray_detail;
        typedef typename vt::disable_trivial_init dti;

        if ( count < m_size )
        {
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            sv::uninitialized_fill(this->end(), this->begin() + count, dti()); // may throw
        }
        m_size = count; // update end
    }

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Inserts or erases elements at the end such that
    //!   the size becomes count. New elements are copy constructed from value.
    //!
    //! @param count    The number of elements which will be stored in the container.
    //! @param value    The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   If Value's copy constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    void resize(size_type count, value_type const& value)
    {
        if ( count < m_size )
        {
            namespace sv = varray_detail;
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw
            
            std::uninitialized_fill(this->end(), this->begin() + count, value);     // may throw
        }
        m_size = count; // update end
    }

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief This call has no effect because the Capacity of this container is constant.
    //!
    //! @param count    The number of elements which the container should be able to contain.
    //!
    //! @par Throws
    //!   Nothing.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Adds a copy of value at the end.
    //!
    //! @param value    The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   If Value's copy constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant O(1).
    void push_back(value_type const& value)
    {
        typedef typename vt::disable_trivial_init dti;

        errh::check_capacity(*this, m_size + 1);                                    // may throw
        
        namespace sv = varray_detail;
        sv::construct(dti(), this->end(), value);                                          // may throw
        ++m_size; // update end
    }

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Moves value to the end.
    //!
    //! @param value    The value to move construct the new element.
    //!
    //! @par Throws
    //!   If Value's move constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant O(1).
    void push_back(BOOST_RV_REF(value_type) value)
    {
        typedef typename vt::disable_trivial_init dti;

        errh::check_capacity(*this, m_size + 1);                                    // may throw

        namespace sv = varray_detail;
        sv::construct(dti(), this->end(), ::boost::move(value));                           // may throw
        ++m_size; // update end
    }

    //! @pre <tt>!empty()</tt>
    //!
    //! @brief Destroys last value and decreases the size.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void pop_back()
    {
        errh::check_not_empty(*this);

        namespace sv = varray_detail;
        sv::destroy(this->end() - 1);
        --m_size; // update end
    }

    //! @pre
    //!  @li \c position must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a copy of element at position.
    //!
    //! @param position    The position at which the new value will be inserted.
    //! @param value       The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   @li If Value's copy constructor or copy assignment throws
    //!   @li If Value's move constructor or move assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant or linear.
    iterator insert(iterator position, value_type const& value)
    {
        typedef typename vt::disable_trivial_init dti;
        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            sv::construct(dti(), position, value);                                  // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should move be used only if it's nonthrowing?
            value_type & r = *(this->end() - 1);
            sv::construct(dti(), this->end(), boost::move(r));                      // may throw
            ++m_size; // update end
            sv::move_backward(position, this->end() - 2, this->end() - 1);          // may throw
            sv::assign(position, value);                                            // may throw
        }

        return position;
    }

    //! @pre
    //!  @li \c position must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a move-constructed element at position.
    //!
    //! @param position    The position at which the new value will be inserted.
    //! @param value       The value used to move construct the new element.
    //!
    //! @par Throws
    //!   If Value's move constructor or move assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant or linear.
    iterator insert(iterator position, BOOST_RV_REF(value_type) value)
    {
        typedef typename vt::disable_trivial_init dti;
        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            sv::construct(dti(), position, boost::move(value));                     // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should move be used only if it's nonthrowing?
            value_type & r = *(this->end() - 1);
            sv::construct(dti(), this->end(), boost::move(r));                      // may throw
            ++m_size; // update end
            sv::move_backward(position, this->end() - 2, this->end() - 1);          // may throw
            sv::assign(position, boost::move(value));                               // may throw
        }

        return position;
    }

    //! @pre
    //!  @li \c position must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() + count <= capacity()</tt>
    //!
    //! @brief Inserts a count copies of value at position.
    //!
    //! @param position    The position at which new elements will be inserted.
    //! @param count       The number of new elements which will be inserted.
    //! @param value       The value used to copy construct new elements.
    //!
    //! @par Throws
    //!   @li If Value's copy constructor or copy assignment throws.
    //!   @li If Value's move constructor or move assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator insert(iterator position, size_type count, value_type const& value)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + count);                                // may throw

        if ( position == this->end() )
        {
            std::uninitialized_fill(position, position + count, value);             // may throw
            m_size += count; // update end
        }
        else
        {
            namespace sv = varray_detail;

            difference_type to_move = std::distance(position, this->end());
            
            // TODO - should following lines check for exception and revert to the old size?

            if ( count < static_cast<size_type>(to_move) )
            {
                sv::uninitialized_move(this->end() - count, this->end(), this->end());          // may throw
                m_size += count; // update end
                sv::move_backward(position, position + to_move - count, this->end() - count);   // may throw
                std::fill_n(position, count, value);                                            // may throw
            }
            else
            {
                std::uninitialized_fill(this->end(), position + count, value);                  // may throw
                m_size += count - to_move; // update end
                sv::uninitialized_move(position, position + to_move, position + count);         // may throw
                m_size += to_move; // update end
                std::fill_n(position, to_move, value);                                          // may throw
            }
        }

        return position;
    }

    //! @pre
    //!  @li \c position must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>distance(first, last) <= capacity()</tt>
    //!  @li \c Iterator must meet the \c ForwardTraversalIterator concept.
    //!
    //! @brief Inserts a copy of a range <tt>[first, last)</tt> at position.
    //!
    //! @param position    The position at which new elements will be inserted.
    //! @param first       The iterator to the first element of a range used to construct new elements.
    //! @param last        The iterator to the one after the last element of a range used to construct new elements.
    //!
    //! @par Throws
    //!   @li If Value's constructor and assignment taking a dereferenced \c Iterator.
    //!   @li If Value's move constructor or move assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    iterator insert(iterator position, Iterator first, Iterator last)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->insert_dispatch(position, first, last, traversal());

        return position;
    }

    //! @pre \c position must be a valid iterator of \c *this in range <tt>[begin(), end())</tt>
    //!
    //! @brief Erases Value from position.
    //!
    //! @param position    The position of the element which will be erased from the container.
    //!
    //! @par Throws
    //!   If Value's move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator erase(iterator position)
    {
        namespace sv = varray_detail;

        errh::check_iterator_end_neq(*this, position);

        //TODO - add empty check?
        //errh::check_empty(*this);

        sv::move(position + 1, this->end(), position);                              // may throw
        sv::destroy(this->end() - 1);
        --m_size;

        return position;
    }

    //! @pre
    //!  @li \c first and \c last must define a valid range
    //!  @li iterators must be in range <tt>[begin(), end()]</tt>
    //!
    //! @brief Erases Values from a range <tt>[first, last)</tt>.
    //!
    //! @param first    The position of the first element of a range which will be erased from the container.
    //! @param last     The position of the one after the last element of a range which will be erased from the container.
    //!
    //! @par Throws
    //!   If Value's move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator erase(iterator first, iterator last)
    {
        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);
        
        difference_type n = std::distance(first, last);
        
        //TODO - add invalid range check?
        //BOOST_GEOMETRY_INDEX_ASSERT(0 <= n, "invalid range");
        //TODO - add this->size() check?
        //BOOST_GEOMETRY_INDEX_ASSERT(n <= this->size(), "invalid range");

        sv::move(last, this->end(), first);                                         // may throw
        sv::destroy(this->end() - n, this->end());
        m_size -= n;

        return first;
    }

    //! @pre <tt>distance(first, last) <= capacity()</tt>
    //!
    //! @brief Assigns a range <tt>[first, last)</tt> of Values to this container.
    //!
    //! @param first       The iterator to the first element of a range used to construct new content of this container.
    //! @param last        The iterator to the one after the last element of a range used to construct new content of this container.
    //!
    //! @par Throws
    //!   If Value's copy constructor or copy assignment throws,
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->assign_dispatch(first, last, traversal());                            // may throw
    }

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Assigns a count copies of value to this container.
    //!
    //! @param count       The new number of elements which will be container in the container.
    //! @param value       The value which will be used to copy construct the new content.
    //!
    //! @par Throws
    //!   If Value's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    void assign(size_type count, value_type const& value)
    {
        if ( count < m_size )
        {
            namespace sv = varray_detail;

            std::fill_n(this->begin(), count, value);                               // may throw
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            std::fill_n(this->begin(), m_size, value);                              // may throw
            std::uninitialized_fill(this->end(), this->begin() + count, value);     // may throw
        }
        m_size = count; // update end
    }

#if !defined(BOOST_CONTAINER_VARRAY_DISABLE_EMPLACE)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a Value constructed with
    //!   \c std::forward<Args>(args)... in the end of the container.
    //!
    //! @param args     The arguments of the constructor of the new element which will be created at the end of the container.
    //!
    //! @par Throws
    //!   If in-place constructor throws or Value's move constructor throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant O(1).
    template<class ...Args>
    void emplace_back(BOOST_FWD_REF(Args) ...args)
    {
        typedef typename vt::disable_trivial_init dti;

        errh::check_capacity(*this, m_size + 1);                                    // may throw

        namespace sv = varray_detail;
        sv::construct(dti(), this->end(), ::boost::forward<Args>(args)...);                // may throw
        ++m_size; // update end
    }

    //! @pre
    //!  @li \c position must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a Value constructed with
    //!   \c std::forward<Args>(args)... before position
    //!
    //! @param position The position at which new elements will be inserted.
    //! @param args     The arguments of the constructor of the new element.
    //!
    //! @par Throws
    //!   If in-place constructor throws or if Value's move constructor or move assignment throws.
    //! @internal
    //!   @li If a throwing error handler is specified, throws when the capacity is exceeded. (not by default).
    //! @endinternal
    //!
    //! @par Complexity
    //!   Constant or linear.
    template<class ...Args>
    iterator emplace(iterator position, BOOST_FWD_REF(Args) ...args)
    {
        typedef typename vt::disable_trivial_init dti;

        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            sv::construct(dti(), position, ::boost::forward<Args>(args)...);               // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should following lines check for exception and revert to the old size?

            // TODO - should move be used only if it's nonthrowing?
            value_type & r = *(this->end() - 1);
            sv::construct(dti(), this->end(), boost::move(r));                             // may throw
            ++m_size; // update end
            sv::move_backward(position, this->end() - 2, this->end() - 1);          // may throw

            aligned_storage<sizeof(value_type), alignment_of<value_type>::value> temp_storage;
            value_type * val_p = static_cast<value_type *>(temp_storage.address());
            sv::construct(dti(), val_p, ::boost::forward<Args>(args)...);                  // may throw
            sv::scoped_destructor<value_type> d(val_p);
            sv::assign(position, ::boost::move(*val_p));                            // may throw
        }

        return position;
    }

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

    #define BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_EMPLACE(N)                                        \
    BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N                                   \
    void emplace_back(BOOST_MOVE_UREF##N)                                                        \
    {                                                                                            \
        typedef typename vt::disable_trivial_init dti;                                           \
                                                                                                 \
        errh::check_capacity(*this, m_size + 1);                                    /*may throw*/\
                                                                                                 \
        namespace sv = varray_detail;                                                            \
        sv::construct(dti(), this->end() BOOST_MOVE_I##N BOOST_MOVE_FWD##N );       /*may throw*/\
        ++m_size; /*update end*/                                                                 \
    }                                                                                            \
    \
    BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N                                      \
    iterator emplace(iterator position BOOST_MOVE_I##N BOOST_MOVE_UREF##N)                          \
    {                                                                                               \
        typedef typename vt::disable_trivial_init dti;                                              \
        namespace sv = varray_detail;                                                               \
                                                                                                    \
        errh::check_iterator_end_eq(*this, position);                                               \
        errh::check_capacity(*this, m_size + 1);                                       /*may throw*/\
                                                                                                    \
        if ( position == this->end() )                                                              \
        {                                                                                           \
            sv::construct(dti(), position BOOST_MOVE_I##N BOOST_MOVE_FWD##N );         /*may throw*/\
            ++m_size; /*update end*/                                                                \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            /* TODO - should following lines check for exception and revert to the old size? */     \
            /* TODO - should move be used only if it's nonthrowing? */                              \
                                                                                                    \
            value_type & r = *(this->end() - 1);                                                    \
            sv::construct(dti(), this->end(), boost::move(r));                         /*may throw*/\
            ++m_size; /*update end*/                                                                \
            sv::move_backward(position, this->end() - 2, this->end() - 1);             /*may throw*/\
                                                                                                    \
            aligned_storage<sizeof(value_type), alignment_of<value_type>::value> temp_storage;      \
            value_type * val_p = static_cast<value_type *>(temp_storage.address());                 \
            sv::construct(dti(), val_p BOOST_MOVE_I##N BOOST_MOVE_FWD##N );            /*may throw*/\
            sv::scoped_destructor<value_type> d(val_p);                                             \
            sv::assign(position, ::boost::move(*val_p));                               /*may throw*/\
        }                                                                                           \
                                                                                                    \
        return position;                                                                            \
    }                                                                                               \
    
    BOOST_MOVE_ITERATE_0TO9(BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_EMPLACE)
    #undef BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_EMPLACE

#endif // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
#endif // !BOOST_CONTAINER_VARRAY_DISABLE_EMPLACE

    //! @brief Removes all elements from the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void clear()
    {
        namespace sv = varray_detail;
        sv::destroy(this->begin(), this->end());
        m_size = 0; // update end
    }

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   \c std::out_of_range exception by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference at(size_type i)
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns const reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return const reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   \c std::out_of_range exception by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference at(size_type i) const
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference operator[](size_type i)
    {
        // TODO: Remove bounds check? std::vector and std::array operator[] don't check.
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns const reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return const reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the first element.
    //!
    //! @return reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference front()
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference front() const
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the last element.
    //!
    //! @return reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference back()
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference back() const
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    //! @brief Pointer such that <tt>[data(), data() + size())</tt> is a valid range.
    //!   For a non-empty vector <tt>data() == &front()</tt>.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    Value * data()
    {
        return boost::addressof(*(this->ptr()));
    }

    //! @brief Const pointer such that <tt>[data(), data() + size())</tt> is a valid range.
    //!   For a non-empty vector <tt>data() == &front()</tt>.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const Value * data() const
    {
        return boost::addressof(*(this->ptr()));
    }

    
    //! @brief Returns iterator to the first element.
    //!
    //! @return iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator begin() { return this->ptr(); }

    //! @brief Returns const iterator to the first element.
    //!
    //! @return const_iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator begin() const { return this->ptr(); }

    //! @brief Returns const iterator to the first element.
    //!
    //! @return const_iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator cbegin() const { return this->ptr(); }

    //! @brief Returns iterator to the one after the last element.
    //!
    //! @return iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator end() { return this->begin() + m_size; }

    //! @brief Returns const iterator to the one after the last element.
    //!
    //! @return const_iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator end() const { return this->begin() + m_size; }

    //! @brief Returns const iterator to the one after the last element.
    //!
    //! @return const_iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator cend() const { return this->cbegin() + m_size; }

    //! @brief Returns reverse iterator to the first element of the reversed container.
    //!
    //! @return reverse_iterator pointing to the beginning
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reverse_iterator rbegin() { return reverse_iterator(this->end()); }

    //! @brief Returns const reverse iterator to the first element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the beginning
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

    //! @brief Returns const reverse iterator to the first element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the beginning
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator crbegin() const { return const_reverse_iterator(this->end()); }

    //! @brief Returns reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return reverse_iterator pointing to the one after the last element
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reverse_iterator rend() { return reverse_iterator(this->begin()); }

    //! @brief Returns const reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the one after the last element
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

    //! @brief Returns const reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the one after the last element
    //! of the reversed varray.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator crend() const { return const_reverse_iterator(this->begin()); }

    //! @brief Returns container's capacity.
    //!
    //! @return container's capacity.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    static size_type capacity() { return Capacity; }

    //! @brief Returns container's capacity.
    //!
    //! @return container's capacity.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    static size_type max_size() { return Capacity; }

    //! @brief Returns the number of stored elements.
    //!
    //! @return Number of elements contained in the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type size() const { return m_size; }

    //! @brief Queries if the container contains elements.
    //!
    //! @return true if the number of elements contained in the
    //!   container is equal to 0.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    bool empty() const { return 0 == m_size; }

private:

    // @par Throws
    //   Nothing.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void move_ctor_dispatch(varray<value_type, C> & other, boost::true_type /*use_memop*/)
    {
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        m_size = other.m_size;
    }

    // @par Throws
    //   @li If boost::has_nothrow_move<Value>::value is true and Value's move constructor throws
    //   @li If boost::has_nothrow_move<Value>::value is false and Value's copy constructor throws.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void move_ctor_dispatch(varray<value_type, C> & other, boost::false_type /*use_memop*/)
    {
        namespace sv = varray_detail;
        sv::uninitialized_move_if_noexcept(other.begin(), other.end(), this->begin());                  // may throw
        m_size = other.m_size;
    }

    // @par Throws
    //   Nothing.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void move_assign_dispatch(varray<value_type, C> & other, boost::true_type /*use_memop*/)
    {
        this->clear();

        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        std::swap(m_size, other.m_size);
    }

    // @par Throws
    //   @li If boost::has_nothrow_move<Value>::value is true and Value's move constructor or move assignment throws
    //   @li If boost::has_nothrow_move<Value>::value is false and Value's copy constructor or move assignment throws.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void move_assign_dispatch(varray<value_type, C> & other, boost::false_type /*use_memop*/)
    {
        namespace sv = varray_detail;
        if ( m_size <= static_cast<size_type>(other.size()) )
        {
            sv::move_if_noexcept(other.begin(), other.begin() + m_size, this->begin());             // may throw
            // TODO - perform uninitialized_copy first?
            sv::uninitialized_move_if_noexcept(other.begin() + m_size, other.end(), this->end());   // may throw
        }
        else
        {
            sv::move_if_noexcept(other.begin(), other.end(), this->begin());                        // may throw
            sv::destroy(this->begin() + other.size(), this->end());
        }
        m_size = other.size(); // update end
    }

    // @par Throws
    //   Nothing.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void swap_dispatch(varray<value_type, C> & other, boost::true_type const& /*use_optimized_swap*/)
    {
        typedef typename
        boost::mpl::if_c<
            Capacity < C,
            aligned_storage_type,
            typename varray<value_type, C>::aligned_storage_type
        >::type
        storage_type;
        
        storage_type temp;
        Value * temp_ptr = reinterpret_cast<Value*>(temp.address());

        ::memcpy(temp_ptr, this->data(), sizeof(Value) * this->size());
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.size());
        ::memcpy(other.data(), temp_ptr, sizeof(Value) * this->size());

        std::swap(m_size, other.m_size);
    }

    // @par Throws
    //   If Value's move constructor or move assignment throws
    //   but only if use_memop_in_swap_and_move is false_type - default.
    // @par Complexity
    //   Linear O(N).
    template <std::size_t C>
    void swap_dispatch(varray<value_type, C> & other, boost::false_type const& /*use_optimized_swap*/)
    {
        namespace sv = varray_detail;

        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        if ( this->size() < other.size() )
            swap_dispatch_impl(this->begin(), this->end(), other.begin(), other.end(), use_memop_in_swap_and_move()); // may throw
        else
            swap_dispatch_impl(other.begin(), other.end(), this->begin(), this->end(), use_memop_in_swap_and_move()); // may throw
        std::swap(m_size, other.m_size);
    }

    // @par Throws
    //   Nothing.
    // @par Complexity
    //   Linear O(N).
    void swap_dispatch_impl(iterator first_sm, iterator last_sm, iterator first_la, iterator last_la, boost::true_type const& /*use_memop*/)
    {
        //BOOST_GEOMETRY_INDEX_ASSERT(std::distance(first_sm, last_sm) <= std::distance(first_la, last_la),
        //                            "incompatible ranges");

        namespace sv = varray_detail;
        for (; first_sm != last_sm ; ++first_sm, ++first_la)
        {
            boost::aligned_storage<
                sizeof(value_type),
                boost::alignment_of<value_type>::value
            > temp_storage;
            value_type * temp_ptr = reinterpret_cast<value_type*>(temp_storage.address());

            ::memcpy(temp_ptr, boost::addressof(*first_sm), sizeof(value_type));
            ::memcpy(boost::addressof(*first_sm), boost::addressof(*first_la), sizeof(value_type));
            ::memcpy(boost::addressof(*first_la), temp_ptr, sizeof(value_type));
        }

        ::memcpy(first_sm, first_la, sizeof(value_type) * std::distance(first_la, last_la));
    }

    // @par Throws
    //   If Value's move constructor or move assignment throws.
    // @par Complexity
    //   Linear O(N).
    void swap_dispatch_impl(iterator first_sm, iterator last_sm, iterator first_la, iterator last_la, boost::false_type const& /*use_memop*/)
    {
        //BOOST_GEOMETRY_INDEX_ASSERT(std::distance(first_sm, last_sm) <= std::distance(first_la, last_la),
        //                            "incompatible ranges");

        namespace sv = varray_detail;
        for (; first_sm != last_sm ; ++first_sm, ++first_la)
        {
            //boost::swap(*first_sm, *first_la);                                    // may throw
            value_type temp(boost::move(*first_sm));                                // may throw
            *first_sm = boost::move(*first_la);                                     // may throw
            *first_la = boost::move(temp);                                          // may throw
        }
        sv::uninitialized_move(first_la, last_la, first_sm);                        // may throw
        sv::destroy(first_la, last_la);
    }

    // insert

    // @par Throws
    //   If Value's move constructor, move assignment throws
    //   or if Value's copy constructor or copy assignment throws.
    // @par Complexity
    //   Linear O(N).
    template <typename Iterator>
    void insert_dispatch(iterator position, Iterator first, Iterator last, boost::random_access_traversal_tag const&)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversal<Iterator>)); // Make sure you passed a RandomAccessIterator
        
        errh::check_iterator_end_eq(*this, position);
        
        typename boost::iterator_difference<Iterator>::type
            count = std::distance(first, last);

        errh::check_capacity(*this, m_size + count);                                             // may throw

        if ( position == this->end() )
        {
            namespace sv = varray_detail;

            sv::uninitialized_copy(first, last, position);                                      // may throw
            m_size += count; // update end
        }
        else
        {
            this->insert_in_the_middle(position, first, last, count);                           // may throw
        }
    }

    // @par Throws
    //   If Value's move constructor, move assignment throws
    //   or if Value's copy constructor or copy assignment throws.
    // @par Complexity
    //   Linear O(N).
    template <typename Iterator, typename Traversal>
    void insert_dispatch(iterator position, Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        errh::check_iterator_end_eq(*this, position);

        if ( position == this->end() )
        {
            namespace sv = varray_detail;

            std::ptrdiff_t d = std::distance(position, this->begin() + Capacity);
            std::size_t count = sv::uninitialized_copy_s(first, last, position, d);                     // may throw
            
            errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? m_size + count : Capacity + 1);  // may throw

            m_size += count;
        }
        else
        {
            typename boost::iterator_difference<Iterator>::type
                count = std::distance(first, last);
            
            errh::check_capacity(*this, m_size + count);                                                // may throw

            this->insert_in_the_middle(position, first, last, count);                                   // may throw
        }
    }

    // @par Throws
    //   If Value's move constructor, move assignment throws
    //   or if Value's copy constructor or copy assignment throws.
    // @par Complexity
    //   Linear O(N).
    template <typename Iterator>
    void insert_in_the_middle(iterator position, Iterator first, Iterator last, difference_type count)
    {
        namespace sv = varray_detail;

        difference_type to_move = std::distance(position, this->end());

        // TODO - should following lines check for exception and revert to the old size?

        if ( count < to_move )
        {
            sv::uninitialized_move(this->end() - count, this->end(), this->end());              // may throw
            m_size += count; // update end
            sv::move_backward(position, position + to_move - count, this->end() - count);       // may throw
            sv::copy(first, last, position);                                                    // may throw
        }
        else
        {
            Iterator middle_iter = first;
            std::advance(middle_iter, to_move);

            sv::uninitialized_copy(middle_iter, last, this->end());                             // may throw
            m_size += count - to_move; // update end
            sv::uninitialized_move(position, position + to_move, position + count);             // may throw
            m_size += to_move; // update end
            sv::copy(first, middle_iter, position);                                             // may throw
        }
    }

    // assign

    // @par Throws
    //   If Value's constructor or assignment taking dereferenced Iterator throws.
    // @par Complexity
    //   Linear O(N).
    template <typename Iterator>
    void assign_dispatch(Iterator first, Iterator last, boost::random_access_traversal_tag const& /*not_random_access*/)
    {
        namespace sv = varray_detail;

        typename boost::iterator_difference<Iterator>::type
            s = std::distance(first, last);

        errh::check_capacity(*this, s);                                     // may throw

        if ( m_size <= static_cast<size_type>(s) )
        {
            sv::copy(first, first + m_size, this->begin());                 // may throw
            // TODO - perform uninitialized_copy first?
            sv::uninitialized_copy(first + m_size, last, this->end());      // may throw
        }
        else
        {
            sv::copy(first, last, this->begin());                           // may throw
            sv::destroy(this->begin() + s, this->end());
        }
        m_size = s; // update end
    }

    // @par Throws
    //   If Value's constructor or assignment taking dereferenced Iterator throws.
    // @par Complexity
    //   Linear O(N).
    template <typename Iterator, typename Traversal>
    void assign_dispatch(Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        namespace sv = varray_detail;

        size_type s = 0;
        iterator it = this->begin();

        for ( ; it != this->end() && first != last ; ++it, ++first, ++s )
            *it = *first;                                                                                   // may throw

        sv::destroy(it, this->end());

        std::ptrdiff_t d = std::distance(it, this->begin() + Capacity);
        std::size_t count = sv::uninitialized_copy_s(first, last, it, d);                                   // may throw
        s += count;

        errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? s : Capacity + 1);               // may throw

        m_size = s; // update end
    }

    pointer ptr()
    {
        return pointer(static_cast<Value*>(m_storage.address()));
    }

    const_pointer ptr() const
    {
        return const_pointer(static_cast<const Value*>(m_storage.address()));
    }

    size_type m_size;
    aligned_storage_type m_storage;
};

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<typename Value>
class varray<Value, 0>
{
    typedef varray_detail::varray_traits<Value, 0> vt;
    typedef varray_detail::checker<varray> errh;

public:
    typedef typename vt::value_type value_type;
    typedef typename vt::size_type size_type;
    typedef typename vt::difference_type difference_type;
    typedef typename vt::pointer pointer;
    typedef typename vt::const_pointer const_pointer;
    typedef typename vt::reference reference;
    typedef typename vt::const_reference const_reference;

    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    // nothrow
    varray() {}

    // strong
    explicit varray(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    varray(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    varray(varray const& /*other*/)
    {
        //errh::check_capacity(*this, count);
    }

    // strong
    template <std::size_t C>
    varray(varray<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
    }

    // strong
    template <typename Iterator>
    varray(Iterator first, Iterator last)
    {
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    varray & operator=(varray const& /*other*/)
    {
        //errh::check_capacity(*this, other.size());
        return *this;
    }

    // basic
    template <size_t C>
    varray & operator=(varray<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
        return *this;
    }

    // nothrow
    ~varray() {}

    // strong
    void resize(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    void resize(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    
    // nothrow
    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    void push_back(value_type const&)
    {
        errh::check_capacity(*this, 1);                                             // may throw
    }

    // nothrow
    void pop_back()
    {
        errh::check_not_empty(*this);
    }

    // basic
    void insert(iterator position, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, 1);                                             // may throw
    }

    // basic
    void insert(iterator position, size_type count, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, count);                                         // may throw
    }

    // basic
    template <typename Iterator>
    void insert(iterator, Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    void erase(iterator position)
    {
        errh::check_iterator_end_neq(*this, position);
    }

    // basic
    void erase(iterator first, iterator last)
    {
        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);

        //BOOST_GEOMETRY_INDEX_ASSERT(0 <= n, "invalid range");
    }

    // basic
    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    void assign(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                     // may throw
    }

    // nothrow
    void clear() {}

    // strong
    reference at(size_type i)
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // strong
    const_reference at(size_type i) const
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // nothrow
    reference operator[](size_type i)
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    const_reference operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    reference front()
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    // nothrow
    const_reference front() const
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    // nothrow
    reference back()
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    const_reference back() const
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    Value * data() { return boost::addressof(*(this->ptr())); }
    const Value * data() const { return boost::addressof(*(this->ptr())); }

    // nothrow
    iterator begin() { return this->ptr(); }
    const_iterator begin() const { return this->ptr(); }
    const_iterator cbegin() const { return this->ptr(); }
    iterator end() { return this->begin(); }
    const_iterator end() const { return this->begin(); }
    const_iterator cend() const { return this->cbegin(); }
    // nothrow
    reverse_iterator rbegin() { return reverse_iterator(this->end()); }
    const_reverse_iterator rbegin() const { return reverse_iterator(this->end()); }
    const_reverse_iterator crbegin() const { return reverse_iterator(this->end()); }
    reverse_iterator rend() { return reverse_iterator(this->begin()); }
    const_reverse_iterator rend() const { return reverse_iterator(this->begin()); }
    const_reverse_iterator crend() const { return reverse_iterator(this->begin()); }

    // nothrow
    size_type capacity() const { return 0; }
    size_type max_size() const { return 0; }
    size_type size() const { return 0; }
    bool empty() const { return true; }

private:
    pointer ptr()
    {
        return pointer(reinterpret_cast<Value*>(this));
    }

    const_pointer ptr() const
    {
        return const_pointer(reinterpret_cast<const Value*>(this));
    }
};

#endif // !BOOST_CONTAINER_DOXYGEN_INVOKED

//! @brief Checks if contents of two varrays are equal.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if containers have the same size and elements in both containers are equal.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator== (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

//! @brief Checks if contents of two varrays are not equal.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if containers have different size or elements in both containers are not equal.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator!= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(x==y);
}

//! @brief Lexicographically compares varrays.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if x compares lexicographically less than y.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator< (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

//! @brief Lexicographically compares varrays.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if y compares lexicographically less than x.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator> (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return y<x;
}

//! @brief Lexicographically compares varrays.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if y don't compare lexicographically less than x.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator<= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(y<x);
}

//! @brief Lexicographically compares varrays.
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @return     \c true if x don't compare lexicographically less than y.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
bool operator>= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(x<y);
}

//! @brief Swaps contents of two varrays.
//!
//! This function calls varray::swap().
//!
//! @ingroup varray_non_member
//!
//! @param x    The first varray.
//! @param y    The second varray.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2>
inline void swap(varray<V, C1> & x, varray<V, C2> & y)
{
    x.swap(y);
}

}}}} // namespace boost::geometry::index::detail

// TODO - REMOVE/CHANGE
#include <boost/container/detail/config_end.hpp>

#endif // BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_HPP

/* varray.hpp
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
*/