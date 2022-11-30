/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ITERATOR_MULTI_PASS_HPP
#define BOOST_SPIRIT_ITERATOR_MULTI_PASS_HPP

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <deque>
#include <iterator>
#include <iostream>
#include <algorithm>    // for std::swap
#include <exception>    // for std::exception
#include <boost/limits.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/assert.hpp> // for BOOST_SPIRIT_ASSERT
#include <boost/spirit/home/classic/iterator/fixed_size_queue.hpp>

#include <boost/spirit/home/classic/iterator/multi_pass_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

namespace impl {
    template <typename T>
    inline void mp_swap(T& t1, T& t2);
}

namespace multi_pass_policies
{

///////////////////////////////////////////////////////////////////////////////
// class ref_counted
// Implementation of an OwnershipPolicy used by multi_pass.
//
// Implementation modified from RefCounted class from the Loki library by
// Andrei Alexandrescu
///////////////////////////////////////////////////////////////////////////////
class ref_counted
{
    protected:
        ref_counted()
            : count(new std::size_t(1))
        {}

        ref_counted(ref_counted const& x)
            : count(x.count)
        {}

        // clone is called when a copy of the iterator is made, so increment
        // the ref-count.
        void clone()
        {
            ++*count;
        }

        // called when a copy is deleted.  Decrement the ref-count.  Return
        // value of true indicates that the last copy has been released.
        bool release()
        {
            if (!--*count)
            {
                delete count;
                count = 0;
                return true;
            }
            return false;
        }

        void swap(ref_counted& x)
        {
            impl::mp_swap(count, x.count);
        }

    public:
        // returns true if there is only one iterator in existence.
        // std_deque StoragePolicy will free it's buffered data if this
        // returns true.
        bool unique() const
        {
            return *count == 1;
        }

    private:
        std::size_t* count;
};

///////////////////////////////////////////////////////////////////////////////
// class first_owner
// Implementation of an OwnershipPolicy used by multi_pass
// This ownership policy dictates that the first iterator created will
// determine the lifespan of the shared components.  This works well for
// spirit, since no dynamic allocation of iterators is done, and all copies
// are make on the stack.
//
// There is a caveat about using this policy together with the std_deque
// StoragePolicy. Since first_owner always returns false from unique(),
// std_deque will only release the queued data if clear_queue() is called.
///////////////////////////////////////////////////////////////////////////////
class first_owner
{
    protected:
        first_owner()
            : first(true)
        {}

        first_owner(first_owner const&)
            : first(false)
        {}

        void clone()
        {
        }

        // return true to indicate deletion of resources
        bool release()
        {
            return first;
        }

        void swap(first_owner&)
        {
            // if we're the first, we still remain the first, even if assigned
            // to, so don't swap first_.  swap is only called from operator=
        }

    public:
        bool unique() const
        {
            return false; // no way to know, so always return false
        }

    private:
        bool first;
};

///////////////////////////////////////////////////////////////////////////////
// class illegal_backtracking
// thrown by buf_id_check CheckingPolicy if an instance of an iterator is
// used after another one has invalidated the queue
///////////////////////////////////////////////////////////////////////////////
class BOOST_SYMBOL_VISIBLE illegal_backtracking : public std::exception
{
public:

    illegal_backtracking() BOOST_NOEXCEPT_OR_NOTHROW {}
    ~illegal_backtracking() BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {}

    const char*
    what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
    { return "BOOST_SPIRIT_CLASSIC_NS::illegal_backtracking"; }
};

///////////////////////////////////////////////////////////////////////////////
// class buf_id_check
// Implementation of the CheckingPolicy used by multi_pass
// This policy is most effective when used together with the std_deque
// StoragePolicy.
// If used with the fixed_size_queue StoragePolicy, it will not detect
// iterator dereferences that are out of the range of the queue.
///////////////////////////////////////////////////////////////////////////////
class buf_id_check
{
    protected:
        buf_id_check()
            : shared_buf_id(new unsigned long(0))
            , buf_id(0)
        {}

        buf_id_check(buf_id_check const& x)
            : shared_buf_id(x.shared_buf_id)
            , buf_id(x.buf_id)
        {}

        // will be called from the destructor of the last iterator.
        void destroy()
        {
            delete shared_buf_id;
            shared_buf_id = 0;
        }

        void swap(buf_id_check& x)
        {
            impl::mp_swap(shared_buf_id, x.shared_buf_id);
            impl::mp_swap(buf_id, x.buf_id);
        }

        // called to verify that everything is okay.
        void check_if_valid() const
        {
            if (buf_id != *shared_buf_id)
            {
                boost::throw_exception(illegal_backtracking());
            }
        }

        // called from multi_pass::clear_queue, so we can increment the count
        void clear_queue()
        {
            ++*shared_buf_id;
            ++buf_id;
        }

    private:
        unsigned long* shared_buf_id;
        unsigned long buf_id;
};

///////////////////////////////////////////////////////////////////////////////
// class no_check
// Implementation of the CheckingPolicy used by multi_pass
// It does not do anything :-)
///////////////////////////////////////////////////////////////////////////////
class no_check
{
    protected:
        no_check() {}
        no_check(no_check const&) {}
        void destroy() {}
        void swap(no_check&) {}
        void check_if_valid() const {}
        void clear_queue() {}
};

///////////////////////////////////////////////////////////////////////////////
// class std_deque
// Implementation of the StoragePolicy used by multi_pass
// This stores all data in a std::deque, and keeps an offset to the current
// position. It stores all the data unless there is only one
// iterator using the queue.
// Note: a position is used instead of an iterator, because a push_back on
// a deque can invalidate any iterators.
///////////////////////////////////////////////////////////////////////////////
class std_deque
{
    public:

template <typename ValueT>
class inner
{
    private:

        typedef std::deque<ValueT> queue_type;
        queue_type* queuedElements;
        mutable typename queue_type::size_type queuePosition;

    protected:
        inner()
            : queuedElements(new queue_type)
            , queuePosition(0)
        {}

        inner(inner const& x)
            : queuedElements(x.queuedElements)
            , queuePosition(x.queuePosition)
        {}

        // will be called from the destructor of the last iterator.
        void destroy()
        {
            BOOST_SPIRIT_ASSERT(NULL != queuedElements);
            delete queuedElements;
            queuedElements = 0;
        }

        void swap(inner& x)
        {
            impl::mp_swap(queuedElements, x.queuedElements);
            impl::mp_swap(queuePosition, x.queuePosition);
        }

        // This is called when the iterator is dereferenced.  It's a template
        // method so we can recover the type of the multi_pass iterator
        // and call unique and access the m_input data member.
        template <typename MultiPassT>
        static typename MultiPassT::reference dereference(MultiPassT const& mp)
        {
            if (mp.queuePosition == mp.queuedElements->size())
            {
                // check if this is the only iterator
                if (mp.unique())
                {
                    // free up the memory used by the queue.
                    if (mp.queuedElements->size() > 0)
                    {
                        mp.queuedElements->clear();
                        mp.queuePosition = 0;
                    }
                }
                return mp.get_input();
            }
            else
            {
                return (*mp.queuedElements)[mp.queuePosition];
            }
        }

        // This is called when the iterator is incremented.  It's a template
        // method so we can recover the type of the multi_pass iterator
        // and call unique and access the m_input data member.
        template <typename MultiPassT>
        static void increment(MultiPassT& mp)
        {
            if (mp.queuePosition == mp.queuedElements->size())
            {
                // check if this is the only iterator
                if (mp.unique())
                {
                    // free up the memory used by the queue.
                    if (mp.queuedElements->size() > 0)
                    {
                        mp.queuedElements->clear();
                        mp.queuePosition = 0;
                    }
                }
                else
                {
                    mp.queuedElements->push_back(mp.get_input());
                    ++mp.queuePosition;
                }
                mp.advance_input();
            }
            else
            {
                ++mp.queuePosition;
            }

        }

        // called to forcibly clear the queue
        void clear_queue()
        {
            queuedElements->clear();
            queuePosition = 0;
        }

        // called to determine whether the iterator is an eof iterator
        template <typename MultiPassT>
        static bool is_eof(MultiPassT const& mp)
        {
            return mp.queuePosition == mp.queuedElements->size() &&
                mp.input_at_eof();
        }

        // called by operator==
        bool equal_to(inner const& x) const
        {
            return queuePosition == x.queuePosition;
        }

        // called by operator<
        bool less_than(inner const& x) const
        {
            return queuePosition < x.queuePosition;
        }
}; // class inner

}; // class std_deque


///////////////////////////////////////////////////////////////////////////////
// class fixed_size_queue
// Implementation of the StoragePolicy used by multi_pass
// fixed_size_queue keeps a circular buffer (implemented by
// BOOST_SPIRIT_CLASSIC_NS::fixed_size_queue class) that is size N+1 and stores N elements.
// It is up to the user to ensure that there is enough look ahead for their
// grammar.  Currently there is no way to tell if an iterator is pointing
// to forgotten data.  The leading iterator will put an item in the queue
// and remove one when it is incremented.  No dynamic allocation is done,
// except on creation of the queue (fixed_size_queue constructor).
///////////////////////////////////////////////////////////////////////////////
template < std::size_t N>
class fixed_size_queue
{
    public:

template <typename ValueT>
class inner
{
    private:

        typedef BOOST_SPIRIT_CLASSIC_NS::fixed_size_queue<ValueT, N> queue_type;
        queue_type * queuedElements;
        mutable typename queue_type::iterator queuePosition;

    protected:
        inner()
            : queuedElements(new queue_type)
            , queuePosition(queuedElements->begin())
        {}

        inner(inner const& x)
            : queuedElements(x.queuedElements)
            , queuePosition(x.queuePosition)
        {}

        // will be called from the destructor of the last iterator.
        void destroy()
        {
            BOOST_SPIRIT_ASSERT(NULL != queuedElements);
            delete queuedElements;
            queuedElements = 0;
        }

        void swap(inner& x)
        {
            impl::mp_swap(queuedElements, x.queuedElements);
            impl::mp_swap(queuePosition, x.queuePosition);
        }

        // This is called when the iterator is dereferenced.  It's a template
        // method so we can recover the type of the multi_pass iterator
        // and access the m_input data member.
        template <typename MultiPassT>
        static typename MultiPassT::reference dereference(MultiPassT const& mp)
        {
            if (mp.queuePosition == mp.queuedElements->end())
            {
                return mp.get_input();
            }
            else
            {
                return *mp.queuePosition;
            }
        }

        // This is called when the iterator is incremented.  It's a template
        // method so we can recover the type of the multi_pass iterator
        // and access the m_input data member.
        template <typename MultiPassT>
        static void increment(MultiPassT& mp)
        {
            if (mp.queuePosition == mp.queuedElements->end())
            {
                // don't let the queue get larger than N
                if (mp.queuedElements->size() >= N)
                    mp.queuedElements->pop_front();

                mp.queuedElements->push_back(mp.get_input());
                mp.advance_input();
            }
            ++mp.queuePosition;
        }

        // no-op
        void clear_queue()
        {}

        // called to determine whether the iterator is an eof iterator
        template <typename MultiPassT>
        static bool is_eof(MultiPassT const& mp)
        {
            return mp.queuePosition == mp.queuedElements->end() &&
                mp.input_at_eof();
        }

        // called by operator==
        bool equal_to(inner const& x) const
        {
            return queuePosition == x.queuePosition;
        }

        // called by operator<
        bool less_than(inner const& x) const
        {
            return queuePosition < x.queuePosition;
        }
}; // class inner

}; // class fixed_size_queue


///////////////////////////////////////////////////////////////////////////////
// class input_iterator
// Implementation of the InputPolicy used by multi_pass
// input_iterator encapsulates an input iterator of type InputT
///////////////////////////////////////////////////////////////////////////////
class input_iterator
{
    public:

template <typename InputT>
class inner
{
    private:
        typedef
            typename std::iterator_traits<InputT>::value_type
            result_type;

    public:
        typedef result_type value_type;

    private:
        struct Data {
            Data(InputT const &input_) 
            :   input(input_), was_initialized(false)
            {}
            
            InputT input;
            value_type curtok;
            bool was_initialized;
        };

       // Needed by compilers not implementing the resolution to DR45. For
       // reference, see
       // http://www.open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#45.

       friend struct Data;

    public:
        typedef
            typename std::iterator_traits<InputT>::difference_type
            difference_type;
        typedef
            typename std::iterator_traits<InputT>::pointer
            pointer;
        typedef
            typename std::iterator_traits<InputT>::reference
            reference;

    protected:
        inner()
            : data(0)
        {}

        inner(InputT x)
            : data(new Data(x))
        {}

        inner(inner const& x)
            : data(x.data)
        {}

        void destroy()
        {
            delete data;
            data = 0;
        }

        bool same_input(inner const& x) const
        {
            return data == x.data;
        }

        typedef
            typename std::iterator_traits<InputT>::value_type
            value_t;
        void swap(inner& x)
        {
            impl::mp_swap(data, x.data);
        }

        void ensure_initialized() const
        {
            if (data && !data->was_initialized) {
                data->curtok = *data->input;      // get the first token
                data->was_initialized = true;
            }
        }

    public:
        reference get_input() const
        {
            BOOST_SPIRIT_ASSERT(NULL != data);
            ensure_initialized();
            return data->curtok;
        }

        void advance_input()
        {
            BOOST_SPIRIT_ASSERT(NULL != data);
            data->was_initialized = false;        // should get the next token
            ++data->input;
        }

        bool input_at_eof() const
        {
            return !data || data->input == InputT();
        }

    private:
        Data *data;
};

};

///////////////////////////////////////////////////////////////////////////////
// class lex_input
// Implementation of the InputPolicy used by multi_pass
// lex_input gets tokens (ints) from yylex()
///////////////////////////////////////////////////////////////////////////////
class lex_input
{
    public:

template <typename InputT>
class inner
{
    public:
        typedef int value_type;
    typedef std::ptrdiff_t difference_type;
        typedef int* pointer;
        typedef int& reference;

    protected:
        inner()
            : curtok(new int(0))
        {}

        inner(InputT x)
            : curtok(new int(x))
        {}

        inner(inner const& x)
            : curtok(x.curtok)
        {}

        void destroy()
        {
            delete curtok;
            curtok = 0;
        }

        bool same_input(inner const& x) const
        {
            return curtok == x.curtok;
        }

        void swap(inner& x)
        {
            impl::mp_swap(curtok, x.curtok);
        }

    public:
        reference get_input() const
        {
            return *curtok;
        }

        void advance_input()
        {
            extern int yylex();
            *curtok = yylex();
        }

        bool input_at_eof() const
        {
            return *curtok == 0;
        }

    private:
        int* curtok;

};

};

///////////////////////////////////////////////////////////////////////////////
// class functor_input
// Implementation of the InputPolicy used by multi_pass
// functor_input gets tokens from a functor
// Note: the functor must have a typedef for result_type
// It also must have a static variable of type result_type defined to
// represent eof that is called eof.
///////////////////////////////////////////////////////////////////////////////
class functor_input
{
    public:

template <typename FunctorT>
class inner
{
    typedef typename FunctorT::result_type result_type;
    public:
        typedef result_type value_type;
    typedef std::ptrdiff_t difference_type;
        typedef result_type* pointer;
        typedef result_type& reference;

    protected:
        inner()
            : ftor(0)
            , curtok(0)
        {}

        inner(FunctorT const& x)
            : ftor(new FunctorT(x))
            , curtok(new result_type((*ftor)()))
        {}

        inner(inner const& x)
            : ftor(x.ftor)
            , curtok(x.curtok)
        {}

        void destroy()
        {
            delete ftor;
            ftor = 0;
            delete curtok;
            curtok = 0;
        }

        bool same_input(inner const& x) const
        {
            return ftor == x.ftor;
        }

        void swap(inner& x)
        {
            impl::mp_swap(curtok, x.curtok);
            impl::mp_swap(ftor, x.ftor);
        }

    public:
        reference get_input() const
        {
            return *curtok;
        }

        void advance_input()
        {
            if (curtok) {
                *curtok = (*ftor)();
            }
        }

        bool input_at_eof() const
        {
            return !curtok || *curtok == ftor->eof;
        }

        FunctorT& get_functor() const
        {
            return *ftor;
        }


    private:
        FunctorT* ftor;
        result_type* curtok;

};

};

} // namespace multi_pass_policies

///////////////////////////////////////////////////////////////////////////////
// iterator_base_creator
///////////////////////////////////////////////////////////////////////////////

namespace iterator_ { namespace impl {

// Meta-function to generate a std::iterator<>-like base class for multi_pass.
template <typename InputPolicyT, typename InputT>
struct iterator_base_creator
{
    typedef typename InputPolicyT::BOOST_NESTED_TEMPLATE inner<InputT> input_t;

    struct type {
        typedef std::forward_iterator_tag iterator_category;
        typedef typename input_t::value_type value_type;
        typedef typename input_t::difference_type difference_type;
        typedef typename input_t::pointer pointer;
        typedef typename input_t::reference reference;
    };
};

}}

///////////////////////////////////////////////////////////////////////////////
// class template multi_pass 
///////////////////////////////////////////////////////////////////////////////

// The default multi_pass instantiation uses a ref-counted std_deque scheme.
template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
class multi_pass
    : public OwnershipPolicy
    , public CheckingPolicy
    , public StoragePolicy::template inner<
                typename InputPolicy::template inner<InputT>::value_type>
    , public InputPolicy::template inner<InputT>
    , public iterator_::impl::iterator_base_creator<InputPolicy, InputT>::type
{
        typedef OwnershipPolicy OP;
        typedef CheckingPolicy CHP;
        typedef typename StoragePolicy::template inner<
            typename InputPolicy::template inner<InputT>::value_type> SP;
        typedef typename InputPolicy::template inner<InputT> IP;
        typedef typename
            iterator_::impl::iterator_base_creator<InputPolicy, InputT>::type
            IB;

    public:
        typedef typename IB::value_type value_type;
        typedef typename IB::difference_type difference_type;
        typedef typename IB::reference reference;
        typedef typename IB::pointer pointer;
        typedef InputT iterator_type;

        multi_pass();
        explicit multi_pass(InputT input);

#if BOOST_WORKAROUND(__GLIBCPP__, == 20020514)
        multi_pass(int);
#endif // BOOST_WORKAROUND(__GLIBCPP__, == 20020514)

        ~multi_pass();

        multi_pass(multi_pass const&);
        multi_pass& operator=(multi_pass const&);

        void swap(multi_pass& x);

        reference operator*() const;
        pointer operator->() const;
        multi_pass& operator++();
        multi_pass operator++(int);

        void clear_queue();

        bool operator==(const multi_pass& y) const;
        bool operator<(const multi_pass& y) const;

    private: // helper functions
        bool is_eof() const;
};

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
multi_pass()
    : OP()
    , CHP()
    , SP()
    , IP()
{
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
multi_pass(InputT input)
    : OP()
    , CHP()
    , SP()
    , IP(input)
{
}

#if BOOST_WORKAROUND(__GLIBCPP__, == 20020514)
    // The standard library shipped with gcc-3.1 has a bug in
    // bits/basic_string.tcc. It tries  to use iter::iter(0) to
    // construct an iterator. Ironically, this  happens in sanity
    // checking code that isn't required by the standard.
    // The workaround is to provide an additional constructor that
    // ignores its int argument and behaves like the default constructor.
template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
multi_pass(int)
    : OP()
    , CHP()
    , SP()
    , IP()
{
}
#endif // BOOST_WORKAROUND(__GLIBCPP__, == 20020514)

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
~multi_pass()
{
    if (OP::release())
    {
        CHP::destroy();
        SP::destroy();
        IP::destroy();
    }
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
multi_pass(
        multi_pass const& x)
    : OP(x)
    , CHP(x)
    , SP(x)
    , IP(x)
{
    OP::clone();
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>&
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator=(
        multi_pass const& x)
{
    multi_pass temp(x);
    temp.swap(*this);
    return *this;
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline void
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
swap(multi_pass& x)
{
    OP::swap(x);
    CHP::swap(x);
    SP::swap(x);
    IP::swap(x);
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
typename multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
reference
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator*() const
{
    CHP::check_if_valid();
    return SP::dereference(*this);
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
typename multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
pointer
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator->() const
{
    return &(operator*());
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>&
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator++()
{
    CHP::check_if_valid();
    SP::increment(*this);
    return *this;
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator++(int)
{
    multi_pass
    <
        InputT,
        InputPolicy,
        OwnershipPolicy,
        CheckingPolicy,
        StoragePolicy
    > tmp(*this);

    ++*this;

    return tmp;
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline void
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
clear_queue()
{
    SP::clear_queue();
    CHP::clear_queue();
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline bool
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
is_eof() const
{
    return SP::is_eof(*this);
}

///// Comparisons
template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline bool
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator==(const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
        StoragePolicy>& y) const
{
    bool is_eof_ = SP::is_eof(*this);
    bool y_is_eof_ = SP::is_eof(y);
    
    if (is_eof_ && y_is_eof_)
    {
        return true;  // both are EOF
    }
    else if (is_eof_ ^ y_is_eof_)
    {
        return false; // one is EOF, one isn't
    }
    else if (!IP::same_input(y))
    {
        return false;
    }
    else
    {
        return SP::equal_to(y);
    }
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline bool
multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy>::
operator<(const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
        StoragePolicy>& y) const
{
    return SP::less_than(y);
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
bool operator!=(
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& x,
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& y)
{
    return !(x == y);
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
bool operator>(
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& x,
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& y)
{
    return y < x;
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
bool operator>=(
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& x,
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& y)
{
    return !(x < y);
}

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
inline
bool operator<=(
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& x,
        const multi_pass<InputT, InputPolicy, OwnershipPolicy, CheckingPolicy,
                        StoragePolicy>& y)
{
    return !(y < x);
}

///// Generator function
template <typename InputT>
inline multi_pass<InputT, 
    multi_pass_policies::input_iterator, multi_pass_policies::ref_counted,
    multi_pass_policies::buf_id_check, multi_pass_policies::std_deque>
make_multi_pass(InputT i)
{
    return multi_pass<InputT, 
        multi_pass_policies::input_iterator, multi_pass_policies::ref_counted,
        multi_pass_policies::buf_id_check, multi_pass_policies::std_deque>(i);
}

// this could be a template typedef, since such a thing doesn't
// exist in C++, we'll use inheritance to accomplish the same thing.

template <typename InputT, std::size_t N>
class look_ahead :
    public multi_pass<
        InputT,
        multi_pass_policies::input_iterator,
        multi_pass_policies::first_owner,
        multi_pass_policies::no_check,
        multi_pass_policies::fixed_size_queue<N> >
{
        typedef multi_pass<
            InputT,
            multi_pass_policies::input_iterator,
            multi_pass_policies::first_owner,
            multi_pass_policies::no_check,
            multi_pass_policies::fixed_size_queue<N> > base_t;
    public:
        look_ahead()
            : base_t() {}

        explicit look_ahead(InputT x)
            : base_t(x) {}

        look_ahead(look_ahead const& x)
            : base_t(x) {}

#if BOOST_WORKAROUND(__GLIBCPP__, == 20020514)
        look_ahead(int)         // workaround for a bug in the library
            : base_t() {}       // shipped with gcc 3.1
#endif // BOOST_WORKAROUND(__GLIBCPP__, == 20020514)

    // default generated operators destructor and assignment operator are okay.
};

template
<
    typename InputT,
    typename InputPolicy,
    typename OwnershipPolicy,
    typename CheckingPolicy,
    typename StoragePolicy
>
void swap(
    multi_pass<
        InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    > &x,
    multi_pass<
        InputT, InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    > &y)
{
    x.swap(y);
}

namespace impl {

    template <typename T>
    inline void mp_swap(T& t1, T& t2)
    {
        using std::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;
        swap(t1, t2);
    }
}

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_ITERATOR_MULTI_PASS_HPP

/* multi_pass.hpp
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
*/