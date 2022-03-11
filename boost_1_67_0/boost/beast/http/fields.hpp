//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_FIELDS_HPP
#define BOOST_BEAST_HTTP_FIELDS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string_param.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/allocator.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A container for storing HTTP header fields.

    This container is designed to store the field value pairs that make
    up the fields and trailers in an HTTP message. Objects of this type
    are iterable, with each element holding the field name and field
    value.

    Field names are stored as-is, but comparisons are case-insensitive.
    The container behaves as a `std::multiset`; there will be a separate
    value for each occurrence of the same field name. When the container
    is iterated the fields are presented in the order of insertion, with
    fields having the same name following each other consecutively.

    Meets the requirements of <em>Fields</em>

    @tparam Allocator The allocator to use.
*/
template<class Allocator>
class basic_fields
#if ! BOOST_BEAST_DOXYGEN
    : private boost::empty_value<Allocator>
#endif
{
    // Fancy pointers are not supported
    static_assert(std::is_pointer<typename
        std::allocator_traits<Allocator>::pointer>::value,
        "Allocator must use regular pointers");

    friend class fields_test; // for `header`

    struct element;

    using off_t = std::uint16_t;

public:
    /// The type of allocator used.
    using allocator_type = Allocator;

    /// The type of element used to represent a field
    class value_type
    {
        friend class basic_fields;

        off_t off_;
        off_t len_;
        field f_;

        char*
        data() const;

        net::const_buffer
        buffer() const;

    protected:
        value_type(field name,
            string_view sname, string_view value);

    public:
        /// Constructor (deleted)
        value_type(value_type const&) = delete;

        /// Assignment (deleted)
        value_type& operator=(value_type const&) = delete;

        /// Returns the field enum, which can be @ref field::unknown
        field
        name() const;

        /// Returns the field name as a string
        string_view const
        name_string() const;

        /// Returns the value of the field
        string_view const
        value() const;
    };

    /** A strictly less predicate for comparing keys, using a case-insensitive comparison.

        The case-comparison operation is defined only for low-ASCII characters.
    */
#if BOOST_BEAST_DOXYGEN
    using key_compare = __implementation_defined__;
#else
    struct key_compare : beast::iless
#endif
    {
        /// Returns `true` if lhs is less than rhs using a strict ordering
        bool
        operator()(
            string_view lhs,
            value_type const& rhs) const noexcept
        {
            if(lhs.size() < rhs.name_string().size())
                return true;
            if(lhs.size() > rhs.name_string().size())
                return false;
            return iless::operator()(lhs, rhs.name_string());
        }

        /// Returns `true` if lhs is less than rhs using a strict ordering
        bool
        operator()(
            value_type const& lhs,
            string_view rhs) const noexcept
        {
            if(lhs.name_string().size() < rhs.size())
                return true;
            if(lhs.name_string().size() > rhs.size())
                return false;
            return iless::operator()(lhs.name_string(), rhs);
        }

        /// Returns `true` if lhs is less than rhs using a strict ordering
        bool
        operator()(
            value_type const& lhs,
            value_type const& rhs) const noexcept
        {
            if(lhs.name_string().size() < rhs.name_string().size())
                return true;
            if(lhs.name_string().size() > rhs.name_string().size())
                return false;
            return iless::operator()(lhs.name_string(), rhs.name_string());
        }
    };

    /// The algorithm used to serialize the header
#if BOOST_BEAST_DOXYGEN
    using writer = __implementation_defined__;
#else
    class writer;
#endif

private:
    struct element
        : public boost::intrusive::list_base_hook<
            boost::intrusive::link_mode<
                boost::intrusive::normal_link>>
        , public boost::intrusive::set_base_hook<
            boost::intrusive::link_mode<
                boost::intrusive::normal_link>>
        , public value_type
    {
        element(field name,
            string_view sname, string_view value);
    };

    using list_t = typename boost::intrusive::make_list<
        element,
        boost::intrusive::constant_time_size<false>
            >::type;

    using set_t = typename boost::intrusive::make_multiset<
        element,
        boost::intrusive::constant_time_size<true>,
        boost::intrusive::compare<key_compare>
            >::type;

    using align_type = typename
        boost::type_with_alignment<alignof(element)>::type;

    using rebind_type = typename
        beast::detail::allocator_traits<Allocator>::
            template rebind_alloc<align_type>;

    using alloc_traits =
        beast::detail::allocator_traits<rebind_type>;

    using size_type = typename
        beast::detail::allocator_traits<Allocator>::size_type;


public:
    /// Destructor
    ~basic_fields();

    /// Constructor.
    basic_fields() = default;

    /** Constructor.

        @param alloc The allocator to use.
    */
    explicit
    basic_fields(Allocator const& alloc) noexcept;

    /** Move constructor.

        The state of the moved-from object is
        as if constructed using the same allocator.
    */
    basic_fields(basic_fields&&) noexcept;

    /** Move constructor.

        The state of the moved-from object is
        as if constructed using the same allocator.

        @param alloc The allocator to use.
    */
    basic_fields(basic_fields&&, Allocator const& alloc);

    /// Copy constructor.
    basic_fields(basic_fields const&);

    /** Copy constructor.

        @param alloc The allocator to use.
    */
    basic_fields(basic_fields const&, Allocator const& alloc);

    /// Copy constructor.
    template<class OtherAlloc>
    basic_fields(basic_fields<OtherAlloc> const&);

    /** Copy constructor.

        @param alloc The allocator to use.
    */
    template<class OtherAlloc>
    basic_fields(basic_fields<OtherAlloc> const&,
        Allocator const& alloc);

    /** Move assignment.

        The state of the moved-from object is
        as if constructed using the same allocator.
    */
    basic_fields& operator=(basic_fields&&) noexcept(
        alloc_traits::propagate_on_container_move_assignment::value);

    /// Copy assignment.
    basic_fields& operator=(basic_fields const&);

    /// Copy assignment.
    template<class OtherAlloc>
    basic_fields& operator=(basic_fields<OtherAlloc> const&);

public:
    /// A constant iterator to the field sequence.
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    using const_iterator = typename list_t::const_iterator;
#endif

    /// A constant iterator to the field sequence.
    using iterator = const_iterator;

    /// Return a copy of the allocator associated with the container.
    allocator_type
    get_allocator() const
    {
        return this->get();
    }

    //--------------------------------------------------------------------------
    //
    // Element access
    //
    //--------------------------------------------------------------------------

    /** Returns the value for a field, or throws an exception.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The name of the field.

        @return The field value.

        @throws std::out_of_range if the field is not found.
    */
    string_view const
    at(field name) const;

    /** Returns the value for a field, or throws an exception.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The name of the field.

        @return The field value.

        @throws std::out_of_range if the field is not found.
    */
    string_view const
    at(string_view name) const;

    /** Returns the value for a field, or `""` if it does not exist.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The name of the field.
    */
    string_view const
    operator[](field name) const;

    /** Returns the value for a case-insensitive matching header, or `""` if it does not exist.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The name of the field.
    */
    string_view const
    operator[](string_view name) const;

    //--------------------------------------------------------------------------
    //
    // Iterators
    //
    //--------------------------------------------------------------------------

    /// Return a const iterator to the beginning of the field sequence.
    const_iterator
    begin() const
    {
        return list_.cbegin();
    }

    /// Return a const iterator to the end of the field sequence.
    const_iterator
    end() const
    {
        return list_.cend();
    }

    /// Return a const iterator to the beginning of the field sequence.
    const_iterator
    cbegin() const
    {
        return list_.cbegin();
    }

    /// Return a const iterator to the end of the field sequence.
    const_iterator
    cend() const
    {
        return list_.cend();
    }

    //--------------------------------------------------------------------------
    //
    // Capacity
    //
    //--------------------------------------------------------------------------

private:
    // VFALCO Since the header and message derive from Fields,
    //        what does the expression m.empty() mean? Its confusing.
    bool
    empty() const
    {
        return list_.empty();
    }
public:

    //--------------------------------------------------------------------------
    //
    // Modifiers
    //
    //--------------------------------------------------------------------------

    /** Remove all fields from the container

        All references, pointers, or iterators referring to contained
        elements are invalidated. All past-the-end iterators are also
        invalidated.

        @par Postconditions:
        @code
            std::distance(this->begin(), this->end()) == 0
        @endcode
    */
    void
    clear();

    /** Insert a field.

        If one or more fields with the same name already exist,
        the new field will be inserted after the last field with
        the matching name, in serialization order.

        @param name The field name.

        @param value The value of the field, as a @ref string_param
    */
    void
    insert(field name, string_param const& value);

    /** Insert a field.

        If one or more fields with the same name already exist,
        the new field will be inserted after the last field with
        the matching name, in serialization order.

        @param name The field name.

        @param value The value of the field, as a @ref string_param
    */
    void
    insert(string_view name, string_param const& value);

    /** Insert a field.

        If one or more fields with the same name already exist,
        the new field will be inserted after the last field with
        the matching name, in serialization order.

        @param name The field name.

        @param name_string The literal text corresponding to the
        field name. If `name != field::unknown`, then this value
        must be equal to `to_string(name)` using a case-insensitive
        comparison, otherwise the behavior is undefined.

        @param value The value of the field, as a @ref string_param
    */
    void
    insert(field name, string_view name_string,
        string_param const& value);

    /** Set a field value, removing any other instances of that field.

        First removes any values with matching field names, then
        inserts the new field value.

        @param name The field name.

        @param value The value of the field, as a @ref string_param

        @return The field value.
    */
    void
    set(field name, string_param const& value);

    /** Set a field value, removing any other instances of that field.

        First removes any values with matching field names, then
        inserts the new field value.

        @param name The field name.

        @param value The value of the field, as a @ref string_param
    */
    void
    set(string_view name, string_param const& value);

    /** Remove a field.

        References and iterators to the erased elements are
        invalidated. Other references and iterators are not
        affected.

        @param pos An iterator to the element to remove.

        @return An iterator following the last removed element.
        If the iterator refers to the last element, the end()
        iterator is returned.
    */
    const_iterator
    erase(const_iterator pos);

    /** Remove all fields with the specified name.

        All fields with the same field name are erased from the
        container.
        References and iterators to the erased elements are
        invalidated. Other references and iterators are not
        affected.

        @param name The field name.

        @return The number of fields removed.
    */
    std::size_t
    erase(field name);

    /** Remove all fields with the specified name.

        All fields with the same field name are erased from the
        container.
        References and iterators to the erased elements are
        invalidated. Other references and iterators are not
        affected.

        @param name The field name.

        @return The number of fields removed.
    */
    std::size_t
    erase(string_view name);

    /** Return a buffer sequence representing the trailers.

        This function returns a buffer sequence holding the
        serialized representation of the trailer fields promised
        in the Accept field. Before calling this function the
        Accept field must contain the exact trailer fields
        desired. Each field must also exist.
    */


    /// Swap this container with another
    void
    swap(basic_fields& other);

    /// Swap two field containers
    template<class Alloc>
    friend
    void
    swap(basic_fields<Alloc>& lhs, basic_fields<Alloc>& rhs);

    //--------------------------------------------------------------------------
    //
    // Lookup
    //
    //--------------------------------------------------------------------------

    /** Return the number of fields with the specified name.

        @param name The field name.
    */
    std::size_t
    count(field name) const;

    /** Return the number of fields with the specified name.

        @param name The field name.
    */
    std::size_t
    count(string_view name) const;

    /** Returns an iterator to the case-insensitive matching field.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The field name.

        @return An iterator to the matching field, or `end()` if
        no match was found.
    */
    const_iterator
    find(field name) const;

    /** Returns an iterator to the case-insensitive matching field name.

        If more than one field with the specified name exists, the
        first field defined by insertion order is returned.

        @param name The field name.

        @return An iterator to the matching field, or `end()` if
        no match was found.
    */
    const_iterator
    find(string_view name) const;

    /** Returns a range of iterators to the fields with the specified name.

        @param name The field name.

        @return A range of iterators to fields with the same name,
        otherwise an empty range.
    */
    std::pair<const_iterator, const_iterator>
    equal_range(field name) const;

    /** Returns a range of iterators to the fields with the specified name.

        @param name The field name.

        @return A range of iterators to fields with the same name,
        otherwise an empty range.
    */
    std::pair<const_iterator, const_iterator>
    equal_range(string_view name) const;

    //--------------------------------------------------------------------------
    //
    // Observers
    //
    //--------------------------------------------------------------------------

    /// Returns a copy of the key comparison function
    key_compare
    key_comp() const
    {
        return key_compare{};
    }

protected:
    /** Returns the request-method string.

        @note Only called for requests.
    */
    string_view
    get_method_impl() const;

    /** Returns the request-target string.

        @note Only called for requests.
    */
    string_view
    get_target_impl() const;

    /** Returns the response reason-phrase string.

        @note Only called for responses.
    */
    string_view
    get_reason_impl() const;

    /** Returns the chunked Transfer-Encoding setting
    */
    bool
    get_chunked_impl() const;

    /** Returns the keep-alive setting
    */
    bool
    get_keep_alive_impl(unsigned version) const;

    /** Returns `true` if the Content-Length field is present.
    */
    bool
    has_content_length_impl() const;

    /** Set or clear the method string.

        @note Only called for requests.
    */
    void
    set_method_impl(string_view s);

    /** Set or clear the target string.

        @note Only called for requests.
    */
    void
    set_target_impl(string_view s);

    /** Set or clear the reason string.

        @note Only called for responses.
    */
    void
    set_reason_impl(string_view s);

    /** Adjusts the chunked Transfer-Encoding value
    */
    void
    set_chunked_impl(bool value);

    /** Sets or clears the Content-Length field
    */
    void
    set_content_length_impl(
        boost::optional<std::uint64_t> const& value);

    /** Adjusts the Connection field
    */
    void
    set_keep_alive_impl(
        unsigned version, bool keep_alive);

private:
    template<class OtherAlloc>
    friend class basic_fields;

    element&
    new_element(field name,
        string_view sname, string_view value);

    void
    delete_element(element& e);

    void
    set_element(element& e);

    void
    realloc_string(string_view& dest, string_view s);

    void
    realloc_target(
        string_view& dest, string_view s);

    template<class OtherAlloc>
    void
    copy_all(basic_fields<OtherAlloc> const&);

    void
    clear_all();

    void
    delete_list();

    void
    move_assign(basic_fields&, std::true_type);

    void
    move_assign(basic_fields&, std::false_type);

    void
    copy_assign(basic_fields const&, std::true_type);

    void
    copy_assign(basic_fields const&, std::false_type);

    void
    swap(basic_fields& other, std::true_type);

    void
    swap(basic_fields& other, std::false_type);

    set_t set_;
    list_t list_;
    string_view method_;
    string_view target_or_reason_;
};

/// A typical HTTP header fields container
using fields = basic_fields<std::allocator<char>>;

} // http
} // beast
} // boost

#include <boost/beast/http/impl/fields.hpp>

#endif

/* fields.hpp
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
*/