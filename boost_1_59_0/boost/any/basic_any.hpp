// Copyright Ruslan Arutyunyan, 2019-2021.
// Copyright Antony Polukhin, 2021-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed by Ruslan Arutyunyan

#ifndef BOOST_ANYS_BASIC_ANY_HPP_INCLUDED
#define BOOST_ANYS_BASIC_ANY_HPP_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <boost/any/bad_any_cast.hpp>
#include <boost/any/fwd.hpp>
#include <boost/assert.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/throw_exception.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/core/addressof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost {

namespace anys {

    template <std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    class basic_any
    {
        BOOST_STATIC_ASSERT_MSG(OptimizeForSize > 0 && OptimizeForAlignment > 0, "Size and Align shall be positive values");
        BOOST_STATIC_ASSERT_MSG(OptimizeForSize >= OptimizeForAlignment, "Size shall non less than Align");
        BOOST_STATIC_ASSERT_MSG((OptimizeForAlignment & (OptimizeForAlignment - 1)) == 0, "Align shall be a power of 2");
        BOOST_STATIC_ASSERT_MSG(OptimizeForSize % OptimizeForAlignment == 0, "Size shall be multiple of alignment");
    private:
        enum operation
        {
            Destroy,
            Move,
            Copy,
            AnyCast,
            UnsafeCast,
            Typeinfo
        };

        template <typename ValueType>
        static void* small_manager(operation op, basic_any& left, const basic_any* right, const boost::typeindex::type_info* info)
        {
            switch (op)
            {
                case Destroy:
                    BOOST_ASSERT(!left.empty());
                    reinterpret_cast<ValueType*>(&left.content.small_value)->~ValueType();
                    break;
                case Move: {
                    BOOST_ASSERT(left.empty());
                    BOOST_ASSERT(right);
                    BOOST_ASSERT(!right->empty());
                    BOOST_ASSERT(right->type() == boost::typeindex::type_id<ValueType>());
                    ValueType* value = reinterpret_cast<ValueType*>(&const_cast<basic_any*>(right)->content.small_value);
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
                    new (&left.content.small_value) ValueType(std::move(*value));
#else
                    new (&left.content.small_value) ValueType(*value);
#endif
                    left.man = right->man;
                    reinterpret_cast<ValueType const*>(&right->content.small_value)->~ValueType();
                    const_cast<basic_any*>(right)->man = 0;

                    };
                    break;

                case Copy:
                    BOOST_ASSERT(left.empty());
                    BOOST_ASSERT(right);
                    BOOST_ASSERT(!right->empty());
                    BOOST_ASSERT(right->type() == boost::typeindex::type_id<ValueType>());
                    new (&left.content.small_value) ValueType(*reinterpret_cast<const ValueType*>(&right->content.small_value));
                    left.man = right->man;
                    break;
                case AnyCast:
                    BOOST_ASSERT(info);
                    BOOST_ASSERT(!left.empty());
                    return boost::typeindex::type_id<ValueType>() == *info ?
                            reinterpret_cast<typename remove_cv<ValueType>::type *>(&left.content.small_value) : 0;
                case UnsafeCast:
                    BOOST_ASSERT(!left.empty());
                    return reinterpret_cast<typename remove_cv<ValueType>::type *>(&left.content.small_value);
                case Typeinfo:
                    return const_cast<void*>(static_cast<const void*>(&boost::typeindex::type_id<ValueType>().type_info()));
            }

            return 0;
        }

        template <typename ValueType>
        static void* large_manager(operation op, basic_any& left, const basic_any* right, const boost::typeindex::type_info* info)
        {
            switch (op)
            {
                case Destroy:
                    BOOST_ASSERT(!left.empty());
                    delete static_cast<ValueType*>(left.content.large_value);
                    break;
                case Move:
                    BOOST_ASSERT(left.empty());
                    BOOST_ASSERT(right);
                    BOOST_ASSERT(!right->empty());
                    BOOST_ASSERT(right->type() == boost::typeindex::type_id<ValueType>());
                    left.content.large_value = right->content.large_value;
                    left.man = right->man;
                    const_cast<basic_any*>(right)->content.large_value = 0;
                    const_cast<basic_any*>(right)->man = 0;
                    break;
                case Copy:
                    BOOST_ASSERT(left.empty());
                    BOOST_ASSERT(right);
                    BOOST_ASSERT(!right->empty());
                    BOOST_ASSERT(right->type() == boost::typeindex::type_id<ValueType>());
                    left.content.large_value = new ValueType(*static_cast<const ValueType*>(right->content.large_value));
                    left.man = right->man;
                    break;
                case AnyCast:
                    BOOST_ASSERT(info);
                    BOOST_ASSERT(!left.empty());
                    return boost::typeindex::type_id<ValueType>() == *info ?
                            static_cast<typename remove_cv<ValueType>::type *>(left.content.large_value) : 0;
                case UnsafeCast:
                    BOOST_ASSERT(!left.empty());
                    return reinterpret_cast<typename remove_cv<ValueType>::type *>(left.content.large_value);
                case Typeinfo:
                    return const_cast<void*>(static_cast<const void*>(&boost::typeindex::type_id<ValueType>().type_info()));
            }

            return 0;
        }

        template <typename ValueType>
        struct is_small_object : boost::integral_constant<bool, sizeof(ValueType) <= OptimizeForSize &&
            boost::alignment_of<ValueType>::value <= OptimizeForAlignment &&
            boost::is_nothrow_move_constructible<ValueType>::value>
        {};

        template <typename ValueType>
        static void create(basic_any& any, const ValueType& value, boost::true_type)
        {
            typedef typename boost::decay<const ValueType>::type DecayedType;

            any.man = &small_manager<DecayedType>;
            new (&any.content.small_value) ValueType(value);
        }

        template <typename ValueType>
        static void create(basic_any& any, const ValueType& value, boost::false_type)
        {
            typedef typename boost::decay<const ValueType>::type DecayedType;

            any.man = &large_manager<DecayedType>;
            any.content.large_value = new DecayedType(value);
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        template <typename ValueType>
        static void create(basic_any& any, ValueType&& value, boost::true_type)
        {
            typedef typename boost::decay<const ValueType>::type DecayedType;
            any.man = &small_manager<DecayedType>;
            new (&any.content.small_value) DecayedType(static_cast<ValueType&&>(value));
        }

        template <typename ValueType>
        static void create(basic_any& any, ValueType&& value, boost::false_type)
        {
            typedef typename boost::decay<const ValueType>::type DecayedType;
            any.man = &large_manager<DecayedType>;
            any.content.large_value = new DecayedType(static_cast<ValueType&&>(value));
        }
#endif
    public: // non-type template parameters accessors
            static BOOST_CONSTEXPR_OR_CONST std::size_t buffer_size = OptimizeForSize;
            static BOOST_CONSTEXPR_OR_CONST std::size_t buffer_align = OptimizeForAlignment;

    public: // structors

        BOOST_CONSTEXPR basic_any() BOOST_NOEXCEPT
            : man(0), content()
        {
        }

        template<typename ValueType>
        basic_any(const ValueType & value)
            : man(0), content()
        {
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<ValueType, boost::any>::value),
                "boost::anys::basic_any shall not be constructed from boost::any"
            );
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<ValueType>::value,
                "boost::anys::basic_any<A, B> shall not be constructed from boost::anys::basic_any<C, D>"
            );
            create(*this, value, is_small_object<ValueType>());
        }

        basic_any(const basic_any & other)
          : man(0), content()
        {
            if (other.man)
            {
                other.man(Copy, *this, &other, 0);
            }
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        // Move constructor
        basic_any(basic_any&& other) BOOST_NOEXCEPT
          : man(0), content()
        {
            if (other.man)
            {
                other.man(Move, *this, &other, 0);
            }
        }

        // Perfect forwarding of ValueType
        template<typename ValueType>
        basic_any(ValueType&& value
            , typename boost::disable_if<boost::is_same<basic_any&, ValueType> >::type* = 0 // disable if value has type `basic_any&`
            , typename boost::disable_if<boost::is_const<ValueType> >::type* = 0) // disable if value has type `const ValueType&&`
          : man(0), content()
        {
            typedef typename boost::decay<ValueType>::type DecayedType;
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<DecayedType, boost::any>::value),
                "boost::anys::basic_any shall not be constructed from boost::any"
            );
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<DecayedType>::value,
                "boost::anys::basic_any<A, B> shall not be constructed from boost::anys::basic_any<C, D>"
            );
            create(*this, static_cast<ValueType&&>(value), is_small_object<DecayedType>());
        }
#endif

        ~basic_any() BOOST_NOEXCEPT
        {
            if (man)
            {
                man(Destroy, *this, 0, 0);
            }
        }

    public: // modifiers

        basic_any & swap(basic_any & rhs) BOOST_NOEXCEPT
        {
            if (this == &rhs)
            {
                return *this;
            }

            if (man && rhs.man)
            {
                basic_any tmp;
                rhs.man(Move, tmp, &rhs, 0);
                man(Move, rhs, this, 0);
                tmp.man(Move, *this, &tmp, 0);
            }
            else if (man)
            {
                man(Move, rhs, this, 0);
            }
            else if (rhs.man)
            {
                rhs.man(Move, *this, &rhs, 0);
            }
            return *this;
        }


#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        template<typename ValueType>
        basic_any & operator=(const ValueType & rhs)
        {
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<ValueType, boost::any>::value),
                "boost::any shall not be assigned into boost::anys::basic_any"
            );
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<ValueType>::value,
                "boost::anys::basic_any<A, B> shall not be assigned into boost::anys::basic_any<C, D>"
            );
            basic_any(rhs).swap(*this);
            return *this;
        }

        basic_any & operator=(basic_any rhs)
        {
            rhs.swap(*this);
            return *this;
        }

#else
        basic_any & operator=(const basic_any& rhs)
        {
            basic_any(rhs).swap(*this);
            return *this;
        }

        // move assignment
        basic_any & operator=(basic_any&& rhs) BOOST_NOEXCEPT
        {
            rhs.swap(*this);
            basic_any().swap(rhs);
            return *this;
        }

        // Perfect forwarding of ValueType
        template <class ValueType>
        basic_any & operator=(ValueType&& rhs)
        {
            typedef typename boost::decay<ValueType>::type DecayedType;
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<DecayedType, boost::any>::value),
                "boost::any shall not be assigned into boost::anys::basic_any"
            );
            BOOST_STATIC_ASSERT_MSG(
                (!anys::detail::is_basic_any<DecayedType>::value || boost::is_same<DecayedType, basic_any>::value),
                "boost::anys::basic_any<A, B> shall not be assigned into boost::anys::basic_any<C, D>"
            );
            basic_any(static_cast<ValueType&&>(rhs)).swap(*this);
            return *this;
        }
#endif

    public: // queries

        bool empty() const BOOST_NOEXCEPT
        {
            return !man;
        }

        void clear() BOOST_NOEXCEPT
        {
            basic_any().swap(*this);
        }

        const boost::typeindex::type_info& type() const BOOST_NOEXCEPT
        {
            return man
                    ? *static_cast<const boost::typeindex::type_info*>(man(Typeinfo, const_cast<basic_any&>(*this), 0, 0))
                    : boost::typeindex::type_id<void>().type_info();
        }

    private: // representation

        template<typename ValueType, std::size_t Size, std::size_t Alignment>
        friend ValueType * any_cast(basic_any<Size, Alignment> *) BOOST_NOEXCEPT;

        template<typename ValueType, std::size_t Size, std::size_t Alignment>
        friend ValueType * unsafe_any_cast(basic_any<Size, Alignment> *) BOOST_NOEXCEPT;

        typedef void*(*manager)(operation op, basic_any& left, const basic_any* right, const boost::typeindex::type_info* info);

        manager man;

        union content {
            void * large_value;
            typename boost::aligned_storage<OptimizeForSize, OptimizeForAlignment>::type small_value;
        } content;
    };

    template<std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    void swap(basic_any<OptimizeForSize, OptimizeForAlignment>& lhs, basic_any<OptimizeForSize, OptimizeForAlignment>& rhs) BOOST_NOEXCEPT
    {
        lhs.swap(rhs);
    }

    template<typename ValueType, std::size_t Size, std::size_t Alignment>
    ValueType * any_cast(basic_any<Size, Alignment> * operand) BOOST_NOEXCEPT
    {
        return operand->man ?
                static_cast<typename remove_cv<ValueType>::type *>(operand->man(basic_any<Size, Alignment>::AnyCast, *operand, 0, &boost::typeindex::type_id<ValueType>().type_info()))
                : 0;
    }

    template<typename ValueType, std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    inline const ValueType * any_cast(const basic_any<OptimizeForSize, OptimizeForAlignment> * operand) BOOST_NOEXCEPT
    {
        return any_cast<ValueType>(const_cast<basic_any<OptimizeForSize, OptimizeForAlignment> *>(operand));
    }

    template<typename ValueType, std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    ValueType any_cast(basic_any<OptimizeForSize, OptimizeForAlignment> & operand)
    {
        typedef typename remove_reference<ValueType>::type nonref;

        nonref * result = any_cast<nonref>(boost::addressof(operand));
        if(!result)
            boost::throw_exception(bad_any_cast());

        // Attempt to avoid construction of a temporary object in cases when
        // `ValueType` is not a reference. Example:
        // `static_cast<std::string>(*result);`
        // which is equal to `std::string(*result);`
        typedef typename boost::conditional<
            boost::is_reference<ValueType>::value,
            ValueType,
            typename boost::add_reference<ValueType>::type
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

    template<typename ValueType, std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    inline ValueType any_cast(const basic_any<OptimizeForSize, OptimizeForAlignment> & operand)
    {
        typedef typename remove_reference<ValueType>::type nonref;
        return any_cast<const nonref &>(const_cast<basic_any<OptimizeForSize, OptimizeForAlignment> &>(operand));
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    template<typename ValueType, std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    inline ValueType any_cast(basic_any<OptimizeForSize, OptimizeForAlignment>&& operand)
    {
        BOOST_STATIC_ASSERT_MSG(
            boost::is_rvalue_reference<ValueType&&>::value /*true if ValueType is rvalue or just a value*/
            || boost::is_const< typename boost::remove_reference<ValueType>::type >::value,
            "boost::any_cast shall not be used for getting nonconst references to temporary objects"
        );
        return any_cast<ValueType>(operand);
    }
#endif


    // Note: The "unsafe" versions of any_cast are not part of the
    // public interface and may be removed at any time. They are
    // required where we know what type is stored in the any and can't
    // use typeid() comparison, e.g., when our types may travel across
    // different shared libraries.
    template<typename ValueType, std::size_t OptimizedForSize, std::size_t OptimizeForAlignment>
    inline ValueType * unsafe_any_cast(basic_any<OptimizedForSize, OptimizeForAlignment> * operand) BOOST_NOEXCEPT
    {
        return static_cast<ValueType*>(operand->man(basic_any<OptimizedForSize, OptimizeForAlignment>::UnsafeCast, *operand, 0, 0));
    }

    template<typename ValueType, std::size_t OptimizeForSize, std::size_t OptimizeForAlignment>
    inline const ValueType * unsafe_any_cast(const basic_any<OptimizeForSize, OptimizeForAlignment> * operand) BOOST_NOEXCEPT
    {
        return unsafe_any_cast<ValueType>(const_cast<basic_any<OptimizeForSize, OptimizeForAlignment> *>(operand));
    }

} // namespace anys

using boost::anys::any_cast;
using boost::anys::unsafe_any_cast;

} // namespace boost

#endif // #ifndef BOOST_ANYS_BASIC_ANY_HPP_INCLUDED

/* basic_any.hpp
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
*/