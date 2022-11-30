// Copyright Antony Polukhin, 2020-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/any for Documentation.

#ifndef BOOST_ANYS_UNIQUE_ANY_HPP_INCLUDED
#define BOOST_ANYS_UNIQUE_ANY_HPP_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#error Header <boost/any/unique_any.hpp> requires C++11 compatible compiler with move semantics
#endif

#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#error Header <boost/any/unique_any.hpp> requires C++11 compatible compiler with defaulted functions
#endif

#ifdef BOOST_NO_CXX11_SMART_PTR
#error Header <boost/any/unique_any.hpp> requires C++11 compatible standard library with std::unique_ptr
#endif
#include <memory>

#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <utility>

#include <boost/any/bad_any_cast.hpp>

#include <boost/core/addressof.hpp>
#include <boost/type_traits/decay.hpp>

namespace boost { namespace anys {

template <class T>
struct in_place_type_t
{
};

#if !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES)
template <class T>
constexpr in_place_type_t<T> in_place_type{};
#endif

class unique_any {
public:

    BOOST_CONSTEXPR unique_any() BOOST_NOEXCEPT = default;

    unique_any(unique_any&& other) BOOST_NOEXCEPT = default;

    // Perfect forwarding of T
    template<typename T>
    unique_any(T&& value
        , typename boost::disable_if<boost::is_same<unique_any&, T> >::type* = 0 // disable if value has type `unique_any&`
        , typename boost::disable_if<boost::is_const<T> >::type* = 0) // disable if value has type `const T&&`
      : content(new holder< typename boost::decay<T>::type >(std::forward<T>(value)))
    {
    }

    template<class T, class... Args>
    explicit unique_any(in_place_type_t<T>, Args&&... args)
      : content(new holder<typename boost::decay<T>::type>(std::forward<Args>(args)...))
    {
    }

#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template <class T, class U, class... Args>
    explicit unique_any(in_place_type_t<T>, std::initializer_list<U> il, Args&&... args)
      : content(new holder<typename boost::decay<T>::type>(il, std::forward<Args>(args)...))
    {
    }
#endif

    ~unique_any() BOOST_NOEXCEPT = default;

    unique_any & operator=(unique_any&& rhs) BOOST_NOEXCEPT = default;

    template <class T>
    unique_any & operator=(T&& rhs)
    {
        unique_any(std::forward<T>(rhs)).swap(*this);
        return *this;
    }

    template<class T, class... Args>
    typename boost::decay<T>::type& emplace(Args&&... args) {
        content = std::unique_ptr<placeholder>(
            new holder<typename boost::decay<T>::type>(std::forward<Args>(args)...)
        );
    }

#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template<class T, class U, class... Args>
    typename boost::decay<T>::type& emplace(initializer_list<U> il, Args&&... args) {
        content = std::unique_ptr<placeholder>(
            new holder<typename boost::decay<T>::type>(il, std::forward<Args>(args)...)
        );
    }
#endif

    void reset() BOOST_NOEXCEPT
    {
        content.reset();
    }

    unique_any& swap(unique_any& rhs) BOOST_NOEXCEPT
    {
        content.swap(rhs.content);
        return *this;
    }


    bool has_value() const BOOST_NOEXCEPT
    {
        return !content;
    }

    const boost::typeindex::type_info& type() const BOOST_NOEXCEPT
    {
        return content ? content->type() : boost::typeindex::type_id<void>().type_info();
    }

private: // types
    class BOOST_SYMBOL_VISIBLE placeholder
    {
        virtual ~placeholder()
        {
        }

        virtual const boost::typeindex::type_info& type() const BOOST_NOEXCEPT = 0;

    };

    template<typename T>
    class holder BOOST_FINAL: public placeholder
    {
    public: // structors

        template <class... Args>
        holder(Args&&... args)
          : held(std::forward<Args>(args)...)
        {
        }

#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        template <class U, class... Args>
        holder(std::initializer_list<U> il, Args&&... args)
          : held(il, std::forward<Args>(args)...)
        {
        }
#endif

        const boost::typeindex::type_info& type() const BOOST_NOEXCEPT BOOST_OVERRIDE
        {
            return boost::typeindex::type_id<T>().type_info();
        }

    public: // representation

        T held;
    };


private: // representation

    template<typename T>
    friend T * any_cast(unique_any *) BOOST_NOEXCEPT;

    template<typename T>
    friend T * unsafe_any_cast(unique_any *) BOOST_NOEXCEPT;

    std::unique_ptr<placeholder> content;
};

inline void swap(unique_any & lhs, unique_any & rhs) BOOST_NOEXCEPT
{
    lhs.swap(rhs);
}

template<typename T>
T * any_cast(unique_any * operand) BOOST_NOEXCEPT
{
    return operand && operand->type() == boost::typeindex::type_id<T>()
        ? boost::addressof(
            static_cast<unique_any::holder<BOOST_DEDUCED_TYPENAME remove_cv<T>::type>&>(*operand->content).held
          )
        : 0;
}

template<typename T>
inline const T * any_cast(const unique_any * operand) BOOST_NOEXCEPT
{
    return any_cast<T>(const_cast<unique_any *>(operand));
}

template<typename T>
T any_cast(unique_any & operand)
{
    typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type nonref;


    nonref * result = any_cast<nonref>(boost::addressof(operand));
    if(!result)
        boost::throw_exception(bad_any_cast());

    // Attempt to avoid construction of a temporary object in cases when
    // `T` is not a reference. Example:
    // `static_cast<std::string>(*result);`
    // which is equal to `std::string(*result);`
    typedef BOOST_DEDUCED_TYPENAME boost::conditional<
        boost::is_reference<T>::value,
        T,
        BOOST_DEDUCED_TYPENAME boost::add_reference<T>::type
    >::type ref_type;

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4172) // "returning address of local variable or temporary" but *result is not local!
#endif
    return static_cast<ref_type>(*result);
#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif
}

template<typename T>
inline T any_cast(const unique_any & operand)
{
    typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type nonref;
    return any_cast<const nonref &>(const_cast<unique_any &>(operand));
}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template<typename T>
inline T any_cast(unique_any&& operand)
{
    BOOST_STATIC_ASSERT_MSG(
        boost::is_rvalue_reference<T&&>::value /*true if T is rvalue or just a value*/
        || boost::is_const< typename boost::remove_reference<T>::type >::value,
        "boost::any_cast shall not be used for getting nonconst references to temporary objects"
    );
    return any_cast<T>(operand);
}
#endif


// Note: The "unsafe" versions of any_cast are not part of the
// public interface and may be removed at any time. They are
// required where we know what type is stored in the any and can't
// use typeid() comparison, e.g., when our types may travel across
// different shared libraries.
template<typename T>
inline T * unsafe_any_cast(unique_any * operand) BOOST_NOEXCEPT
{
    return boost::addressof(
        static_cast<unique_any::holder<T>&>(*operand->content)->held
    );
}

template<typename T>
inline const T * unsafe_any_cast(const unique_any * operand) BOOST_NOEXCEPT
{
    return unsafe_any_cast<T>(const_cast<unique_any *>(operand));
}

} // namespace anys

using boost::anys::any_cast;
using boost::anys::unsafe_any_cast;

} // namespace boost


#endif // BOOST_ANYS_UNIQUE_ANY_HPP_INCLUDED

/* unique_any.hpp
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
*/