//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_VALUE_REF_HPP
#define BOOST_JSON_VALUE_REF_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/string.hpp>
#include <initializer_list>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN

#ifndef BOOST_JSON_DOCS
class value;
class object;
class array;
class string;
#endif

//----------------------------------------------------------

/** The type used in initializer lists.

    This type is used in initializer lists for
    lazy construction of and assignment to the
    container types @ref value, @ref array,
    and @ref object. The two types of initializer
    lists used are:

    @li `std::initializer_list< value_ref >` for
    constructing or assigning a @ref value or
    @ref array, and

    @li `std::initializer_list< std::pair< string_view, value_ref > >`
    for constructing or assigning an @ref object.

    A `value_ref` uses reference semantics. Creation
    of the actual container from the initializer
    list is lazily deferred until the list is used.
    This means that the @ref memory_resource used to
    construct a container can be specified after the
    point where the initializer list is specified.

    @par Example

    This example demonstrates how a user-defined type
    containing a JSON value can be constructed from
    an initializer list:

    @code

    class my_type
    {
        value jv_;

    public:
        my_type( std::initializer_list< value_ref > init )
            : jv_(init)
        {
        }
    };

    @endcode

    @note Never declare a variable of type
    `std::initializer_list` except in function
    parameter lists, otherwise the behavior may
    be undefined.

    @see
        @ref value,
        @ref array,
        @ref object
*/
class value_ref
{
    friend class value;
    friend class object;
    friend class array;

    friend class value_ref_test;

    enum class what
    {
        str,
        ini,
        func,
        cfunc,
        strfunc,
    };

    using init_list =
        std::initializer_list<value_ref>;

    struct func_type
    {
        value(*f)(void*, storage_ptr);
        void* p;
    };

    struct cfunc_type
    {
        value(*f)(void const*, storage_ptr);
        void const* p;
    };

    union arg_type
    {
        string_view         str_;
        init_list           init_list_;

        signed char         schar_;
        short               short_;
        int                 int_;
        long                long_;
        long long           long_long_;
        unsigned char       uchar_;
        unsigned short      ushort_;
        unsigned int        uint_;
        unsigned long       ulong_;
        unsigned long long  ulong_long_;
        float               float_;
        double              double_;
        bool                bool_;
        std::nullptr_t      nullptr_;

        arg_type() {}
        explicit arg_type(string_view t) noexcept : str_(t) {}
        explicit arg_type(init_list t) noexcept : init_list_(t) {}
        explicit arg_type(signed char t) noexcept : schar_(t) {}
        explicit arg_type(short t) noexcept : short_(t) {}
        explicit arg_type(int t) noexcept : int_(t) {}
        explicit arg_type(long t) noexcept : long_(t) {}
        explicit arg_type(long long t) noexcept : long_long_(t) {}
        explicit arg_type(unsigned char t) noexcept : uchar_(t) {}
        explicit arg_type(unsigned short t) noexcept : ushort_(t) {}
        explicit arg_type(unsigned int t) noexcept : uint_(t) {}
        explicit arg_type(unsigned long t) noexcept : ulong_(t) {}
        explicit arg_type(unsigned long long t) noexcept : ulong_long_(t) {}
        explicit arg_type(float t) noexcept : float_(t) {}
        explicit arg_type(double t) noexcept : double_(t) {}
        explicit arg_type(bool t) noexcept : bool_(t) {}
        explicit arg_type(std::nullptr_t) noexcept : nullptr_() {}
    };

    arg_type arg_;
#ifndef BOOST_JSON_DOCS
    // VFALCO doc toolchain erroneously
    // displays private, anonymous unions as public
    union
    {
        func_type f_;
        cfunc_type cf_;
    };
#endif
    what what_;

public:
    /// Constructor
    value_ref(
        value_ref const&) = default;

    /// Constructor
#ifdef BOOST_JSON_DOCS
    value_ref(string_view s) noexcept;
#else
    template<
        class T
        ,class = typename
            std::enable_if<
                std::is_constructible<
                    string_view, T>::value>::type
    >
    value_ref(
        T const& t) noexcept
        : arg_(string_view(t))
        , what_(what::str)
    {

    }
#endif

    /// Constructor
    template<class T>
    value_ref(
        T const& t
#ifndef BOOST_JSON_DOCS
        ,typename std::enable_if<
            ! std::is_constructible<
                string_view, T>::value &&
            ! std::is_same<bool, T>::value
                >::type* = 0
#endif
        ) noexcept
        : cf_{&from_const<T>, &t}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    template<class T>
    value_ref(
        T&& t
#ifndef BOOST_JSON_DOCS
        ,typename std::enable_if<
            (! std::is_constructible<
                string_view, T>::value ||
            std::is_same<string, T>::value) &&
            ! std::is_same<bool,
                detail::remove_cvref<T>>::value &&
            std::is_same<T, detail::remove_cvref<T>>
                ::value>::type* = 0
#endif
        ) noexcept
        : f_{&from_rvalue<
            detail::remove_cvref<T>>, &t}
        , what_(std::is_same<string, T>::value ?
                what::strfunc : what::func)
    {
    }

    /// Constructor
#ifdef BOOST_JSON_DOCS
    value_ref(bool b) noexcept;
#else
    template<
        class Bool
        ,class = typename std::enable_if<
            std::is_same<Bool, bool>::value>::type
    >
    value_ref(
        Bool b) noexcept
        : arg_(b)
        , cf_{&from_builtin<bool>, &arg_.bool_}
        , what_(what::cfunc)
    {
    }
#endif

    /// Constructor
    value_ref(
        std::initializer_list<
            value_ref> t) noexcept
        : arg_(t)
        , what_(what::ini)
    {
    }

    /// Constructor
    value_ref(signed char t) noexcept
        : arg_(t)
        , cf_{&from_builtin<signed char>, &arg_.schar_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(short t) noexcept
        : arg_(t)
        , cf_{&from_builtin<short>, &arg_.short_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(int t) noexcept
        : arg_(t)
        , cf_{&from_builtin<int>, &arg_.int_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(long t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            long>, &arg_.long_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(long long t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            long long>, &arg_.long_long_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(unsigned char t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            unsigned char>, &arg_.uchar_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(unsigned short t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            unsigned short>, &arg_.ushort_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(unsigned int t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            unsigned int>, &arg_.uint_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(unsigned long t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            unsigned long>, &arg_.ulong_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(unsigned long long t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            unsigned long long>, &arg_.ulong_long_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(float t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            float>, &arg_.float_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(double t) noexcept
        : arg_(t)
        , cf_{&from_builtin<
            double>, &arg_.double_}
        , what_(what::cfunc)
    {
    }

    /// Constructor
    value_ref(std::nullptr_t) noexcept
        : arg_(nullptr)
        , cf_{&from_builtin<
            std::nullptr_t>, &arg_.nullptr_}
        , what_(what::cfunc)
    {
    }

#ifndef BOOST_JSON_DOCS
// Not public
//private:
    // VFALCO Why is this needed?
    /** Operator conversion to @ref value

        This allows creation of a @ref value from
        an initializer list element.
    */
    BOOST_JSON_DECL
    operator value() const;
#endif

private:
    template<class T>
    static
    value
    from_builtin(
        void const* p,
        storage_ptr sp) noexcept;

    template<class T>
    static
    value
    from_const(
        void const* p,
        storage_ptr sp);

    template<class T>
    static
    value
    from_rvalue(
        void* p,
        storage_ptr sp);

    static
    BOOST_JSON_DECL
    value
    from_init_list(
        void const* p,
        storage_ptr sp);

    inline
    bool
    is_key_value_pair() const noexcept;

    static
    inline
    bool
    maybe_object(
        std::initializer_list<
            value_ref> init) noexcept;

    inline
    string_view
    get_string() const noexcept;

    BOOST_JSON_DECL
    value
    make_value(
        storage_ptr sp) const;

    BOOST_JSON_DECL
    static
    value
    make_value(
        std::initializer_list<
            value_ref> init,
        storage_ptr sp);

    BOOST_JSON_DECL
    static
    object
    make_object(
        std::initializer_list<value_ref> init,
        storage_ptr sp);

    BOOST_JSON_DECL
    static
    array
    make_array(
        std::initializer_list<
            value_ref> init,
        storage_ptr sp);

    BOOST_JSON_DECL
    static
    void
    write_array(
        value* dest,
        std::initializer_list<
            value_ref> init,
        storage_ptr const& sp);
};

BOOST_JSON_NS_END

// Must be included here for this file to stand alone
#include <boost/json/value.hpp>

// includes are at the bottom of <boost/json/value.hpp>
//#include <boost/json/impl/value.hpp>
//#include <boost/json/impl/value.ipp>

#endif

/* value_ref.hpp
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
*/