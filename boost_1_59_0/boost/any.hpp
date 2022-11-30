// See http://www.boost.org/libs/any for Documentation.

#ifndef BOOST_ANY_INCLUDED
#define BOOST_ANY_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

// what:  variant type boost::any
// who:   contributed by Kevlin Henney,
//        with features contributed and bugs found by
//        Antony Polukhin, Ed Brey, Mark Rodgers,
//        Peter Dimov, and James Curran
// when:  July 2001, April 2013 - 2020

#include <boost/any/bad_any_cast.hpp>
#include <boost/any/fwd.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/throw_exception.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/core/addressof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost
{
    class any
    {
    public: // structors

        BOOST_CONSTEXPR any() BOOST_NOEXCEPT
          : content(0)
        {
        }

        template<typename ValueType>
        any(const ValueType & value)
          : content(new holder<
                BOOST_DEDUCED_TYPENAME remove_cv<BOOST_DEDUCED_TYPENAME decay<const ValueType>::type>::type
            >(value))
        {
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<ValueType>::value,
                "boost::any shall not be constructed from boost::anys::basic_any"
            );
        }

        any(const any & other)
          : content(other.content ? other.content->clone() : 0)
        {
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        // Move constructor
        any(any&& other) BOOST_NOEXCEPT
          : content(other.content)
        {
            other.content = 0;
        }

        // Perfect forwarding of ValueType
        template<typename ValueType>
        any(ValueType&& value
            , typename boost::disable_if<boost::is_same<any&, ValueType> >::type* = 0 // disable if value has type `any&`
            , typename boost::disable_if<boost::is_const<ValueType> >::type* = 0) // disable if value has type `const ValueType&&`
          : content(new holder< typename decay<ValueType>::type >(static_cast<ValueType&&>(value)))
        {
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<typename boost::decay<ValueType>::type>::value,
                "boost::any shall not be constructed from boost::anys::basic_any"
            );
        }
#endif

        ~any() BOOST_NOEXCEPT
        {
            delete content;
        }

    public: // modifiers

        any & swap(any & rhs) BOOST_NOEXCEPT
        {
            placeholder* tmp = content;
            content = rhs.content;
            rhs.content = tmp;
            return *this;
        }


#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        template<typename ValueType>
        any & operator=(const ValueType & rhs)
        {
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<ValueType>::value,
                "boost::anys::basic_any shall not be assigned into boost::any"
            );
            any(rhs).swap(*this);
            return *this;
        }

        any & operator=(any rhs)
        {
            rhs.swap(*this);
            return *this;
        }

#else
        any & operator=(const any& rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }

        // move assignment
        any & operator=(any&& rhs) BOOST_NOEXCEPT
        {
            rhs.swap(*this);
            any().swap(rhs);
            return *this;
        }

        // Perfect forwarding of ValueType
        template <class ValueType>
        any & operator=(ValueType&& rhs)
        {
            BOOST_STATIC_ASSERT_MSG(
                !anys::detail::is_basic_any<typename boost::decay<ValueType>::type>::value,
                "boost::anys::basic_any shall not be assigned into boost::any"
            );
            any(static_cast<ValueType&&>(rhs)).swap(*this);
            return *this;
        }
#endif

    public: // queries

        bool empty() const BOOST_NOEXCEPT
        {
            return !content;
        }

        void clear() BOOST_NOEXCEPT
        {
            any().swap(*this);
        }

        const boost::typeindex::type_info& type() const BOOST_NOEXCEPT
        {
            return content ? content->type() : boost::typeindex::type_id<void>().type_info();
        }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    private: // types
#else
    public: // types (public so any_cast can be non-friend)
#endif

        class BOOST_SYMBOL_VISIBLE placeholder
        {
        public: // structors

            virtual ~placeholder()
            {
            }

        public: // queries

            virtual const boost::typeindex::type_info& type() const BOOST_NOEXCEPT = 0;

            virtual placeholder * clone() const = 0;

        };

        template<typename ValueType>
        class holder
#ifndef BOOST_NO_CXX11_FINAL
          final
#endif
          : public placeholder
        {
        public: // structors

            holder(const ValueType & value)
              : held(value)
            {
            }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            holder(ValueType&& value)
              : held(static_cast< ValueType&& >(value))
            {
            }
#endif
        public: // queries

            const boost::typeindex::type_info& type() const BOOST_NOEXCEPT BOOST_OVERRIDE
            {
                return boost::typeindex::type_id<ValueType>().type_info();
            }

            placeholder * clone() const BOOST_OVERRIDE
            {
                return new holder(held);
            }

        public: // representation

            ValueType held;

        private: // intentionally left unimplemented
            holder & operator=(const holder &);
        };

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

    private: // representation

        template<typename ValueType>
        friend ValueType * any_cast(any *) BOOST_NOEXCEPT;

        template<typename ValueType>
        friend ValueType * unsafe_any_cast(any *) BOOST_NOEXCEPT;

#else

    public: // representation (public so any_cast can be non-friend)

#endif

        placeholder * content;

    };

    inline void swap(any & lhs, any & rhs) BOOST_NOEXCEPT
    {
        lhs.swap(rhs);
    }

    template<typename ValueType>
    ValueType * any_cast(any * operand) BOOST_NOEXCEPT
    {
        return operand && operand->type() == boost::typeindex::type_id<ValueType>()
            ? boost::addressof(
                static_cast<any::holder<BOOST_DEDUCED_TYPENAME remove_cv<ValueType>::type> *>(operand->content)->held
              )
            : 0;
    }

    template<typename ValueType>
    inline const ValueType * any_cast(const any * operand) BOOST_NOEXCEPT
    {
        return any_cast<ValueType>(const_cast<any *>(operand));
    }

    template<typename ValueType>
    ValueType any_cast(any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;


        nonref * result = any_cast<nonref>(boost::addressof(operand));
        if(!result)
            boost::throw_exception(bad_any_cast());

        // Attempt to avoid construction of a temporary object in cases when
        // `ValueType` is not a reference. Example:
        // `static_cast<std::string>(*result);`
        // which is equal to `std::string(*result);`
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            boost::is_reference<ValueType>::value,
            ValueType,
            BOOST_DEDUCED_TYPENAME boost::add_reference<ValueType>::type
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

    template<typename ValueType>
    inline ValueType any_cast(const any & operand)
    {
        typedef BOOST_DEDUCED_TYPENAME remove_reference<ValueType>::type nonref;
        return any_cast<const nonref &>(const_cast<any &>(operand));
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    template<typename ValueType>
    inline ValueType any_cast(any&& operand)
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
    template<typename ValueType>
    inline ValueType * unsafe_any_cast(any * operand) BOOST_NOEXCEPT
    {
        return boost::addressof(
            static_cast<any::holder<ValueType> *>(operand->content)->held
        );
    }

    template<typename ValueType>
    inline const ValueType * unsafe_any_cast(const any * operand) BOOST_NOEXCEPT
    {
        return unsafe_any_cast<ValueType>(const_cast<any *>(operand));
    }
}

// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
// Copyright Antony Polukhin, 2013-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif

/* any.hpp
BTXHK0Hrivoq1O+IOh7Ad8YH6d2FnviYa4Dgiy9twoRYfC2Tgy9xyvDKXLVwWpDLbvMhufRPLv1TSP+U0j8X6Z8AbjmcXi7J4Ib2PdDyfUI/fOMTja9wFgu7BJlssUwmlylkSpmrTCVzl3nKvGUaWYAsSjatXZutbbW14Uo6kVakF2lGuuGfO/554B/VUqBcDR0j8QQQfzCRMQVzY2rWl0WyRYw57bnu7PPFwnTsq4H/Ga9EK8Vf3qcB0r3vs6V735dK976/eNO97K68z7cDT2PgEGKq34BYKRqxlHrFG7Er8b3F/e008RNuxnO+026Dn3ebe+BX3OZe9xdvg998G3zVbfCHboOvvw2+6TZ4QX4zns9B4DXjcELq5Lwnfu805FXO/GwjzqYuzvzxQuRdnfkoK+wvd+YHzQPInHndfEGYIDjzr82//p76hIU/dE+9iuNKO95mLfmO8T9fXLlyRbhy8Qrd1yHUVNcIFxovCLibQ1j97Grh7Omzwvq164VZxllCTnaOsPKplULdkTrhwP4DqIt636HexQvC1m1bheWPLxfKl5QLpz47JcwqmCVsen2TsPKXK4WzjWeFU6dPCezt0QI7OEtgVzYJ7Ox6gZ0oF9hny5FeiccJjwiMeIH2wlnAadTZfwDt1AgHfrtVOAueB2prhBq0s3PDJsB6YSelXwdAvq2As/vXC5teWC3UgH4TZNk0/xFh6/xyoebtncImlB94F/Ey4J+CTJBn+cNmYSXkvAL5r1yADo+vFFajznrUPQA7jEseLWx6FvzAc/Wj5cL6knJhJ/GGThNSxwk7X9kk1IBnDeL14FkDmWqg81bEW1Fn+eQJoF0trH+0HHngnkUa7W8F7Hwddat3CuuXLAeUC3Vorw76bYIMy2HnreB56kQdbH1AuBvuhv+R4HqPV4+/4f+i1zV63H3e3bp16/ADdWJmjh+vGx9NyfsyjSpZT9du7t0QbtlOdHRS5Jgxk7UjYsYnThfCO6v85BTihnTide65njp5coTJaDSZBht89WO0MYnd4ozd5YpYRWcKRv9p7t2uIx89uOMgP6NRbcr1j9AHj0nXuqsGd5cpYmPjEGI7x3Yefh19Zsf7VSq/jqA3+EcNjkifPCY5arCfDNRubm4qlSqqc+p19FFA9+zYMcroZ4gw+fv7jpmaFDXYqIhzIeoohM7B7emD3dzuVaKsV3djRG5Eeroe9JrBxtg4UHcEtZ9f3/D29KlxsQqZXOnWsaPRPzd9DMLUZNCDnBP7GUP6Pni9vgqZTKYAvUnvq52qnTpyTHLIYJObG5EbBw8OCek7Vri+QtxgI1ToFaYfM5KCNjokxORG1H6DQxA0ke7u13VBrnbkGF+jMWPMVE4/NTkkZDDoiZrTj0109/bu1qONPmLkmJB0LahjZsbExIzMfRD04E7kIv/E6CnR3t73tfGf2rt3n5Ax2pHjKYyM9eL0Ia1BE5+oi4kf7d0mkh70CP1CtCNngl6WRvQhbWEA0U+c7NFGP0ak542MHK+VTQkJyQ1xhv4zEmeOGjEq0Unf2xn6jBk5BvSD/fyiBkuV+oUmuifNSNLdQO+sEuPjOyRWLpfBRpz/qMTE6LT4NnkybqDvndxvTLeurkYabhqqoJ+Z6J2W5qSf2sa5D49mRgUnJibOjJ6SmqqHOH369NF5x6e5t9L7jgElaKXQe+rM2Exdog5V8OsxMz4kRJfokeTl0cEpT592offMEI2x67Tg5OiZmNC6RG83P9dOHmleOok+IV2k86GAeHRISJRc3rlz35CQqfE5o2Z6POjXsVtaZg/3HhL9GE7cjwdUGRMzMeaeVMPgEI2mP2SPTNTpZiZNeqCHu5dIbxgjkvengCpoY6r/tGn3POg1anRGnzHe05NGRY+amBydGC2NNn0fHyIewEN/qjA1zB8XvY1L6eA1pVvXccODR0dOmZjspAdzUGt4GIA2wH+4vz8qJCSMy07w9Bzn7z88Isyjm0QfAu6g7ktBQ02ETB0+PJAqRCTgPkeTaWh2QoLJ1LoK6UHPyVsr9NePGZYyfDg1EREWlj1kSMK4BIPR2KpvViqGLMg7ixUg0pjU1GkpKcMD0YK/f/YQ09CEoQajupX+nunx8RMe8A/R9MXqx1sYo0eFaSmBw/3Dhvtne5o8h3iaolrpO2JJmTQhfvr0+KzUhBASq//UaQ/wCsP9ofc4T7XJpDZ2JHmcIWxaZlZkTvJE7ZgMdGtqJlUYhgopgdmeaqPR2NHNT6J3Bv8MrM4Tk0eOHJEaHMxbGDZ8WuA4k7G7sbvq3ijvmy7IygyeNCk4A+tbwKTgzFTewrQUou8e9bPYW9A/GDkjcsKkSUEBwVnBwQEB1ETqtHGmXqqePRUDVTfTj54xfUZkZOTYCaMnZ6FGJtoIJvqePd26yFTuN9GHxydNn5I2dsLYyLFjJ0wYTXWy8rLV3bv3Ut0b64fxcGMIxfo2amJOZHxk/BTckjh2dNbo1HFDEoan+EcMzk28kX/rk+WAyMhRtFvGoPKoyEkRD4ROfGhGuq/uThuyweCfGhA/2ZRAozXXNE34Hwg33hvjvG+mReBx1TxBjfiaoOL35zRL9+g0SXH9DXFVW+ykE6R6QqQUq6XY7cfHTXeI63+i+LgUs9a4SYqb7xC3SDGrkmLUVN/5np5B0qfuUe39VOVt+4r7qlcucD+V+6tn4a+dOnYK/mEd91UvUP7EKeER+G87397J/Vbzw2b4iDvJXyWfFnx2Ag5wf7XuWJ1gtpqFR0oeEQ4cPACoEdjp5fBJ4Yc2rkd7BxCvFtjFTeSnij7qacB3NUgTfqvALoDuyk7Em4DfJPqyV65wX/IsZDkFvvBNIc9W+Iorga8R/dbXJR/2hfXcn9y6BP4h5V/ZRD4q6m6Cr7hS9BHf3kl+L/dna0T/FeV18DnLhQMog09JPib3j0+9bub+6oG1oq+62ir6spteEH3QOtS5cGw996FXwzbrn1ou1G14RNiE+MpnK4UDr4MOtOTLnqpdD77LhVPbIAfqkn+9sgD8IfN6kuE02b6G++B15Ke/vpX8dPJZue9eB93PHikHbrXo58Kv3UR8j9WR/yz6w2hrK+mIevC3yRfm/u7W35LewKHeqSOgXwJ9AFcOmoWtqAs/GWWr+XOCu+FuaB+8vW+BLA1OGZuREYwD/6SZOrW6+/U04ea588PjZ5Wn5KijC1zkHQJzvdVqdRtNaPjogtFupeHh8wPG+WuVOF7LXIb2iG0jKO3YodPo0tL40njTIxHaoS5DKfSRTeoueZyKjoouHe55IDw+zJQSYUFZQUFBUFCfTPdWL0ou8+vSKXrWxOTklCmlBVTsHxThM7btf7c21P+xLh0WBmRnZ1N5gdbfPyItbVCGuk2B7IDwionJKB87LaIgyD8oDUGT41Qh66/sXQVUFc8evpR0o3RdGqRBSkK6O6S7u6W7EaQlJYQHV7rhSvxppFtaaSkJCUHl7UVexzmv3zvnfecMu7/vNzszu3fY+WZmdydMQ98UBmMTYSBpmNuIHPDfpWAHdPXCwjRMzc3NTIyAo2FuE0pzbG2/nwlwAF6FMCCYimsYCWsaGRmZmJiQmmOb32WgDzh/wvSpEZsjW7CwEcz/22uoFPYbKClIo6AiIVFwaxrp6f7W//S3fmVhZWxsc1UeLn0TBYXfnsBvk1cw536mDdAwyBhh3PlFAT8ZGTU1GZm0giY8kLiJcYgKNpGUDRH27SV2AbykpDQ0pKQK0tKGQkIuJs5hYUA2yuo/L4B+GDULmJKcnBJMSq1gr2XDr0ako2wjISrkY3nrNyEjpSNnoqKnYgDTKNj7aGmJPZZwJbYOeiIVcPsTSTvrMTDj09IyUpHTPfXh5wciiElYW7s+kX92m7+hjjFXpDA3BQE+PaUGoAr5tQK1xEj8bZ0cAf8tcCzcVHVFXIw09ZSA3oOojxa/mJPHAwfWgN+rp0J84SEhpgI8gkJCvD6imMQO6FZINr/n9/KU9fLh8DYz4xESFRXi9LdCRYPj/D2/GjC97akoK+vtZcbzyMwGF/XefThODNDvoG2uouznF+qnaugpq2Zj6yvxhE0NG/THEJLV9VNXVxaX8ZJ0t5MzAP3LcXML0ZtLDISbD8CPDagMSlgIvtt+AMIRoDxgAdhH+HOh8y+EIyDc/H4IBsIPIPweGH/7WZ7f6RQxuD9f1rtxdJj2gGmSWz3SB2vXgLbOD2iLAW0CGz+/HVdvgLX7t237KCgcaF8BTQIbN4fpktsx877+Ppg+gekOmAb5qTmm3GF646ceWf85Zn6xXnzbLl7stYE+LzYAbeIK6PMqTO9sw9r6u7F0gNtbAdpyWLsOxO93v2tDgQBoigZAAwG6AqYlfra/txqlAtAmQIDAtg2wtvtWi/RVFoNmKwHNBNuHwM7J/VZ7pAI6Y2UM0AK14Xdj5n6gPuD4lXZAj8DyAnTGLMBt94cD+gU2jl8B2q51B45pA8oVDthA2dvdb3XBKATQF3OAlgDa+JWhCuAcRkF9WTAtkQqUtxjQBDCNNAryAzTM//F//HcCGwAyEADcmghID9mwDYAhU0YMGAEPj8CKja1PS89ApfczAgzaYBpNOl1sTBAIS0lFjp1DS4eOjlkDGw1wq7FQsjxlUlBmZpLFFgFsSgBC2NiPn0iLY6PCbGJyYklsKWxsQ0Xs+4BNSkb0QB6bV1AYSBYFsB8QkhASYfOpCsjIcAHpAc0nCTUF9iM+VVYuUfzflJiT+xEPAS4O+m/PgF9C/R4eotjvTuon/vQ+Dev7wr4biwALwD4csP0r4egu/ADCzc0fz1vedQTv/eX+INCfg801/m5OcTH8d/OKd3OKwD0FNgcHmwOEzeXdzg/+A0Dg5v6z/OM67j/yDA/vd4IQOnBxuX/fg9G92LY8vI6OCwDm4fhJY06CwcBKPm/XKYERQVxc0ro7HqBhPHSKkhoM85D+5NHBd/wy5TFsl/qOh8MFjGuAngJ4GO74mp982/JU4skt7/cbHhfGA9/BT7yNzx5wly8uLh6YpQ3gb6hh/E0Awk8e7gYXDAX4pVv+5ub53amhL0PBQDJAfCD9G4BfBxwwfvF6cXl4+JZnh/H7j4FTBvhpqWsYj39zAqNvwva7p37ykpLOy8MjAH8DQ9H+8MpveEnjNoDvuOVzf8NLwiDVVneXr+O+sMgdfwsD+1rgTGDxu2956B2vZM8FlD/x5nqY+5Zvg5FakpKKpIf73dCOcy2Dbu6f8TW1AGgukR7C0H3zm3SktG75sUShtuHR0XVc7lsevUFLS9vKSsvwBheX8GZqeXQCX4j7J28Fg/1IN/QmOl1r5bAb+pPXtrLNzASOGIIKCy/qcwuPLI92wnirzCwIpMzKcgj4kbm5haDLwiswvtEqqzQ6OjYTxt+hHZbOeWZplLd3LOTVT76WBVpLc8tnwRY4egbJ/k38O77jKsoNcESX37F38RG4haGXbmDvZ7/jwQAPHNDGzb3YEeWdc8cDVQ7Gw65E29LwUMe3O5795o6HeaBLw8N3mZ6c/I5HB4jf8uDf8ZjLy78tJBiMi/9bnhtWsRb/hEfn5haGeWA88K9BAfA/sQTUN2HAuQg7pqP9J39XWKDSDY8sA9vF3/G/LW/dJOyUQf9y/H/c8Q+3l//RcUfEnz14+L/4W8HGEH+OA173wcb1gHCrmWGa+3ZcLQfwA7oa0Ni3ehs2Vnarsf8SwL9rDvIgZSCwN/iOQc709s4rdMUldPvJeGsB/6S+/lpqAAMr8C9aOre2lkEPIRUQHRf3p20wbCVDdXvb1vKGtvr3Dg87ysNsuGEt78Ndf1iVB2wAZd7Qw922vr7lZUEwjCiFHgI2YK7e2mil0XG7kA7AvhaElQCtORogOpZvrqG/sYG7T8dw/+qdHQ2zobi40qsCv7MXIGWZwC3it7YtBAAlzIZEA01e7ASBfRakAA+wS7lhNgQCjQb+3NowNHn7Qn7lnbEGAhVx80hKADYMrsmAzQPcpn/PhkBeA5PqTRm/sUFARh1TLZmAOfwLYN8yQGmACLi/uN3ambfwcQVauDv7FoD90492ewCQgj/s+DvqFoWgvxX/Xf3Wn/UcOPbPAuir/n4f9LbvedfX/NkPhNw+0wTU79u+I6zuw/qKt32+31Vs8BoYqEfwuFqAiAkFwYPV6XAJ1WE8Cy40lAp+eO2aFJp8BD+8tNMALaSCX17uotPvooKftVoLBQN+q8au6GQwFXyTd220ltYRCtiv9mWE2hGQAFtZhMQHWEKHmzAbSBrI6J+lO2FX597degAowJN8sC0V1Z2FAmQGwsG5tW6f4kMAYuLAruftM3yIQMxb6/YJPiQg5q0Fe34PSFP1yd+7rgACCA30/3UF/r+uwP/XFfj/ugL/X1fg/+sK/DvWFfi//b9hgyAPQZJ3fbyfXb473OMHgVTxgcbdHw6EI0IBl+9BBYcNbEF/BqMA+xDh534vcEzzE6BLjXPnROFX0qDSMAVeVNawdLO1Am77v3kpGrg13L4pTCX3e+8zA4yvqZsFGxsb6EC/I5FWV70y5RIhoUYZJcqQfK1HoJ+jb42KdrZTgi9loXwF3/oDXFfIDEeQmHzmjP1kVjlzrm4pV90cWRkLNzKq869ShBESBXwNXJx+IPCvXbdHZ8wLk9VFKY/fq/rVSf/QxVoAO9hI8u1Azqpehfbq9z67swyvH327OtqMQd+Q33i/Mw44zX4zFnit/2YsCPjeR9CFTEe77/F354r2yx/O7z/zHVwJvQmq3uu4+cVbuyrwcnkm8eaL3xvKm68X2jdfCDuarua2gxqvmoLIdFZH80QCfniweX3fLwsc8/nyrh876PiEUeOCij/R1Hvs1XKlRS65Q7kjVC/gOsV68cBpaO1XN4X7ja+Efb/srCceXGwUWY/lfT9L2TdfKS5KE/U/2TheZ/B6tkY43z+v9530x1pik8gS23c6Aig7xlzUK39X7oxXS0tvp1EJRdXohvZyCZ3zDld12vVwvvpujizORdp/n2QLehc7d7B8knz27Kr1gvmsAeJNcpNTGGMTXqW18iO+2ankEy2W9mmZMthiPpFVGdK236RlLVsU2aC1KzI3XdY/lL3ocE0oumpa4rQKmkPWdWd0v2aJLXz4jqvf0+iD8beC2Ab+eUfd+1K8WG1nLKqQZPJj871Q6+UXmpnOXlMcSlP8R871e6a1KcsYzzpJlhZm+JfEEigfgwvAY65b/FQVydtGhlbHtLET3AbQxr0FvQpZBhmaJBziYYyMbC8iFPin98AnQsvrXpNfNxdTBo+pY+wGwN6SujXjS3HDu3Vcc92e3WYWCT7FNQsdMTGglK1PI7nF/HycPwzIolVLTk4c0QPp8HYMq+KuMBYWpBZtdyrqtYxch9/iC/j5DhSpZdMxcuMMBsHVLnjvEr3VS1dD/hZwdv6KTgZ1CEt/lEmQ1mTUxW3NgV7LIZ+CFdGjngHnV4htqkiovIhQXZB+arjcJp3r90rGedM5vyI1BoL+gSlUhNz1Vu6Hjhomqe2lgmRxhc4S02Zqk1XxvMxQJ3p+s3aSfjqcZuVUmtaKbKfB9zEdm/WdWehFgSIvhLTs30Vr93Mho9sLZfXwNge/LXLYmG/1tPCOlbZAFdCLqtPWitHy
*/