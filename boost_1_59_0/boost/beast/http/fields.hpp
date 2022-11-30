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

        @param value The value of the field, as a @ref string_view
    */
    void
    insert(field name, string_view const& value);

    /* Set a field from a null pointer (deleted).
    */
    void
    insert(field, std::nullptr_t) = delete;

    /** Insert a field.

        If one or more fields with the same name already exist,
        the new field will be inserted after the last field with
        the matching name, in serialization order.

        @param name The field name.

        @param value The value of the field, as a @ref string_view
    */
    void
    insert(string_view name, string_view const& value);

    /* Insert a field from a null pointer (deleted).
    */
    void
    insert(string_view, std::nullptr_t) = delete;

    /** Insert a field.

        If one or more fields with the same name already exist,
        the new field will be inserted after the last field with
        the matching name, in serialization order.

        @param name The field name.

        @param name_string The literal text corresponding to the
        field name. If `name != field::unknown`, then this value
        must be equal to `to_string(name)` using a case-insensitive
        comparison, otherwise the behavior is undefined.

        @param value The value of the field, as a @ref string_view
    */
    void
    insert(field name, string_view name_string,
           string_view const& value);

    void
    insert(field, string_view, std::nullptr_t) = delete;

    /** Set a field value, removing any other instances of that field.

        First removes any values with matching field names, then
        inserts the new field value.

        @param name The field name.

        @param value The value of the field, as a @ref string_view

        @return The field value.
    */
    void
    set(field name, string_view const& value);

    void
    set(field, std::nullptr_t) = delete;

    /** Set a field value, removing any other instances of that field.

        First removes any values with matching field names, then
        inserts the new field value.

        @param name The field name.

        @param value The value of the field, as a @ref string_view
    */
    void
    set(string_view name, string_view const& value);

    void
    set(string_view, std::nullptr_t) = delete;

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
TFyQwiWP3lix8ju8WeQo36TswyFFG96uE7OSrGX2xbsuah2RrnyLgMDvUJ993O3V4mdq/gIPeVOiNcOS7x91XricUyu4jOuhOXhEZRZ5UGMs7buTlEoA/wb9TqJMielgbgmcc5Pu76/r7+wnwFyEa/90F7cw3T2Lfmv0dhTydk1DZkD+5zjL5MciiloTxQQ7nhXuus14EncEHpEnZ7f6QsyD3y/wMFz6ksod2xug44QWktCmGXKyT8/bUk0x/aZUC5PY54HB+eKbs+6RfaW5qIm3MWuxztbASWhIy2OG8nmGa4hxRyfRsVnif1WeTipFDWgC7Iz6ckePB2iykzutdHXxonYIQMej/3ilLafXFnyYThq72+235VVafIaIgl2/z1JjToTvlvNO3PHl0P3xOmJtsaHbx0WFgeuW4I6/WyEHAA0DfgXdb4HZ/ioinPFYDLpjRMssG5jzPQtGLSCvGWW4OwAaq8or8BMcP1NkjRPTMeNSavucKeecvW+GGkc1JtAaP8eZmdllEiyMHVVazLNRnB64fQggNIRP72jK96sixZPS9wwj26p2wkqsTKzLs5I79rvVnYTr9FgDSqgWonDnT6ssuvW+e6H4Z5dnjXnFbi9xdpD5z+sQlwImIT84Mdb+ss3r4VIqngkaCrfd2qfngHLOAQx3xMyFL5PzaY7HHpLpvZDeGnI+afGhQxA70mozbKqPOTp3EaKOeY+56GrterRCtFspTVoMjuUjk/0Jc3xzzll62F0t38s1iYHzI+dKa6nCe3d16dhHwrTotWilVq0kho6T4tH8byfLISooZE5SJSBVRv03+5vQiedxFSUg/NZGuIlOGmIIWHZeH1T5CJeJs+xQc00mKwmZILALrvgD0Mj4CK28HS8if8LivoOOd0GBs0adesUlpduruZ5uo1pPrj2RI5RfMAj6BYomiFot3cHj3la9px4IeqlacEQig5HGBs51Ys/g31gdvwfmKD1gtNyPH52wRaGetr+/nhe2f3r0b1kGLnvdT1J1Rjh+ZT93UlyuhBsfu7VN62QHv7tpLzW9ohfddoVJuaErFk5gHcsR1Qgjxj7Aaketv33fjxZSZoKBQ9AzVI+qG37CLDjUIgRB6vdfqVSlVkvpnfDyn7py3KXNeBYvVaQcThnTSHOEuqawQesO7Cj+bjG2K49giivG7TYdQ2f5gV0T0U9gaFcj90ZCMBAt7Y9wUxItyImQWEP32iAJnwUV7nTIapwv2oVFNqvR8Od/LBM2N1PtM2XfViM5knAdESmmiBocWDVLp+ueMBsUIBBNgVe1ozON72uGUdj2ImDg1q7YtiwV4gVr/acc157C6D154QNUx4TXtK8J31dH2t05QH20Vbicrn+K4XtPVgjX27VlnVdfcMMK42jjAkNvopjJ3Tr14ONdDtbY9En97vrPXvZjbB5JHsA5r1TaSm2eSQZvrQ+ECd8UzBn2wjJCp7nV4+vtfCUWjVTU2xcvCydY26zBQq0nVUCb2wS+3tSazMnlHkkz3z+6xEfbyZyYiy05fgmgFWfBczNwJpcIVNvY6qJCXuZhPG8mDDYy4bmJfd5D5WWG/tg3XOPFc3vCCaZw63Cir1n3/CyMcaeCxbxVbRetNwjWMHNrRiDyBRObc1KCjLIwIfbs4lXCFZLjizRkIfVJHTjICoHhPi80Oo9r9IWTx8rOed84nmfHmD8w5t4WyU+2W2XOI+Rxj+VG/Jspz01/IUhgzi4UwbOiwu+sB72LaegErpm+0JrnoPmLoqQv97/EM1bCvtHNiFy9EqpxeW3LAOgfW1Gdh3Q2Zh02BEcw+I0s17qvTxk95dqOxuKt06+WcgybzMNCOXChHnu3367hbhuLCVaKOkVHPpMw/4BfBprb5WqDfd9h4EG4atLalPZaXOBNkRsCUsctLfMdMMonK3NtS8tw9oJ/7SpuVBDFbv5IuzGhc7BrK7D4QYo04iSc1ZPB67SQD9Wr+OgVP8Ex9JTxJr1tewBoi8mQekhlSU2GScrxKao0lhzhI9jfVwgKO5il4P6DC9suJGZKwTfCHUsoLw96iHr83+pmFZSSDE/2rvVZ7IToliD3g/8E4U7WuIIW7/JkhvNuM4gIx1WwX7alFaDMcPxVjbHxGbWOesZ1c3/mF2N+2B4j6PMPz/zznnF2idiGhDiNmcWJ7Nb/4btrFjWqPMgthdol3IljSxbdowzLGbVyVjEtcAP0mOXNEvKuh7Lyy3hED0QJ4LGsgyRg0/DhraRAtPASYuGQn5fqqlMuOB0EXQpnRl6/lqrobXzvsq49KT5Jf7z1F4xwvxq9HtQJ7IWSavq4iKev0k8rh/ho4Lja1lSz5LSfZlWveE4Tnlct/MDnCx62h14gB4UWpsWoOIrNQyBqzwZzsAor3Qy4gco6qAs5jb8SjQ0auAi+rNyROE88ffDM97ioGynOBmTNkb4QNCY0TI+Jc35bD/LK8NziLnutlGl9fY5abS6+gmlMQBVBmR3R4RluCv5ctI1xp9THSRtk9AhIDeldnF6X9+TbeqjuuJJ6z9a2Tkxpdd2U5Zyx+NqcVyf/pqoh/fOD80QUPl7O3SWNHTwg0IV03brDah2sQuKKUphjl0Q3uQjViStrfui964C457H+6+1crbnl0bLciorgawMypxOqDWwYUgIt2jZNGBpucVIv2fHkljcszYMWYfrtENmyu+LUmIX0MbK9JC+t9h505XZgMeh8Vha766hMWaySxUCunNYhGSx8K3ft9Z3y9eBrXB4xFq0MU6PJAzn1SIjRsTZ3X5ZLxL+EahpWAlP6ZsRe5IwCgzD1dmk9jCI79YBdYjZjISUs+3y5a7Qh+7FyuA+KMHON6OjnZ602hUbE+E95jmpl7OqcR9BrOT5o3k2M2dmAwoZKe19GyR49YbJT97n81Ll+9Ln/4mVWvvrPB/G2iTwm05lMwSpkDjV2Ko/U+xrJI6dz92km2Wn8c48kUFGTXi1+C0esx1b7O5ujw7g2G6Bh93Fbu7pmun862Wew1NCv2Pk6RxfGNJDk3caVqc8tPoXYBr0SVXRvu61yvJ6w3/NrNW4sU88lm31LtH4DV9HDHRNk2c3AQgUUTn+FCW4TzuSpVPYMdC2PvMZwHaU+fIfAo4LAXiqsxCUTDGbjI168sNngyuh4fxY7tDm9PsR3h7acwyx955Q8Ex3hm1mvaEtfw41RrGjujnkgW3+lEfJFYR7IGIIwdZ4WZzQDhHRxXDopznyZ9ZZFkw04z/gpMR9He0iy7MepJH3gmxj/oVzlpCla4BjUoc/qI5mlccSpZpwwovpX+5BjwTrJVl30fzlaaw/HD8XNNtygncUYcKMMLlmHdKCjTRuJdXSOYiz+6W6FH1lMJVSanHcNxDa8OptbpOObFq3b7oeHYp+gyL79wsNdEtndJ+0S5L53cTGevyd7EDAPrymqSy94pz/uX/LPrefjcx5ai+1aLmLjotwOWf9Jzi6e++f9IYAZc1twP3is+B4yDQORbgJiIw6RwhMwKqXgeWdoR8ROkUN0l4RLUlwYBNZG+DYw6+FIOZFjOM/D18C2qmlZE6HbKMZK2DW2utoy8a/VmvVh5OOGZcOU5mHbRiYO3mqtJf8Uz68/P4HV4pT43slHRChkjBNwN2wlceK7w6hEF7FT+PZRIQ6fpJdFG6nf/8UPM52WNcZG+Qj9ShYSb2PeKC7yluH0Xvqbm4kFnqEuuccwJ0it8NU4stxE8W+qIo3HqZojrdYdoqYGxM1QIaExEepWh17UVOsfwKUnupyA/ozWyFgN+QeXqIongiFUFNN8ldC/ax20a9D4jd10hnNLJ16XW7qTkn0QkB+OPFQW64UKqs0yXGvCxef4jh+7BisPSuTSR2sCZWnaEQVWkmQC3R5r/82AmGeTXcFUT3RaJtHR8X967pJqLKeQhgGFVJOElBLBHNs7vpqzJO2HyVrNbNBC0SO1Iz6PFmmxHmZ2yX8XESCLoPivWvc1uyRYbefV2jbUW4eHXso/AtqP3Z32Vsr4p/WS6WsIV7Qs60SLuvrh+IxWXC2z7NF8giYCmkECZWS/PazPLq1BQwVBB2KL6SaLh/6JXIbXEARkd8otIOmCiKNxu71n3OQGiwLnz2x5xzKKLSKqcTU0E2AqRtEpRXU5QRzDKXebt1tbNMGQrUyF29HiG9tQt7H4KapWkdW7wD27byxIiUiKcFPJKUoz7U5UIzQGpn77pvN6U7AGdPgt4sLrxlI5s/3hg7uOCuRz+IvzuLIToffJ47net/sbpg5S06iRF2YS12QrJcPhapuMHuYct9ko5ivGrV166vQO49CT7o0/ZuPDby9Rc49mKwsCC1+ydZe/VoA8hdRQXXl1yNH2GxKWCAhbgectMhO0e/pArn5GvPGdKrck4W4D7nsO/F8aijW0eg102Spl0D9KsH+lBewoiyM5HVQnQLpJhuDvkHCyz0kUW0ZINhqss7FXh7yC3nb49Hw+WVTp97UgEIkolKbezI26oZWneVmkHm4NoI9S8YXGgNT38h6G7GIVNMBrHsRapForfDh8Hq5Yy/BXtv+bo1GBWOYgyWFn2iFyd0tzBpuszWwCqf8doBDj5qpFT+nOxpn7dvawW9yZcmgfAwINo58fSVX3lWeS3ZE3uhiFSZXjXV8YmovRvKDMj1l65YSiR0N8RzQ9/fxedLQS5kxdQt1zn68H3/udPyEMsmm/3e6ydlvsdEAoks5MAAn5DLN+VSt4Tl4yF8znNQu5wjo513V/Xz8MAIdkTKqfQdepbGm/J1k44ivBDvj1RT+5AzQN1ugcxS3ch8HBBFhiBdAWaOkmE89bux2cTsFlbdsOIEQtyAt4TSpE8BZq/Zi+U0nS4ZCt4YX/ocyP897R897B5ByGN+dcIAuGbKnztaEdze6rPqfA1CqHXb2gcKSI/ZKaElztKvdfWnbjJZl/YACqtp+gAvn3TZ/GUafhQPf0Od/knfayJEXWYL/kTIXmQPzcncrt9aJc110v4oYD0A2YoYYCQeYKBr6+fIwdY3D+ft3j8yZBvfyP+274lqVRerZ97HFO3tlOmNmPM1qk6DiboabvxiJwY2xZpPZwOhxWuMZCYi5wbyBVUTdcdbUfin/O4/qcSutJdUEL07krvXDK6mQHSKj9kn9R5UpZp5LNen8NWEY64HtaLShCOv+p5GuASx5ppZw931ilqxHMBDDbdMUzPlYq07JuOzRgiQpCcS4i3fS47tIyEqLuP4MT44MeIWtaGE81xhZx+7ypxRNtxO0+aNliaDuIH3Y7zkrpZUKhuKi2UPmUUD482+KQ2Ai4uRT/Cyd0PrMITOPzeBKW/YzG1iXex/KNTZ2UFZsUtjaOUr9S3Ltsk18jmaH+L2t49ky0FFo4QJDTF7KHxEQj/AqBZ9pYnPuEeTdqy21gGm+yC/rNti2AvkHNO+ugzKGn0rJFYHHHt/ufhrY+7fsgFXVp1iN4WW0U4/Bctjvf/v7cXgGDFupjZeyItJBdJhz3iFN3hScdnND7umPf/cuwdDqmVxyLRfisM+Q6TiiPec5DYDxyh1VfrwZXACB7IJOGJcs625rxWmkr1SmzAYdmH2lhmFYWqTvVX4mMVLrO6zRKdtE5SiUY5KDMhQltgD7PbQiJ4i+FC8CAabjufidXjUwwk9Du6YLutI9tu/gF7EN6tmPKGthUauCQ13MR7qBjkbfp+n4oEcC/D6O3PziF8rps7+do/+DuWTn1lskJMdrCw9I2wpz0ePWPbWxrmc5drSZ84NhyLQC5S+iU0UsBHSRCZgnWULNQ3gGtMqVjdNieCbpl66DSu4tPaXwkqfzDRHi6dGuPHLSqqJrWgGf8HIJ/feewJt92JCqM+nWX0rPxJuIi+URSnXB47yTXpnfUPoYrCMrZejQjO1UQ+g+76HRJ48Qffnjk7dXM6lnm6JGrEQO1gfruban0y5of2oD4gEBH0S9ZG3dlXOCJ5Jn3qxpZ7baXenc+66CdT2eWMTO+6utRTPf3v6ZYXxIUelFa8hSe4mf9zrVVmg9d1jJVD3/S6fdG5x8rR1S1bLXPQgYgtLgjXajxoB4ZLtwFVaglVyATdYfVMi48xV0rx6bWyxMUl9VCw6rxKgX+8cFIulWIuDylVXujmkUogipTyp1o/iie3n//VHo54tVedlUcF//+mGItkXAXhdM5rkfYX+OmrKiZqGzfnuC7wyJrLgND4q1tnD6B1rBsUDg1RWme5LPskEHckwYxLJYlXwm7hXCXomt/XNbSku6+kpRQPkLiPsnF4CxF1rWYUWFG3zK6EtxP4TrAZ1iR1jjAToxpF8v5h9OY8bp8BuJI9Bar3Ke/EJ8ntDmeP4iGIG8gocRxux6KGOiaBByNbfVrXB87kSKgkN4ctl6GOabpE2JelHxtE2B7O/9GZEoarGg7IOgoh0cgiK6Ohzu2bDpb2Mam0YiIagTlYZ4OHyY4HDtpdEc3nunKcJzUTkQ5YhmrH39EXM34fN0XGj2TnbjxZp1r/voj8LyTEkDqf0D4tUsYT9ceKWGVs0pjQPl1VlHjHWvxSGCCNoa7Tw0iJARrCbonAJFY0WRziIKQMO+HKFYIUQvk8tp+30pRsDlYCM30XY2iAYWuT2or9zB2c4+KiWLOPiRhaC+etPHcxz19xz0iOcHU0arWPV+S7i5/e7afcQNIgkMiaSPCug3R6Cp2PPfKsbmn1QzlB4GOGP+X1CqtVqP9LOVLhCdzawitNKMYQNt9N05DaOsJDnYawXvMYtW0pHoKc5wdaHWzaWk4uaBpVx1aNvHMtmjXpXDM4dQWh/n8ZhenptEa2rMwD0mrf2OHLgYukcs5jyUit03HRqh8fNw+qrJ5rJtG047pIXQW+LkavPU67ZL8RHAT3hzWdQdUs3n33cOk8dRNw2Pq/kEkJyEIEPExdoo/2cuwbjfLhmfv0ihRgKWIMkObNJg2sR+S4fqmou49PGy8Wm2X6OOqEdR20UI8rfDETxu/0+pR4J/repiXRgXyLpYPdKywJpfRCjxHaKt088Z4IK5HUn1PjRJCDr2N1FrN9fbKNcEZ9U1xbPPqsXtGfPQcGqOPraEQMeYhdwLsc2DfiO18PvYJlRl+BJF0T9r8Q+4yoV+z2QOHZ528B4yWeJ0RmRO07Rxbdsk/5w0mgBrs0F+imF63CnkUfb20E7UHpXvbp7pxMgd9xB1dHkgLPm8lPuUXfDsG642funZD6EjUneo7nOI8LhZeAXMoRNBSBmigsBDxNgqjOV8PJSGLyDE/QlqQFeCSFwaQBHg3HX6CwF6Lmk5Siwdombm117vOo2864DVWM+wfvoyGtN460xN6bTuvW0X9l0B0SozmgVJymqREcafaVv5u/Dy+RzWycwO2lEj3c8Zj617qcrIZy0pZeDbov3xi4Y0EhBxgm4pxR3YTQMgQC86NMafKSEw+5SaCoefjbll7kGhMEKUm7Re++0leFUEg7H3i+YONgjGNrjE6bUXnftzYrtyiWRWj6STq/nmw0ZfugKhxH5ybPN/j4kMYPSCMyE6nnW7hNXx8cn+SJ+Y43UOUPoaDMRcyiIr9ZS7GuxENbzScQ0KGoeOC+Yhg9fr5gULYqPudMj6iVRNgV5RxAkapl6BXeVjf
*/