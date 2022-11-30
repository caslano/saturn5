//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_VALUE_STACK_HPP
#define BOOST_JSON_VALUE_STACK_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/error.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/value.hpp>
#include <stddef.h>

BOOST_JSON_NS_BEGIN

//----------------------------------------------------------

/** A stack of @ref value elements, for building a document.

    This stack of @ref value allows iterative
    construction of a JSON document in memory.
    The implementation uses temporary internal
    storage to buffer elements so that arrays, objects,
    and strings in the document are constructed using a
    single memory allocation. This improves performance
    and makes efficient use of the @ref memory_resource
    used to create the resulting @ref value.

    Temporary storage used by the implementation
    initially comes from an optional memory buffer
    owned by the caller. If that storage is exhausted,
    then memory is obtained dynamically from the
    @ref memory_resource provided on construction.

    @par Usage

    Construct the stack with an optional initial
    temporary buffer, and a @ref storage_ptr to use for
    more storage when the initial buffer is exhausted.
    Then to build a @ref value, first call @ref reset
    and optionally specify the @ref memory_resource
    which will be used for the value. Then push elements
    onto the stack by calling the corresponding functions.
    After the document has been fully created, call
    @ref release to acquire ownership of the top-level
    @ref value.

    @par Performance

    The initial buffer and any dynamically allocated
    temporary buffers are retained until the stack
    is destroyed. This improves performance when using
    a single stack instance to produce multiple
    values.

    @par Example

    The following code constructs a @ref value which
    when serialized produces a JSON object with three
    elements. It uses a local buffer for the temporary
    storage, and a separate local buffer for the storage
    of the resulting value. No memory is dynamically
    allocated; this shows how to construct a value
    without using the heap.

    @code

    // This example builds a json::value without any dynamic memory allocations:

    // Construct the value stack using a local buffer
    unsigned char temp[4096];
    value_stack st( storage_ptr(), temp, sizeof(temp) );

    // Create a static resource with a local initial buffer
    unsigned char buf[4096];
    static_resource mr( buf, sizeof(buf) );

    // All values on the stack will use `mr`
    st.reset(&mr);

    // Push the key/value pair "a":1.
    st.push_key("a");
    st.push_int64(1);

    // Push "b":null
    st.push_key("b");
    st.push_null();

    // Push "c":"hello"
    st.push_key("c");
    st.push_string("hello");

    // Pop the three key/value pairs and push an object with those three values.
    st.push_object(3);

    // Pop the object from the stack and take ownership.
    value jv = st.release();

    assert( serialize(jv) == "{\"a\":1,\"b\":null,\"c\":\"hello\"}" );

    // At this point we could re-use the stack by calling reset

    @endcode

    @par Thread Safety

    Distinct instances may be accessed concurrently.
    Non-const member functions of a shared instance
    may not be called concurrently with any other
    member functions of that instance.
*/
class value_stack
{
    class stack
    {
        enum
        {
            min_size_ = 16
        };

        storage_ptr sp_;
        void* temp_;
        value* begin_;
        value* top_;
        value* end_;
        // string starts at top_+1
        std::size_t chars_ = 0;
        bool run_dtors_ = true;

    public:
        inline ~stack();
        inline stack(
            storage_ptr sp,
            void* temp, std::size_t size) noexcept;
        inline void run_dtors(bool b) noexcept;
        inline std::size_t size() const noexcept;
        inline bool has_chars();

        inline void clear() noexcept;
        inline void maybe_grow();
        inline void grow_one();
        inline void grow(std::size_t nchars);

        inline void append(string_view s);
        inline string_view release_string() noexcept;
        inline value* release(std::size_t n) noexcept;
        template<class... Args> value& push(Args&&... args);
        template<class Unchecked> void exchange(Unchecked&& u);
    };

    stack st_;
    storage_ptr sp_;

public:
    /// Copy constructor (deleted)
    value_stack(
        value_stack const&) = delete;

    /// Copy assignment (deleted)
    value_stack& operator=(
        value_stack const&) = delete;

    /** Destructor.

        All dynamically allocated memory and
        partial or complete elements is freed.

        @par Complexity
        Linear in the size of partial results.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    ~value_stack();

    /** Constructor.

        Constructs an empty stack. Before any
        @ref value can be built, the function
        @ref reset must be called.

        The `sp` parameter is only used to allocate
        intermediate storage; it will not be used
        for the @ref value returned by @ref release.

        @param sp A pointer to the @ref memory_resource
        to use for intermediate storage allocations. If
        this argument is omitted, the default memory
        resource is used.

        @param temp_buffer A pointer to a caller-owned
        buffer which will be used to store temporary
        data used while building the value. If this
        pointer is null, the builder will use the
        storage pointer to allocate temporary data.

        @param temp_size The number of valid bytes of
        storage pointed to by `temp_buffer`.
    */
    BOOST_JSON_DECL
    value_stack(
        storage_ptr sp = {},
        unsigned char* temp_buffer = nullptr,
        std::size_t temp_size = 0) noexcept;

    /** Prepare to build a new document.

        This function must be called before constructing
        a new top-level @ref value. Any previously existing
        partial or complete elements are destroyed, but
        internal dynamically allocated memory is preserved
        which may be reused to build new values.

        @par Exception Safety

        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use for top-level @ref value and all child
        values. The stack will acquire shared ownership
        of the memory resource until @ref release or
        @ref reset is called, or when the stack is
        destroyed.
    */
    BOOST_JSON_DECL
    void
    reset(storage_ptr sp = {}) noexcept;

    /** Return the top-level @ref value.

        This function transfers ownership of the
        constructed top-level value to the caller.
        The behavior is undefined if there is not
        a single, top-level element.

        @par Exception Safety

        No-throw guarantee.

        @return A __value__ holding the result.
        Ownership of this value is transferred
        to the caller. Ownership of the memory
        resource used in the last call to @ref reset
        is released.
    */
    BOOST_JSON_DECL
    value
    release() noexcept;

    //--------------------------------------------

    /** Push an array formed by popping `n` values from the stack.

        This function pushes an @ref array value
        onto the stack. The array is formed by first
        popping the top `n` values from the stack.
        If the stack contains fewer than `n` values,
        or if any of the top `n` values on the stack
        is a key, the behavior is undefined.

        @par Example

        The following statements produce an array
        with the contents 1, 2, 3:

        @code

        value_stack st;

        // reset must be called first or else the behavior is undefined
        st.reset();

        // Place three values on the stack
        st.push_int64( 1 );
        st.push_int64( 2 );
        st.push_int64( 3 );

        // Remove the 3 values, and push an array with those 3 elements on the stack
        st.push_array( 3 );

        // Pop the object from the stack and take ownership.
        value jv = st.release();

        assert( serialize(jv) == "[1,2,3]" );

        // At this point, reset must be called again to use the stack

        @endcode

        @param n The number of values to pop from the
        top of the stack to form the array.
    */
    BOOST_JSON_DECL
    void
    push_array(std::size_t n);

    /** Push an object formed by popping `n` key/value pairs from the stack.

        This function pushes an @ref object value
        onto the stack. The object is formed by first
        popping the top `n` key/value pairs from the
        stack. If the stack contains fewer than `n`
        key/value pairs, or if any of the top `n` key/value
        pairs on the stack does not consist of exactly one
        key followed by one value, the behavior is undefined.

        @note

        A key/value pair is formed by pushing a key, and then
        pushing a value.

        @par Example

        The following code creates an object on the stack
        with a single element, where key is "x" and value
        is true:

        @code

        value_stack st;

        // reset must be called first or else the behavior is undefined
        st.reset();

        // Place a key/value pair onto the stack
        st.push_key( "x" );
        st.push_bool( true );

        // Replace the key/value pair with an object containing a single element
        st.push_object( 1 );

        // Pop the object from the stack and take ownership.
        value jv = st.release();

        assert( serialize(jv) == "{\"x\",true}" );

        // At this point, reset must be called again to use the stack

        @endcode

        @par Duplicate Keys

        If there are object elements with duplicate keys;
        that is, if multiple elements in an object have
        keys that compare equal, only the last equivalent
        element will be inserted.

        @param n The number of key/value pairs to pop from the
        top of the stack to form the array.
    */
    BOOST_JSON_DECL
    void
    push_object(std::size_t n);

    /** Push part of a key or string onto the stack.

        This function pushes the characters in `s` onto
        the stack, appending to any existing characters
        or creating new characters as needed. Once a
        string part is placed onto the stack, the only
        valid stack operations are:

        @li @ref push_chars to append additional
        characters to the key or string being built,

        @li @ref push_key or @ref push_string to
        finish building the key or string and place
        the value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The characters to append. This may be empty.
    */
    BOOST_JSON_DECL
    void
    push_chars(
        string_view s);

    /** Push a key onto the stack.

        This function notionally removes all the
        characters currently on the stack, then
        pushes a @ref value containing a key onto
        the stack formed by appending `s` to the
        removed characters.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The characters to append. This may be empty.
    */
    BOOST_JSON_DECL
    void
    push_key(
        string_view s);

    /** Place a string value onto the stack.

        This function notionally removes all the
        characters currently on the stack, then
        pushes a @ref value containing a @ref string
        onto the stack formed by appending `s` to the
        removed characters.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The characters to append. This may be empty.
    */
    BOOST_JSON_DECL
    void
    push_string(
        string_view s);

    /** Push a number onto the stack

        This function pushes a number value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param i The number to insert.
    */
    BOOST_JSON_DECL
    void
    push_int64(
        int64_t i);

    /** Push a number onto the stack

        This function pushes a number value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param u The number to insert.
    */
    BOOST_JSON_DECL
    void
    push_uint64(
        uint64_t u);

    /** Push a number onto the stack

        This function pushes a number value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param d The number to insert.
    */
    BOOST_JSON_DECL
    void
    push_double(
        double d);

    /** Push a `bool` onto the stack

        This function pushes a boolean value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param b The boolean to insert.
    */
    BOOST_JSON_DECL
    void
    push_bool(
        bool b);

    /** Push a null onto the stack

        This function pushes a boolean value onto the stack.

        @par Exception Safety

        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
    */
    BOOST_JSON_DECL
    void
    push_null();
};

BOOST_JSON_NS_END

#endif

/* value_stack.hpp
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
*/